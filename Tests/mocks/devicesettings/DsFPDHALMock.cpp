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

dsError_t dsSetFPState(dsFPDIndicator_t indicator, dsFPDState_t state) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPState(indicator, state);
    return dsERR_NONE;
}

dsError_t dsGetFPState(dsFPDIndicator_t indicator, dsFPDState_t* state) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPState(indicator, state);
    if (state) *state = dsFPD_STATE_ON;
    return dsERR_NONE;
}

dsError_t dsSetFPBlink(dsFPDIndicator_t indicator, unsigned int uBlinkDuration, unsigned int uBlinkIterations) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPBlink(indicator, uBlinkDuration, uBlinkIterations);
    return dsERR_NONE;
}

dsError_t dsSetFPBrightness(dsFPDIndicator_t eIndicator, dsFPDBrightness_t eBrightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPBrightness(eIndicator, eBrightness);
    return dsERR_NONE;
}

dsError_t dsGetFPBrightness(dsFPDIndicator_t eIndicator, dsFPDBrightness_t* pBrightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPBrightness(eIndicator, pBrightness);
    if (pBrightness) *pBrightness = dsFPD_BRIGHTNESS_MAX;
    return dsERR_NONE;
}

dsError_t dsSetFPColor(dsFPDIndicator_t eIndicator, dsFPDColor_t eColor) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPColor(eIndicator, eColor);
    return dsERR_NONE;
}

dsError_t dsGetFPColor(dsFPDIndicator_t eIndicator, dsFPDColor_t* pColor) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPColor(eIndicator, pColor);
    if (pColor) *pColor = dsFPD_COLOR_BLUE;
    return dsERR_NONE;
}

dsError_t dsSetFPText(const char* pText) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPText(pText);
    return dsERR_NONE;
}

dsError_t dsSetFPTextBrightness(dsFPDTextDisplay_t eIndicator, dsFPDBrightness_t eBrightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPTextBrightness(eIndicator, eBrightness);
    return dsERR_NONE;
}

dsError_t dsGetFPTextBrightness(dsFPDTextDisplay_t eIndicator, dsFPDBrightness_t* eBrightness) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPTextBrightness(eIndicator, eBrightness);
    if (eBrightness) *eBrightness = dsFPD_BRIGHTNESS_MAX;
    return dsERR_NONE;
}

dsError_t dsSetFPScroll(unsigned int uScrollHoldOnDur, unsigned int uHorzScrollIterations, unsigned int uVertScrollIterations) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPScroll(uScrollHoldOnDur, uHorzScrollIterations, uVertScrollIterations);
    return dsERR_NONE;
}

dsError_t dsSetFPTime(dsFPDTimeFormat_t eTimeFormat, const unsigned int uHour, const unsigned int uMinutes) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPTime(eTimeFormat, uHour, uMinutes);
    return dsERR_NONE;
}

dsError_t dsSetFPTimeFormat(dsFPDTimeFormat_t eTimeFormat) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPTimeFormat(eTimeFormat);
    return dsERR_NONE;
}

dsError_t dsGetFPTimeFormat(dsFPDTimeFormat_t* pTimeFormat) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsGetFPTimeFormat(pTimeFormat);
    if (pTimeFormat) *pTimeFormat = dsFPD_TIME_12_HOUR;
    return dsERR_NONE;
}

dsError_t dsFPEnableCLockDisplay(int enable) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPEnableCLockDisplay(enable);
    return dsERR_NONE;
}

dsError_t dsFPGetLEDState(dsFPDLedState_t* state) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPGetLEDState(state);
    if (state) *state = dsFPD_LED_DEVICE_NONE;
    return dsERR_NONE;
}

dsError_t dsFPSetLEDState(dsFPDLedState_t state) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPSetLEDState(state);
    return dsERR_NONE;
}

dsError_t dsFPGetSupportedLEDStates(unsigned int* states) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsFPGetSupportedLEDStates(states);
    if (states) *states = 0;
    return dsERR_NONE;
}

dsError_t dsSetFPDMode(dsFPDMode_t eMode) {
    DsFPDHalMock* impl = DsFPDApi::getImpl();
    if (impl) return impl->dsSetFPDMode(eMode);
    return dsERR_NONE;
}

} // extern "C"
