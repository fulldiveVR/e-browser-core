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

try:
  # Python 3.0 or later
  from urllib.error import HTTPError, URLError
  from urllib.request import urlopen
except ImportError:
  from urllib2 import urlopen, HTTPError, URLError


# Path constants. (All of these should be absolute paths.)
BASE_PATH = os.path.join(os.path.abspath( os.path.join(os.path.dirname(__file__), '..', '..', '..')))

THIS_DIR = os.path.abspath(os.path.dirname(__file__))

URL_AIWIZE_LLM_DIST = os.environ.get('URL_AIWIZE_LLM_DIST',
    'https://files.dmiche.com/fulldive/aiwiz-browser-cli.zip')


def DownloadUrl(url, output_file):
  """Download url into output_file."""
  CHUNK_SIZE = 4096
  TOTAL_DOTS = 10
  num_retries = 3
  retry_wait_s = 5  # Doubled at each retry.

  while True:
    try:
      sys.stdout.write('Downloading %s ' % url)
      sys.stdout.flush()
      
      response = urlopen(url)
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
      return
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


def DownloadAndUnpack(url, output_dir):
  f = tempfile.NamedTemporaryFile(suffix='.zip',  mode='wb', delete=False)
  DownloadUrl(url, f)
  f.close()
  zip_path  = f.name
  # zip_path = os.path.abspath("aiwiz-browser-cli.zip")
  EnsureDirExists(output_dir)
  print("zip_path:", zip_path)
  with zipfile.ZipFile(zip_path) as zip_ref:
      zip_ref.extractall(output_dir)
      
  os.unlink(zip_path)


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


def UpdateAIWizeLLM(gen_path: str, output_path: str, names_list: list):
  out_path = os.path.normpath(os.path.join(BASE_PATH, output_path.removeprefix("//")))
  out_gen_path = os.path.normpath(os.path.join(os.path.join(BASE_PATH, gen_path.removeprefix("//")), "aiwize_llm"))

  files = [os.path.join(out_gen_path, name) for name in names_list]
  files_not_exists = [x for x in files if not os.path.exists(x)]


  if len(files_not_exists) > 0:
    print('Downloading aiwize_llm')
    
    try:
      DownloadAndUnpack(URL_AIWIZE_LLM_DIST, out_gen_path)
      print('aiwize_llm unpacked')
    except URLError:
      print('Failed to download aiwize_llm')
      print('Exiting.')
      return 1

  for file in names_list:
    file_src_path = os.path.join(out_gen_path, file)
    file_out_path = os.path.join(out_path, file)
    if os.path.exists(file_out_path):
      os.remove(file_out_path)
    shutil.copy(file_src_path, file_out_path)
    print(f"{file} copied.")

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
  
  parser.add_argument('-n', '--names-list', nargs='+', required=True)
  options = parser.parse_args(args)

  return UpdateAIWizeLLM(options.gen_path, options.output_path, options.names_list)


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))