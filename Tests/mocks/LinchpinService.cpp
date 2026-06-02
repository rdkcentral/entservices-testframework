/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
 */

#include "LinchpinService.h"
#include <gmock/gmock.h>

// Static impl pointer — tests assign a LinchpinServiceImplMock instance here before
// exercising ConnectionHandler or SubscriptionManager code paths.
WPEFramework::Plugin::LinchpinServiceImpl* WPEFramework::Plugin::LinchpinService::impl = nullptr;

namespace WPEFramework {
namespace Plugin {

void LinchpinService::setImpl(LinchpinServiceImpl* newImpl)
{
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    if (!((nullptr == impl) || (nullptr == newImpl))) {
        ADD_FAILURE() << "LinchpinService::setImpl called without clearing existing impl";
        return;
    }
    impl = newImpl;
}

LinchpinService::LinchpinService(std::string /* url */,
                                  std::string /* credentials */,
                                  uint32_t /* operationTimeout */,
                                  uint32_t /* retryInterval */,
                                  uint64_t /* maximumRetryTimeoutInMs */,
                                  IEventSender* /* eventSender */)
{
}

LinchpinService::~LinchpinService()
{
}

Core::hresult LinchpinService::Connect(string& connectionId, int& lastStatusCode)
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::Connect called without impl set";
        return Core::ERROR_GENERAL;
    }
    return impl->Connect(connectionId, lastStatusCode);
}

void LinchpinService::Disconnect()
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::Disconnect called without impl set";
        return;
    }
    impl->Disconnect();
}

bool LinchpinService::IsConnected()
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::IsConnected called without impl set";
        return false;
    }
    return impl->IsConnected();
}

Core::hresult LinchpinService::Subscribe(Topic topic, string& connectionStatus, int& lastStatusCode)
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::Subscribe called without impl set";
        return Core::ERROR_GENERAL;
    }
    return impl->Subscribe(topic, connectionStatus, lastStatusCode);
}

Core::hresult LinchpinService::Unsubscribe(Topic topic)
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::Unsubscribe called without impl set";
        return Core::ERROR_GENERAL;
    }
    return impl->Unsubscribe(topic);
}

bool LinchpinService::FetchMessage(const string& topic, JsonObject& response)
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::FetchMessage called without impl set";
        return false;
    }
    return impl->FetchMessage(topic, response);
}

Core::hresult LinchpinService::Publish(const string& topic, const string& payloadType, const string& payload)
{
    if (impl == nullptr) {
        ADD_FAILURE() << "LinchpinService::Publish called without impl set";
        return Core::ERROR_GENERAL;
    }
    return impl->Publish(topic, payloadType, payload);
}

} // namespace Plugin
} // namespace WPEFramework
