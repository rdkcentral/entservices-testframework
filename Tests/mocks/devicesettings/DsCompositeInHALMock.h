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
#include "dsCompositeInTypes.h"
#include "dsCompositeIn.h"
}

/**
 * @brief Mock interface for dsCompositeIn HAL
 */
class DsCompositeInHalMock {
public:
    virtual ~DsCompositeInHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsCompositeInInit, ());
    MOCK_METHOD(dsError_t, dsCompositeInTerm, ());
    
    // Port management
    MOCK_METHOD(dsError_t, dsCompositeInGetNumberOfInputs, (uint8_t* pNumberOfInputs));
    MOCK_METHOD(dsError_t, dsCompositeInGetStatus, (dsCompositeInStatus_t* pStatus));
    MOCK_METHOD(dsError_t, dsCompositeInSelectPort, (dsCompositeInPort_t Port));
    MOCK_METHOD(dsError_t, dsCompositeInScaleVideo, (int32_t x, int32_t y, int32_t width, int32_t height));
    
    // Callbacks
    MOCK_METHOD(dsError_t, dsCompositeInRegisterConnectCB, (dsCompositeInConnectCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsCompositeInRegisterSignalChangeCB, (dsCompositeInSignalChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsCompositeInRegisterStatusChangeCB, (dsCompositeInStatusChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsCompositeInRegisterVideoModeUpdateCB, (dsCompositeInVideoModeUpdateCB_t CBFunc));
};

/**
 * @brief API wrapper for DsCompositeIn HAL mock
 */
class DsCompositeInApi {
public:
    static void setImpl(DsCompositeInHalMock* impl);
    static DsCompositeInHalMock* getImpl();

private:
    DsCompositeInApi();
    ~DsCompositeInApi();
    static DsCompositeInHalMock* impl;
};
