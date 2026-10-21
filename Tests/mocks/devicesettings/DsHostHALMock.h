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
#include "dsHost.h"
}

/**
 * @brief Mock interface for dsHost HAL
 */
class DsHostHalMock {
public:
    virtual ~DsHostHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsHostInit, ());
    MOCK_METHOD(dsError_t, dsHostTerm, ());
    
    // Host information
    MOCK_METHOD(dsError_t, dsGetCPUTemperature, (float* cpuTemperature));
    MOCK_METHOD(dsError_t, dsGetSocIDFromSDK, (char* socID));
    MOCK_METHOD(dsError_t, dsGetHostEDID, (unsigned char* edid, int* length));
};

/**
 * @brief API wrapper for DsHost HAL mock
 */
class DsHostApi {
public:
    static void setImpl(DsHostHalMock* impl);
    static DsHostHalMock* getImpl();

private:
    DsHostApi();
    ~DsHostApi();
    static DsHostHalMock* impl;
};
