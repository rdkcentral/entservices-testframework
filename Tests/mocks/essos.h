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

// Mock replacement for the essos.h header used by WatermarkRenderer. Only the
// subset of the real Essos API consumed by entservices-watermark is declared here.

#ifndef __ESSOS__
#define __ESSOS__

#ifndef __cplusplus
#include <stdbool.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct _EssCtx EssCtx;

typedef struct _EssTerminateListener
{
   void (*terminated)( void *userData );
} EssTerminateListener;

#if 0
EssCtx* EssContextCreate();
void EssContextDestroy( EssCtx *ctx );
const char *EssContextGetLastErrorDetail( EssCtx *ctx );
bool EssContextInit( EssCtx *ctx );
bool EssContextSetUseWayland( EssCtx *ctx, bool useWayland );
bool EssContextSetTerminateListener( EssCtx *ctx, void *userData, EssTerminateListener *listener );
bool EssContextGetDisplaySize( EssCtx *ctx, int *width, int *height );
bool EssContextSetInitialWindowSize( EssCtx *ctx, int width, int height );
bool EssContextStart( EssCtx *ctx );
void EssContextRunEventLoopOnce( EssCtx *ctx );
void EssContextUpdateDisplay( EssCtx *ctx );
#endif

#if defined(__cplusplus)
} //extern "C"
#endif

class EssosImpl {
public:
    virtual ~EssosImpl() = default;

    virtual EssCtx* EssContextCreate() = 0;
    virtual void EssContextDestroy(EssCtx* ctx) = 0;
    virtual const char* EssContextGetLastErrorDetail(EssCtx* ctx) = 0;
    virtual bool EssContextInit(EssCtx* ctx) = 0;
    virtual bool EssContextSetUseWayland(EssCtx* ctx, bool useWayland) = 0;
    virtual bool EssContextSetTerminateListener(EssCtx* ctx, void* userData, EssTerminateListener* listener) = 0;
    virtual bool EssContextGetDisplaySize(EssCtx* ctx, int* width, int* height) = 0;
    virtual bool EssContextSetInitialWindowSize(EssCtx* ctx, int width, int height) = 0;
    virtual bool EssContextStart(EssCtx* ctx) = 0;
    virtual void EssContextRunEventLoopOnce(EssCtx* ctx) = 0;
    virtual void EssContextUpdateDisplay(EssCtx* ctx) = 0;
};

class EssosApi {
protected:
    static EssosImpl* impl;

public:
    EssosApi();
    EssosApi(const EssosApi &obj) = delete;
    static void setImpl(EssosImpl* newImpl);

    static EssCtx* EssContextCreate();
    static void EssContextDestroy(EssCtx* ctx);
    static const char* EssContextGetLastErrorDetail(EssCtx* ctx);
    static bool EssContextInit(EssCtx* ctx);
    static bool EssContextSetUseWayland(EssCtx* ctx, bool useWayland);
    static bool EssContextSetTerminateListener(EssCtx* ctx, void* userData, EssTerminateListener* listener);
    static bool EssContextGetDisplaySize(EssCtx* ctx, int* width, int* height);
    static bool EssContextSetInitialWindowSize(EssCtx* ctx, int width, int height);
    static bool EssContextStart(EssCtx* ctx);
    static void EssContextRunEventLoopOnce(EssCtx* ctx);
    static void EssContextUpdateDisplay(EssCtx* ctx);
};

extern EssCtx* (*EssContextCreate)();
extern void (*EssContextDestroy)( EssCtx *ctx );
extern const char* (*EssContextGetLastErrorDetail)( EssCtx *ctx );
extern bool (*EssContextInit)( EssCtx *ctx );
extern bool (*EssContextSetUseWayland)( EssCtx *ctx, bool useWayland );
extern bool (*EssContextSetTerminateListener)( EssCtx *ctx, void *userData, EssTerminateListener *listener );
extern bool (*EssContextGetDisplaySize)( EssCtx *ctx, int *width, int *height );
extern bool (*EssContextSetInitialWindowSize)( EssCtx *ctx, int width, int height );
extern bool (*EssContextStart)( EssCtx *ctx );
extern void (*EssContextRunEventLoopOnce)( EssCtx *ctx );
extern void (*EssContextUpdateDisplay)( EssCtx *ctx );

#endif
