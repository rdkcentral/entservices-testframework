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

#include "DsDisplayHALMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsDisplayHalMock* DsDisplayApi::impl = nullptr;

DsDisplayApi::DsDisplayApi() {}
DsDisplayApi::~DsDisplayApi() {}

void DsDisplayApi::setImpl(DsDisplayHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsDisplayApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsDisplayHalMock* DsDisplayApi::getImpl() {
    return impl;
}

// Actual HAL function implementations
extern "C" {

dsError_t dsDisplayInit() {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsDisplayInit();
    return dsERR_NONE;
}

dsError_t dsDisplayTerm() {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsDisplayTerm();
    return dsERR_NONE;
}

dsError_t dsGetDisplay(dsVideoPortType_t vType, int index, intptr_t* handle) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetDisplay(vType, index, handle);
    if (handle) *handle = 1;
    return dsERR_NONE;
}

dsError_t dsGetEDID(intptr_t handle, dsDisplayEDID_t* edid) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetEDID(handle, edid);
    if (edid) {
        memset(edid, 0, sizeof(dsDisplayEDID_t));
        edid->productCode = 0x1234;
        edid->serialNumber = 0x5678;
        edid->manufactureYear = 2024;
        edid->manufactureWeek = 1;
        edid->isRepeater = false;
        edid->physicalAddressA = 1;
        edid->physicalAddressB = 0;
        edid->physicalAddressC = 0;
        edid->physicalAddressD = 0;
        edid->numOfSupportedResolution = 1;
        // suppResolutionList is dsVideoPortResolution_t, not dsVideoResolution_t
        edid->suppResolutionList[0].pixelResolution = dsVIDEO_PIXELRES_1920x1080;
        edid->suppResolutionList[0].aspectRatio = dsVIDEO_ASPECT_RATIO_16x9;
        edid->suppResolutionList[0].stereoScopicMode = dsVIDEO_SSMODE_2D;
        edid->suppResolutionList[0].frameRate = dsVIDEO_FRAMERATE_60;
        edid->suppResolutionList[0].interlaced = false;
    }
    return dsERR_NONE;
}

dsError_t dsGetEDIDBytes(intptr_t handle, unsigned char* edid, int* length) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetEDIDBytes(handle, edid, length);
    if (edid && length) {
        // Minimal valid EDID header
        memset(edid, 0, *length);
        if (*length >= 8) {
            edid[0] = 0x00; edid[1] = 0xFF; edid[2] = 0xFF; edid[3] = 0xFF;
            edid[4] = 0xFF; edid[5] = 0xFF; edid[6] = 0xFF; edid[7] = 0x00;
        }
        *length = 256; // Standard EDID size
    }
    return dsERR_NONE;
}

dsError_t dsGetDisplayAspectRatio(intptr_t handle, dsVideoAspectRatio_t* aspectRatio) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetDisplayAspectRatio(handle, aspectRatio);
    if (aspectRatio) *aspectRatio = dsVIDEO_ASPECT_RATIO_16x9;
    return dsERR_NONE;
}

dsError_t dsGetAVIContentType(intptr_t handle, dsAviContentType_t* contentType) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetAVIContentType(handle, contentType);
    if (contentType) *contentType = dsAVI_CONTENT_TYPE_GRAPHICS;
    return dsERR_NONE;
}

dsError_t dsSetAVIContentType(intptr_t handle, dsAviContentType_t contentType) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsSetAVIContentType(handle, contentType);
    return dsERR_NONE;
}

dsError_t dsGetAVIScanInformation(intptr_t handle, dsAVIScanInformation_t* scanInfo) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetAVIScanInformation(handle, scanInfo);
    if (scanInfo) *scanInfo = dsAVI_SCANINFO_NODATA;
    return dsERR_NONE;
}

dsError_t dsSetAVIScanInformation(intptr_t handle, dsAVIScanInformation_t scanInfo) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsSetAVIScanInformation(handle, scanInfo);
    return dsERR_NONE;
}

dsError_t dsGetAllmEnabled(intptr_t handle, bool* enabled) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsGetAllmEnabled(handle, enabled);
    if (enabled) *enabled = false;
    return dsERR_NONE;
}

dsError_t dsSetAllmEnabled(intptr_t handle, bool enabled) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsSetAllmEnabled(handle, enabled);
    return dsERR_NONE;
}

dsError_t dsRegisterDisplayEventCallback(intptr_t handle, dsDisplayEventCallback_t cb) {
    DsDisplayHalMock* impl = DsDisplayApi::getImpl();
    if (impl) return impl->dsRegisterDisplayEventCallback(handle, cb);
    return dsERR_NONE;
}

} // extern "C"
