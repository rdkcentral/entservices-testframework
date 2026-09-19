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

#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#include "L2TestsMock.h"
#ifdef L2_TEST_OOP_RPC
#include "MockAccessor.h"
#endif /* L2_TEST_OOP_RPC */

#define TEST_CALLSIGN _T("org.rdk.L2Tests.1")  /* Test module callsign. */
#define INVOKE_TIMEOUT 3000                        /* Method invoke timeout in milliseconds. */
#define THUNDER_ADDRESS _T("127.0.0.1:")
#define TEST_LOG(x, ...) fprintf(stderr, "\033[1;32m[%s:%d](%s)<PID:%d><TID:%d>" x "\n\033[0m", __FILE__, __LINE__, __FUNCTION__, getpid(), gettid(), ##__VA_ARGS__); fflush(stderr);

#ifndef THUNDER_PORT
#define THUNDER_PORT "9998"
#endif

using namespace WPEFramework;

/* L2TestMock consturctor */
L2TestMocks::L2TestMocks()
{
    p_rfcApiImplMock    = new NiceMock <RfcApiImplMock>;
    p_iarmBusImplMock   = new NiceMock <IarmBusImplMock>;
    p_readprocImplMock  = new NiceMock <readprocImplMock>;
    p_wrapsImplMock     = new NiceMock <WrapsImplMock>;
    p_udevImplMock      = new NiceMock <UdevImplMock>;
    p_rBusApiImplMock   = new NiceMock <RBusApiImplMock>;
    p_telemetryApiImplMock  = new NiceMock <TelemetryApiImplMock>;
    p_btmgrImplMock     = new NiceMock <BtmgrImplMock>;
    p_libUSBApiImplMock  = new NiceMock <libUSBImplMock>;
    p_tvSettingsImplMock  = new NiceMock <TvSettingsImplMock>;
    p_tr181ApiImplMock = new NiceMock <Tr181ApiImplMock>;
   p_essRMgrMock       = new NiceMock <EssRMgrMock>;
   p_rdkloggerImplMock = new NiceMock <RdkLoggerMilestoneImplMock>;
   p_drmScreenCaptureApiImplMock = new NiceMock<DRMScreenCaptureApiImplMock>;
   p_systemAudioPlatformAPIMock = new NiceMock<SystemAudioPlatformAPIMock>;
   p_renderSessionMock = new NiceMock <RenderSessionMock>;
   p_dobbyProxyMock = new NiceMock <DobbyProxyMock>;
   p_ipcservicemock  = new NiceMock <IpcServiceMock>;
   p_mockOmiProxy = new NiceMock<MockOmiProxy>;
   p_powerManagerHalMock = new NiceMock<PowerManagerHalMock>;
   p_mfrMock = new NiceMock<mfrMock>;
   p_connectionMock = new NiceMock<ConnectionImplMock>;
   p_libCCECMock = new NiceMock<LibCCECImplMock>;
   p_messageEncoderMock = new NiceMock<MessageEncoderMock>;
   p_messageDecoderMock = new NiceMock<MessageDecoderMock>;
   
   // DeviceSettings HAL Mocks
   p_dsAudioHalMock = new NiceMock<DsAudioHalMock>;
   p_dsDisplayHalMock = new NiceMock<DsDisplayHalMock>;
   p_dsFPDHalMock = new NiceMock<DsFPDHalMock>;
   p_dsHdmiInHalMock = new NiceMock<DsHdmiInHalMock>;
   p_dsVideoDeviceHalMock = new NiceMock<DsVideoDeviceHalMock>;
   p_dsVideoPortHalMock = new NiceMock<DsVideoPortHalMock>;

#ifdef RDK_SERVICE_CPC_L2_TEST    
    p_secSecurityApiImplMock      = new NiceMock <SecSecurityApiImplMock>;
    p_keyProvisionObjectImplMock      = new NiceMock <KeyProvisionObjectImplMock>;
    p_keyProvisionDirectorySerializerImplMock = new NiceMock<secclient::KeyProvisionDirectorySerializerImplMock>;
    p_credentialUtilsImplMock = new NiceMock<secclient::CredentialUtilsImplMock>;
    p_keyProvisionClientImplMock = new NiceMock<secclient::KeyProvisionClientImplMock>;
    p_secApiProvisionerImplMock = new NiceMock<secclient::SecApiProvisionerImplMock>;
#endif    

   TEST_LOG("Inside L2TestMocks constructor");

#ifdef L2_TEST_OOP_RPC
    MockAccessor<IarmBusImpl>::setPtr(p_iarmBusImplMock);
    MockAccessor<readprocImpl>::setPtr(p_readprocImplMock);
    MockAccessor<RBusApiImpl>::setPtr(p_rBusApiImplMock);
    MockAccessor<RfcApiImpl>::setPtr(p_rfcApiImplMock);
    MockAccessor<PowerManagerImpl>::setPtr(p_powerManagerHalMock);
    MockAccessor<mfrImpl>::setPtr(p_mfrMock);
#else
    IarmBus::setImpl(p_iarmBusImplMock);
    RfcApi::setImpl(p_rfcApiImplMock);
    ProcImpl::setImpl(p_readprocImplMock);
    Wraps::setImpl(p_wrapsImplMock);
    RBusApi::setImpl(p_rBusApiImplMock);
    TelemetryApi::setImpl(p_telemetryApiImplMock);
    Udev::setImpl(p_udevImplMock);
    Btmgr::setImpl(p_btmgrImplMock);
    libusbApi::setImpl(p_libUSBApiImplMock);
    TvSettings::setImpl(p_tvSettingsImplMock);
    Tr181Api::setImpl(p_tr181ApiImplMock);
    EssRMgrApi::setImpl(p_essRMgrMock);
    DRMScreenCaptureApi::getInstance().impl = p_drmScreenCaptureApiImplMock;
    SystemAudioPlatformMockImpl::setImpl(p_systemAudioPlatformAPIMock);


    RenderSession::setImpl(p_renderSessionMock);
    DobbyProxy::setImpl(p_dobbyProxyMock);
    IpcService::setImpl(p_ipcservicemock);
    omi::OmiProxy::setImpl(p_mockOmiProxy);
    PowerManagerAPI::setImpl(p_powerManagerHalMock);
    mfr::setImpl(p_mfrMock);
    LibCCEC::setImpl(p_libCCECMock);
    Connection::setImpl(p_connectionMock);
    MessageEncoder::setImpl(p_messageEncoderMock);
    MessageDecoder::setImpl(p_messageDecoderMock);
    
    // DeviceSettings HAL Mocks - Register and set up common behaviors
    DsAudioApi::setImpl(p_dsAudioHalMock);
    ON_CALL(*p_dsAudioHalMock, dsAudioPortInit()).WillByDefault(::testing::Return(dsERR_NONE));
    ON_CALL(*p_dsAudioHalMock, dsAudioPortTerm()).WillByDefault(::testing::Return(dsERR_NONE));
    
    DsDisplayApi::setImpl(p_dsDisplayHalMock);
    ON_CALL(*p_dsDisplayHalMock, dsDisplayInit()).WillByDefault(::testing::Return(dsERR_NONE));
    ON_CALL(*p_dsDisplayHalMock, dsDisplayTerm()).WillByDefault(::testing::Return(dsERR_NONE));
    
    DsFPDApi::setImpl(p_dsFPDHalMock);
    ON_CALL(*p_dsFPDHalMock, dsFPInit()).WillByDefault(::testing::Return(dsERR_NONE));
    ON_CALL(*p_dsFPDHalMock, dsFPTerm()).WillByDefault(::testing::Return(dsERR_NONE));
    
    DsHdmiInApi::setImpl(p_dsHdmiInHalMock);
    ON_CALL(*p_dsHdmiInHalMock, dsHdmiInInit()).WillByDefault(::testing::Return(dsERR_NONE));
    ON_CALL(*p_dsHdmiInHalMock, dsHdmiInTerm()).WillByDefault(::testing::Return(dsERR_NONE));
    
    DsVideoDeviceApi::setImpl(p_dsVideoDeviceHalMock);
    ON_CALL(*p_dsVideoDeviceHalMock, dsVideoDeviceInit()).WillByDefault(::testing::Return(dsERR_NONE));
    ON_CALL(*p_dsVideoDeviceHalMock, dsVideoDeviceTerm()).WillByDefault(::testing::Return(dsERR_NONE));
    
    DsVideoPortApi::setImpl(p_dsVideoPortHalMock);
    ON_CALL(*p_dsVideoPortHalMock, dsVideoPortInit()).WillByDefault(::testing::Return(dsERR_NONE));
    ON_CALL(*p_dsVideoPortHalMock, dsVideoPortTerm()).WillByDefault(::testing::Return(dsERR_NONE));
    
#ifdef RDK_SERVICE_CPC_L2_TEST    
    SecSecurityApi::setImpl(p_secSecurityApiImplMock);
    secclient::KeyProvisionObject::setImpl(p_keyProvisionObjectImplMock);
    secclient::KeyProvisionDirectorySerializer::setImpl(p_keyProvisionDirectorySerializerImplMock);
    secclient::CredentialUtils::setImpl(p_credentialUtilsImplMock);
    secclient::KeyProvisionClient::setImpl(p_keyProvisionClientImplMock);
    secclient::SecApiProvisioner::setImpl(p_secApiProvisionerImplMock);
#endif
#endif /* L2_TEST_OOP_RPC */

    thunder_address = THUNDER_ADDRESS + std::string(THUNDER_PORT);
    (void)Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), thunder_address);

#ifdef L2_TEST_OOP_RPC
    ActivateService("org.rdk.MockPlugin");
#endif /* L2_TEST_OOP_RPC */

}

/* L2TestMock Destructor */
L2TestMocks::~L2TestMocks()
{

#ifdef L2_TEST_OOP_RPC
   DeactivateService("org.rdk.MockPlugin");
   MockAccessor<IarmBusImpl>::setPtr(nullptr);
   MockAccessor<readprocImpl>::setPtr(nullptr);
   MockAccessor<RBusApiImpl>::setPtr(nullptr);
   MockAccessor<RfcApiImpl>::setPtr(nullptr);
   MockAccessor<PowerManagerImpl>::setPtr(nullptr);
   MockAccessor<mfrImpl>::setPtr(nullptr);
#else
   IarmBus::setImpl(nullptr);
   RfcApi::setImpl(nullptr);
   ProcImpl::setImpl(nullptr);
   Wraps::setImpl(nullptr);
   RBusApi::setImpl(nullptr);
   TelemetryApi::setImpl(nullptr);
   Udev::setImpl(nullptr);
   Btmgr::setImpl(nullptr);
   libusbApi::setImpl(nullptr);
   TvSettings::setImpl(nullptr);
   Tr181Api::setImpl(nullptr);
   EssRMgrApi::setImpl(nullptr);
   DRMScreenCaptureApi::getInstance().impl = nullptr;
   SystemAudioPlatformMockImpl::setImpl(nullptr);
   RenderSession::setImpl(nullptr);
   DobbyProxy::setImpl(nullptr);
   IpcService::setImpl(nullptr);
   omi::OmiProxy::setImpl(nullptr);
   PowerManagerAPI::setImpl(nullptr);
   mfr::setImpl(nullptr);
   Connection::setImpl(nullptr);
   LibCCEC::setImpl(nullptr);
   MessageEncoder::setImpl(nullptr);
   MessageDecoder::setImpl(nullptr);
   
   // DeviceSettings HAL Mocks
   DsAudioApi::setImpl(nullptr);
   DsDisplayApi::setImpl(nullptr);
   DsFPDApi::setImpl(nullptr);
   DsHdmiInApi::setImpl(nullptr);
   DsVideoDeviceApi::setImpl(nullptr);
   DsVideoPortApi::setImpl(nullptr);

#ifdef RDK_SERVICE_CPC_L2_TEST   
   SecSecurityApi::setImpl(nullptr);
   secclient::KeyProvisionObject::setImpl(nullptr);
   secclient::KeyProvisionDirectorySerializer::setImpl(nullptr);
   secclient::CredentialUtils::setImpl(nullptr);
   secclient::KeyProvisionClient::setImpl(nullptr);
   secclient::SecApiProvisioner::setImpl(nullptr);
#endif   
 
#endif /* L2_TEST_OOP_RPC */

   TEST_LOG("Inside L2TestMocks destructor");

   if (p_iarmBusImplMock != nullptr)
   {
        delete p_iarmBusImplMock;
        p_iarmBusImplMock = nullptr;
   }

   if (p_essRMgrMock != nullptr)
   {
         delete p_essRMgrMock;
         p_essRMgrMock = nullptr;
   }

   if (p_rfcApiImplMock != nullptr)
   {
        delete p_rfcApiImplMock;
        p_rfcApiImplMock = nullptr;
   }

   if (p_readprocImplMock != nullptr)
   {
        delete p_readprocImplMock;
        p_readprocImplMock = nullptr;
   }

   if (p_wrapsImplMock != nullptr)
   {
        delete p_wrapsImplMock;
        p_wrapsImplMock = nullptr;
   }


   if (p_rBusApiImplMock != nullptr)
   {
        delete p_rBusApiImplMock;
        p_rBusApiImplMock = nullptr;
   }


   if (p_telemetryApiImplMock != nullptr)
   {
        delete p_telemetryApiImplMock;
        p_telemetryApiImplMock = nullptr;
   }

   if (p_udevImplMock != nullptr)
   {
        delete p_udevImplMock;
        p_udevImplMock = nullptr;
   }


   if (p_btmgrImplMock != nullptr)
   {
        delete p_btmgrImplMock;
        p_btmgrImplMock = nullptr;
   }



   if (p_libUSBApiImplMock != nullptr)
   {
        delete p_libUSBApiImplMock;
        p_libUSBApiImplMock = nullptr;
   }

   if (p_tvSettingsImplMock != nullptr)
   {
      delete p_tvSettingsImplMock;
      p_tvSettingsImplMock = nullptr;
   }

   if (p_tr181ApiImplMock != nullptr)
   {
      delete p_tr181ApiImplMock;
      p_tr181ApiImplMock = nullptr;
   }

   if (p_drmScreenCaptureApiImplMock != nullptr)
   {
      delete p_drmScreenCaptureApiImplMock;
      p_drmScreenCaptureApiImplMock = nullptr;
   }

   if (p_systemAudioPlatformAPIMock != nullptr)
   {
      delete p_systemAudioPlatformAPIMock;
      p_systemAudioPlatformAPIMock = nullptr;
   }

   if (p_renderSessionMock != nullptr)
   {
      delete p_renderSessionMock;
      p_renderSessionMock = nullptr;
   }

   if (p_dobbyProxyMock != nullptr)
   {
      delete p_dobbyProxyMock;
      p_dobbyProxyMock = nullptr;
   }

   if (p_ipcservicemock != nullptr)
   {
      delete p_ipcservicemock;
      p_ipcservicemock = nullptr;
   }

   if(p_mockOmiProxy != nullptr)
   {
      delete p_mockOmiProxy;
      p_mockOmiProxy = nullptr;
   }

   if(p_powerManagerHalMock != nullptr)
   {
      delete p_powerManagerHalMock;
      p_powerManagerHalMock = nullptr;
   }

   if(p_mfrMock != nullptr)
   {
      delete p_mfrMock;
      p_mfrMock = nullptr;
   }

   if (p_connectionMock != nullptr)
   {
      delete p_connectionMock;
      p_connectionMock = nullptr;
   }

   if (p_libCCECMock != nullptr)
   {
      delete p_libCCECMock;
      p_libCCECMock = nullptr;
   }

   if (p_messageEncoderMock != nullptr)
   {
      delete p_messageEncoderMock;
      p_messageEncoderMock = nullptr;
   }

   if (p_messageDecoderMock != nullptr)
   {
      delete p_messageDecoderMock;
      p_messageDecoderMock = nullptr;
   }
   
   // DeviceSettings HAL Mocks
   if (p_dsAudioHalMock != nullptr)
   {
      delete p_dsAudioHalMock;
      p_dsAudioHalMock = nullptr;
   }
   
   if (p_dsDisplayHalMock != nullptr)
   {
      delete p_dsDisplayHalMock;
      p_dsDisplayHalMock = nullptr;
   }
   
   if (p_dsFPDHalMock != nullptr)
   {
      delete p_dsFPDHalMock;
      p_dsFPDHalMock = nullptr;
   }
   
   if (p_dsHdmiInHalMock != nullptr)
   {
      delete p_dsHdmiInHalMock;
      p_dsHdmiInHalMock = nullptr;
   }
   
   if (p_dsVideoDeviceHalMock != nullptr)
   {
      delete p_dsVideoDeviceHalMock;
      p_dsVideoDeviceHalMock = nullptr;
   }
   
   if (p_dsVideoPortHalMock != nullptr)
   {
      delete p_dsVideoPortHalMock;
      p_dsVideoPortHalMock = nullptr;
   }

#ifdef RDK_SERVICE_CPC_L2_TEST
   if (p_secSecurityApiImplMock != nullptr)
   {
        delete p_secSecurityApiImplMock;
        p_secSecurityApiImplMock = nullptr;
   }

   if (p_keyProvisionObjectImplMock != nullptr)
   {
        delete p_keyProvisionObjectImplMock;
        p_keyProvisionObjectImplMock = nullptr;
   }

   if (p_keyProvisionDirectorySerializerImplMock != nullptr) {
       delete p_keyProvisionDirectorySerializerImplMock;
       p_keyProvisionDirectorySerializerImplMock = nullptr;
   }

   if (p_credentialUtilsImplMock != nullptr) {
       delete p_credentialUtilsImplMock;
       p_credentialUtilsImplMock = nullptr;
   }

   if (p_keyProvisionClientImplMock != nullptr) {
       delete p_keyProvisionClientImplMock;
       p_keyProvisionClientImplMock = nullptr;
   }

   if (p_secApiProvisionerImplMock != nullptr) {
       delete p_secApiProvisionerImplMock;
       p_secApiProvisionerImplMock = nullptr;
   }
#endif


}

/**
 * @brief Invoke a service method
 *
 * @param[in] callsign Service callsign
 * @param[in] method Method name
 * @param[in] params Method parameters
 * @param[out] results Method results
 * @return Zero (Core::ERROR_NONE) on succes or another value on error
 */
uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, JsonObject &params, JsonObject &results)
{

   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string message;
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   params.ToString(message);
   TEST_LOG("Invoking %s.%s, parameters %s\n", callsign, method, message.c_str());

   results = JsonObject();
   status = jsonrpc.Invoke<JsonObject, JsonObject>(INVOKE_TIMEOUT, std::string(method), params, results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());
   if(status == 11) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second 
        status = jsonrpc.Invoke<JsonObject, JsonObject>(INVOKE_TIMEOUT, std::string(method), params, results);
        results.ToString(reply);
        TEST_LOG("Retry Status %u, results %s", status, reply.c_str());
    }   

   return status;
}

/**
 * @brief Invoke a service method (jsonObject Return Type)
 *
 * @param[in] callsign Service callsign
 * @param[in] method Method name
 * @param[out] results Method results (JsonObject)
 * @return Zero (Core::ERROR_NONE) on success or another value on error
 */
uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, JsonObject &results)
{
   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   TEST_LOG("Invoking %s.%s \n", callsign, method);

   results = JsonObject();
   status = jsonrpc.Invoke<void, JsonObject>(INVOKE_TIMEOUT, std::string(method), results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());

   return status;
}

/**
 * @brief Invoke a service method
 *
 * @param[in] callsign Service callsign
 * @param[in] method Method name
 * @param[in] params Method parameters
 * @param[out] results Method results
 * @return Zero (Core::ERROR_NONE) on succes or another value on error
 */
uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, JsonObject &params, Core::JSON::String &results)
{

   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string message;
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   params.ToString(message);
   TEST_LOG("Invoking %s.%s, parameters %s\n", callsign, method, message.c_str());

   status = jsonrpc.Invoke<JsonObject, Core::JSON::String>(INVOKE_TIMEOUT, std::string(method), params, results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());

   return status;

}

/**
 * @brief Invoke a service method
 *
 * @param[in] callsign Service callsign
 * @param[in] method Method name
 * @param[in] params Method parameters
 * @param[out] results Method results with string format
 * @return Zero (Core::ERROR_NONE) on succes or another value on error
 */
uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, JsonObject &params, Core::JSON::Boolean &results)
{

   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string message;
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   params.ToString(message);
   TEST_LOG("Invoking %s.%s, parameters %s\n", callsign, method, message.c_str());

   status = jsonrpc.Invoke<JsonObject, Core::JSON::Boolean>(INVOKE_TIMEOUT, std::string(method), params, results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());

   return status;

}

/**
 * @brief Invoke a service method
 *
 * @param[in] callsign Service callsign
 * @param[in] method Method name
 * @param[out] results Method results
 * @return Zero (Core::ERROR_NONE) on succes or another value on error
 */
uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, Core::JSON::Boolean &results)
{

   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   TEST_LOG("Invoking %s.%s \n", callsign, method);

   status = jsonrpc.Invoke<void, Core::JSON::Boolean>(INVOKE_TIMEOUT, std::string(method), results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());

   return status;
}

/**
 * @brief Invoke a service method
 *
 * @param[in] callsign Service callsign
 * @param[in] method Method name
 * @param[out] results Method results
 * @return Zero (Core::ERROR_NONE) on succes or another value on error
 */
uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, Core::JSON::String &results)
{

   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   TEST_LOG("Invoking %s.%s \n", callsign, method);

   status = jsonrpc.Invoke<void, Core::JSON::String>(INVOKE_TIMEOUT, std::string(method), results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());

   return status;

}

uint32_t L2TestMocks::InvokeServiceMethod(const char *callsign, const char *method, Core::JSON::Double &results)
{
   JSONRPC::LinkType<Core::JSON::IElement> jsonrpc(std::string(callsign), TEST_CALLSIGN);
   std::string reply;
   uint32_t status = Core::ERROR_NONE;

   TEST_LOG("Invoking %s.%s \n", callsign, method);

   status = jsonrpc.Invoke<void, Core::JSON::Double>(INVOKE_TIMEOUT, std::string(method), results);

   results.ToString(reply);
   TEST_LOG("Status %u, results %s", status, reply.c_str());

   return status;
}

/**
* @brief Activate a service plugin
*
* @param[in] callsign Service callsign
* @return Zero (Core::ERROR_NONE) on succes or another value on error
*/
uint32_t L2TestMocks::ActivateService(const char *callsign)
{
   JsonObject params;
   JsonObject result;
   uint32_t status = Core::ERROR_GENERAL;

   if(callsign != NULL)
   {
     params["callsign"] = callsign;
     status = InvokeServiceMethod("Controller.1", "activate", params, result);
   }

   return status;
}

/**
* @brief Deactivate a service plugin
*
* @param[in] callsign Service callsign
* @return Zero (Core::ERROR_NONE) on succes or another value on error
*/
uint32_t L2TestMocks::DeactivateService(const char *callsign)
{
   JsonObject params;
   JsonObject result;
   uint32_t status = Core::ERROR_GENERAL;

   if(callsign != NULL)
   {
      params["callsign"] = callsign;
      status = InvokeServiceMethod("Controller.1", "deactivate", params, result);
   }
   return status;
}

/**
* @brief Get the state of a plugin
*
* @param[in] callsign Service callsign
* @param[out] state Plugin state
* @return Zero (Core::ERROR_NONE) on success or another value on error
*/
uint32_t L2TestMocks::GetPluginState(const char *callsign, std::string &state)
{
   JsonObject params;
   JsonObject result;
   uint32_t status = Core::ERROR_GENERAL;

   if(callsign != NULL)
   {
      params["callsign"] = callsign;
      status = InvokeServiceMethod("Controller.1", "status", params, result);
      
      if (status == Core::ERROR_NONE) {
         // Try different response formats
         if (result.HasLabel("state")) {
            state = result["state"].String();
         } else if (result.HasLabel("0")) {
            // Some Thunder versions return state in array format
            JsonArray stateArray = result["0"].Array();
            if (stateArray.Length() > 0) {
               JsonObject stateObj = stateArray[0].Object();
               if (stateObj.HasLabel("state")) {
                  state = stateObj["state"].String();
               }
            }
         } else {
            // Response is empty or in unknown format
            // Try to get list of plugins and check if this one exists
            JsonObject listResult;
            uint32_t listStatus = InvokeServiceMethod("Controller.1", "status", listResult);
            if (listStatus == Core::ERROR_NONE && listResult.HasLabel(callsign)) {
               JsonObject pluginInfo = listResult[callsign].Object();
               if (pluginInfo.HasLabel("state")) {
                  state = pluginInfo["state"].String();
                  status = Core::ERROR_NONE;
                  return status;
               }
            }
            TEST_LOG("GetPluginState: Unable to determine state for %s, assuming not activated", callsign);
            state = "deactivated";
            status = Core::ERROR_NONE;
         }
      }
   }

   return status;
}

/**
* @brief Wait for a plugin to reach a specific state
*
* @param[in] callsign Service callsign
* @param[in] expectedState Expected state to wait for
* @param[in] timeoutMs Timeout in milliseconds
* @return Zero (Core::ERROR_NONE) on success, ERROR_TIMEDOUT on timeout
*/
uint32_t L2TestMocks::WaitForPluginState(const char *callsign, const char *expectedState, uint32_t timeoutMs)
{
   auto startTime = std::chrono::steady_clock::now();
   std::string currentState;
   
   TEST_LOG("WaitForPluginState: Waiting for %s to reach state '%s' (timeout: %u ms)", 
            callsign, expectedState, timeoutMs);
   
   while (true) {
      uint32_t status = GetPluginState(callsign, currentState);
      
      if (status == Core::ERROR_NONE) {
         TEST_LOG("WaitForPluginState: Current state of %s is '%s'", callsign, currentState.c_str());
         
         if (currentState == expectedState) {
            TEST_LOG("WaitForPluginState: %s reached expected state '%s'", callsign, expectedState);
            return Core::ERROR_NONE;
         }
      } else {
         TEST_LOG("WaitForPluginState: Failed to get state of %s (status: %u)", callsign, status);
      }
      
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
         std::chrono::steady_clock::now() - startTime).count();
      
      if (elapsed >= timeoutMs) {
         TEST_LOG("WaitForPluginState: Timeout waiting for %s to reach state '%s' (current: '%s')", 
                  callsign, expectedState, currentState.c_str());
         return Core::ERROR_TIMEDOUT;
      }
      
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }
}

/**
* @brief Activate a service with retry logic
*
* @param[in] callsign Service callsign
* @param[in] maxRetries Maximum number of retries
* @param[in] retryDelayMs Delay between retries in milliseconds
* @return Zero (Core::ERROR_NONE) on success or another value on error
*/
uint32_t L2TestMocks::ActivateServiceWithRetry(const char *callsign, uint32_t maxRetries, uint32_t retryDelayMs)
{
   uint32_t status = Core::ERROR_GENERAL;
   
   for (uint32_t attempt = 0; attempt < maxRetries; attempt++) {
      TEST_LOG("ActivateServiceWithRetry: Attempt %u/%u to activate %s", 
               attempt + 1, maxRetries, callsign);
      
      status = ActivateService(callsign);
      
      if (status == Core::ERROR_NONE) {
         TEST_LOG("ActivateServiceWithRetry: Successfully activated %s", callsign);
         // Wait for plugin to reach activated state
         status = WaitForPluginState(callsign, "activated", 5000);
         if (status == Core::ERROR_NONE) {
            return Core::ERROR_NONE;
         }
         TEST_LOG("ActivateServiceWithRetry: Plugin activated but didn't reach 'activated' state");
      } else if (status == Core::ERROR_INPROGRESS) {
         TEST_LOG("ActivateServiceWithRetry: Activation in progress, waiting...");
         // Activation is in progress, wait for it to complete
         status = WaitForPluginState(callsign, "activated", 5000);
         if (status == Core::ERROR_NONE) {
            return Core::ERROR_NONE;
         }
      } else if (status == 6) {
         // ERROR_OPENING_FAILED - plugin failed to load (missing symbols, etc)
         TEST_LOG("ActivateServiceWithRetry: FATAL - Plugin failed to load (status 6 - ERROR_OPENING_FAILED)");
         TEST_LOG("ActivateServiceWithRetry: This usually indicates missing library dependencies or symbols");
         TEST_LOG("ActivateServiceWithRetry: Check for 'undefined symbol' errors in the logs above");
         return status;  // Don't retry on fatal errors
      } else {
         TEST_LOG("ActivateServiceWithRetry: Activation failed with status %u", status);
      }
      
      if (attempt < maxRetries - 1) {
         TEST_LOG("ActivateServiceWithRetry: Retrying after %u ms...", retryDelayMs);
         std::this_thread::sleep_for(std::chrono::milliseconds(retryDelayMs));
      }
   }
   
   TEST_LOG("ActivateServiceWithRetry: Failed to activate %s after %u attempts (final status: %u)", callsign, maxRetries, status);
   return status;
}


