// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import '//resources/cr_elements/md_select.css.js'
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {WebUiListenerMixin} from 'chrome://resources/cr_elements/web_ui_listener_mixin.js';
import {PrefsMixin} from 'chrome://resources/cr_components/settings_prefs/prefs_mixin.js';
import {I18nMixin} from 'chrome://resources/cr_elements/i18n_mixin.js';
import {getTemplate} from './aiwize_llm_page.html.js'
import {AIWizeLLMBrowserProxy, AIWizeLLMBrowserProxyImpl}
  from './aiwize_llm_browser_proxy.js'
import 'chrome://resources/brave/leo.bundle.js'

const AIWizeLLMAssistantPageBase =
  WebUiListenerMixin(I18nMixin(PrefsMixin(PolymerElement)))

/**
 * 'settings-aiwize-llm-page' is the settings page containing
 * AI Wize Chat Assistant features.
 */
class AIWizeLLMAssistantPageElement extends AIWizeLLMAssistantPageBase {
    static get is() {
        return 'settings-aiwize-llm-page'
    }

    static get template() {
        return getTemplate()
    }

    static get properties() {
      return {
      }
    }

    browserProxy_: AIWizeLLMBrowserProxy =
      AIWizeLLMBrowserProxyImpl.getInstance()

      onStartLLM_() {
        const message = this.i18n('aiWizeLLMStartConfirmationText')
        if(window.confirm(message)) {
          this.browserProxy_.startAIWizeLLM()
        }
      }

      onStopLLM_() {
        const message = this.i18n('aiWizeLLMStopConfirmationText')
        if(window.confirm(message)) {
          this.browserProxy_.stopAIWizeLLM()
        }
      }
    
    private isLLMStarted_() {
      return true;
    }
}

customElements.define(
  AIWizeLLMAssistantPageElement.is, AIWizeLLMAssistantPageElement)
