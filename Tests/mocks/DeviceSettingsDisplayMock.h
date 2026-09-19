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
#include <interfaces/IDeviceSettingsDisplay.h>

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsDisplayMock : public Exchange::IDeviceSettingsDisplay {

public:
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsDisplay::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsDisplay::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsDisplay::IDisplayHDMIHotPlugNotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsDisplay::IDisplayHDMIHotPlugNotification* notification), (override));
    MOCK_METHOD(Core::hresult, GetDisplayEdid, (const int32_t handle, DisplayEDID& edId, IDSVideoPortResolutionIterator*& supportedResolutionList), (override));
    MOCK_METHOD(Core::hresult, GetDisplayEdidBytes, (const int32_t handle, uint8_t edIdBytes[], const uint16_t edidLength), (override));
    MOCK_METHOD(Core::hresult, GetDisplay, (const DisplayPortType portType, const int32_t index, int32_t& handle), (override));
    MOCK_METHOD(Core::hresult, GetDisplayAspectRatio, (const int32_t handle, DisplayVideoAspectRatio& aspectRatio), (override));
    MOCK_METHOD(Core::hresult, SetAllmEnabled, (const int32_t handle, const bool enabled), (override));
    MOCK_METHOD(Core::hresult, SetAVIContentType, (const int32_t handle, const DisplayAVIContentType contentType), (override));
    MOCK_METHOD(Core::hresult, SetAVIScanInformation, (const int32_t handle, const DisplayAVIScanInformation scanInfo), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsDisplayMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettingsDisplay)
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsDisplay>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsDisplay>> mocks;
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

    static Exchange::IDeviceSettingsDisplay* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsDisplayMock>>(id, Core::ProxyType<DeviceSettingsDisplayMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsDisplayMock& Mock()
    {
        DeviceSettingsDisplayMock* mock = static_cast<DeviceSettingsDisplayMock*>(Get());
        return *mock;
    }

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
    }
};
