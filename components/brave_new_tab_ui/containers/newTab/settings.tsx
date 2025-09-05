// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import {
  SettingsContent,
  SettingsFeatureBody,
  SettingsTitle,
} from '../../components/default'

import Navigation from '@brave/leo/react/navigation'
import NavigationItem from '@brave/leo/react/navigationItem'
import NavigationMenu from '@brave/leo/react/navigationMenu'

import { getLocale } from '$web-common/locale'
import { loadTimeData } from '$web-common/loadTimeData'
import Dialog from '@brave/leo/react/dialog'

import styled from 'styled-components'

// Tabs
const BackgroundImageSettings = React.lazy(() => import('./settings/backgroundImage'))
const BraveStatsSettings = React.lazy(() => import('./settings/braveStats'))
const TopSitesSettings = React.lazy(() => import('./settings/topSites'))
const ClockSettings = React.lazy(() => import('./settings/clock'))
const SearchSettings = React.lazy(() => import('./settings/search'))

export const SettingsDialog = styled(Dialog)`
  --leo-dialog-width: 720px;
  --leo-dialog-padding: 24px 24px 0 24px;
`

const Sidebar = styled(Navigation)`
  /* normalize against SettingsMenu default padding */
  margin-inline-start: -24px;
`

const SidebarItem = styled(NavigationItem)`
  text-transform: capitalize;
`

export interface Props {
  newTabData: NewTab.State
  textDirection: string
  showSettingsMenu: boolean
  featureCustomBackgroundEnabled: boolean
  onClose: () => void
  toggleShowBackgroundImage: () => void
  toggleShowTopSites: () => void
  setMostVisitedSettings: (show: boolean, customize: boolean) => void
  chooseNewCustomImageBackground: () => void
  setCustomImageBackground: (selectedBackground: string) => void
  removeCustomImageBackground: (background: string) => void
  setBraveBackground: (selectedBackground: string) => void
  setColorBackground: (color: string, useRandomColor: boolean) => void
  showBackgroundImage: boolean
  showTopSites: boolean
  customLinksEnabled: boolean
  allowBackgroundCustomization: boolean
  setActiveTab?: TabType
}

export enum TabType {
  BackgroundImage = 'backgroundImage',
  BraveStats = 'braveStats',
  TopSites = 'topSites',
  Clock = 'clock',
  Search = 'search'
}

const tabTypes = Object.values(TabType)

type TabMap<T> = { [P in TabType]: T }
const tabIcons: TabMap<string> = {
  [TabType.BackgroundImage]: 'image',
  [TabType.BraveStats]: 'bar-chart',
  [TabType.Clock]: 'clock',
  [TabType.TopSites]: 'window-content',
  [TabType.Search]: 'search'
}

const tabTranslationKeys: TabMap<string> = {
  [TabType.BackgroundImage]: 'backgroundImageTitle',
  [TabType.BraveStats]: 'statsTitle',
  [TabType.Clock]: 'clockTitle',
  [TabType.TopSites]: 'topSitesTitle',
  [TabType.Search]: 'searchTitle'
}

const featureFlagSearchWidget = loadTimeData.getBoolean('featureFlagSearchWidget')
export default function Settings(props: Props) {
  const allowedTabTypes = React.useMemo(() => tabTypes.filter(t =>
    (props.allowBackgroundCustomization || t !== TabType.BackgroundImage) &&
    (featureFlagSearchWidget || t !== TabType.Search)), [props.allowBackgroundCustomization])
  const [activeTab, setActiveTab] = React.useState(props.allowBackgroundCustomization
    ? TabType.BackgroundImage
    : TabType.BraveStats)

  const changeTab = React.useCallback((tab: TabType) => {
    setActiveTab(tab)
  }, [])

  // When the outside world tells us to update the active tab, do so.
  React.useEffect(() => {
    if (!props.setActiveTab || !allowedTabTypes.includes(props.setActiveTab)) return
    changeTab(props.setActiveTab)
  }, [props.setActiveTab])

  return <SettingsDialog isOpen={props.showSettingsMenu} showClose onClose={() => {
    props.onClose?.()
  }}>
    <SettingsTitle slot='title'>
      {getLocale('dashboardSettingsTitle')}
    </SettingsTitle>
    <SettingsContent id='settingsBody'>
      <Sidebar id="sidebar">
        <NavigationMenu>
          {allowedTabTypes.map(tabType => <SidebarItem key={tabType} icon={tabIcons[tabType]} isCurrent={activeTab === tabType} onClick={() => changeTab(tabType)}>
            {getLocale(tabTranslationKeys[tabType])}
          </SidebarItem>)}
        </NavigationMenu>
      </Sidebar>
      <SettingsFeatureBody id='content'>
        {/* Empty loading fallback is ok here since we are loading from local disk. */}
        <React.Suspense fallback={(<div />)}>
          {activeTab === TabType.BackgroundImage && <BackgroundImageSettings
            newTabData={props.newTabData}
            toggleShowBackgroundImage={props.toggleShowBackgroundImage}
            chooseNewCustomImageBackground={props.chooseNewCustomImageBackground}
            setCustomImageBackground={props.setCustomImageBackground}
            removeCustomImageBackground={props.removeCustomImageBackground}
            setBraveBackground={props.setBraveBackground}
            setColorBackground={props.setColorBackground}
            showBackgroundImage={props.showBackgroundImage}
            featureCustomBackgroundEnabled={props.featureCustomBackgroundEnabled}
          />}
          {activeTab === TabType.BraveStats && <BraveStatsSettings />}
          {activeTab === TabType.TopSites && <TopSitesSettings
            toggleShowTopSites={props.toggleShowTopSites}
            showTopSites={props.showTopSites}
            customLinksEnabled={props.customLinksEnabled}
            setMostVisitedSettings={props.setMostVisitedSettings}
          />}
          {activeTab === TabType.Clock && <ClockSettings />}
          {activeTab === TabType.Search && <SearchSettings />}
        </React.Suspense>
      </SettingsFeatureBody>
    </SettingsContent>
  </SettingsDialog>
}
