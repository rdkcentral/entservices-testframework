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

#include "DsAudioHALMock.h"
#include <cstdio>

// Static implementation pointer
DsAudioHalMock* DsAudioApi::impl = nullptr;

// DsAudioApi implementation
DsAudioApi::DsAudioApi() {}
DsAudioApi::~DsAudioApi() {}

void DsAudioApi::setImpl(DsAudioHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsAudioApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsAudioHalMock* DsAudioApi::getImpl() {
    return impl;
}

// Actual HAL function implementations that delegate to the mock
extern "C" {

dsError_t dsAudioPortInit() {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioPortInit();
    return dsERR_NONE;
}

dsError_t dsAudioPortTerm() {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioPortTerm();
    return dsERR_NONE;
}

dsError_t dsGetAudioPort(dsAudioPortType_t type, int index, intptr_t* handle) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioPort(type, index, handle);
    if (handle) *handle = 0;
    return dsERR_NONE;
}

dsError_t dsGetAudioFormat(intptr_t handle, dsAudioFormat_t* audioFormat) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioFormat(handle, audioFormat);
    if (audioFormat) *audioFormat = dsAUDIO_FORMAT_NONE;
    return dsERR_NONE;
}

dsError_t dsGetAudioCompression(intptr_t handle, int* compression) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioCompression(handle, compression);
    if (compression) *compression = 0;
    return dsERR_NONE;
}

dsError_t dsSetAudioCompression(intptr_t handle, int compression) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioCompression(handle, compression);
    return dsERR_NONE;
}

dsError_t dsSetStereoMode(intptr_t handle, dsAudioStereoMode_t mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetStereoMode(handle, mode);
    return dsERR_NONE;
}

dsError_t dsGetStereoMode(intptr_t handle, dsAudioStereoMode_t* mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetStereoMode(handle, mode);
    if (mode) *mode = dsAUDIO_STEREO_STEREO;
    return dsERR_OPERATION_NOT_SUPPORTED;
}

dsError_t dsSetStereoAuto(intptr_t handle, int autoMode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetStereoAuto(handle, autoMode);
    return dsERR_NONE;
}

dsError_t dsGetStereoAuto(intptr_t handle, int* autoMode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetStereoAuto(handle, autoMode);
    if (autoMode) *autoMode = 0;
    return dsERR_NONE;
}

dsError_t dsSetAudioLevel(intptr_t handle, float level) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioLevel(handle, level);
    return dsERR_NONE;
}

dsError_t dsGetAudioLevel(intptr_t handle, float* level) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioLevel(handle, level);
    if (level) *level = 0.0f;
    return dsERR_NONE;
}

dsError_t dsSetAudioMute(intptr_t handle, bool mute) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioMute(handle, mute);
    return dsERR_NONE;
}

dsError_t dsIsAudioMute(intptr_t handle, bool* muted) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsIsAudioMute(handle, muted);
    if (muted) *muted = false;
    return dsERR_NONE;
}

dsError_t dsSetAudioDelay(intptr_t handle, const uint32_t audioDelayMs) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioDelay(handle, audioDelayMs);
    return dsERR_NONE;
}

dsError_t dsGetAudioDelay(intptr_t handle, uint32_t* audioDelayMs) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioDelay(handle, audioDelayMs);
    if (audioDelayMs) *audioDelayMs = 0;
    return dsERR_NONE;
}

dsError_t dsGetAudioCapabilities(intptr_t handle, int* capabilities) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioCapabilities(handle, capabilities);
    if (capabilities) *capabilities = 0;
    return dsERR_NONE;
}

dsError_t dsGetMS12Capabilities(intptr_t handle, int* capabilities) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetMS12Capabilities(handle, capabilities);
    if (capabilities) *capabilities = 0;
    return dsERR_NONE;
}

dsError_t dsAudioEnableARC(intptr_t handle, dsAudioARCStatus_t arcStatus) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioEnableARC(handle, arcStatus);
    return dsERR_NONE;
}

dsError_t dsGetLEConfig(intptr_t handle, bool* enable) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetLEConfig(handle, enable);
    if (enable) *enable = false;
    return dsERR_NONE;
}

dsError_t dsAudioOutIsConnected(intptr_t handle, bool* isConnected) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioOutIsConnected(handle, isConnected);
    if (isConnected) *isConnected = true;
    return dsERR_NONE;
}

dsError_t dsAudioOutRegisterConnectCB(dsAudioOutPortConnectCB_t CBFunc) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioOutRegisterConnectCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsIsAudioPortEnabled(intptr_t handle, bool* enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsIsAudioPortEnabled(handle, enabled);
    if (enabled) *enabled = true;
    return dsERR_NONE;
}

dsError_t dsEnableAudioPort(intptr_t handle, bool enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsEnableAudioPort(handle, enabled);
    return dsERR_NONE;
}

dsError_t dsAudioFormatUpdateRegisterCB(dsAudioFormatUpdateCB_t cbFun) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioFormatUpdateRegisterCB(cbFun);
    return dsERR_NONE;
}

dsError_t dsAudioAtmosCapsChangeRegisterCB(dsAtmosCapsChangeCB_t cbFun) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioAtmosCapsChangeRegisterCB(cbFun);
    return dsERR_NONE;
}

dsError_t dsSetAudioAtmosOutputMode(intptr_t handle, bool enable) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioAtmosOutputMode(handle, enable);
    return dsERR_NONE;
}

dsError_t dsGetSinkDeviceAtmosCapability(intptr_t handle, dsATMOSCapability_t* capability) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetSinkDeviceAtmosCapability(handle, capability);
    if (capability) *capability = dsAUDIO_ATMOS_NOTSUPPORTED;
    return dsERR_NONE;
}

dsError_t dsGetSupportedARCTypes(intptr_t handle, int* types) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetSupportedARCTypes(handle, types);
    if (types) *types = 0;
    return dsERR_NONE;
}

dsError_t dsAudioSetSAD(intptr_t handle, dsAudioSADList_t sad_list) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioSetSAD(handle, sad_list);
    return dsERR_NONE;
}

dsError_t dsSetAudioGain(intptr_t handle, float gain) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioGain(handle, gain);
    return dsERR_NONE;
}

dsError_t dsGetAudioGain(intptr_t handle, float* gain) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioGain(handle, gain);
    if (gain) *gain = 0.0f;
    return dsERR_NONE;
}

dsError_t dsSetBassEnhancer(intptr_t handle, int boost) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetBassEnhancer(handle, boost);
    return dsERR_NONE;
}

dsError_t dsGetBassEnhancer(intptr_t handle, int* boost) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetBassEnhancer(handle, boost);
    if (boost) *boost = 0;
    return dsERR_NONE;
}

dsError_t dsSetSurroundVirtualizer(intptr_t handle, dsSurroundVirtualizer_t virtualizer) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetSurroundVirtualizer(handle, virtualizer);
    return dsERR_NONE;
}

dsError_t dsGetSurroundVirtualizer(intptr_t handle, dsSurroundVirtualizer_t* virtualizer) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetSurroundVirtualizer(handle, virtualizer);
    if (virtualizer) { virtualizer->mode = 0; virtualizer->boost = 0; }
    return dsERR_NONE;
}

dsError_t dsSetVolumeLeveller(intptr_t handle, dsVolumeLeveller_t volLeveller) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetVolumeLeveller(handle, volLeveller);
    return dsERR_NONE;
}

dsError_t dsGetVolumeLeveller(intptr_t handle, dsVolumeLeveller_t* volLeveller) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetVolumeLeveller(handle, volLeveller);
    if (volLeveller) { volLeveller->mode = 0; volLeveller->level = 0; }
    return dsERR_NONE;
}

dsError_t dsEnableSurroundDecoder(intptr_t handle, bool enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsEnableSurroundDecoder(handle, enabled);
    return dsERR_NONE;
}

dsError_t dsIsSurroundDecoderEnabled(intptr_t handle, bool* enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsIsSurroundDecoderEnabled(handle, enabled);
    if (enabled) *enabled = false;
    return dsERR_NONE;
}

dsError_t dsSetDRCMode(intptr_t handle, int mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetDRCMode(handle, mode);
    return dsERR_NONE;
}

dsError_t dsGetDRCMode(intptr_t handle, int* mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetDRCMode(handle, mode);
    if (mode) *mode = 0;
    return dsERR_NONE;
}

dsError_t dsSetDialogEnhancement(intptr_t handle, int level) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetDialogEnhancement(handle, level);
    return dsERR_NONE;
}

dsError_t dsGetDialogEnhancement(intptr_t handle, int* level) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetDialogEnhancement(handle, level);
    if (level) *level = 0;
    return dsERR_NONE;
}

dsError_t dsSetDolbyVolumeMode(intptr_t handle, bool mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetDolbyVolumeMode(handle, mode);
    return dsERR_NONE;
}

dsError_t dsGetDolbyVolumeMode(intptr_t handle, bool* mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetDolbyVolumeMode(handle, mode);
    if (mode) *mode = false;
    return dsERR_NONE;
}

dsError_t dsSetIntelligentEqualizerMode(intptr_t handle, int mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetIntelligentEqualizerMode(handle, mode);
    return dsERR_NONE;
}

dsError_t dsGetIntelligentEqualizerMode(intptr_t handle, int* mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetIntelligentEqualizerMode(handle, mode);
    if (mode) *mode = 0;
    return dsERR_NONE;
}

dsError_t dsSetGraphicEqualizerMode(intptr_t handle, int mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetGraphicEqualizerMode(handle, mode);
    return dsERR_NONE;
}

dsError_t dsGetGraphicEqualizerMode(intptr_t handle, int* mode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetGraphicEqualizerMode(handle, mode);
    if (mode) *mode = 0;
    return dsERR_NONE;
}

dsError_t dsSetMISteering(intptr_t handle, bool enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetMISteering(handle, enabled);
    return dsERR_NONE;
}

dsError_t dsGetMISteering(intptr_t handle, bool* enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetMISteering(handle, enabled);
    if (enabled) *enabled = false;
    return dsERR_NONE;
}

dsError_t dsSetFaderControl(intptr_t handle, int mixerbalance) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetFaderControl(handle, mixerbalance);
    return dsERR_NONE;
}

dsError_t dsGetFaderControl(intptr_t handle, int* mixerbalance) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetFaderControl(handle, mixerbalance);
    if (mixerbalance) *mixerbalance = 0;
    return dsERR_NONE;
}

dsError_t dsIsAudioMSDecode(intptr_t handle, bool* HasMS11Decode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsIsAudioMSDecode(handle, HasMS11Decode);
    if (HasMS11Decode) *HasMS11Decode = false;
    return dsERR_NONE;
}

dsError_t dsIsAudioMS12Decode(intptr_t handle, bool* hasMS12Decode) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsIsAudioMS12Decode(handle, hasMS12Decode);
    if (hasMS12Decode) *hasMS12Decode = false;
    return dsERR_NONE;
}

dsError_t dsEnableMS12Config(intptr_t handle, dsMS12FEATURE_t feature, const bool enable) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsEnableMS12Config(handle, feature, enable);
    return dsERR_NONE;
}

dsError_t dsSetMS12AudioProfile(intptr_t handle, const char* profile) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetMS12AudioProfile(handle, profile);
    return dsERR_NONE;
}

dsError_t dsGetMS12AudioProfile(intptr_t handle, char* profile) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetMS12AudioProfile(handle, profile);
    if (profile) strcpy(profile, "");
    return dsERR_NONE;
}

dsError_t dsGetMS12AudioProfileList(intptr_t handle, dsMS12AudioProfileList_t* profiles) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetMS12AudioProfileList(handle, profiles);
    if (profiles) {
        profiles->audioProfileCount = 0;
        profiles->audioProfileList[0] = '\0';
    }
    return dsERR_NONE;
}

dsError_t dsSetPrimaryLanguage(intptr_t handle, const char* pLang) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetPrimaryLanguage(handle, pLang);
    return dsERR_NONE;
}

dsError_t dsGetPrimaryLanguage(intptr_t handle, char* pLang) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetPrimaryLanguage(handle, pLang);
    if (pLang) strcpy(pLang, "");
    return dsERR_NONE;
}

dsError_t dsSetSecondaryLanguage(intptr_t handle, const char* sLang) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetSecondaryLanguage(handle, sLang);
    return dsERR_NONE;
}

dsError_t dsGetSecondaryLanguage(intptr_t handle, char* sLang) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetSecondaryLanguage(handle, sLang);
    if (sLang) strcpy(sLang, "");
    return dsERR_NONE;
}

dsError_t dsSetAssociatedAudioMixing(intptr_t handle, bool mixing) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAssociatedAudioMixing(handle, mixing);
    return dsERR_NONE;
}

dsError_t dsGetAssociatedAudioMixing(intptr_t handle, bool* mixing) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAssociatedAudioMixing(handle, mixing);
    if (mixing) *mixing = false;
    return dsERR_NONE;
}

dsError_t dsSetAudioMixerLevels(intptr_t handle, dsAudioInput_t aInput, int volume) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsSetAudioMixerLevels(handle, aInput, volume);
    return dsERR_NONE;
}

dsError_t dsEnableLEConfig(intptr_t handle, const bool enable) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsEnableLEConfig(handle, enable);
    return dsERR_NONE;
}

} // extern "C"
