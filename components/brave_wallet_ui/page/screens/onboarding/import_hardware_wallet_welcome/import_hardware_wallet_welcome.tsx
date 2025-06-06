// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { useHistory } from 'react-router'

// utils
import { getLocale, formatLocale } from '$web-common/locale'
import { WalletRoutes } from '../../../../constants/types'

// components
import {
  OnboardingContentLayout //
} from '../components/onboarding_content_layout/content_layout'

// styles
import {
  Bold,
  Description,
  HardwareGraphic
} from './import_hardware_wallet_welcome.style'
import { ContinueButton } from '../onboarding.style'
import { Column, VerticalSpace } from '../../../../components/shared/style'

const walletHardwareDescription = formatLocale(
  'braveWalletConnectHardwareDescription',
  {
    $1: <Bold>{getLocale('braveWalletConnectHardwareLedger')}</Bold>,
    $2: <Bold>{getLocale('braveWalletConnectHardwareTrezor')}</Bold>
  }
)

export const OnboardingImportHardwareWalletWelcome = () => {
  const history = useHistory()

  const onClickContinue = () => {
    history.push(WalletRoutes.OnboardingHardwareWalletCreatePassword)
  }

  return (
    <OnboardingContentLayout
      title={getLocale('braveWalletConnectHardwareWallet')}
    >
      <HardwareGraphic />
      <Description>
        {getLocale('braveWalletImportHardwareWalletDescription')}
      </Description>
      <VerticalSpace space='28px' />
      <Description>
        {walletHardwareDescription}
      </Description>
      <Column margin='117px 0 88px 0'>
        <ContinueButton onClick={onClickContinue}>
          {getLocale('braveWalletButtonContinue')}
        </ContinueButton>
      </Column>
    </OnboardingContentLayout>
  )
}
