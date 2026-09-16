/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2025 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

// std inc
#include <gmock/gmock.h>
#include <map>
#include <string>

// interface inc
#include <interfaces/IDeviceSettings.h>

// service / internal inc
// Each DeviceSettings sub-interface has its own dedicated mock + per-test registry
// (mirroring DeviceSettingsMock's own Get()/Mock()/Delete() pattern below). The root
// mock's INTERFACE_AGGREGATE entries resolve QueryInterface() for each sub-interface
// to that sub-interface's own current-test singleton, so DSHelper::AcquireSubInterface<T>()
// reaches the SAME mock instance a test configures via e.g. DeviceSettingsVideoDeviceMock::Mock().
#include "DeviceSettingsAudioMock.h"
#include "DeviceSettingsCompositeInMock.h"
#include "DeviceSettingsDisplayMock.h"
#include "DeviceSettingsFPDMock.h"
#include "DeviceSettingsHDMIInMock.h"
#include "DeviceSettingsHostMock.h"
#include "DeviceSettingsVideoDeviceMock.h"
#include "DeviceSettingsVideoPortMock.h"

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsMock : public Exchange::IDeviceSettings {

public:
    MOCK_METHOD(Core::hresult, Configure, (WPEFramework::PluginHost::IShell* service), (override));
    MOCK_METHOD(Core::hresult, GetDeviceSettingConfigs, (Exchange::IDeviceSettings::DeviceSettingConfigs& configs), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettings)
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsAudio, DeviceSettingsAudioMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsVideoPort, DeviceSettingsVideoPortMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsVideoDevice, DeviceSettingsVideoDeviceMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsDisplay, DeviceSettingsDisplayMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsFPD, DeviceSettingsFPDMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsHost, DeviceSettingsHostMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsHDMIIn, DeviceSettingsHDMIInMock::Get())
    INTERFACE_AGGREGATE(Exchange::IDeviceSettingsCompositeIn, DeviceSettingsCompositeInMock::Get())
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettings>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettings>> mocks;
        return mocks;
    }

    static std::string testId()
    {
        auto* testInfo = ::testing::UnitTest::GetInstance()->current_test_info();
        if (!testInfo) {
            return {};
        }

        // unique std::string {testClass#testName}
        return std::string(testInfo->test_suite_name()) + "#" + std::string(testInfo->name());
    }

    static Exchange::IDeviceSettings* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsMock>>(id, Core::ProxyType<DeviceSettingsMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsMock& Mock()
    {
        DeviceSettingsMock* mock = static_cast<DeviceSettingsMock*>(Get());
        return *mock;
    }

    // Erases the root mock AND every sub-interface mock registered for the current test,
    // so the next test starts with a clean set of DeviceSettings mocks.
    static void Delete(void)
    {
        std::string id = testId();

        ASSERT_FALSE(id.empty()) << "testId should have been valid for all testcases";

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it != mocks.end()) {
            // ProxyType<> Release gets called on destructor
            mocks.erase(it);
        }

        DeviceSettingsAudioMock::Delete();
        DeviceSettingsVideoPortMock::Delete();
        DeviceSettingsVideoDeviceMock::Delete();
        DeviceSettingsDisplayMock::Delete();
        DeviceSettingsFPDMock::Delete();
        DeviceSettingsHostMock::Delete();
        DeviceSettingsHDMIInMock::Delete();
        DeviceSettingsCompositeInMock::Delete();
    }
};
