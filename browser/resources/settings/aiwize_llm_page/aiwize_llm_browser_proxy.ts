/* Copyright (c) 2023 The AI Wize Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

 export interface AIWizeLLMBrowserProxy {
  startAIWizeLLM(): void
  stopAIWizeLLM(): void
 }

 export class AIWizeLLMBrowserProxyImpl
    implements AIWizeLLMBrowserProxy {

   static getInstance(): AIWizeLLMBrowserProxyImpl {
     return instance || (instance = new AIWizeLLMBrowserProxyImpl())
   }

   startAIWizeLLM() {
    chrome.send('startAIWizeLLM')
   }
   stopAIWizeLLM() {
    chrome.send('stopAIWizeLLM')
   }
 }

 let instance: AIWizeLLMBrowserProxyImpl|null = null
