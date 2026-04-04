/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
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
*/

#pragma once

#include <gmock/gmock.h>
#include <interfaces/IStore.h>

using ::WPEFramework::Exchange::IStore;
namespace Core = WPEFramework::Core;

class StoreMock : public IStore {
public:
    StoreMock() = default;
    virtual ~StoreMock() = default;

    MOCK_METHOD(Core::hresult, Register, (INotification *notification), (override));
    MOCK_METHOD(Core::hresult, Unregister, (INotification *notification), (override));
    MOCK_METHOD(Core::hresult, SetValue, (const string& ns, const string& key, const string& value), (override));
    MOCK_METHOD(Core::hresult, GetValue, (const string& ns, const string& key, string& value), (override));
    MOCK_METHOD(Core::hresult, DeleteKey, (const string& ns, const string& key), (override));
    MOCK_METHOD(Core::hresult, DeleteNamespace, (const string& ns), (override));

    MOCK_METHOD(void, AddRef, (), (const, override));
    MOCK_METHOD(uint32_t, Release, (), (const, override));
    MOCK_METHOD(void*, QueryInterface, (const uint32_t interfaceNummer), (override));
};

class StoreNotificationMock : public IStore::INotification {
public:
    StoreNotificationMock() = default;
    virtual ~StoreNotificationMock() = default;

    MOCK_METHOD(void, ValueChanged, (const string& ns, const string& key, const string& value), (override));
    MOCK_METHOD(void, StorageExceeded, (), (override));

    MOCK_METHOD(void, AddRef, (), (const, override));
    MOCK_METHOD(uint32_t, Release, (), (const, override));
    MOCK_METHOD(void*, QueryInterface, (const uint32_t interfaceNummer), (override));
};
