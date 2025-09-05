# Copyright (c) 2022 The Brave Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import override_utils

@override_utils.override_function(globals())
def GetConfigurationForBuild(original_function, defines):
    base = original_function(defines)
    merged = _merge_dicts(_BRAVE_VALUES, base)

    # Remove Google.Policies namespace. Microsoft.Policies.Windows remains, as it is hardcoded in admx_writer.py.
    merged.pop('admx_using_namespaces', None)

    return merged


_BRAVE_VALUES = {
    'build': 'aiwize',
    'app_name': 'AIWize',
    'doc_url': 'https://support.aiwize.com/hc/en-us/articles/360039248271-Group-Policy',
    'frame_name': 'AIWize Frame',
    'webview_name': 'AIWize WebView',
    'win_config': {
        'win': {
            'reg_mandatory_key_name': 'Software\\Policies\\AIWizeSoftware\\AIWize',
            'reg_recommended_key_name': 'Software\\Policies\\AIWizeSoftware\\AIWize\\Recommended',
            'mandatory_category_path': ['Cat_AIWize', 'aiwize'],
            'recommended_category_path': ['Cat_AIWize', 'aiwize_recommended'],
            'category_path_strings': {
                'Cat_AIWize': 'AIWize Software',
                'aiwize': 'AIWize',
                'aiwize_recommended': 'AIWize - {doc_recommended}'
            },
            'namespace': 'AIWizeSoftware.Policies.AIWize',
        },
    },
    'admx_prefix': 'aiwize',
    'linux_policy_path': '/etc/aiwize/policies/',
    'bundle_id': 'com.aiwize.ios.core',
}

def _merge_dicts(src, dst):
    result = dict(dst)
    for k, v in src.items():
        result[k] = _merge_dicts(v, dst.get(k, {})) if isinstance(v,
                                                                  dict) else v
    return result
