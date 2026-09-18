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
#include "dsHdmiIn.h"

/**
 * @brief Mock interface for dsHdmiIn HAL
 */
class DsHdmiInHalMock {
public:
    virtual ~DsHdmiInHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsHdmiInInit, ());
    MOCK_METHOD(dsError_t, dsHdmiInTerm, ());
    
    // Port management
    MOCK_METHOD(dsError_t, dsHdmiInGetNumberOfInputs, (uint8_t* numInputs));
    MOCK_METHOD(dsError_t, dsHdmiInGetStatus, (dsHdmiInPort_t* pStatus));
    
    // Port selection
    MOCK_METHOD(dsError_t, dsHdmiInSelectPort, (dsHdmiInPort_t port));
    MOCK_METHOD(dsError_t, dsHdmiInScaleVideo, (int32_t x, int32_t y, int32_t width, int32_t height));
    
    // Port capabilities
    MOCK_METHOD(dsError_t, dsHdmiInSelectZoomMode, (dsVideoZoom_t zoomMode));
    MOCK_METHOD(dsError_t, dsHdmiInPauseAudio, ());
    MOCK_METHOD(dsError_t, dsHdmiInResumeAudio, ());
    
    // Current video mode
    MOCK_METHOD(dsError_t, dsHdmiInGetCurrentVideoMode, (dsVideoPortResolution_t* resolution));
    
    // Callbacks
    MOCK_METHOD(dsError_t, dsHdmiInRegisterConnectCB, (dsHdmiInConnectCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterSignalChangeCB, (dsHdmiInSignalChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterStatusChangeCB, (dsHdmiInStatusChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterVideoModeUpdateCB, (dsHdmiInVideoModeUpdateCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterAllmChangeCB, (dsHdmiInAllmChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterAVLatencyChangeCB, (dsAVLatencyChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterAviContentTypeChangeCB, (dsAviContentTypeChangeCB_t CBFunc));
};

/**
 * @brief API class for dsHdmiIn mock
 */
class DsHdmiInApi {
protected:
    static DsHdmiInHalMock* impl;
    
public:
    DsHdmiInApi();
    DsHdmiInApi(const DsHdmiInApi &obj) = delete;
    virtual ~DsHdmiInApi();
    
    static void setImpl(DsHdmiInHalMock* newImpl);
    static DsHdmiInHalMock* getImpl();
};
