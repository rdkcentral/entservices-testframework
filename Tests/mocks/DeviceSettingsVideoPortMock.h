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
#include <interfaces/IDeviceSettingsVideoPort.h>

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsVideoPortMock : public Exchange::IDeviceSettingsVideoPort {

public:
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsVideoPort::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsVideoPort::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, GetVideoPort, (const VideoPort videoPort, const int32_t index, int32_t& handle), (override));
    MOCK_METHOD(Core::hresult, GetVideoPortResolutionConfig, (VideoPort videoPortType, IVideoPortResolutionIterator*& videoPortResolutions), (override, const));
    MOCK_METHOD(Core::hresult, IsVideoPortEnabled, (const int32_t handle, bool& enabled), (override));
    MOCK_METHOD(Core::hresult, IsVideoPortDisplayConnected, (const int32_t handle, bool& connected), (override));
    MOCK_METHOD(Core::hresult, IsVideoPortDisplaySurround, (const int32_t handle, bool& surround), (override));
    MOCK_METHOD(Core::hresult, GetVideoPortDisplaySurroundMode, (const int32_t handle, VideoPortSurroundMode& surroundMode), (override));
    MOCK_METHOD(Core::hresult, EnableVideoPort, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, GetVideoPortResolution, (const int32_t handle, VideoPortResolution& videoPortResolution), (override));
    MOCK_METHOD(Core::hresult, SetVideoPortResolution, (const int32_t handle, const VideoPortResolution& videoPortResolution, const bool persist, const bool forceCompatibility), (override));
    MOCK_METHOD(Core::hresult, EnableHDCPOnVideoPort, (const int32_t handle, const bool hdcpEnable, const uint8_t hdcpKey[], const uint16_t hdcpKeySize), (override));
    MOCK_METHOD(Core::hresult, IsHDCPEnabledOnVideoPort, (const int32_t handle, bool& hdcpEnabled), (override));
    MOCK_METHOD(Core::hresult, GetHDCPStatusOnVideoPort, (const int32_t handle, HDCPStatus& hdcpStatus), (override));
    MOCK_METHOD(Core::hresult, GetHDCPProtocolVersionOnVideoPort, (const int32_t handle, HDCPProtocolVersion& hdcpVersion), (override));
    MOCK_METHOD(Core::hresult, GetHDCPReceiverProtocolVersionOnVideoPort, (const int32_t handle, HDCPProtocolVersion& hdcpVersion), (override));
    MOCK_METHOD(Core::hresult, GetHDCPCurrentProtocolVersionOnVideoPort, (const int32_t handle, HDCPProtocolVersion& hdcpVersion), (override));
    MOCK_METHOD(Core::hresult, IsVideoPortActive, (const int32_t handle, bool& active), (override));
    MOCK_METHOD(Core::hresult, GetTVHDRCapabilities, (const int32_t handle, int32_t& capabilities), (override));
    MOCK_METHOD(Core::hresult, GetTVSupportedResolutions, (const int32_t handle, int32_t& resolutions), (override));
    MOCK_METHOD(Core::hresult, SetForceDisable4K, (const int32_t handle, const bool disable), (override));
    MOCK_METHOD(Core::hresult, GetForceDisable4K, (const int32_t handle, bool& disabled), (override));
    MOCK_METHOD(Core::hresult, IsVideoPortOutputHDR, (const int32_t handle, bool& isHDR), (override));
    MOCK_METHOD(Core::hresult, ResetVideoPortOutputToSDR, (), (override));
    MOCK_METHOD(Core::hresult, GetHDMIPreference, (const int32_t handle, HDCPProtocolVersion& hdcpVersion), (override));
    MOCK_METHOD(Core::hresult, SetHDMIPreference, (const int32_t handle, const HDCPProtocolVersion hdcpVersion), (override));
    MOCK_METHOD(Core::hresult, GetVideoEOTF, (const int32_t handle, HDRStandard& hdrStandard), (override));
    MOCK_METHOD(Core::hresult, GetMatrixCoefficients, (const int32_t handle, DisplayMatrixCoefficients& matrixCoefficients), (override));
    MOCK_METHOD(Core::hresult, GetColorDepth, (const int32_t handle, uint32_t& colorDepth), (override));
    MOCK_METHOD(Core::hresult, GetColorSpace, (const int32_t handle, DisplayColorSpace& colorSpace), (override));
    MOCK_METHOD(Core::hresult, GetQuantizationRange, (const int32_t handle, DisplayQuantizationRange& quantizationRange), (override));
    MOCK_METHOD(Core::hresult, GetCurrentOutputSettings, (const int32_t handle, DSOutputSettings& outputSettings), (override));
    MOCK_METHOD(Core::hresult, SetBackgroundColor, (const int32_t handle, const VideoBackgroundColor backgroundColor), (override));
    MOCK_METHOD(Core::hresult, SetForceHDRMode, (const int32_t handle, const HDRStandard hdrMode), (override));
    MOCK_METHOD(Core::hresult, GetColorDepthCapabilities, (const int32_t handle, uint32_t& colorDepthCapabilities), (override));
    MOCK_METHOD(Core::hresult, GetPreferredColorDepth, (const int32_t handle, DisplayColorDepth& colorDepth, const bool persist), (override));
    MOCK_METHOD(Core::hresult, SetPreferredColorDepth, (const int32_t handle, const DisplayColorDepth colorDepth, const bool persist), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsVideoPortMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettingsVideoPort)
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsVideoPort>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsVideoPort>> mocks;
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

    static Exchange::IDeviceSettingsVideoPort* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsVideoPortMock>>(id, Core::ProxyType<DeviceSettingsVideoPortMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsVideoPortMock& Mock()
    {
        DeviceSettingsVideoPortMock* mock = static_cast<DeviceSettingsVideoPortMock*>(Get());
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
