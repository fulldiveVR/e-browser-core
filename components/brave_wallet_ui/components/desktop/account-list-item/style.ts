// Copyright (c) 2021 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import * as leo from '@brave/leo/tokens/css/variables'
import Icon from '@brave/leo/react/icon'

// Shared Styles
import { WalletButton, Text, Row } from '../../shared/style'
import { layoutPanelWidth } from '../wallet-page-wrapper/wallet-page-wrapper.style'

export const StyledWrapper = styled.div<{
  isRewardsAccount: boolean
  isOutOfSync: boolean
}>`
  cursor: ${(p) => (p.isRewardsAccount ? 'default' : 'pointer')};
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  width: 100%;
  padding-right: 14px;
  border-bottom: 1px solid ${leo.color.divider.subtle};
  background-color: ${(p) =>
    p.isOutOfSync ? leo.color.yellow[5] : 'transparent'};
  transition: background-color 300ms ease-out;
  &:first-child {
    border-radius: ${leo.radius.l} ${leo.radius.l} 0px 0px;
  }
  &:last-child {
    border-bottom: none;
    border-radius: 0px 0px ${leo.radius.l} ${leo.radius.l};
  }
  &:only-child {
    border-radius: ${leo.radius.l};
  }
  &:hover {
    background-color: ${(p) =>
      p.isRewardsAccount ? 'transparent' : leo.color.page.background};
  }
`

export const AccountButton = styled(WalletButton)`
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-direction: row;
  width: 100%;
  outline: none;
  background: none;
  border: none;
  color: none;
  margin: 0px;
  padding: 14px 0px 14px 14px;
  &:disabled {
    cursor: default;
  }
`

export const NameAndIcon = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: row;
`

export const AccountMenuWrapper = styled.div`
  position: relative;
`

export const ButtonIcon = styled(Icon)`
  --leo-icon-size: 14px;
  color: ${leo.color.icon.default};
  margin-left: 4px;
  margin-right: 8px;
`

export const OvalButton = styled(WalletButton)`
  display: flex;
  align-items: center;
  justify-content: center;
  cursor: pointer;
  outline: none;
  background: none;
  border-radius: 48px;
  padding: 3px 10px;
  border: 1px solid ${(p) => p.theme.color.interactive08};
  margin-right: 6px;
  pointer-events: auto;
`

export const OvalButtonText = styled.span`
  font-family: Poppins;
  font-size: 12px;
  line-height: 18px;
  letter-spacing: 0.01em;
  color: ${(p) => p.theme.color.text02};
  font-weight: 600;
`

export const AccountMenuButton = styled(WalletButton)`
  display: flex;
  align-items: center;
  justify-content: center;
  cursor: pointer;
  outline: none;
  background: none;
  pointer-events: auto;
  border: none;
  margin: 0px;
  padding: 0px;
`

export const AccountMenuIcon = styled(Icon).attrs({
  name: 'more-vertical'
})`
  --leo-icon-size: 24px;
  color: ${leo.color.icon.default};
`

export const AccountBalanceText = styled(Text)`
  color: ${leo.color.text.primary};
  margin-right: 12px;
`

export const AccountNameWrapper = styled(Row)`
  @media screen and (max-width: ${layoutPanelWidth}px) {
    flex-direction: column;
    align-items: flex-start;
  }
`

export const WarningIcon = styled(Icon).attrs({
  name: 'warning-triangle-filled'
})`
  --leo-icon-size: 20px;
  color: ${leo.color.systemfeedback.warningIcon};
`
