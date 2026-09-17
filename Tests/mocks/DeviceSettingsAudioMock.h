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
#include <interfaces/IDeviceSettingsAudio.h>

using ::testing::NiceMock;

namespace Core = WPEFramework::Core;
namespace Exchange = WPEFramework::Exchange;

class DeviceSettingsAudioMock : public Exchange::IDeviceSettingsAudio {

public:
    MOCK_METHOD(Core::hresult, Register, (const string clientName, Exchange::IDeviceSettingsAudio::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (Exchange::IDeviceSettingsAudio::INotification* notification), (override));
    MOCK_METHOD(Core::hresult, GetAudioPort, (const AudioPortType type, const int32_t index, int32_t& handle), (override));
    MOCK_METHOD(Core::hresult, IsAudioPortEnabled, (const int32_t handle, bool& enabled), (override));
    MOCK_METHOD(Core::hresult, EnableAudioPort, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, GetSupportedARCTypes, (const int32_t handle, int32_t& types), (override));
    MOCK_METHOD(Core::hresult, SetSAD, (const int32_t handle, const uint8_t sadList[], const uint8_t count), (override));
    MOCK_METHOD(Core::hresult, EnableARC, (const int32_t handle, const AudioARCStatus arcStatus), (override));
    MOCK_METHOD(Core::hresult, GetStereoMode, (const int32_t handle, StereoMode& mode, const bool persist), (override));
    MOCK_METHOD(Core::hresult, SetStereoMode, (const int32_t handle, const StereoMode mode, const bool persist), (override));
    MOCK_METHOD(Core::hresult, GetStereoAuto, (const int32_t handle, int32_t& mode), (override));
    MOCK_METHOD(Core::hresult, SetStereoAuto, (const int32_t handle, const int32_t mode, const bool persist), (override));
    MOCK_METHOD(Core::hresult, SetAudioMute, (const int32_t handle, const bool mute), (override));
    MOCK_METHOD(Core::hresult, IsAudioMuted, (const int32_t handle, bool& muted), (override));
    MOCK_METHOD(Core::hresult, SetAudioDucking, (const int32_t handle, const AudioDuckingType duckingType, const AudioDuckingAction duckingAction, const uint8_t level), (override));
    MOCK_METHOD(Core::hresult, SetAudioLevel, (const int32_t handle, const float audioLevel), (override));
    MOCK_METHOD(Core::hresult, GetAudioLevel, (const int32_t handle, float& audioLevel), (override));
    MOCK_METHOD(Core::hresult, SetAudioGain, (const int32_t handle, const float gainLevel), (override));
    MOCK_METHOD(Core::hresult, GetAudioGain, (const int32_t handle, float& gainLevel), (override));
    MOCK_METHOD(Core::hresult, GetAudioFormat, (const int32_t handle, AudioFormat& audioFormat), (override));
    MOCK_METHOD(Core::hresult, GetAudioEncoding, (const int32_t handle, AudioEncoding& encoding), (override));
    MOCK_METHOD(Core::hresult, GetAudioEnablePersist, (const int32_t handle, bool& enabled, string& portName), (override));
    MOCK_METHOD(Core::hresult, SetAudioEnablePersist, (const int32_t handle, const bool enable, const string& portName), (override));
    MOCK_METHOD(Core::hresult, IsAudioMSDecoded, (const int32_t handle, bool& hasms11Decode), (override));
    MOCK_METHOD(Core::hresult, IsAudioMS12Decoded, (const int32_t handle, bool& hasms12Decode), (override));
    MOCK_METHOD(Core::hresult, GetAudioLEConfig, (const int32_t handle, bool& enabled), (override));
    MOCK_METHOD(Core::hresult, EnableAudioLEConfig, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, SetAudioDelay, (const int32_t handle, const uint32_t audioDelay), (override));
    MOCK_METHOD(Core::hresult, GetAudioDelay, (const int32_t handle, uint32_t& audioDelay), (override));
    MOCK_METHOD(Core::hresult, SetAudioDelayOffset, (const int32_t handle, const uint32_t delayOffset), (override));
    MOCK_METHOD(Core::hresult, GetAudioDelayOffset, (const int32_t handle, uint32_t& delayOffset), (override));
    MOCK_METHOD(Core::hresult, GetAudioSinkDeviceAtmosCapability, (const int32_t handle, DolbyAtmosCapability& atmosCapability), (override));
    MOCK_METHOD(Core::hresult, SetAudioAtmosOutputMode, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, SetAudioCompression, (const int32_t handle, const int32_t compressionLevel), (override));
    MOCK_METHOD(Core::hresult, GetAudioCompression, (const int32_t handle, int32_t& compressionLevel), (override));
    MOCK_METHOD(Core::hresult, SetAudioDialogEnhancement, (const int32_t handle, const int32_t level), (override));
    MOCK_METHOD(Core::hresult, GetAudioDialogEnhancement, (const int32_t handle, int32_t& level), (override));
    MOCK_METHOD(Core::hresult, SetAudioDolbyVolumeMode, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, GetAudioDolbyVolumeMode, (const int32_t handle, bool& enabled), (override));
    MOCK_METHOD(Core::hresult, SetAudioIntelligentEqualizerMode, (const int32_t handle, const int32_t mode), (override));
    MOCK_METHOD(Core::hresult, GetAudioIntelligentEqualizerMode, (const int32_t handle, int32_t& mode), (override));
    MOCK_METHOD(Core::hresult, SetAudioVolumeLeveller, (const int32_t handle, const VolumeLeveller volumeLeveller), (override));
    MOCK_METHOD(Core::hresult, GetAudioVolumeLeveller, (const int32_t handle, VolumeLeveller& volumeLeveller), (override));
    MOCK_METHOD(Core::hresult, SetAudioBassEnhancer, (const int32_t handle, const int32_t boost), (override));
    MOCK_METHOD(Core::hresult, GetAudioBassEnhancer, (const int32_t handle, int32_t& boost), (override));
    MOCK_METHOD(Core::hresult, EnableAudioSurroundDecoder, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, IsAudioSurroundDecoderEnabled, (const int32_t handle, bool& enabled), (override));
    MOCK_METHOD(Core::hresult, SetAudioDRCMode, (const int32_t handle, const int32_t drcMode), (override));
    MOCK_METHOD(Core::hresult, GetAudioDRCMode, (const int32_t handle, int32_t& drcMode), (override));
    MOCK_METHOD(Core::hresult, SetAudioSurroundVirtualizer, (const int32_t handle, const SurroundVirtualizer surroundVirtualizer), (override));
    MOCK_METHOD(Core::hresult, GetAudioSurroundVirtualizer, (const int32_t handle, SurroundVirtualizer& surroundVirtualizer), (override));
    MOCK_METHOD(Core::hresult, SetAudioMISteering, (const int32_t handle, const bool enable), (override));
    MOCK_METHOD(Core::hresult, GetAudioMISteering, (const int32_t handle, bool& enable), (override));
    MOCK_METHOD(Core::hresult, SetAudioGraphicEqualizerMode, (const int32_t handle, const int32_t mode), (override));
    MOCK_METHOD(Core::hresult, GetAudioGraphicEqualizerMode, (const int32_t handle, int32_t& mode), (override));
    MOCK_METHOD(Core::hresult, GetAudioMS12ProfileList, (const int32_t handle, IDeviceSettingsAudioMS12AudioProfileIterator*& ms12ProfileList), (override, const));
    MOCK_METHOD(Core::hresult, GetAudioMS12Profile, (const int32_t handle, string& profile), (override));
    MOCK_METHOD(Core::hresult, SetAudioMS12Profile, (const int32_t handle, const string& profile), (override));
    MOCK_METHOD(Core::hresult, SetAudioMixerLevels, (const int32_t handle, const AudioInput audioInput, const int32_t volume), (override));
    MOCK_METHOD(Core::hresult, SetAssociatedAudioMixing, (const int32_t handle, const bool mixing), (override));
    MOCK_METHOD(Core::hresult, GetAssociatedAudioMixing, (const int32_t handle, bool& mixing), (override));
    MOCK_METHOD(Core::hresult, SetAudioFaderControl, (const int32_t handle, const int32_t mixerBalance), (override));
    MOCK_METHOD(Core::hresult, GetAudioFaderControl, (const int32_t handle, int32_t& mixerBalance), (override));
    MOCK_METHOD(Core::hresult, SetAudioPrimaryLanguage, (const int32_t handle, const string& primaryAudioLanguage), (override));
    MOCK_METHOD(Core::hresult, GetAudioPrimaryLanguage, (const int32_t handle, string& primaryAudioLanguage), (override));
    MOCK_METHOD(Core::hresult, SetAudioSecondaryLanguage, (const int32_t handle, const string& secondaryAudioLanguage), (override));
    MOCK_METHOD(Core::hresult, GetAudioSecondaryLanguage, (const int32_t handle, string& secondaryAudioLanguage), (override));
    MOCK_METHOD(Core::hresult, GetAudioCapabilities, (const int32_t handle, int32_t& capabilities), (override));
    MOCK_METHOD(Core::hresult, GetAudioMS12Capabilities, (const int32_t handle, int32_t& capabilities), (override));
    MOCK_METHOD(Core::hresult, SetAudioMS12SettingsOverride, (const int32_t handle, const string& profileName, const string& profileSettingsName, const string& profileSettingValue, const MS12ProfileState profileState), (override));
    MOCK_METHOD(Core::hresult, IsAudioOutputConnected, (const int32_t handle, bool& isConnected), (override));
    MOCK_METHOD(Core::hresult, ResetAudioDialogEnhancement, (const int32_t handle), (override));
    MOCK_METHOD(Core::hresult, ResetAudioBassEnhancer, (const int32_t handle), (override));
    MOCK_METHOD(Core::hresult, ResetAudioSurroundVirtualizer, (const int32_t handle), (override));
    MOCK_METHOD(Core::hresult, ResetAudioVolumeLeveller, (const int32_t handle), (override));
    MOCK_METHOD(Core::hresult, GetAudioHDMIARCPortId, (const int32_t handle, int32_t& portId), (override));

    BEGIN_INTERFACE_MAP(DeviceSettingsAudioMock)
    INTERFACE_ENTRY(Exchange::IDeviceSettingsAudio)
    END_INTERFACE_MAP

    static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsAudio>>& mockInstances()
    {
        static std::map<std::string, Core::ProxyType<Exchange::IDeviceSettingsAudio>> mocks;
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

    static Exchange::IDeviceSettingsAudio* Get()
    {
        std::string id = testId();

        ASSERT(!id.empty());

        auto& mocks = mockInstances();

        auto it = mocks.find(id);
        if (it == mocks.end()) {
            // create new
            mocks.insert(std::pair<std::string, Core::ProxyType<DeviceSettingsAudioMock>>(id, Core::ProxyType<DeviceSettingsAudioMock>::Create()));
            it = mocks.find(id);
            ASSERT(it != mocks.end());
        }

        return &(*(it->second));
    }

    static DeviceSettingsAudioMock& Mock()
    {
        DeviceSettingsAudioMock* mock = static_cast<DeviceSettingsAudioMock*>(Get());
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
