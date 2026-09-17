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

#include <gmock/gmock.h>

#include "rdkStorageMgr.h"

class RdkStorageMgrApiImplMock : public RdkStorageMgrApiImpl {
public:
    MOCK_METHOD(void, rdkStorage_init, (), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getDeviceIds, (eSTMGRDeviceIDs*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getDeviceInfo, (char*, eSTMGRDeviceInfo*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getDeviceInfoList, (eSTMGRDeviceInfoList*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getPartitionInfo, (char*, char*, eSTMGRPartitionInfo*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getTSBStatus, (eSTMGRTSBStatus*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_setTSBMaxMinutes, (unsigned int), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getTSBMaxMinutes, (unsigned int*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getTSBCapacityMinutes, (unsigned int*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getTSBCapacity, (unsigned long long*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getTSBFreeSpace, (unsigned long long*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getDVRCapacity, (unsigned long long*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getDVRFreeSpace, (unsigned long long*), (override));
    MOCK_METHOD(bool, rdkStorage_isTSBEnabled, (), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_setTSBEnabled, (bool), (override));
    MOCK_METHOD(bool, rdkStorage_isDVREnabled, (), (override));
    MOCK_METHOD(bool, rdkStorage_isSDCard, (), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_setDVREnabled, (bool), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getHealth, (char*, eSTMGRHealthInfo*), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_RegisterEventCallback, (fnSTMGR_EventCallback), (override));
    MOCK_METHOD(eSTMGRReturns, rdkStorage_getTSBPartitionMountPath, (char*), (override));
    MOCK_METHOD(void, rdkStorage_notifyMGRAboutFailure, (eSTMGRErrorEvent), (override));
};