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

#include "DsCompositeInHALMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsCompositeInHalMock* DsCompositeInApi::impl = nullptr;

// DsCompositeInApi implementation
DsCompositeInApi::DsCompositeInApi() {}
DsCompositeInApi::~DsCompositeInApi() {}

void DsCompositeInApi::setImpl(DsCompositeInHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsCompositeInApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsCompositeInHalMock* DsCompositeInApi::getImpl() {
    return impl;
}

// Actual HAL function implementations that delegate to the mock
extern "C" {

dsError_t dsCompositeInInit() {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInInit();
    return dsERR_NONE;
}

dsError_t dsCompositeInTerm() {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInTerm();
    return dsERR_NONE;
}

dsError_t dsCompositeInGetNumberOfInputs(uint8_t* pNumberOfInputs) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInGetNumberOfInputs(pNumberOfInputs);
    if (pNumberOfInputs) *pNumberOfInputs = 0;
    return dsERR_NONE;
}

dsError_t dsCompositeInGetStatus(dsCompositeInStatus_t* pStatus) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInGetStatus(pStatus);
    if (pStatus) memset(pStatus, 0, sizeof(dsCompositeInStatus_t));
    return dsERR_NONE;
}

dsError_t dsCompositeInSelectPort(dsCompositeInPort_t Port) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInSelectPort(Port);
    return dsERR_NONE;
}

dsError_t dsCompositeInScaleVideo(int32_t x, int32_t y, int32_t width, int32_t height) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInScaleVideo(x, y, width, height);
    return dsERR_NONE;
}

dsError_t dsCompositeInRegisterConnectCB(dsCompositeInConnectCB_t CBFunc) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInRegisterConnectCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsCompositeInRegisterSignalChangeCB(dsCompositeInSignalChangeCB_t CBFunc) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInRegisterSignalChangeCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsCompositeInRegisterStatusChangeCB(dsCompositeInStatusChangeCB_t CBFunc) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInRegisterStatusChangeCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsCompositeInRegisterVideoModeUpdateCB(dsCompositeInVideoModeUpdateCB_t CBFunc) {
    DsCompositeInHalMock* impl = DsCompositeInApi::getImpl();
    if (impl) return impl->dsCompositeInRegisterVideoModeUpdateCB(CBFunc);
    return dsERR_NONE;
}

} // extern "C"
