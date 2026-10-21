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
#include "dsVideoPort.h"
}

/**
 * @brief Mock interface for dsVideoPort HAL
 */
class DsVideoPortHalMock {
public:
    virtual ~DsVideoPortHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsVideoPortInit, ());
    MOCK_METHOD(dsError_t, dsVideoPortTerm, ());
    
    // Port management
    MOCK_METHOD(dsError_t, dsGetVideoPort, (dsVideoPortType_t type, int index, intptr_t* handle));
    MOCK_METHOD(dsError_t, dsIsVideoPortEnabled, (intptr_t handle, bool* enabled));
    MOCK_METHOD(dsError_t, dsEnableVideoPort, (intptr_t handle, bool enabled));
    MOCK_METHOD(dsError_t, dsIsVideoPortActive, (intptr_t handle, bool* active));
    
    // Display connection
    MOCK_METHOD(dsError_t, dsIsDisplayConnected, (intptr_t handle, bool* connected));
    MOCK_METHOD(dsError_t, dsIsDisplaySurround, (intptr_t handle, bool* surround));
    
    // Resolution
    MOCK_METHOD(dsError_t, dsGetResolution, (intptr_t handle, dsVideoPortResolution_t* resolution));
    MOCK_METHOD(dsError_t, dsSetResolution, (intptr_t handle, dsVideoPortResolution_t* resolution));
    
    // HDCP
    MOCK_METHOD(dsError_t, dsEnableHDCP, (intptr_t handle, bool contentProtect, char* hdcpKey, size_t keySize));
    MOCK_METHOD(dsError_t, dsIsHDCPEnabled, (intptr_t handle, bool* pContentProtected));
    MOCK_METHOD(dsError_t, dsGetHDCPStatus, (intptr_t handle, dsHdcpStatus_t* status));
    MOCK_METHOD(dsError_t, dsGetHDCPProtocol, (intptr_t handle, dsHdcpProtocolVersion_t* protocolVersion));
    MOCK_METHOD(dsError_t, dsGetHDCPReceiverProtocol, (intptr_t handle, dsHdcpProtocolVersion_t* protocolVersion));
    MOCK_METHOD(dsError_t, dsGetHDCPCurrentProtocol, (intptr_t handle, dsHdcpProtocolVersion_t* protocolVersion));
    
    // Color/Display settings
    MOCK_METHOD(dsError_t, dsGetColorDepth, (intptr_t handle, unsigned int* color_depth));
    MOCK_METHOD(dsError_t, dsGetPreferredColorDepth, (intptr_t handle, dsDisplayColorDepth_t* colorDepth));
    MOCK_METHOD(dsError_t, dsSetPreferredColorDepth, (intptr_t handle, dsDisplayColorDepth_t colorDepth));
    MOCK_METHOD(dsError_t, dsColorDepthCapabilities, (intptr_t handle, unsigned int* capabilities));
    
    MOCK_METHOD(dsError_t, dsGetColorSpace, (intptr_t handle, dsDisplayColorSpace_t* color_space));
    
    MOCK_METHOD(dsError_t, dsGetQuantizationRange, (intptr_t handle, dsDisplayQuantizationRange_t* quantization_range));
    
    MOCK_METHOD(dsError_t, dsGetMatrixCoefficients, (intptr_t handle, dsDisplayMatrixCoefficients_t* matrix_coefficients));
    
    // HDR
    MOCK_METHOD(dsError_t, dsIsOutputHDR, (intptr_t handle, bool* hdr));
    MOCK_METHOD(dsError_t, dsResetOutputToSDR, ());
    MOCK_METHOD(dsError_t, dsSetHdmiPreference, (intptr_t handle, dsHdcpProtocolVersion_t* hdcpCurrentProtocol));
    MOCK_METHOD(dsError_t, dsGetHdmiPreference, (intptr_t handle, dsHdcpProtocolVersion_t* hdcpCurrentProtocol));
    MOCK_METHOD(dsError_t, dsGetTVHDRCapabilities, (intptr_t handle, int* capabilities));
    MOCK_METHOD(dsError_t, dsSupportedTvResolutions, (intptr_t handle, int* resolutions));
    MOCK_METHOD(dsError_t, dsSetForceHDRMode, (intptr_t handle, dsHDRStandard_t mode));
    MOCK_METHOD(dsError_t, dsSetForceDisable4KSupport, (intptr_t handle, bool disable));
    MOCK_METHOD(dsError_t, dsGetForceDisable4KSupport, (intptr_t handle, bool* disable));
    
    // Video format/EOTF
    MOCK_METHOD(dsError_t, dsGetVideoEOTF, (intptr_t handle, dsHDRStandard_t* video_eotf));
    MOCK_METHOD(dsError_t, dsGetCurrentOutputSettings, (intptr_t handle, dsHDRStandard_t* video_eotf, dsDisplayMatrixCoefficients_t* matrix_coefficients, dsDisplayColorSpace_t* color_space, unsigned int* color_depth, dsDisplayQuantizationRange_t* quantization_range));
    
    // Surround mode
    MOCK_METHOD(dsError_t, dsGetSurroundMode, (intptr_t handle, int* surround));
    
    // EDID
    MOCK_METHOD(dsError_t, dsGetIgnoreEDIDStatus, (intptr_t handle, bool* status));
    MOCK_METHOD(dsError_t, dsSetBackgroundColor, (intptr_t handle, dsVideoBackgroundColor_t color));
    
    // Callbacks
    MOCK_METHOD(dsError_t, dsVideoFormatUpdateRegisterCB, (dsVideoFormatUpdateCB_t cb));
    MOCK_METHOD(dsError_t, dsRegisterHdcpStatusCallback, (intptr_t handle, dsHDCPStatusCallback_t cb));
};

/**
 * @brief API class for dsVideoPort mock
 */
class DsVideoPortApi {
protected:
    static DsVideoPortHalMock* impl;
    
public:
    DsVideoPortApi();
    DsVideoPortApi(const DsVideoPortApi &obj) = delete;
    virtual ~DsVideoPortApi();
    
    static void setImpl(DsVideoPortHalMock* newImpl);
    static DsVideoPortHalMock* getImpl();
};
