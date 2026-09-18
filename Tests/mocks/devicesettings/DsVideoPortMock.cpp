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

#include "DsVideoPortMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsVideoPortHalMock* DsVideoPortApi::impl = nullptr;

DsVideoPortApi::DsVideoPortApi() {}
DsVideoPortApi::~DsVideoPortApi() {}

void DsVideoPortApi::setImpl(DsVideoPortHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsVideoPortApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsVideoPortHalMock* DsVideoPortApi::getImpl() {
    return impl;
}

// Actual HAL function implementations
extern "C" {

dsError_t dsVideoPortInit() {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsVideoPortInit();
    return dsERR_NONE;
}

dsError_t dsVideoPortTerm() {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsVideoPortTerm();
    return dsERR_NONE;
}

dsError_t dsGetVideoPort(dsVideoPortType_t type, int index, intptr_t* handle) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetVideoPort(type, index, handle);
    if (handle) *handle = 1;
    return dsERR_NONE;
}

dsError_t dsIsVideoPortEnabled(intptr_t handle, bool* enabled) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsIsVideoPortEnabled(handle, enabled);
    if (enabled) *enabled = true;
    return dsERR_NONE;
}

dsError_t dsEnableVideoPort(intptr_t handle, bool enabled) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsEnableVideoPort(handle, enabled);
    return dsERR_NONE;
}

dsError_t dsIsDisplayConnected(intptr_t handle, bool* connected) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsIsDisplayConnected(handle, connected);
    if (connected) *connected = true;
    return dsERR_NONE;
}

dsError_t dsIsDisplaySurround(intptr_t handle, bool* surround) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsIsDisplaySurround(handle, surround);
    if (surround) *surround = false;
    return dsERR_NONE;
}

dsError_t dsGetResolution(intptr_t handle, dsVideoPortResolution_t* resolution) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetResolution(handle, resolution);
    if (resolution) {
        resolution->pixelResolution = dsVIDEO_PIXELRES_1920x1080;
        resolution->aspectRatio = dsVIDEO_ASPECT_RATIO_16x9;
        resolution->stereoScopicMode = dsVIDEO_SSMODE_2D;
        resolution->frameRate = dsVIDEO_FRAMERATE_60;
        resolution->interlaced = false;
    }
    return dsERR_NONE;
}

dsError_t dsSetResolution(intptr_t handle, dsVideoPortResolution_t* resolution) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetResolution(handle, resolution);
    return dsERR_NONE;
}

dsError_t dsEnableHDCP(intptr_t handle, bool contentProtect, char* hdcpKey, size_t keySize) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsEnableHDCP(handle, contentProtect, hdcpKey, keySize);
    return dsERR_NONE;
}

dsError_t dsIsHDCPEnabled(intptr_t handle, bool* pContentProtected) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsIsHDCPEnabled(handle, pContentProtected);
    if (pContentProtected) *pContentProtected = false;
    return dsERR_NONE;
}

dsError_t dsGetHDCPStatus(intptr_t handle, dsHdcpStatus_t* status) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetHDCPStatus(handle, status);
    if (status) *status = dsHDCP_STATUS_AUTHENTICATED;
    return dsERR_NONE;
}

dsError_t dsGetHDCPProtocol(intptr_t handle, dsHdcpProtocolVersion_t* protocolVersion) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetHDCPProtocol(handle, protocolVersion);
    if (protocolVersion) *protocolVersion = dsHDCP_VERSION_2X;
    return dsERR_NONE;
}

dsError_t dsGetHDCPReceiverProtocol(intptr_t handle, dsHdcpProtocolVersion_t* protocolVersion) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetHDCPReceiverProtocol(handle, protocolVersion);
    if (protocolVersion) *protocolVersion = dsHDCP_VERSION_2X;
    return dsERR_NONE;
}

dsError_t dsGetHDCPCurrentProtocol(intptr_t handle, dsHdcpProtocolVersion_t* protocolVersion) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetHDCPCurrentProtocol(handle, protocolVersion);
    if (protocolVersion) *protocolVersion = dsHDCP_VERSION_2X;
    return dsERR_NONE;
}

dsError_t dsGetColorDepth(intptr_t handle, unsigned int* color_depth) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetColorDepth(handle, color_depth);
    if (color_depth) *color_depth = 8;
    return dsERR_NONE;
}

dsError_t dsSetColorDepth(intptr_t handle, unsigned int color_depth) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetColorDepth(handle, color_depth);
    return dsERR_NONE;
}

dsError_t dsGetPreferredColorDepth(intptr_t handle, dsDisplayColorDepth_t* colorDepth) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetPreferredColorDepth(handle, colorDepth);
    if (colorDepth) *colorDepth = dsDISPLAY_COLORDEPTH_8BIT;
    return dsERR_NONE;
}

dsError_t dsColorDepthCapabilities(intptr_t handle, unsigned int* capabilities) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsColorDepthCapabilities(handle, capabilities);
    if (capabilities) *capabilities = 0xFF;
    return dsERR_NONE;
}

dsError_t dsGetColorSpace(intptr_t handle, dsDisplayColorSpace_t* color_space) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetColorSpace(handle, color_space);
    if (color_space) *color_space = dsDISPLAY_COLORSPACE_RGB;
    return dsERR_NONE;
}

dsError_t dsSetColorSpace(intptr_t handle, dsDisplayColorSpace_t color_space) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetColorSpace(handle, color_space);
    return dsERR_NONE;
}

dsError_t dsGetQuantizationRange(intptr_t handle, dsDisplayQuantizationRange_t* quantization_range) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetQuantizationRange(handle, quantization_range);
    if (quantization_range) *quantization_range = dsDISPLAY_QUANTIZATIONRANGE_FULL;
    return dsERR_NONE;
}

dsError_t dsSetQuantizationRange(intptr_t handle, dsDisplayQuantizationRange_t quantization_range) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetQuantizationRange(handle, quantization_range);
    return dsERR_NONE;
}

dsError_t dsGetMatrixCoefficients(intptr_t handle, dsDisplayMatrixCoefficients_t* matrix_coefficients) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetMatrixCoefficients(handle, matrix_coefficients);
    if (matrix_coefficients) *matrix_coefficients = dsDISPLAY_MATRIXCOEFFICIENT_BT_709;
    return dsERR_NONE;
}

dsError_t dsIsOutputHDR(intptr_t handle, bool* hdr) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsIsOutputHDR(handle, hdr);
    if (hdr) *hdr = false;
    return dsERR_NONE;
}

dsError_t dsResetOutputToSDR() {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsResetOutputToSDR();
    return dsERR_NONE;
}

dsError_t dsSetHdmiPreference(intptr_t handle, dsHdcpProtocolVersion_t* hdcpCurrentProtocol) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetHdmiPreference(handle, hdcpCurrentProtocol);
    return dsERR_NONE;
}

dsError_t dsGetHdmiPreference(intptr_t handle, dsHdcpProtocolVersion_t* hdcpCurrentProtocol) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetHdmiPreference(handle, hdcpCurrentProtocol);
    if (hdcpCurrentProtocol) *hdcpCurrentProtocol = dsHDCP_VERSION_2X;
    return dsERR_NONE;
}

dsError_t dsGetTVHDRCapabilities(intptr_t handle, int* capabilities) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetTVHDRCapabilities(handle, capabilities);
    if (capabilities) *capabilities = 0;
    return dsERR_NONE;
}

dsError_t dsSupportedTvResolutions(intptr_t handle, int* resolutions) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSupportedTvResolutions(handle, resolutions);
    if (resolutions) *resolutions = 0xFF;
    return dsERR_NONE;
}

dsError_t dsSetForceHDRMode(intptr_t handle, dsHDRStandard_t mode) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetForceHDRMode(handle, mode);
    return dsERR_NONE;
}

dsError_t dsGetVideoEOTF(intptr_t handle, dsHDRStandard_t* video_eotf) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetVideoEOTF(handle, video_eotf);
    if (video_eotf) *video_eotf = dsHDRSTANDARD_SDR;
    return dsERR_NONE;
}

dsError_t dsGetCurrentOutputSettings(intptr_t handle, dsHDRStandard_t* video_eotf, dsDisplayMatrixCoefficients_t* matrix_coefficients, dsDisplayColorSpace_t* color_space, unsigned int* color_depth, dsDisplayQuantizationRange_t* quantization_range) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetCurrentOutputSettings(handle, video_eotf, matrix_coefficients, color_space, color_depth, quantization_range);
    if (video_eotf) *video_eotf = dsHDRSTANDARD_SDR;
    if (matrix_coefficients) *matrix_coefficients = dsDISPLAY_MATRIXCOEFFICIENT_BT_709;
    if (color_space) *color_space = dsDISPLAY_COLORSPACE_RGB;
    if (color_depth) *color_depth = 8;
    if (quantization_range) *quantization_range = dsDISPLAY_QUANTIZATIONRANGE_FULL;
    return dsERR_NONE;
}

dsError_t dsGetSurroundMode(intptr_t handle, int* surround) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetSurroundMode(handle, surround);
    if (surround) *surround = 0;
    return dsERR_NONE;
}

dsError_t dsGetIgnoreEDIDStatus(intptr_t handle, bool* status) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsGetIgnoreEDIDStatus(handle, status);
    if (status) *status = false;
    return dsERR_NONE;
}

dsError_t dsSetBackgroundColor(intptr_t handle, dsVideoBackgroundColor_t color) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsSetBackgroundColor(handle, color);
    return dsERR_NONE;
}

dsError_t dsRegisterHdcpStatusCallback(intptr_t handle, dsHDCPStatusCallback_t cb) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsRegisterHdcpStatusCallback(handle, cb);
    return dsERR_NONE;
}

dsError_t dsRegisterVideoOutputPortConnectCB(dsVideoPortConnectCB_t cb) {
    DsVideoPortHalMock* impl = DsVideoPortApi::getImpl();
    if (impl) return impl->dsRegisterVideoOutputPortConnectCB(cb);
    return dsERR_NONE;
}

} // extern "C"
