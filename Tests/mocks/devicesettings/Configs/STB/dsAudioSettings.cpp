/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
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



#ifdef __cplusplus
extern "C" {
#endif


#include "dsUtl.h"
#include "dsTypes.h"

namespace  {


/*
 * Enumerate the supported configurations here.
 */
dsAudioPortType_t 	    kSupportedAudioPortTypes[] 				= { dsAUDIOPORT_TYPE_HDMI };
dsAudioEncoding_t 		kSupportedHDMIEncodings[]			= { dsAUDIO_ENC_PCM, dsAUDIO_ENC_AC3, dsAUDIO_ENC_EAC3 };
dsAudioCompression_t 	kSupportedHDMICompressions[] 		= { dsAUDIO_CMP_NONE, dsAUDIO_CMP_LIGHT, dsAUDIO_CMP_MEDIUM, dsAUDIO_CMP_HEAVY, };
dsAudioStereoMode_t 	kSupportedHDMIStereoModes[] 		= { dsAUDIO_STEREO_STEREO, dsAUDIO_STEREO_SURROUND, dsAUDIO_STEREO_PASSTHRU,dsAUDIO_STEREO_DD,dsAUDIO_STEREO_DDPLUS};
dsAudioStereoMode_t 	kSupportedHDMIStereoModes[] 		= { dsAUDIO_STEREO_STEREO, dsAUDIO_STEREO_SURROUND, dsAUDIO_STEREO_PASSTHRU };

/* 
 * Enumerate the supported Audio port types 
 */
dsAudioTypeConfig_t 	kAudioConfigs[]= {
		{
		/*.typeId = */					dsAUDIOPORT_TYPE_HDMI,
		/*.name = */					"HDMI", //HDMI
		/*.numSupportedCompressions = */dsUTL_DIM(kSupportedHDMICompressions),
		/*.compressions = */			kSupportedHDMICompressions,
		/*.numSupportedEncodings = */	dsUTL_DIM(kSupportedHDMIEncodings),
		/*.encodings = */				kSupportedHDMIEncodings,
		/*.numSupportedStereoModes = */	dsUTL_DIM(kSupportedHDMIStereoModes),
		/*.stereoModes = */				kSupportedHDMIStereoModes,
		}
};

/*
 * Enumerate the Video Ports that are connected to each Audio port.
 */
dsVideoPortPortId_t connectedVOPs[dsAUDIOPORT_TYPE_MAX][dsVIDEOPORT_TYPE_MAX] = {
		{/*VOPs connected to LR Audio */

		},
		{/*VOPs connected to HDMI Audio */
				{dsVIDEOPORT_TYPE_HDMI, 0},
		},
		{/*VOPs connected to SPDIF Audio */

		},
};

/*
 * Enumerate the Audio Ports available on the device.  
 */
dsAudioPortConfig_t kAudioPorts[] = {
		{
		/*.typeId = */ 					{dsAUDIOPORT_TYPE_HDMI, 0},
		/*.connectedVOPs = */			connectedVOPs[dsAUDIOPORT_TYPE_HDMI],
		}
};

int kAudioConfigs_size = sizeof(kAudioConfigs)/sizeof(kAudioConfigs[0]);

int kAudioPorts_size = sizeof(kAudioPorts)/sizeof(kAudioPorts[0]);

}
#ifdef __cplusplus
}
#endif




/** @} */
/** @} */
