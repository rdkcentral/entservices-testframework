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
#include "dsHdmiIn.h"
}

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
    MOCK_METHOD(dsError_t, dsHdmiInGetNumberOfInputs, (uint8_t* pNumberOfinputs));
    MOCK_METHOD(dsError_t, dsHdmiInGetStatus, (dsHdmiInStatus_t* pStatus));
    
    // Port selection
    MOCK_METHOD(dsError_t, dsHdmiInSelectPort, (dsHdmiInPort_t Port, bool audioMix, dsVideoPlaneType_t evideoPlaneType, bool topMost));
    MOCK_METHOD(dsError_t, dsHdmiInScaleVideo, (int32_t x, int32_t y, int32_t width, int32_t height));
    
    // Port capabilities
    MOCK_METHOD(dsError_t, dsHdmiInSelectZoomMode, (dsVideoZoom_t requestedZoomMode));
    
    // Current video mode
    MOCK_METHOD(dsError_t, dsHdmiInGetCurrentVideoMode, (dsVideoPortResolution_t* resolution));
    
    // EDID
    MOCK_METHOD(dsError_t, dsGetEDIDBytesInfo, (dsHdmiInPort_t iHdmiPort, unsigned char* edid, int* length));
    MOCK_METHOD(dsError_t, dsGetEdidVersion, (dsHdmiInPort_t iHdmiPort, tv_hdmi_edid_version_t* iEdidVersion));
    MOCK_METHOD(dsError_t, dsSetEdidVersion, (dsHdmiInPort_t iHdmiPort, tv_hdmi_edid_version_t iEdidVersion));
    MOCK_METHOD(dsError_t, dsGetHDMISPDInfo, (dsHdmiInPort_t iHdmiPort, unsigned char* data));
    MOCK_METHOD(dsError_t, dsSetEdid2AllmSupport, (dsHdmiInPort_t iHdmiPort, bool allmSupport));
    
    // ALLM
    MOCK_METHOD(dsError_t, dsGetAllmStatus, (dsHdmiInPort_t iHdmiPort, bool* allmStatus));
    
    // ARC
    MOCK_METHOD(dsError_t, dsIsHdmiARCPort, (dsHdmiInPort_t iPort, bool* isArcPort));
    
    // Latency
    MOCK_METHOD(dsError_t, dsGetAVLatency, (int* audio_latency, int* video_latency));
    
    // HDMI version
    MOCK_METHOD(dsError_t, dsGetHdmiVersion, (dsHdmiInPort_t iHdmiPort, dsHdmiMaxCapabilityVersion_t* maxCompatibilityVersion));
    
    // VRR
    MOCK_METHOD(dsError_t, dsHdmiInGetVRRStatus, (dsHdmiInPort_t port, dsHdmiInVrrStatus_t* vrrStatus));
    MOCK_METHOD(dsError_t, dsHdmiInGetVRRSupport, (dsHdmiInPort_t port, bool* vrrSupport));
    MOCK_METHOD(dsError_t, dsHdmiInSetVRRSupport, (dsHdmiInPort_t port, bool vrrSupport));
    
    // Game features
    MOCK_METHOD(dsError_t, dsGetSupportedGameFeaturesList, (dsSupportedGameFeatureList_t* features));
    
    // Callbacks
    MOCK_METHOD(dsError_t, dsHdmiInRegisterConnectCB, (dsHdmiInConnectCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterSignalChangeCB, (dsHdmiInSignalChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterStatusChangeCB, (dsHdmiInStatusChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterVideoModeUpdateCB, (dsHdmiInVideoModeUpdateCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterAllmChangeCB, (dsHdmiInAllmChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterAVLatencyChangeCB, (dsAVLatencyChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterAviContentTypeChangeCB, (dsHdmiInAviContentTypeChangeCB_t CBFunc));
    MOCK_METHOD(dsError_t, dsHdmiInRegisterVRRChangeCB, (dsHdmiInVRRChangeCB_t cb));
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
