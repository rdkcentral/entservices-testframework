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

#pragma once

#include <gmock/gmock.h>

extern "C" {
#include "dsError.h"
#include "dsFPD.h"
}

/**
 * @brief Mock interface for dsFPD (Front Panel Display) HAL
 */
class DsFPDHalMock {
public:
    virtual ~DsFPDHalMock() = default;

    // Initialization
    MOCK_METHOD(dsError_t, dsFPInit, ());
    MOCK_METHOD(dsError_t, dsFPTerm, ());
    
    // LED control
    MOCK_METHOD(dsError_t, dsSetFPState, (dsFPDIndicator_t eIndicator, dsFPDState_t state));
    MOCK_METHOD(dsError_t, dsGetFPState, (dsFPDIndicator_t eIndicator, dsFPDState_t* state));
    MOCK_METHOD(dsError_t, dsSetFPBlink, (dsFPDIndicator_t eIndicator, unsigned int uBlinkDuration, unsigned int uBlinkIterations));
    MOCK_METHOD(dsError_t, dsSetFPBrightness, (dsFPDIndicator_t eIndicator, dsFPDBrightness_t eBrightness));
    MOCK_METHOD(dsError_t, dsGetFPBrightness, (dsFPDIndicator_t eIndicator, dsFPDBrightness_t* pBrightness));
    MOCK_METHOD(dsError_t, dsSetFPColor, (dsFPDIndicator_t eIndicator, dsFPDColor_t eColor));
    MOCK_METHOD(dsError_t, dsGetFPColor, (dsFPDIndicator_t eIndicator, dsFPDColor_t* pColor));
    
    // Text display
    MOCK_METHOD(dsError_t, dsSetFPText, (const char* pText));
    MOCK_METHOD(dsError_t, dsSetFPTextBrightness, (dsFPDTextDisplay_t eIndicator, dsFPDBrightness_t eBrightness));
    MOCK_METHOD(dsError_t, dsGetFPTextBrightness, (dsFPDTextDisplay_t eIndicator, dsFPDBrightness_t* eBrightness));
    MOCK_METHOD(dsError_t, dsSetFPScroll, (unsigned int uScrollHoldOnDur, unsigned int uHorzScrollIterations, unsigned int uVertScrollIterations));
    
    // Time/Clock
    MOCK_METHOD(dsError_t, dsSetFPTime, (dsFPDTimeFormat_t eTimeFormat, const unsigned int uHour, const unsigned int uMinutes));
    MOCK_METHOD(dsError_t, dsSetFPTimeFormat, (dsFPDTimeFormat_t eTimeFormat));
    MOCK_METHOD(dsError_t, dsGetFPTimeFormat, (dsFPDTimeFormat_t* pTimeFormat));
    MOCK_METHOD(dsError_t, dsFPEnableCLockDisplay, (int enable));
    
    // LED State
    MOCK_METHOD(dsError_t, dsFPGetLEDState, (dsFPDLedState_t* state));
    MOCK_METHOD(dsError_t, dsFPSetLEDState, (dsFPDLedState_t state));
    MOCK_METHOD(dsError_t, dsFPGetSupportedLEDStates, (unsigned int* states));
    
    // Mode
    MOCK_METHOD(dsError_t, dsSetFPDMode, (dsFPDMode_t eMode));
};

/**
 * @brief API class for dsFPD mock
 */
class DsFPDApi {
protected:
    static DsFPDHalMock* impl;
    
public:
    DsFPDApi();
    DsFPDApi(const DsFPDApi &obj) = delete;
    virtual ~DsFPDApi();
    
    static void setImpl(DsFPDHalMock* newImpl);
    static DsFPDHalMock* getImpl();
};
