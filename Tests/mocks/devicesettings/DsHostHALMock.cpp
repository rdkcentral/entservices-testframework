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

#include "DsHostHALMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsHostHalMock* DsHostApi::impl = nullptr;

// DsHostApi implementation
DsHostApi::DsHostApi() {}
DsHostApi::~DsHostApi() {}

void DsHostApi::setImpl(DsHostHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsHostApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsHostHalMock* DsHostApi::getImpl() {
    return impl;
}

// Actual HAL function implementations that delegate to the mock
extern "C" {

dsError_t dsHostInit() {
    DsHostHalMock* impl = DsHostApi::getImpl();
    if (impl) return impl->dsHostInit();
    return dsERR_NONE;
}

dsError_t dsHostTerm() {
    DsHostHalMock* impl = DsHostApi::getImpl();
    if (impl) return impl->dsHostTerm();
    return dsERR_NONE;
}

dsError_t dsGetCPUTemperature(float* cpuTemperature) {
    DsHostHalMock* impl = DsHostApi::getImpl();
    if (impl) return impl->dsGetCPUTemperature(cpuTemperature);
    if (cpuTemperature) *cpuTemperature = 0.0f;
    return dsERR_NONE;
}

dsError_t dsGetSocIDFromSDK(char* socID) {
    DsHostHalMock* impl = DsHostApi::getImpl();
    if (impl) return impl->dsGetSocIDFromSDK(socID);
    if (socID) strcpy(socID, "");
    return dsERR_NONE;
}

dsError_t dsGetHostEDID(unsigned char* edid, int* length) {
    DsHostHalMock* impl = DsHostApi::getImpl();
    if (impl) return impl->dsGetHostEDID(edid, length);
    if (length) *length = 0;
    return dsERR_NONE;
}

} // extern "C"
