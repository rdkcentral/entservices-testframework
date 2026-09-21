/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2022 Sky UK
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

/**
* @defgroup devicesettings
* @{
* @defgroup hal
* @{
**/



#include "dsTypes.h"
#include "dsUtl.h"
#include "dsVideoResolutionSettings.h"

#ifdef __cplusplus
extern "C" {
#endif


namespace {
/*
 * Enumerate the supported configurations here.
 */
dsVideoPortType_t kSupportedPortTypes[] = { dsVIDEOPORT_TYPE_HDMI };

/* 
 * Enumerate all configuarations for each port type. 
 */
 dsVideoPortTypeConfig_t kVideoPortConfigs[]= {
		{
		/*.typeId = */					dsVIDEOPORT_TYPE_HDMI,
		/*.name = */ 					"HDMI",
		/*.dtcpSupported = */			false,
		/*.hdcpSupported = */			true,
		/*.restrictedResollution = */	-1,
		/*.numSupportedResolutions = */ dsUTL_DIM(kResolutionsSettings), // 0 means "Info available at runtime"
		/*.supportedResolutons = */     kResolutionsSettings,
		},
};

/*
 *  Enumerate all enabled Video Output Ports here.
 */
 dsVideoPortPortConfig_t kVideoPortPorts[] = {
		{
		/*.typeId = */ 					{dsVIDEOPORT_TYPE_HDMI, 0},
		/*.connectedAOP */              {dsAUDIOPORT_TYPE_HDMI, 0},
#if defined(ENABLE_US_RESOLUTION)
		/*.defaultResolution = */		"720p"
#elif defined(ENABLE_FLEX2_RESOLUTION) 
               /*.defaultResolution = */                "1080p60"
#else
              /*.defaultResolution = */                 "1080p50"
#endif
		},
};

int kVideoPortConfigs_size = sizeof(kVideoPortConfigs)/sizeof(kVideoPortConfigs[0]);

int kVideoPortPorts_size = sizeof(kVideoPortPorts)/sizeof(kVideoPortPorts[0]);

}

#ifdef __cplusplus
}
#endif




/** @} */
/** @} */
