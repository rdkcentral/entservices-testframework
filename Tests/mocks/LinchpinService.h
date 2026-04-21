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

#pragma once

#include <string>
#include <cstdint>
#include <core/core.h>
#include <core/JSON.h>

// Forward declaration to avoid pulling in the full IEventSender header
class IEventSender;

// Matches the real LinchPinConnectionManager.h alias used throughout the plugin
using Topic = std::string;
using ConnectionID = std::string;

namespace WPEFramework {
namespace Plugin {

/**
 * @brief Abstract interface for LinchpinService — mirrors the public API of the real
 *        LinchpinService class (LinchpinBroker/LinchpinService/inc/LinchpinService.h).
 *
 *        Used by LinchpinServiceImplMock (LinchpinServiceMock.h) to provide a
 *        controllable test double for L1 unit tests of ConnectionHandler and
 *        SubscriptionManager.
 */
class LinchpinServiceImpl {
public:
    virtual ~LinchpinServiceImpl() = default;

    virtual Core::hresult Connect(string& connectionId, int& lastStatusCode) = 0;
    virtual void Disconnect() = 0;
    virtual bool IsConnected() = 0;
    virtual Core::hresult Subscribe(Topic topic, string& connectionStatus, int& lastStatusCode) = 0;
    virtual Core::hresult Unsubscribe(Topic topic) = 0;
    virtual bool FetchMessage(const string& topic, Core::JSON::JsonObject& response) = 0;
    virtual Core::hresult Publish(const string& topic, const string& payloadType, const string& payload) = 0;
};

/**
 * @brief Mock wrapper class for LinchpinService.
 *
 *        Provides the same constructor signature and public interface as the real
 *        LinchpinService class so that ConnectionHandler and SubscriptionManager can be
 *        compiled unchanged in test builds. All method calls are forwarded to the static
 *        LinchpinServiceImpl* impl pointer, which tests set to a LinchpinServiceImplMock
 *        instance via setImpl().
 *
 * Usage in tests:
 *   LinchpinServiceImplMock mockImpl;
 *   LinchpinService::setImpl(&mockImpl);
 *   // ... run test ...
 *   LinchpinService::setImpl(nullptr);
 */
class LinchpinService {
protected:
    static LinchpinServiceImpl* impl;

public:
    LinchpinService(const std::string& url,
                    const std::string& credentials,
                    uint32_t operationTimeout,
                    uint32_t retryInterval,
                    uint64_t maximumRetryTimeoutInMs,
                    IEventSender* eventSender);
    ~LinchpinService();

    static void setImpl(LinchpinServiceImpl* newImpl);

    Core::hresult Connect(string& connectionId, int& lastStatusCode);
    void Disconnect();
    bool IsConnected();
    Core::hresult Subscribe(Topic topic, string& connectionStatus, int& lastStatusCode);
    Core::hresult Unsubscribe(Topic topic);
    bool FetchMessage(const string& topic, Core::JSON::JsonObject& response);
    Core::hresult Publish(const string& topic, const string& payloadType, const string& payload);
};

} // namespace Plugin
} // namespace WPEFramework
