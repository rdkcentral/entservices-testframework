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
#include "essos.h"

class EssosMock : public EssosImpl {
public:
    EssosMock()
        : EssosImpl()
    {
        char fakeMemory[64] = {}; // 64 bytes is arbitrary, depends on actual size
        EssCtx* EssCtxObj = reinterpret_cast<EssCtx*>(fakeMemory);
        ON_CALL(*this, EssContextCreate())
            .WillByDefault(::testing::Return(EssCtxObj));
    }
    virtual ~EssosMock() = default;

    MOCK_METHOD(EssCtx*, EssContextCreate, (), (override));
    MOCK_METHOD(void, EssContextDestroy, (EssCtx * ctx), (override));
    MOCK_METHOD(const char*, EssContextGetLastErrorDetail, (EssCtx * ctx), (override));
    MOCK_METHOD(bool, EssContextInit, (EssCtx * ctx), (override));
    MOCK_METHOD(bool, EssContextSetUseWayland, (EssCtx * ctx, bool useWayland), (override));
    MOCK_METHOD(bool, EssContextSetTerminateListener, (EssCtx * ctx, void* userData, EssTerminateListener* listener), (override));
    MOCK_METHOD(bool, EssContextGetDisplaySize, (EssCtx * ctx, int* width, int* height), (override));
    MOCK_METHOD(bool, EssContextSetInitialWindowSize, (EssCtx * ctx, int width, int height), (override));
    MOCK_METHOD(bool, EssContextStart, (EssCtx * ctx), (override));
    MOCK_METHOD(void, EssContextRunEventLoopOnce, (EssCtx * ctx), (override));
    MOCK_METHOD(void, EssContextUpdateDisplay, (EssCtx * ctx), (override));
};
