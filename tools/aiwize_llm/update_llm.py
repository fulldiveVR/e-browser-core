#!/usr/bin/env python3
import os
import shutil
import stat
import sys
import zipfile
import tempfile
import time
import shutil
import argparse
import json
from google.oauth2 import service_account
from google.auth.transport.requests import Request as GoogleRequest

try:
  # Python 3.0 or later
  from urllib.error import HTTPError, URLError
  from urllib.request import urlopen, Request
except ImportError:
  from urllib2 import urlopen, HTTPError, URLError, Request

# Path constants. (All of these should be absolute paths.)
BASE_PATH = os.path.join(os.path.abspath( os.path.join(os.path.dirname(__file__), '..', '..', '..')))

URL_AIWIZE_LLM_DIST = os.environ.get('URL_AIWIZE_LLM_DIST', 'https://aiwize-browser.storage.googleapis.com/cli/aiwize-browser-cli.zip')
AIWIZE_LLM_GCP_CREDENTIALS = os.environ.get('AIWIZE_LLM_GCP_CREDENTIALS', '')

service_account_info = json.loads(AIWIZE_LLM_GCP_CREDENTIALS)
credentials = service_account.Credentials.from_service_account_info(
  service_account_info,
  scopes=["https://www.googleapis.com/auth/devstorage.read_only"]
)
credentials.refresh(GoogleRequest())

def DownloadUrl(url, output_file) -> int:
  """Download url into output_file."""
  CHUNK_SIZE = 4096
  TOTAL_DOTS = 10
  num_retries = 3
  retry_wait_s = 5  # Doubled at each retry.

  while True:
    try:
      print('Downloading %s ' % url)
      
      request = Request(url)
      request.add_header('Authorization', "Bearer %s" % credentials.token)

      response = urlopen(request)
      total_size = int(response.headers.get('Content-Length').strip())
      bytes_done = 0
      dots_printed = 0
      while True:
        chunk = response.read(CHUNK_SIZE)
        if not chunk:
          break
        output_file.write(chunk)
        bytes_done += len(chunk)
        num_dots = TOTAL_DOTS * bytes_done // total_size
        sys.stdout.write('.' * (num_dots - dots_printed))
        sys.stdout.flush()
        dots_printed = num_dots
      if bytes_done != total_size:
        raise URLError("only got %d of %d bytes" % (bytes_done, total_size))
      print(' Done.')
      return total_size
    except URLError as e:
      sys.stdout.write('\n')
      print(e)
      if num_retries == 0 or isinstance(e, HTTPError) and e.code == 404:
        raise e
      num_retries -= 1
      print('Retrying in %d s ...' % retry_wait_s)
      time.sleep(retry_wait_s)
      retry_wait_s *= 2


def EnsureDirExists(path):
  if not os.path.exists(path):
    print("Creating directory %s" % path)
    os.makedirs(path)


def DownloadAndUnpack(url, output_dir) -> int:
  f = tempfile.NamedTemporaryFile(suffix='.zip',  mode='wb', delete=False)
  total_size: int = DownloadUrl(url, f)
  f.close()
  zip_path  = f.name
  EnsureDirExists(output_dir)
  print("zip_path:", zip_path)
  with zipfile.ZipFile(zip_path) as zip_ref:
      zip_ref.extractall(output_dir)
      
  os.unlink(zip_path)
  return total_size


def CheckUpdateNeends(url: str, last_total_size: int) -> bool:
  """Check file size for file by link."""
  if last_total_size <= 0:
    return True

  num_retries = 3
  retry_wait_s = 5  # Doubled at each retry.

  while True:
    try:
      request = Request(url)
      request.add_header('Authorization', "Bearer %s" % credentials.token)

      response = urlopen(request)
      total_size = int(response.headers.get('Content-Length').strip())
      return last_total_size != total_size
    except URLError as e:
      print(e)
      if num_retries == 0 or isinstance(e, HTTPError) and e.code == 404:
        raise e
      num_retries -= 1
      print('Retrying in %d s ...' % retry_wait_s)
      time.sleep(retry_wait_s)
      retry_wait_s *= 2

def RmTree(dir):
  """Delete dir."""
  def ChmodAndRetry(func, path, _):
    # Subversion can leave read-only files around.
    if not os.access(path, os.W_OK):
      os.chmod(path, stat.S_IWUSR)
      return func(path)
    raise

  shutil.rmtree(dir, onerror=ChmodAndRetry)


def CopyFile(src, dst):
  """Copy a file from src to dst."""
  print("Copying %s to %s" % (src, dst))
  shutil.copy(src, dst)


def UpdateAIWizeLLM(gen_path: str, output_path: str, names_list: list, sub_path: str | None):
  out_path = os.path.normpath(os.path.join(BASE_PATH, output_path.removeprefix("//")))
  out_gen_path = os.path.normpath(os.path.join(os.path.join(BASE_PATH, gen_path.removeprefix("//")), "aiwize_llm"))
  if sub_path != None:
    out_cli_path = os.path.join(out_gen_path, sub_path)
  else:
    out_cli_path = out_gen_path

  last_update_info_path = os.path.join(out_gen_path, "last_update_info")

  files = [os.path.join(out_cli_path, name) for name in names_list]
  updateRequired = len([x for x in files if not os.path.exists(x)]) > 0

  if not updateRequired:
    last_total_size = -1
    try:
      f = open(last_update_info_path, "r")
      last_total_size = int(f.read().strip())
      f.close()
    except Exception as e:
      print(e)

    updateRequired = CheckUpdateNeends(URL_AIWIZE_LLM_DIST, last_total_size)

  if not updateRequired:
    return 0

  print('Downloading aiwize_llm')
    
  try:
    last_total_size = DownloadAndUnpack(URL_AIWIZE_LLM_DIST, out_gen_path)
    try:
      f = open(last_update_info_path, "w")
      f.write(f"{last_total_size}")
      f.close()
    except Exception as e:
      print(e)

    print('aiwize_llm unpacked')
  except URLError:
    print('Failed to download aiwize_llm')
    print('Exiting.')
    return 1

  for file in names_list:
    file_src_path = os.path.join(out_cli_path, file)
    file_out_path = os.path.join(out_path, file)
    if os.path.exists(file_out_path):
      os.remove(file_out_path)
    shutil.copy(file_src_path, file_out_path)
    print(f"{file} copied.")


  print('Updating ui...')
    
  ui_src_path = os.path.join(out_cli_path, "aiwize-browser-cli-ui.zip")
  ui_gen_path = os.path.join(out_cli_path, "ui")

  if os.path.exists(ui_src_path):
    print('Extraction ui...')
    EnsureDirExists(ui_gen_path)
    print("zip_path:", ui_src_path)
    with zipfile.ZipFile(ui_src_path) as zip_ref:
        zip_ref.extractall(ui_gen_path)

    ui_resources_path = os.path.join(os.path.abspath( os.path.join(os.path.dirname(__file__), '..', '..', 'components', 'aiwize_dashboard', 'browser', 'resources')))
    ui_files = ['index.html', 'favicon.ico', 'index.css', 'index.js', 'materialdesignicons-webfont.eot', 'materialdesignicons-webfont.ttf', 'materialdesignicons-webfont.woff', 'materialdesignicons-webfont.woff2']
    for file in ui_files:
      CopyFile(os.path.join(ui_gen_path, file), os.path.join(ui_resources_path, file))

  return 0

def main(args):
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '--output-path',
      required=True
  )
  
  parser.add_argument(
      '--gen-path',
      required=True
  )
  parser.add_argument(
      '--sub-path',
      required=False,
      default=None
  )
  
  parser.add_argument('-n', '--names-list', nargs='+', required=True)
  options = parser.parse_args(args)

  return UpdateAIWizeLLM(options.gen_path, options.output_path, options.names_list, options.sub_path)

if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
