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

// Stub implementations for telemetry API to provide symbols in TestMocklib.so
// This avoids including Telemetry.cpp which has gmock dependencies
#include "../Telemetry.h"

// Stub implementations that don't use gmock
static void stub_t2_init(char* component) {
    // Stub for L2 OOP tests - no-op implementation
}

static void stub_t2_uninit(void) {
    // Stub for L2 OOP tests - no-op implementation
}

static T2ERROR stub_t2_event_s(const char* marker, const char* value) {
    // Stub for L2 OOP tests - no-op implementation
    return T2ERROR_SUCCESS;
}

static T2ERROR stub_t2_event_d(const char* marker, int value) {
    // Stub for L2 OOP tests - no-op implementation
    return T2ERROR_SUCCESS;
}

// Define the function pointers that Telemetry.h declares
void (*t2_init)(char*) = &stub_t2_init;
void (*t2_uninit)(void) = &stub_t2_uninit;
T2ERROR (*t2_event_s)(const char*,const char*) = &stub_t2_event_s;
T2ERROR (*t2_event_d)(const char*,int) = &stub_t2_event_d;
