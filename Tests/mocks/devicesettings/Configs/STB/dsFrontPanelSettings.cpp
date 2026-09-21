/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
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



#include "dsTypes.h"
#define _MAX_BRIGHTNESS 100
#define _MIN_BRIGHTNESS 0
#define _DEFAULT_LEVELS 1
#define _DEFAULT_LEVELS_US 10
#define _MAX_CYCLERATE  2
#define _MAX_HORZ_COLS  0
#define _MAX_VERT_ROWS  0
#define _MAX_HORZ_ITER  0
#define _MAX_VERT_ITER  0
#define _DEFAULT_COLOR_MODE 0
#define _MULTI_COLOR_MODE   2

#ifdef ENABLE_US_LED_CONFIG

dsFPDColorConfig_t  kFPDIndicatorColors[] = {
    {
        /*.Id = */ 5,
        /*.color = */ dsFPD_COLOR_WHITE,
    },
};

dsFPDIndicatorConfig_t kIndicators[] = {
    {
        /*.id = */              dsFPD_INDICATOR_POWER,
        /*.supportedColors = */ kFPDIndicatorColors,
        /*.maxBrightness   = */ _MAX_BRIGHTNESS,
        /*.maxCycleRate    = */ _MAX_CYCLERATE,
        /*.minBrightness   = */ _MIN_BRIGHTNESS,
        /*.levels          = */ _DEFAULT_LEVELS_US,
        /*.colorMode       = */ _DEFAULT_COLOR_MODE,
    },
};

#else

dsFPDColorConfig_t  kFPDIndicatorColors[] = {
    {
        /*.Id = */ 1,
        /*.color = */ dsFPD_COLOR_GREEN,
    },
    {
        /*.Id = */ 2,
        /*.color = */ dsFPD_COLOR_RED,
    },
    {
        /*.Id = */ 4,
        /*.color = */ dsFPD_COLOR_ORANGE,
    },
    {
        /*.Id = */ 5,
        /*.color = */ dsFPD_COLOR_WHITE,
    },
};

dsFPDIndicatorConfig_t kIndicators[] = {
    {
        /*.id = */              dsFPD_INDICATOR_POWER,
        /*.supportedColors = */ kFPDIndicatorColors,
        /*.maxBrightness   = */ _MAX_BRIGHTNESS,
        /*.maxCycleRate    = */ _MAX_CYCLERATE,
        /*.minBrightness   = */ _MIN_BRIGHTNESS,
        /*.levels          = */ _DEFAULT_LEVELS,
        /*.colorMode       = */ _MULTI_COLOR_MODE,
    },
};

#endif

/* Dummy definition to fix the compilation failure */
dsFPDTextDisplayConfig_t  kFPDTextDisplays[] = {
};

int kFPDTextDisplays_size = 0;

int kFPDIndicatorColors_size = sizeof(kFPDIndicatorColors)/sizeof(kFPDIndicatorColors[0]);

int kIndicators_size = sizeof(kIndicators)/sizeof(kIndicators[0]);

