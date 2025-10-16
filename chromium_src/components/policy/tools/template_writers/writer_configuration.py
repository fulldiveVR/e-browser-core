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
    'app_name': 'AIWIZE',
    'doc_url': 'https://support.aiwize.app/hc/en-us/articles/360039248271-Group-Policy',
    'frame_name': 'AIWIZE Frame',
    'webview_name': 'AIWIZE WebView',
    'win_config': {
        'win': {
            'reg_mandatory_key_name': 'Software\\Policies\\AIWIZESoftware\\AIWIZE',
            'reg_recommended_key_name': 'Software\\Policies\\AIWIZESoftware\\AIWIZE\\Recommended',
            'mandatory_category_path': ['Cat_AIWIZE', 'aiwize'],
            'recommended_category_path': ['Cat_AIWIZE', 'aiwize_recommended'],
            'category_path_strings': {
                'Cat_AIWIZE': 'AIWIZE Software',
                'aiwize': 'AIWIZE',
                'aiwize_recommended': 'AIWIZE - {doc_recommended}'
            },
            'namespace': 'AIWIZESoftware.Policies.AIWIZE',
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
