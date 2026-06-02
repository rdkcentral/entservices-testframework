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

#include <gmock/gmock.h>
#include "LinchpinService.h"


/**
 * @brief GMock implementation of LinchpinServiceImpl.
 *
 *        Used to inject a test double for LinchpinService calls made by
 *        ConnectionHandler and SubscriptionManager during L1 unit tests.
 *
 * Usage:
 *   LinchpinServiceImplMock linchpinServiceMock;
 *   LinchpinService::setImpl(&linchpinServiceMock);
 *
 *   EXPECT_CALL(linchpinServiceMock, Connect(::testing::_, ::testing::_))
 *       .WillOnce(::testing::Return(WPEFramework::Core::ERROR_NONE));
 *
 *   // ... exercise code under test ...
 *
 *   LinchpinService::setImpl(nullptr);
 */
class LinchpinServiceImplMock : public WPEFramework::Plugin::LinchpinServiceImpl {
public:
    virtual ~LinchpinServiceImplMock() = default;

    MOCK_METHOD(WPEFramework::Core::hresult, Connect,
        (std::string& connectionId, int& lastStatusCode), (override));

    MOCK_METHOD(void, Disconnect, (), (override));

    MOCK_METHOD(bool, IsConnected, (), (override));

    MOCK_METHOD(WPEFramework::Core::hresult, Subscribe,
        (Topic topic, std::string& connectionStatus, int& lastStatusCode), (override));

    MOCK_METHOD(WPEFramework::Core::hresult, Unsubscribe,
        (Topic topic), (override));

    MOCK_METHOD(bool, FetchMessage,
        (const std::string& topic, JsonObject& response), (override));

    MOCK_METHOD(WPEFramework::Core::hresult, Publish,
        (const std::string& topic, const std::string& payloadType,
         const std::string& payload), (override));
};
