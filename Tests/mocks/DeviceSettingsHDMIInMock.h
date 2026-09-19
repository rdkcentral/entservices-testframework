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
#include <interfaces/IDeviceSettingsHDMIIn.h>

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsHDMIInMock : public Exchange::IDeviceSettingsHDMIIn {

public:
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsHDMIIn::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsHDMIIn::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, GetHDMIInNumberOfInputs, (int32_t& count), (override));
    MOCK_METHOD(Core::hresult, GetHDMIInStatus, (HDMIInStatus& hdmiStatus, IHDMIInPortConnectionStatusIterator*& portConnectionStatus), (override));
    MOCK_METHOD(Core::hresult, SelectHDMIInPort, (const HDMIInPort port, const bool requestAudioMix, const bool topMostPlane, const HDMIVideoPlaneType videoPlaneType), (override));
    MOCK_METHOD(Core::hresult, ScaleHDMIInVideo, (const HDMIInVideoRectangle videoPosition), (override));
    MOCK_METHOD(Core::hresult, SelectHDMIZoomMode, (const HDMIInVideoZoom zoomMode), (override));
    MOCK_METHOD(Core::hresult, GetSupportedGameFeaturesList, (IHDMIInGameFeatureListIterator*& gameFeatureList), (override));
    MOCK_METHOD(Core::hresult, GetHDMIInAVLatency, (uint32_t& videoLatency, uint32_t& audioLatency), (override));
    MOCK_METHOD(Core::hresult, GetHDMIInAllmStatus, (const HDMIInPort port, bool& allmStatus), (override));
    MOCK_METHOD(Core::hresult, GetHDMIInEdid2AllmSupport, (const HDMIInPort port, bool& allmSupport), (override));
    MOCK_METHOD(Core::hresult, SetHDMIInEdid2AllmSupport, (const HDMIInPort port, bool allmSupport), (override));
    MOCK_METHOD(Core::hresult, GetEdidBytes, (const HDMIInPort port, const uint16_t edidBytesLength, uint8_t edidBytes[]), (override));
    MOCK_METHOD(Core::hresult, GetHDMISPDInformation, (const HDMIInPort port, const uint16_t spdBytesLength, uint8_t spdBytes[]), (override));
    MOCK_METHOD(Core::hresult, GetHDMIEdidVersion, (const HDMIInPort port, HDMIInEdidVersion& edidVersion), (override));
    MOCK_METHOD(Core::hresult, SetHDMIEdidVersion, (const HDMIInPort port, const HDMIInEdidVersion edidVersion), (override));
    MOCK_METHOD(Core::hresult, GetHDMIVideoMode, (HDMIVideoPortResolution& videoPortResolution), (override));
    MOCK_METHOD(Core::hresult, GetHDMIVersion, (const HDMIInPort port, HDMIInCapabilityVersion& capabilityVersion), (override));
    MOCK_METHOD(Core::hresult, SetVRRSupport, (const HDMIInPort port, const bool vrrSupport), (override));
    MOCK_METHOD(Core::hresult, GetVRRSupport, (const HDMIInPort port, bool& vrrSupport), (override));
    MOCK_METHOD(Core::hresult, GetVRRStatus, (const HDMIInPort port, HDMIInVRRStatus& vrrStatus), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsHDMIInMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettingsHDMIIn)
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsHDMIIn>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsHDMIIn>> mocks;
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

    static Exchange::IDeviceSettingsHDMIIn* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsHDMIInMock>>(id, Core::ProxyType<DeviceSettingsHDMIInMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsHDMIInMock& Mock()
    {
        DeviceSettingsHDMIInMock* mock = static_cast<DeviceSettingsHDMIInMock*>(Get());
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
