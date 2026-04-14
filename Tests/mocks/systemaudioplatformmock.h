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

#pragma once

#include "systemaudioplatform.h"
#include <gmock/gmock.h>

class SystemAudioPlatformAPIMock : public ISystemAudioPlatform {
public:
    SystemAudioPlatformAPIMock() = default;
    virtual ~SystemAudioPlatformAPIMock() = default;

    MOCK_METHOD(void, systemAudioInitialize, (), (override));
    MOCK_METHOD(void, systemAudioDeinitialize, (), (override));
    MOCK_METHOD(void, systemAudioChangePrimaryVol, (MixGain gain, int volume), (override));
    MOCK_METHOD(void, systemAudioSetDetectTime, (int detectTimeMs), (override));
    MOCK_METHOD(void, systemAudioSetHoldTime, (int holdTimeMs), (override));
    MOCK_METHOD(void, systemAudioSetThreshold, (double thresHold), (override));
    MOCK_METHOD(void, systemAudioSetVolume, (GstElement * audioVolume, AudioType audioType, PlayMode playMode, int thisVol), (override));
    MOCK_METHOD(bool, systemAudioGeneratePipeline, (GstElement * *pipeline, GstElement** source, GstElement* capsfilter, GstElement** audioSink, GstElement** audioVolume, AudioType type, PlayMode mode, SourceType sourceType, bool smartVolumeEnable), (override));
};
