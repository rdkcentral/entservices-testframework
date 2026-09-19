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

#include "DsHdmiInHALMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsHdmiInHalMock* DsHdmiInApi::impl = nullptr;

DsHdmiInApi::DsHdmiInApi() {}
DsHdmiInApi::~DsHdmiInApi() {}

void DsHdmiInApi::setImpl(DsHdmiInHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsHdmiInApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsHdmiInHalMock* DsHdmiInApi::getImpl() {
    return impl;
}

// Actual HAL function implementations
extern "C" {

dsError_t dsHdmiInInit() {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInInit();
    return dsERR_NONE;
}

dsError_t dsHdmiInTerm() {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInTerm();
    return dsERR_NONE;
}

dsError_t dsHdmiInGetNumberOfInputs(uint8_t* numInputs) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInGetNumberOfInputs(numInputs);
    if (numInputs) *numInputs = 3; // Default 3 HDMI inputs
    return dsERR_NONE;
}

dsError_t dsHdmiInGetStatus(dsHdmiInPort_t* pStatus) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInGetStatus(pStatus);
    if (pStatus) {
        memset(pStatus, 0, sizeof(dsHdmiInPort_t));
        pStatus->isPresented = true;
        pStatus->isPortConnected[0] = true;
        pStatus->isPortConnected[1] = false;
        pStatus->isPortConnected[2] = false;
        pStatus->activePort = dsHDMI_IN_PORT_0;
    }
    return dsERR_NONE;
}

dsError_t dsHdmiInSelectPort(dsHdmiInPort_t port) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInSelectPort(port);
    return dsERR_NONE;
}

dsError_t dsHdmiInScaleVideo(int32_t x, int32_t y, int32_t width, int32_t height) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInScaleVideo(x, y, width, height);
    return dsERR_NONE;
}

dsError_t dsHdmiInSelectZoomMode(dsVideoZoom_t zoomMode) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInSelectZoomMode(zoomMode);
    return dsERR_NONE;
}

dsError_t dsHdmiInPauseAudio() {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInPauseAudio();
    return dsERR_NONE;
}

dsError_t dsHdmiInResumeAudio() {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInResumeAudio();
    return dsERR_NONE;
}

dsError_t dsHdmiInGetCurrentVideoMode(dsVideoPortResolution_t* resolution) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInGetCurrentVideoMode(resolution);
    if (resolution) {
        resolution->pixelResolution = dsVIDEO_PIXELRES_1920x1080;
        resolution->aspectRatio = dsVIDEO_ASPECT_RATIO_16x9;
        resolution->stereoScopicMode = dsVIDEO_SSMODE_2D;
        resolution->frameRate = dsVIDEO_FRAMERATE_60;
        resolution->interlaced = false;
    }
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterConnectCB(dsHdmiInConnectCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterConnectCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterSignalChangeCB(dsHdmiInSignalChangeCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterSignalChangeCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterStatusChangeCB(dsHdmiInStatusChangeCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterStatusChangeCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterVideoModeUpdateCB(dsHdmiInVideoModeUpdateCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterVideoModeUpdateCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterAllmChangeCB(dsHdmiInAllmChangeCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterAllmChangeCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterAVLatencyChangeCB(dsAVLatencyChangeCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterAVLatencyChangeCB(CBFunc);
    return dsERR_NONE;
}

dsError_t dsHdmiInRegisterAviContentTypeChangeCB(dsAviContentTypeChangeCB_t CBFunc) {
    DsHdmiInHalMock* impl = DsHdmiInApi::getImpl();
    if (impl) return impl->dsHdmiInRegisterAviContentTypeChangeCB(CBFunc);
    return dsERR_NONE;
}

} // extern "C"
