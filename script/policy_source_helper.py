#!/usr/bin/env python

# Copyright (c) 2019 The Brave Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/. */


CHROMIUM_POLICY_KEY = 'SOFTWARE\\\\Policies\\\\BraveSoftware\\\\Brave'


def AddBravePolicies(template_file_contents):
    highest_id = template_file_contents['highest_id_currently_used']
    policies = [
        {
            'name': 'TorDisabled',
            'type': 'main',
            'schema': {
                'type': 'boolean'
            },
            'supported_on': [
                'chrome.win:78-', 'chrome.mac:93-', 'chrome.linux:93-'
            ],
            'features': {
                'dynamic_refresh': False,
                'per_profile': False,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': True,
            'id': 0,
            'caption': '''Disables the tor feature.''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify that tor '''
                     '''must be disabled at startup.'''),
        },
        {
            'name': 'IPFSEnabled',
            'type': 'main',
            'schema': {
                'type': 'boolean'
            },
            'supported_on': ['chrome.*:87-'],
            'future_on': ['android'],
            'features': {
                'dynamic_refresh': False,
                'per_profile': True,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': True,
            'id': 1,
            'caption': '''Enable IPFS feature''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify whether IPFS '''
                     '''feature can be enabled.'''),
        },
        {
            'name': 'BraveRewardsDisabled',
            'type': 'main',
            'schema': {
                'type': 'boolean'
            },
            'supported_on': ['chrome.*:105-'],
            'features': {
                'dynamic_refresh': False,
                'per_profile': True,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': True,
            'id': 2,
            'caption': '''Disable AI Wiz Rewards feature.''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify that AI Wiz '''
                     '''Rewards feature will be disabled.'''),
        },
        {
            'name': 'BraveWalletDisabled',
            'type': 'main',
            'schema': {
                'type': 'boolean'
            },
            'supported_on': ['chrome.*:106-'],
            'features': {
                'dynamic_refresh': False,
                'per_profile': True,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': True,
            'id': 3,
            'caption': '''Disable AI Wiz Wallet feature.''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify that AI Wiz '''
                     '''Wallet feature will be disabled.'''),
        },
        {
            'name': 'BraveShieldsDisabledForUrls',
            'type': 'main',
            'schema': {
                'type': 'array',
                'items': {
                    'type': 'string'
                },
            },
            'supported_on': ['chrome.*:107-'],
            'features': {
                'dynamic_refresh': False,
                'per_profile': True,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': ['https://aiwize.com'],
            'id': 4,
            'caption': '''Disables AI Wiz Shields for urls.''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify that AI Wiz '''
                     '''Shields disabled.'''),
        },
        {
            'name': 'BraveShieldsEnabledForUrls',
            'type': 'main',
            'schema': {
                'type': 'array',
                'items': {
                    'type': 'string'
                },
            },
            'supported_on': ['chrome.*:107-'],
            'features': {
                'dynamic_refresh': False,
                'per_profile': True,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': ['https://aiwize.com'],
            'id': 5,
            'caption': '''Enables AI Wiz Shields for urls.''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify that AI Wiz '''
                     '''Shields enabled.'''),
        },
        {
            'name': 'BraveVPNDisabled',
            'type': 'main',
            'schema': {
                'type': 'boolean'
            },
            'supported_on': ['chrome.*:112-'],
            'future_on': ['android'],
            'features': {
                'dynamic_refresh': False,
                'per_profile': True,
                'can_be_recommended': False,
                'can_be_mandatory': True
            },
            'example_value': True,
            'id': 6,
            'caption': '''Disable AI Wiz VPN feature.''',
            'tags': [],
            'desc': ('''This policy allows an admin to specify that AI Wiz '''
                     '''VPN feature will be disabled.'''),
        },
    ]

    # Our new polices are added with highest id
    next_id = highest_id + 1
    for policy in policies:
        next_id += 1
        policy['id'] = next_id
        template_file_contents['policy_definitions'].append(policy)

    # Update highest id
    template_file_contents['highest_id_currently_used'] = highest_id + \
        len(policies)
