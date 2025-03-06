# Copyright (c) 2022 The Brave Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import override_utils

@override_utils.override_function(globals())
def GetConfigurationForBuild(original_function, defines):
  base = original_function(defines)
  return _merge_dicts(_BRAVE_VALUES, base)

_BRAVE_VALUES = {
  'build': 'taubrowser',
  'app_name': 'TauBrowser',
  'doc_url':
    'https://support.tau-browser.ru/hc/en-us/articles/360039248271-Group-Policy',
  'frame_name': 'TauBrowser Frame',
  'webview_name': 'TauBrowser WebView',
  'win_config': {
    'win': {
      'reg_mandatory_key_name': 'Software\\Policies\\TauTechnologies\\TauBrowser',
      'reg_recommended_key_name':
        'Software\\Policies\\TauTechnologies\\TauBrowser\\Recommended',
      'mandatory_category_path': ['TauBrowser:Cat_TauBrowser', 'taubrowser'],
      'recommended_category_path': ['TauBrowser:Cat_TauBrowser', 'taubrowser_recommended'],
      'category_path_strings': {
        'taubrowser': 'TauBrowser',
        'taubrowser_recommended':
        'TauBrowser - {doc_recommended}'
      },
      'namespace': 'TauTechnologies.Policies.TauBrowser',
    },
  },
  # The string 'TauBrowser' is defined in taubrowser.adml for ADMX, but ADM doesn't
  # support external references, so we define this map here.
  'adm_category_path_strings': {
    'TauBrowser:Cat_TauBrowser': 'TauBrowser'
  },
  'admx_prefix': 'taubrowser',
  'admx_using_namespaces': {
    'TauBrowser': 'TauTechnologies.Policies'  # prefix: namespace
  },
  'linux_policy_path': '/etc/taubrowser/policies/',
  'bundle_id': 'com.taubrowser.ios.core',
}

def _merge_dicts(src, dst):
  result = dict(dst)
  for k, v in src.items():
    result[k] = _merge_dicts(v, dst.get(k, {})) if isinstance(v, dict) else v
  return result
