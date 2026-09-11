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

#include "essos.h"
#include <gtest/gtest.h>

EssosImpl* EssosApi::impl = nullptr;

EssosApi::EssosApi() {}

void EssosApi::setImpl(EssosImpl* newImpl) {
    EXPECT_TRUE((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

EssCtx* EssosApi::EssContextCreate() {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextCreate();
}

void EssosApi::EssContextDestroy(EssCtx* ctx) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextDestroy(ctx);
}

const char* EssosApi::EssContextGetLastErrorDetail(EssCtx* ctx) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextGetLastErrorDetail(ctx);
}

bool EssosApi::EssContextInit(EssCtx* ctx) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextInit(ctx);
}

bool EssosApi::EssContextSetUseWayland(EssCtx* ctx, bool useWayland) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextSetUseWayland(ctx, useWayland);
}

bool EssosApi::EssContextSetTerminateListener(EssCtx* ctx, void* userData, EssTerminateListener* listener) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextSetTerminateListener(ctx, userData, listener);
}

bool EssosApi::EssContextGetDisplaySize(EssCtx* ctx, int* width, int* height) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextGetDisplaySize(ctx, width, height);
}

bool EssosApi::EssContextSetInitialWindowSize(EssCtx* ctx, int width, int height) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextSetInitialWindowSize(ctx, width, height);
}

bool EssosApi::EssContextStart(EssCtx* ctx) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextStart(ctx);
}

void EssosApi::EssContextRunEventLoopOnce(EssCtx* ctx) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextRunEventLoopOnce(ctx);
}

void EssosApi::EssContextUpdateDisplay(EssCtx* ctx) {
    EXPECT_NE(impl, nullptr);
    return impl->EssContextUpdateDisplay(ctx);
}

EssCtx* (*EssContextCreate)() = &EssosApi::EssContextCreate;
void (*EssContextDestroy)( EssCtx *ctx ) = &EssosApi::EssContextDestroy;
const char* (*EssContextGetLastErrorDetail)( EssCtx *ctx ) = &EssosApi::EssContextGetLastErrorDetail;
bool (*EssContextInit)( EssCtx *ctx ) = &EssosApi::EssContextInit;
bool (*EssContextSetUseWayland)( EssCtx *ctx, bool useWayland ) = &EssosApi::EssContextSetUseWayland;
bool (*EssContextSetTerminateListener)( EssCtx *ctx, void *userData, EssTerminateListener *listener ) = &EssosApi::EssContextSetTerminateListener;
bool (*EssContextGetDisplaySize)( EssCtx *ctx, int *width, int *height ) = &EssosApi::EssContextGetDisplaySize;
bool (*EssContextSetInitialWindowSize)( EssCtx *ctx, int width, int height ) = &EssosApi::EssContextSetInitialWindowSize;
bool (*EssContextStart)( EssCtx *ctx ) = &EssosApi::EssContextStart;
void (*EssContextRunEventLoopOnce)( EssCtx *ctx ) = &EssosApi::EssContextRunEventLoopOnce;
void (*EssContextUpdateDisplay)( EssCtx *ctx ) = &EssosApi::EssContextUpdateDisplay;
