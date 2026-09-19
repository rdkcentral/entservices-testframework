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

dsError_t dsGetAudioEncoding(intptr_t handle, dsAudioEncoding_t* encoding) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsGetAudioEncoding(handle, encoding);
    if (encoding) *encoding = dsAUDIO_ENC_PCM;
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

dsError_t dsSetAudioDelay(intptr_t handle, uint32_t audioDelayMs) {
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

dsError_t dsAudioEnableARC(intptr_t handle, bool enabled) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioEnableARC(handle, enabled);
    return dsERR_NONE;
}

dsError_t dsAudioEnableLEConfig(intptr_t handle, bool enable) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioEnableLEConfig(handle, enable);
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

dsError_t dsAudioFormatUpdateRegisterCB(dsAudioFormatUpdateCB_t cbFun) {
    DsAudioHalMock* impl = DsAudioApi::getImpl();
    if (impl) return impl->dsAudioFormatUpdateRegisterCB(cbFun);
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

} // extern "C"
