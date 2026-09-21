/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
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
*/

/**
* @defgroup devicesettings
* @{
* @defgroup hal
* @{
**/



#include "dsTypes.h"

#ifdef __cplusplus
extern "C" {
namespace {
#endif


#define  _INTERLACED true
#define _PROGRESSIVE false

#define dsVideoPortRESOLUTION_NUMMAX 32

/* List all supported resolutions here */

dsVideoPortResolution_t kResolutionsSettings[] = {
		{   /*480i*/
			/*.name = */					"480i",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x480,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_INTERLACED,
		},
		{   /*480p*/
			/*.name = */					"480p",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x480,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*576i*/
			/*.name = */					"576i",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x576,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_INTERLACED,
		},
		{   /*576p*/
			/*.name = */					"576p",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x576,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*720p50 - Default - AutoSelect */
			/*.name = */					"720p50",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1280x720,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*720p - Default - AutoSelect */
                        /*.name = */                                    "720p",
                        /*.pixelResolution = */                 dsVIDEO_PIXELRES_1280x720,
                        /*.aspectRatio = */                             dsVIDEO_ASPECT_RATIO_16x9,
                        /*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
                        /*.frameRate = */                               dsVIDEO_FRAMERATE_59dot94,
                        /*.interlaced = */                              _PROGRESSIVE,
                },
                {   /*1080i25/1080i50 - Default - AutoSelect */
			/*.name = */					"1080i25",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_INTERLACED,
		},
	        {   /*1080i60 - Default - AutoSelect */
                        /*.name = */                                    "1080i",
                        /*.pixelResolution = */                 dsVIDEO_PIXELRES_1920x1080,
                        /*.aspectRatio = */                             dsVIDEO_ASPECT_RATIO_16x9,
                        /*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
                        /*.frameRate = */                               dsVIDEO_FRAMERATE_59dot94,
                        /*.interlaced = */                              _INTERLACED,
                },
                {       /*1080p24*/
                        /*.name = */                                    "1080p24",
                        /*.pixelResolution = */                 dsVIDEO_PIXELRES_1920x1080,
                        /*.aspectRatio = */                     dsVIDEO_ASPECT_RATIO_16x9,
                        /*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
                        /*.frameRate = */                               dsVIDEO_FRAMERATE_23dot98,
                        /*.interlaced = */                              _PROGRESSIVE,
                },
                {       /*1080p25*/
                        /*.name = */                                    "1080p25",
                        /*.pixelResolution = */                 dsVIDEO_PIXELRES_1920x1080,
                        /*.aspectRatio = */                     dsVIDEO_ASPECT_RATIO_16x9,
                        /*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
                        /*.frameRate = */                               dsVIDEO_FRAMERATE_25,
                        /*.interlaced = */                              _PROGRESSIVE,
                },
		{   /*1080p30*/
			/*.name = */					"1080p30",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_30,
			/*.interlaced = */				_PROGRESSIVE,
		},
	        {   /*1080p50 - Default - AutoSelect */
			/*.name = */					"1080p50",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*1080p60*/
			/*.name = */					"1080p60",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{       /*2160p24*/
				/*.name = */                                    "2160p24",
				/*.pixelResolution = */                 dsVIDEO_PIXELRES_3840x2160,
				/*.aspectRatio = */                     dsVIDEO_ASPECT_RATIO_16x9,
				/*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
				/*.frameRate = */                               dsVIDEO_FRAMERATE_23dot98,
				/*.interlaced = */                              _PROGRESSIVE,
		},
		{       /*2160p25*/
				/*.name = */                                    "2160p25",
				/*.pixelResolution = */                 dsVIDEO_PIXELRES_3840x2160,
				/*.aspectRatio = */                     dsVIDEO_ASPECT_RATIO_16x9,
				/*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
				/*.frameRate = */                               dsVIDEO_FRAMERATE_25,
				/*.interlaced = */                              _PROGRESSIVE,
		},
		{	/*2160p30*/
			/*.name = */					"2160p30",
			/*.pixelResolution = */ 		dsVIDEO_PIXELRES_3840x2160,
			/*.aspectRatio = */ 			dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_30,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{	/*2160p50*/
			/*.name = */					"2160p50",
			/*.pixelResolution = */ 		dsVIDEO_PIXELRES_3840x2160,
			/*.aspectRatio = */ 			dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{	/*2160p60*/
			/*.name = */					"2160p60",
			/*.pixelResolution = */ 		dsVIDEO_PIXELRES_3840x2160,
			/*.aspectRatio = */ 			dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_PROGRESSIVE,
		},
};
#if defined(ENABLE_US_RESOLUTION)
int kDefaultResIndex = 5; //Pick one resolution from kResolutionsSettings[] as default
#endif
#if defined(ENABLE_EU_RESOLUTION)
int kDefaultResIndex = 11; //Pick one resolution from kResolutionsSettings[] as default
#endif
#if defined(ENABLE_FLEX2_RESOLUTION)
int kDefaultResIndex = 12; //Pick one resolution from kResolutionsSettings[] as default
#endif

int kResolutionsSettings_size = sizeof(kResolutionsSettings)/sizeof(kResolutionsSettings[0]);

#ifdef __cplusplus
}
}
#endif



/** @} */
/** @} */
