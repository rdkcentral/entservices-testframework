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
#include "dsDisplay.h"

/**
 * @brief Mock interface for dsDisplay HAL
 */
class DsDisplayHalMock {
public:
    virtual ~DsDisplayHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsDisplayInit, ());
    MOCK_METHOD(dsError_t, dsDisplayTerm, ());
    
    // Display management
    MOCK_METHOD(dsError_t, dsGetDisplay, (dsVideoPortType_t vType, int index, intptr_t* handle));
    
    // EDID
    MOCK_METHOD(dsError_t, dsGetEDID, (intptr_t handle, dsDisplayEDID_t* edid));
    MOCK_METHOD(dsError_t, dsGetEDIDBytes, (intptr_t handle, unsigned char* edid, int* length));
    
    // Aspect ratio
    MOCK_METHOD(dsError_t, dsGetDisplayAspectRatio, (intptr_t handle, dsVideoAspectRatio_t* aspectRatio));
    
    // AVI Info
    MOCK_METHOD(dsError_t, dsGetAVIContentType, (intptr_t handle, dsAviContentType_t* contentType));
    MOCK_METHOD(dsError_t, dsSetAVIContentType, (intptr_t handle, dsAviContentType_t contentType));
    MOCK_METHOD(dsError_t, dsGetAVIScanInformation, (intptr_t handle, dsAVIScanInformation_t* scanInfo));
    MOCK_METHOD(dsError_t, dsSetAVIScanInformation, (intptr_t handle, dsAVIScanInformation_t scanInfo));
    
    // ALLM
    MOCK_METHOD(dsError_t, dsGetAllmEnabled, (intptr_t handle, bool* enabled));
    MOCK_METHOD(dsError_t, dsSetAllmEnabled, (intptr_t handle, bool enabled));
    
    // Callbacks
    MOCK_METHOD(dsError_t, dsRegisterDisplayEventCallback, (intptr_t handle, dsDisplayEventCallback_t cb));
};

/**
 * @brief API class for dsDisplay mock
 */
class DsDisplayApi {
protected:
    static DsDisplayHalMock* impl;
    
public:
    DsDisplayApi();
    DsDisplayApi(const DsDisplayApi &obj) = delete;
    virtual ~DsDisplayApi();
    
    static void setImpl(DsDisplayHalMock* newImpl);
    static DsDisplayHalMock* getImpl();
};
