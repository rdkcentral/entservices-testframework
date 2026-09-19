/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
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
**/

#include "DsFPDHALMock.h"
#include <cstdio>
#include <cstring>

// Static implementation pointer
DsFPDHalMock* DsFPDApi::impl = nullptr;

DsFPDApi::DsFPDApi() {}
DsFPDApi::~DsFPDApi() {}

void DsFPDApi::setImpl(DsFPDHalMock* newImpl) {
    if (impl != nullptr && newImpl != nullptr) {
        fprintf(stderr, "WARNING: DsFPDApi::setImpl called when impl is already set!\n");
    }
    impl = newImpl;
}

DsFPDHalMock* DsFPDApi::getImpl() {
    return impl;
}

// Actual HAL function implementations
extern "C" {

dsError_t dsFPInit() {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPInit();
    return dsERR_NONE;
}

dsError_t dsFPTerm() {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPTerm();
    return dsERR_NONE;
}

dsError_t dsSetFPState(dsFPDState_t state) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPState(state);
    return dsERR_NONE;
}

dsError_t dsGetFPState(dsFPDState_t* state) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPState(state);
    if (state) *state = dsFPD_STATE_ON;
    return dsERR_NONE;
}

dsError_t dsSetFPBlink(dsFPDIndicator_t indicator, unsigned int uBlinkDuration, unsigned int uBlinkIterations) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPBlink(indicator, uBlinkDuration, uBlinkIterations);
    return dsERR_NONE;
}

dsError_t dsSetFPBrightness(dsFPDIndicator_t indicator, int brightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPBrightness(indicator, brightness);
    return dsERR_NONE;
}

dsError_t dsGetFPBrightness(dsFPDIndicator_t indicator, int* brightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPBrightness(indicator, brightness);
    if (brightness) *brightness = 50;
    return dsERR_NONE;
}

dsError_t dsSetFPColor(dsFPDIndicator_t indicator, dsFPDColor_t color) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPColor(indicator, color);
    return dsERR_NONE;
}

dsError_t dsGetFPColor(dsFPDIndicator_t indicator, dsFPDColor_t* color) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPColor(indicator, color);
    if (color) *color = dsFPD_COLOR_BLUE;
    return dsERR_NONE;
}

dsError_t dsSetFPText(const char* text) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPText(text);
    return dsERR_NONE;
}

dsError_t dsGetFPText(char* text) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPText(text);
    if (text) strcpy(text, "");
    return dsERR_NONE;
}

dsError_t dsSetFPTextBrightness(int brightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPTextBrightness(brightness);
    return dsERR_NONE;
}

dsError_t dsGetFPTextBrightness(int* brightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPTextBrightness(brightness);
    if (brightness) *brightness = 50;
    return dsERR_NONE;
}

dsError_t dsSetFPScroll(unsigned int uScrollHoldOnDur, unsigned int uHorzScrollIterations, unsigned int uVertScrollIterations) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPScroll(uScrollHoldOnDur, uHorzScrollIterations, uVertScrollIterations);
    return dsERR_NONE;
}

dsError_t dsFPEnableCLockDisplay(int enable) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPEnableCLockDisplay(enable);
    return dsERR_NONE;
}

} // extern "C"
