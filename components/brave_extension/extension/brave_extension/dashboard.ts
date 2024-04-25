// Copyright (c) 2024 The AI Wize Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

const config = { attributes: true, childList: true, subtree: true }

console.log("test dashboard mutable!!!!")

const callback = () => {
  console.log("dashboard test mutable")
}

const observer: MutationObserver = new MutationObserver(callback)
observer.observe(document, config)
