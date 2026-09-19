/* If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2023 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

#pragma once

#include <websocket/JSONRPCLink.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "UtilsJsonRpc.h"

#include "IarmBusMock.h"
#include "RfcApiMock.h"
#include "readprocMock.h"
#include "readprocMockInterface.h"
#include "WrapsMock.h"
#include "RBusMock.h"
#include "TelemetryMock.h"
// OLD LIBDS MOCKS REMOVED - Using new HAL mocks instead
// #include "VideoOutputPortConfigMock.h"
// #include "VideoOutputPortMock.h"
// #include "HostMock.h"
#include "ManagerMock.h"
#include "UdevMock.h"
#include "btmgrMock.h"
// #include "HdmiInputMock.h"  // OLD LIBDS
#include "libUSBMock.h"
// #include "devicesettings.h"  // OLD LIBDS HEADER - REMOVED
#include "tvSettingsMock.h"
#include "Tr181ApiMock.h"
// #include "AudioOutputPortMock.h"  // OLD LIBDS
// #include "AudioStereoModeMock.h"  // OLD LIBDS
// #include "VideoDeviceMock.h"  // OLD LIBDS
// #include "VideoDFCMock.h"  // OLD LIBDS
// #include "DisplayMock.h"  // OLD LIBDS
// #include "VideoResolutionMock.h"  // OLD LIBDS
// #include "FrontPanelConfigMock.h"  // OLD LIBDS
// #include "AudioOutputPortTypeMock.h"  // OLD LIBDS
// #include "VideoOutputPortTypeMock.h"  // OLD LIBDS
#include "EssRMgrMock.h"
#include "RdkLoggerMilestoneMock.h"
#include "DRMScreenCaptureMock.h"
#include "dsFPDMock.h"
#include "systemaudioplatformmock.h"
#include "RenderSessionMock.h"
#include "DobbyMock.h"
#include "OmiMock.h"
#include "PowerManagerHalMock.h"
#include "MfrMock.h"
// #include "FrontPanelIndicatorMock.h"  // OLD LIBDS
#include "HdmiCecMock.h"
// #include "ColorMock.h"  // OLD LIBDS


#ifdef RDK_SERVICE_CPC_L2_TEST
#include "sec_securityMock.h"
#include "KeyProvisionObjectMock.h"
#include "KeyProvisionDirectorySerializerMock.h"
#include "CredentialUtilsMock.h"
#include "KeyProvisionClientMock.h"
#include "SecApiProvisionerMock.h"
#endif 



using ::testing::NiceMock;
using namespace WPEFramework;

class L2TestMocks : public ::testing::Test {
protected:
        RfcApiImplMock   *p_rfcApiImplMock = nullptr ;
        RfcApi           *p_rfcApi         = nullptr ;
        IarmBusImplMock  *p_iarmBusImplMock = nullptr ;
        readprocImplMock *p_readprocImplMock = nullptr ;
        ProcImpl         *p_procImpl           = nullptr ;
        WrapsImplMock    *p_wrapsImplMock = nullptr ;
        // HostImplMock     *p_hostImplMock = nullptr ;  // OLD LIBDS - REMOVED
        // VideoOutputPortConfigImplMock *p_videoOutputPortConfigImplMock = nullptr ;  // OLD LIBDS - REMOVED
        ManagerImplMock  *p_managerImplMock = nullptr ;
        // VideoOutputPortMock *p_videoOutputPortMock = nullptr;  // OLD LIBDS - REMOVED
        UdevImplMock     *p_udevImplMock = nullptr ;
        RBusApiImplMock *p_rBusApiImplMock = nullptr;
        TelemetryApiImplMock   *p_telemetryApiImplMock = nullptr ;
        BtmgrImplMock *p_btmgrImplMock = nullptr;
        // HdmiInputImplMock   *p_hdmiInputImplMock = nullptr ;  // OLD LIBDS - REMOVED
        libUSBImplMock   *p_libUSBApiImplMock = nullptr ;
        TvSettingsImplMock   *p_tvSettingsImplMock = nullptr ;
        Tr181ApiImplMock *p_tr181ApiImplMock = nullptr ;
        // AudioOutputPortMock *p_audioOutputPortMock = nullptr;  // OLD LIBDS - REMOVED
        // AudioStereoModeMock *p_audioStereoModeMock = nullptr;  // OLD LIBDS - REMOVED
        // VideoDeviceMock *p_videoDeviceMock = nullptr;  // OLD LIBDS - REMOVED
        // VideoDFCMock *p_videoDFCMock = nullptr;  // OLD LIBDS - REMOVED
        // DisplayMock  *p_displayMock = nullptr ;  // OLD LIBDS - REMOVED
        // VideoResolutionMock      *p_videoResolutionMock = nullptr ;  // OLD LIBDS - REMOVED
        // FrontPanelConfigMock   *p_frontPanelConfigImplMock = nullptr;  // OLD LIBDS - REMOVED
        // FrontPanelIndicatorMock *p_frontPanelIndicatorMock = nullptr;  // OLD LIBDS - REMOVED
        // AudioOutputPortTypeMock        *p_audioOutputPortTypeMock = nullptr ;  // OLD LIBDS - REMOVED
        // VideoOutputPortTypeMock        *p_videoOutputPortTypeMock = nullptr ;  // OLD LIBDS - REMOVED
	EssRMgrMock      *p_essRMgrMock = nullptr;
        RdkLoggerMilestoneImplMock *p_rdkloggerImplMock = nullptr;
        DRMScreenCaptureApiImplMock *p_drmScreenCaptureApiImplMock = nullptr;
	dsFPDMock *p_dsFPDMock = nullptr;
        SystemAudioPlatformAPIMock *p_systemAudioPlatformAPIMock = nullptr;
        RenderSessionMock *p_renderSessionMock = nullptr;
        DobbyProxyMock *p_dobbyProxyMock = nullptr;
        IpcServiceMock    *p_ipcservicemock = nullptr;
        MockOmiProxy *p_mockOmiProxy = nullptr;
        PowerManagerHalMock *p_powerManagerHalMock = nullptr;
        mfrMock *p_mfrMock = nullptr;
	ConnectionImplMock *p_connectionMock = nullptr;
        LibCCECImplMock *p_libCCECMock = nullptr;
        MessageEncoderMock *p_messageEncoderMock = nullptr;
        MessageDecoderMock *p_messageDecoderMock = nullptr;
        // ColorMock *p_colorImplMock = nullptr ;  // OLD LIBDS - REMOVED
#ifdef RDK_SERVICE_CPC_L2_TEST        
        SecSecurityApiImplMock *p_secSecurityApiImplMock  = nullptr ;
        KeyProvisionObjectImplMock *p_keyProvisionObjectImplMock  = nullptr ;
        secclient::KeyProvisionDirectorySerializerImplMock* p_keyProvisionDirectorySerializerImplMock = nullptr;
        secclient::CredentialUtilsImplMock* p_credentialUtilsImplMock = nullptr;
        secclient::KeyProvisionClientImplMock* p_keyProvisionClientImplMock = nullptr;
        secclient::SecApiProvisionerImplMock* p_secApiProvisionerImplMock = nullptr;
#endif        

        std::string thunder_address;

        L2TestMocks();
        virtual ~L2TestMocks();

       /**
         * @brief Invoke a service method
         *
         * @param[in] callsign Service callsign
         * @param[in] method Method name
         * @param[in] params Method parameters
         * @param[out] results Method results
         * @return Zero (Core::ERROR_NONE) on succes or another value on error
         */
        uint32_t InvokeServiceMethod(const char *callsign, const char *method, JsonObject &params, JsonObject &results);

        /**
         * @brief Invoke a service method (jsonObject Return Type)
         *
         * @param[in] callsign Service callsign
         * @param[in] method Method name
         * @param[out] results Method results (JsonObject)
         * @return Zero (Core::ERROR_NONE) on success or another value on error
         */
        uint32_t InvokeServiceMethod(const char *callsign, const char *method, JsonObject &results);

       /**
        * @brief Invoke a service method
        *
        * @param[in] callsign Service callsign
        * @param[in] method Method name
        * @param[in] params Method parameters
        * @param[out] results Method results with string format
        * @return Zero (Core::ERROR_NONE) on succes or another value on error
        */
        uint32_t InvokeServiceMethod(const char *callsign, const char *method, JsonObject &params, Core::JSON::String &results);

        /**
        * @brief Invoke a service method
        *
        * @param[in] callsign Service callsign
        * @param[in] method Method name
        * @param[in] params Method parameters
        * @param[out] results Method results with string format
        * @return Zero (Core::ERROR_NONE) on succes or another value on error
        */
        uint32_t InvokeServiceMethod(const char *callsign, const char *method, JsonObject &params, Core::JSON::Boolean &results);

       /**
         * @brief Invoke a service method
         *
         * @param[in] callsign Service callsign
         * @param[in] method Method name
         * @param[out] results Method results
         * @return Zero (Core::ERROR_NONE) on succes or another value on error
         */
        uint32_t InvokeServiceMethod(const char *callsign, const char *method, Core::JSON::Boolean &results);

       /**
         * @brief Invoke a service method
         *
         * @param[in] callsign Service callsign
         * @param[in] method Method name
         * @param[out] results Method results
         * @return Zero (Core::ERROR_NONE) on succes or another value on error
         */
        uint32_t InvokeServiceMethod(const char *callsign, const char *method, Core::JSON::String &results);

        /**
          * @brief Invoke a service method
          *
          * @param[in] callsign Service callsign
          * @param[in] method Method name
          * @param[out] results Method results
          * @return Zero (Core::ERROR_NONE) on succes or another value on error
          */
          uint32_t InvokeServiceMethod(const char *callsign, const char *method, Core::JSON::Double &results);

        /**
         * @brief Activate a service plugin
         *
         * @param[in] callsign Service callsign
         * @return Zero (Core::ERROR_NONE) on succes or another value on error
         */
        uint32_t ActivateService(const char *callsign);

        /**
         * @brief Deactivate a service plugin
         *
         * @param[in] callsign Service callsign
         * @return Zero (Core::ERROR_NONE) on succes or another value on error
         */
        uint32_t DeactivateService(const char *callsign);

        /**
         * @brief Get the state of a plugin
         *
         * @param[in] callsign Service callsign
         * @param[out] state Plugin state (e.g., "activated", "deactivated", "suspended")
         * @return Zero (Core::ERROR_NONE) on success or another value on error
         */
        uint32_t GetPluginState(const char *callsign, std::string &state);

        /**
         * @brief Wait for a plugin to reach a specific state
         *
         * @param[in] callsign Service callsign
         * @param[in] expectedState Expected state to wait for
         * @param[in] timeoutMs Timeout in milliseconds
         * @return Zero (Core::ERROR_NONE) on success, ERROR_TIMEDOUT on timeout
         */
        uint32_t WaitForPluginState(const char *callsign, const char *expectedState, uint32_t timeoutMs);

        /**
         * @brief Activate a service with retry logic
         *
         * @param[in] callsign Service callsign
         * @param[in] maxRetries Maximum number of retries
         * @param[in] retryDelayMs Delay between retries in milliseconds
         * @return Zero (Core::ERROR_NONE) on success or another value on error
         */
        uint32_t ActivateServiceWithRetry(const char *callsign, uint32_t maxRetries = 3, uint32_t retryDelayMs = 500);

};

