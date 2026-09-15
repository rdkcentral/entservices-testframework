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
#include <interfaces/IDeviceSettingsVideoDevice.h>

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsVideoDeviceMock : public Exchange::IDeviceSettingsVideoDevice {

public:
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsVideoDevice::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsVideoDevice::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, GetVideoDeviceHandle, (const int32_t index, int32_t& handle), (override));
    MOCK_METHOD(Core::hresult, SetVideoDeviceDFC, (const int32_t handle, const VideoZoom zoomSetting), (override));
    MOCK_METHOD(Core::hresult, GetVideoDeviceDFC, (const int32_t handle, VideoZoom& zoomSetting), (override));
    MOCK_METHOD(Core::hresult, GetHDRCapabilities, (const int32_t handle, int32_t& capabilities), (override));
    MOCK_METHOD(Core::hresult, GetSupportedVideoCodingFormats, (const int32_t handle, int32_t& supportedFormats), (override));
    MOCK_METHOD(Core::hresult, GetCodecInfo, (const int32_t handle, const VideoCodec videoCodec, IDeviceSettingsVideoCodecProfileSupportIterator*& codecInfo), (override));
    MOCK_METHOD(Core::hresult, DisableHDR, (const int32_t handle, const bool disable), (override));
    MOCK_METHOD(Core::hresult, SetFRFMode, (const int32_t handle, const int32_t frfmode), (override));
    MOCK_METHOD(Core::hresult, GetFRFMode, (const int32_t handle, int32_t& frfmode), (override));
    MOCK_METHOD(Core::hresult, GetCurrentDisplayFrameRate, (const int32_t handle, string& framerate), (override));
    MOCK_METHOD(Core::hresult, SetDisplayFrameRate, (const int32_t handle, const string& framerate), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsVideoDeviceMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettingsVideoDevice)
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsVideoDevice>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsVideoDevice>> mocks;
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

    static Exchange::IDeviceSettingsVideoDevice* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsVideoDeviceMock>>(id, Core::ProxyType<DeviceSettingsVideoDeviceMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsVideoDeviceMock& Mock()
    {
        DeviceSettingsVideoDeviceMock* mock = static_cast<DeviceSettingsVideoDeviceMock*>(Get());
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
