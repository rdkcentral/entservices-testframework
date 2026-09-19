/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2024 RDK Management
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
#include "dsVideoDevice.h"

/**
 * @brief Mock interface for dsVideoDevice HAL
 */
class DsVideoDeviceHalMock {
public:
    virtual ~DsVideoDeviceHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsVideoDeviceInit, ());
    MOCK_METHOD(dsError_t, dsVideoDeviceTerm, ());
    
    // Device management
    MOCK_METHOD(dsError_t, dsGetVideoDevice, (int index, intptr_t* handle));
    
    // Framerate
    MOCK_METHOD(dsError_t, dsSetDisplayframerate, (intptr_t handle, char* framerate));
    MOCK_METHOD(dsError_t, dsGetCurrentDisplayframerate, (intptr_t handle, char* framerate));
    MOCK_METHOD(dsError_t, dsRegisterFrameratePreChangeCB, (dsRegisterFrameratePreChangeCB_t cb));
    MOCK_METHOD(dsError_t, dsRegisterFrameratePostChangeCB, (dsRegisterFrameratePostChangeCB_t cb));
    
    // HDR capabilities
    MOCK_METHOD(dsError_t, dsGetHDRCapabilities, (intptr_t handle, int* capabilities));
    MOCK_METHOD(dsError_t, dsGetSupportedVideoCodingFormats, (intptr_t handle, unsigned int* supported_formats));
    MOCK_METHOD(dsError_t, dsGetVideoCodecInfo, (intptr_t handle, dsVideoCodingFormat_t format, dsVideoCodecInfo_t* info));
    
    // FRF (Frame Rate Flexibility)
    MOCK_METHOD(dsError_t, dsSetFRFMode, (intptr_t handle, int frfmode));
    MOCK_METHOD(dsError_t, dsGetFRFMode, (intptr_t handle, int* frfmode));
    MOCK_METHOD(dsError_t, dsGetCurrentDisframerate, (intptr_t handle, char* framerate));
    
    // DFC (Display Framerate Control)
    MOCK_METHOD(dsError_t, dsSetDFC, (intptr_t handle, dsVideoZoom_t dfc));
    MOCK_METHOD(dsError_t, dsGetDFC, (intptr_t handle, dsVideoZoom_t* dfc));
};

/**
 * @brief API class for dsVideoDevice mock
 */
class DsVideoDeviceApi {
protected:
    static DsVideoDeviceHalMock* impl;
    
public:
    DsVideoDeviceApi();
    DsVideoDeviceApi(const DsVideoDeviceApi &obj) = delete;
    virtual ~DsVideoDeviceApi();
    
    static void setImpl(DsVideoDeviceHalMock* newImpl);
    static DsVideoDeviceHalMock* getImpl();
};
