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

#include "DsVideoDeviceHALMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsVideoDeviceHalMock* DsVideoDeviceApi::impl = nullptr;

// DsVideoDeviceApi implementation
DsVideoDeviceApi::DsVideoDeviceApi() {}
DsVideoDeviceApi::~DsVideoDeviceApi() {}

void DsVideoDeviceApi::setImpl(DsVideoDeviceHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsVideoDeviceApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsVideoDeviceHalMock* DsVideoDeviceApi::getImpl() {
    return impl;
}

// Actual HAL function implementations that delegate to the mock
extern "C" {

dsError_t dsVideoDeviceInit() {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsVideoDeviceInit();
    return dsERR_NONE;
}

dsError_t dsVideoDeviceTerm() {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsVideoDeviceTerm();
    return dsERR_NONE;
}

dsError_t dsGetVideoDevice(int index, intptr_t* handle) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetVideoDevice(index, handle);
    if (handle) *handle = 1; // Return a valid handle
    return dsERR_NONE;
}

dsError_t dsSetDisplayframerate(intptr_t handle, char* framerate) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsSetDisplayframerate(handle, framerate);
    return dsERR_NONE;
}

dsError_t dsGetCurrentDisplayframerate(intptr_t handle, char* framerate) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetCurrentDisplayframerate(handle, framerate);
    if (framerate) strcpy(framerate, "60");
    return dsERR_NONE;
}

dsError_t dsRegisterFrameratePreChangeCB(dsRegisterFrameratePreChangeCB_t cb) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsRegisterFrameratePreChangeCB(cb);
    return dsERR_NONE;
}

dsError_t dsRegisterFrameratePostChangeCB(dsRegisterFrameratePostChangeCB_t cb) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsRegisterFrameratePostChangeCB(cb);
    return dsERR_NONE;
}

dsError_t dsGetHDRCapabilities(intptr_t handle, int* capabilities) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetHDRCapabilities(handle, capabilities);
    if (capabilities) *capabilities = 0;
    return dsERR_NONE;
}

dsError_t dsGetSupportedVideoCodingFormats(intptr_t handle, unsigned int* supported_formats) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetSupportedVideoCodingFormats(handle, supported_formats);
    if (supported_formats) *supported_formats = 0;
    return dsERR_NONE;
}

dsError_t dsGetVideoCodecInfo(intptr_t handle, dsVideoCodingFormat_t format, dsVideoCodecInfo_t* info) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetVideoCodecInfo(handle, format, info);
    return dsERR_NONE;
}

dsError_t dsSetFRFMode(intptr_t handle, int frfmode) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsSetFRFMode(handle, frfmode);
    return dsERR_NONE;
}

dsError_t dsGetFRFMode(intptr_t handle, int* frfmode) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetFRFMode(handle, frfmode);
    if (frfmode) *frfmode = 0;
    return dsERR_NONE;
}

dsError_t dsSetDFC(intptr_t handle, dsVideoZoom_t dfc) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsSetDFC(handle, dfc);
    return dsERR_NONE;
}

dsError_t dsGetDFC(intptr_t handle, dsVideoZoom_t* dfc) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsGetDFC(handle, dfc);
    if (dfc) *dfc = dsVIDEO_ZOOM_NONE;
    return dsERR_NONE;
}

dsError_t dsForceDisableHDRSupport(intptr_t handle, bool disable) {
    DsVideoDeviceHalMock* impl = DsVideoDeviceApi::getImpl();
    if (impl) return impl->dsForceDisableHDRSupport(handle, disable);
    return dsERR_NONE;
}

} // extern "C"
