#!/usr/bin/env python3
#
# Copyright (c) 2022 The AI Wize Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/. */


# Strings we want to replace but that we also replace automatically
# for XTB files
branding_replacements = [
    (r'The Chromium Authors. All rights reserved.',
     r'The AI Wize Authors. All rights reserved.'),
    (r'Google LLC. All rights reserved.',
     r'The AI Wize Authors. All rights reserved.'),
    (r'The Chromium Authors', r'AI Wize Software Inc'),
    (r'Google Chrome', r'AI Wize'),
    (r'(Google)(?! Play)', r'AI Wize'),
    (r'Chromium', r'AI Wize'),
    (r'Chrome', r'AI Wize'),
    (r'क्रोमियम', r'AI Wize'),  # Chromium in Hindi
]


# Strings we want to replace but that we need to use Transifex for
# to translate the XTB files
default_replacements = [
    (r'AI Wize Web Store', r'Web Store'),
    (r'You\'re incognito', r'This is a private window'),
    (r'an incognito', r'a private'),
    (r'an Incognito', r'a Private'),
    (r'incognito', r'private'),
    (r'Incognito', r'Private'),
    (r'inco&gnito', r'&private'),
    (r'Inco&gnito', r'&Private'),
    (r'People', r'Profiles'),
    # 'people' but only in the context of profiles, not humans.
    (r'(?<!authenticate )people', r'profiles'),
    (r'(Person)(?!\w)', r'Profile'),
    (r'(person)(?!\w)', r'profile'),
    (r'Bookmarks Bar\n', r'Bookmarks\n'),
    (r'Bookmarks bar\n', r'Bookmarks\n'),
    (r'bookmarks bar\n', r'bookmarks\n'),
]


# Fix up some strings after aggressive first round replacement.
fixup_replacements = [
    (r'AI Wize Cloud Print', r'Google Cloud Print'),
    (r'AI Wize Docs', r'Google Docs'),
    (r'AI Wize Drive', r'Google Drive'),
    (r'AI Wize OS', r'Chrome OS'),
    (r'AI WizeOS', r'ChromeOS'),
    (r'AI Wize Safe Browsing', r'Google Safe Browsing'),
    (r'Safe Browsing \(protects you and your device from dangerous sites\)',
     r'Google Safe Browsing (protects you and your device from dangerous sites)'
     ),
    (r'Sends URLs of some pages you visit to AI Wize',
     r'Sends URLs of some pages you visit to Google'),
    (r'Google Google', r'Google'),
    (r'AI Wize Account', r'AI Wize sync chain'),
    (r'AI Wize Lens', r'Google Lens'),
    (r'AI Wizebook', r'Chromebook'),
    (r'AI Wizecast', r'Chromecast'),
    (r'AI Wize Cloud', r'Google Cloud'),
    (r'AI Wize Pay', r'Google Pay'),
    (r'AI Wize Photos', r'Google Photos'),
    (r'AI Wize Projects', r'Chromium Projects'),
    (r'AI WizeVox', r'ChromeVox'),
    (r'powered by AI Wize AI', r'powered by Google AI'),
]


# Replacements for text nodes and neither for inside descriptions nor comments
main_text_only_replacements = [
    # By converting it back first, it makes this idempotent
    ('Copyright \xa9', 'Copyright'),
    ('Copyright', 'Copyright \xa9'),
]
