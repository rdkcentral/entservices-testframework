/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Stub header for systimerifc/itimermsg.h
 * Required when ENABLE_SYSTIMEMGR_SUPPORT is defined in test builds
 * where the real systimemgr package is not installed.
 */
#pragma once

#ifndef IARM_BUS_SYSTIME_MGR_NAME
#define IARM_BUS_SYSTIME_MGR_NAME    "SYSTEMTIME"
#endif

#ifndef TIMER_STATUS_MSG
#define TIMER_STATUS_MSG             "TimerStatus"
#endif

#ifndef cTIMER_STATUS_UPDATE
#define cTIMER_STATUS_UPDATE         0
#endif

#ifndef cTIMER_STATUS_MESSAGE_LENGTH
#define cTIMER_STATUS_MESSAGE_LENGTH 256
#endif

typedef struct {
    char message[cTIMER_STATUS_MESSAGE_LENGTH];
    char timerSrc[cTIMER_STATUS_MESSAGE_LENGTH];
    char currentTime[cTIMER_STATUS_MESSAGE_LENGTH];
} TimerMsg;
