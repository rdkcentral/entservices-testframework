/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2026 RDK Management
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
**/

#pragma once

#include <gmock/gmock.h>

extern "C" {
#include "dsError.h"
#include "dsAudio.h"
}

/**
 * @brief Mock interface for dsAudio HAL
 */
class DsAudioHalMock {
public:
    virtual ~DsAudioHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsAudioPortInit, ());
    MOCK_METHOD(dsError_t, dsAudioPortTerm, ());
    
    // Port management
    MOCK_METHOD(dsError_t, dsGetAudioPort, (dsAudioPortType_t type, int index, intptr_t* handle));
    MOCK_METHOD(dsError_t, dsGetAudioFormat, (intptr_t handle, dsAudioFormat_t* audioFormat));
    MOCK_METHOD(dsError_t, dsGetAudioCompression, (intptr_t handle, int* compression));
    MOCK_METHOD(dsError_t, dsSetAudioCompression, (intptr_t handle, int compression));
    
    // Stereo mode
    MOCK_METHOD(dsError_t, dsSetStereoMode, (intptr_t handle, dsAudioStereoMode_t mode));
    MOCK_METHOD(dsError_t, dsGetStereoMode, (intptr_t handle, dsAudioStereoMode_t* mode));
    MOCK_METHOD(dsError_t, dsSetStereoAuto, (intptr_t handle, int autoMode));
    MOCK_METHOD(dsError_t, dsGetStereoAuto, (intptr_t handle, int* autoMode));
    
    // Audio level and mute
    MOCK_METHOD(dsError_t, dsSetAudioLevel, (intptr_t handle, float level));
    MOCK_METHOD(dsError_t, dsGetAudioLevel, (intptr_t handle, float* level));
    MOCK_METHOD(dsError_t, dsSetAudioMute, (intptr_t handle, bool mute));
    MOCK_METHOD(dsError_t, dsIsAudioMute, (intptr_t handle, bool* muted));
    
    // Audio delay
    MOCK_METHOD(dsError_t, dsSetAudioDelay, (intptr_t handle, const uint32_t audioDelayMs));
    MOCK_METHOD(dsError_t, dsGetAudioDelay, (intptr_t handle, uint32_t* audioDelayMs));
    
    // Audio capabilities
    MOCK_METHOD(dsError_t, dsGetAudioCapabilities, (intptr_t handle, int* capabilities));
    MOCK_METHOD(dsError_t, dsGetMS12Capabilities, (intptr_t handle, int* capabilities));
    
    // ARC/eARC
    MOCK_METHOD(dsError_t, dsAudioEnableARC, (intptr_t handle, dsAudioARCStatus_t arcStatus));
    MOCK_METHOD(dsError_t, dsGetLEConfig, (intptr_t handle, bool* enable));
    
    // Audio output
    MOCK_METHOD(dsError_t, dsAudioOutIsConnected, (intptr_t handle, bool* isConnected));
    MOCK_METHOD(dsError_t, dsAudioOutRegisterConnectCB, (dsAudioOutPortConnectCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsIsAudioPortEnabled, (intptr_t handle, bool* enabled));
    MOCK_METHOD(dsError_t, dsEnableAudioPort, (intptr_t handle, bool enabled));
    
    // Audio format callbacks
    MOCK_METHOD(dsError_t, dsAudioFormatUpdateRegisterCB, (dsAudioFormatUpdateCB_t cbFun));
    MOCK_METHOD(dsError_t, dsAudioAtmosCapsChangeRegisterCB, (dsAtmosCapsChangeCB_t cbFun));
    
    // Atmos
    MOCK_METHOD(dsError_t, dsSetAudioAtmosOutputMode, (intptr_t handle, bool enable));
    MOCK_METHOD(dsError_t, dsGetSinkDeviceAtmosCapability, (intptr_t handle, dsATMOSCapability_t* capability));
    
    // ARC/SAD
    MOCK_METHOD(dsError_t, dsGetSupportedARCTypes, (intptr_t handle, int* types));
    MOCK_METHOD(dsError_t, dsAudioSetSAD, (intptr_t handle, dsAudioSADList_t sad_list));
    
    // Audio processing
    MOCK_METHOD(dsError_t, dsSetAudioGain, (intptr_t handle, float gain));
    MOCK_METHOD(dsError_t, dsGetAudioGain, (intptr_t handle, float* gain));
    MOCK_METHOD(dsError_t, dsSetBassEnhancer, (intptr_t handle, int boost));
    MOCK_METHOD(dsError_t, dsGetBassEnhancer, (intptr_t handle, int* boost));
    MOCK_METHOD(dsError_t, dsSetSurroundVirtualizer, (intptr_t handle, dsSurroundVirtualizer_t virtualizer));
    MOCK_METHOD(dsError_t, dsGetSurroundVirtualizer, (intptr_t handle, dsSurroundVirtualizer_t* virtualizer));
    MOCK_METHOD(dsError_t, dsSetVolumeLeveller, (intptr_t handle, dsVolumeLeveller_t volLeveller));
    MOCK_METHOD(dsError_t, dsGetVolumeLeveller, (intptr_t handle, dsVolumeLeveller_t* volLeveller));
    MOCK_METHOD(dsError_t, dsEnableSurroundDecoder, (intptr_t handle, bool enabled));
    MOCK_METHOD(dsError_t, dsIsSurroundDecoderEnabled, (intptr_t handle, bool* enabled));
    MOCK_METHOD(dsError_t, dsSetDRCMode, (intptr_t handle, int mode));
    MOCK_METHOD(dsError_t, dsGetDRCMode, (intptr_t handle, int* mode));
    MOCK_METHOD(dsError_t, dsSetDialogEnhancement, (intptr_t handle, int level));
    MOCK_METHOD(dsError_t, dsGetDialogEnhancement, (intptr_t handle, int* level));
    MOCK_METHOD(dsError_t, dsSetDolbyVolumeMode, (intptr_t handle, bool mode));
    MOCK_METHOD(dsError_t, dsGetDolbyVolumeMode, (intptr_t handle, bool* mode));
    MOCK_METHOD(dsError_t, dsSetIntelligentEqualizerMode, (intptr_t handle, int mode));
    MOCK_METHOD(dsError_t, dsGetIntelligentEqualizerMode, (intptr_t handle, int* mode));
    MOCK_METHOD(dsError_t, dsSetGraphicEqualizerMode, (intptr_t handle, int mode));
    MOCK_METHOD(dsError_t, dsGetGraphicEqualizerMode, (intptr_t handle, int* mode));
    MOCK_METHOD(dsError_t, dsSetMISteering, (intptr_t handle, bool enabled));
    MOCK_METHOD(dsError_t, dsGetMISteering, (intptr_t handle, bool* enabled));
    MOCK_METHOD(dsError_t, dsSetFaderControl, (intptr_t handle, int mixerbalance));
    MOCK_METHOD(dsError_t, dsGetFaderControl, (intptr_t handle, int* mixerbalance));
    
    // MS12/MS11
    MOCK_METHOD(dsError_t, dsIsAudioMSDecode, (intptr_t handle, bool* HasMS11Decode));
    MOCK_METHOD(dsError_t, dsIsAudioMS12Decode, (intptr_t handle, bool* hasMS12Decode));
    MOCK_METHOD(dsError_t, dsEnableMS12Config, (intptr_t handle, dsMS12FEATURE_t feature, const bool enable));
    MOCK_METHOD(dsError_t, dsSetMS12AudioProfile, (intptr_t handle, const char* profile));
    MOCK_METHOD(dsError_t, dsGetMS12AudioProfile, (intptr_t handle, char* profile));
    MOCK_METHOD(dsError_t, dsGetMS12AudioProfileList, (intptr_t handle, dsMS12AudioProfileList_t* profiles));
    
    // Language & Mixing
    MOCK_METHOD(dsError_t, dsSetPrimaryLanguage, (intptr_t handle, const char* pLang));
    MOCK_METHOD(dsError_t, dsGetPrimaryLanguage, (intptr_t handle, char* pLang));
    MOCK_METHOD(dsError_t, dsSetSecondaryLanguage, (intptr_t handle, const char* sLang));
    MOCK_METHOD(dsError_t, dsGetSecondaryLanguage, (intptr_t handle, char* sLang));
    MOCK_METHOD(dsError_t, dsSetAssociatedAudioMixing, (intptr_t handle, bool mixing));
    MOCK_METHOD(dsError_t, dsGetAssociatedAudioMixing, (intptr_t handle, bool* mixing));
    MOCK_METHOD(dsError_t, dsSetAudioMixerLevels, (intptr_t handle, dsAudioInput_t aInput, int volume));
    
    // LE Config
    MOCK_METHOD(dsError_t, dsEnableLEConfig, (intptr_t handle, const bool enable));
};

/**
 * @brief API class for dsAudio mock
 */
class DsAudioApi {
protected:
    static DsAudioHalMock* impl;
    
public:
    DsAudioApi();
    DsAudioApi(const DsAudioApi &obj) = delete;
    virtual ~DsAudioApi();
    
    static void setImpl(DsAudioHalMock* newImpl);
    static DsAudioHalMock* getImpl();
};
