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
#include "dsError.h"
#include "dsAudio.h"

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
    MOCK_METHOD(dsError_t, dsGetAudioEncoding, (intptr_t handle, dsAudioEncoding_t* encoding));
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
    MOCK_METHOD(dsError_t, dsSetAudioDelay, (intptr_t handle, uint32_t audioDelayMs));
    MOCK_METHOD(dsError_t, dsGetAudioDelay, (intptr_t handle, uint32_t* audioDelayMs));
    
    // Audio capabilities
    MOCK_METHOD(dsError_t, dsGetAudioCapabilities, (intptr_t handle, int* capabilities));
    MOCK_METHOD(dsError_t, dsGetMS12Capabilities, (intptr_t handle, int* capabilities));
    
    // ARC/eARC
    MOCK_METHOD(dsError_t, dsAudioEnableARC, (intptr_t handle, bool enabled));
    MOCK_METHOD(dsError_t, dsAudioEnableLEConfig, (intptr_t handle, bool enable));
    MOCK_METHOD(dsError_t, dsGetLEConfig, (intptr_t handle, bool* enable));
    
    // Audio output
    MOCK_METHOD(dsError_t, dsAudioOutIsConnected, (intptr_t handle, bool* isConnected));
    MOCK_METHOD(dsError_t, dsAudioOutRegisterConnectCB, (dsAudioOutPortConnectCB_t CBFunc));
    
    // Audio format callbacks
    MOCK_METHOD(dsError_t, dsAudioFormatUpdateRegisterCB, (dsAudioFormatUpdateCB_t cbFun));
    
    // Atmos
    MOCK_METHOD(dsError_t, dsSetAudioAtmosOutputMode, (intptr_t handle, bool enable));
    MOCK_METHOD(dsError_t, dsGetSinkDeviceAtmosCapability, (intptr_t handle, dsATMOSCapability_t* capability));
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
