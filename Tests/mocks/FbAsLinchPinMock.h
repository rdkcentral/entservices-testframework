/*
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
 */

#pragma once

#include <gmock/gmock.h>
#include <interfaces/IFbAsLinchPin.h>

class FbAsLinchPinMock : public WPEFramework::Exchange::IFbAsLinchPin {
public:
    MOCK_METHOD(WPEFramework::Core::hresult, Register,
        (WPEFramework::Exchange::IFbAsLinchPin::INotification* notification), (override));
    MOCK_METHOD(WPEFramework::Core::hresult, Unregister,
        (WPEFramework::Exchange::IFbAsLinchPin::INotification* notification), (override));

    MOCK_METHOD(uint32_t, AddRef, (), (const, override));
    MOCK_METHOD(uint32_t, Release, (), (const, override));

    BEGIN_INTERFACE_MAP(FbAsLinchPinMock)
        INTERFACE_ENTRY(WPEFramework::Exchange::IFbAsLinchPin)
    END_INTERFACE_MAP
};
