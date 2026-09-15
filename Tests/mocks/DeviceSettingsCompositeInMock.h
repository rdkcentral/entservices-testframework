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
#include <interfaces/IDeviceSettingsCompositeIn.h>

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsCompositeInMock : public Exchange::IDeviceSettingsCompositeIn {

public:
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsCompositeIn::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsCompositeIn::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, GetNrOfCompositeInputs, (int32_t& nrCompositeInputs), (override));
    MOCK_METHOD(Core::hresult, GetCompositeInStatus, (CompositeInStatus& status), (override));
    MOCK_METHOD(Core::hresult, SelectCompositeInPort, (const CompositeInPort port), (override));
    MOCK_METHOD(Core::hresult, ScaleCompositeInVideo, (const VideoRectangle videoRect), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsCompositeInMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettingsCompositeIn)
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsCompositeIn>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsCompositeIn>> mocks;
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

    static Exchange::IDeviceSettingsCompositeIn* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsCompositeInMock>>(id, Core::ProxyType<DeviceSettingsCompositeInMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsCompositeInMock& Mock()
    {
        DeviceSettingsCompositeInMock* mock = static_cast<DeviceSettingsCompositeInMock*>(Get());
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
