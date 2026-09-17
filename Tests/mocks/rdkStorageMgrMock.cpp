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

#include "rdkStorageMgr.h"

#include <gmock/gmock.h>

RdkStorageMgrApiImpl* RdkStorageMgrApi::impl = nullptr;

void RdkStorageMgrApi::setImpl(RdkStorageMgrApiImpl* newImpl)
{
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

void RdkStorageMgrApi::rdkStorage_init()
{
    EXPECT_NE(impl, nullptr);
    impl->rdkStorage_init();
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getDeviceIds(eSTMGRDeviceIDs* deviceIds)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getDeviceIds(deviceIds);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getDeviceInfo(char* deviceId, eSTMGRDeviceInfo* deviceInfo)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getDeviceInfo(deviceId, deviceInfo);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getDeviceInfoList(eSTMGRDeviceInfoList* deviceInfoList)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getDeviceInfoList(deviceInfoList);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getPartitionInfo(char* deviceId, char* partitionId, eSTMGRPartitionInfo* partitionInfo)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getPartitionInfo(deviceId, partitionId, partitionInfo);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getTSBStatus(eSTMGRTSBStatus* tsbStatus)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getTSBStatus(tsbStatus);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_setTSBMaxMinutes(unsigned int minutes)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_setTSBMaxMinutes(minutes);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getTSBMaxMinutes(unsigned int* minutes)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getTSBMaxMinutes(minutes);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getTSBCapacityMinutes(unsigned int* minutes)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getTSBCapacityMinutes(minutes);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getTSBCapacity(unsigned long long* capacity)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getTSBCapacity(capacity);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getTSBFreeSpace(unsigned long long* freeSpace)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getTSBFreeSpace(freeSpace);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getDVRCapacity(unsigned long long* capacity)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getDVRCapacity(capacity);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getDVRFreeSpace(unsigned long long* freeSpace)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getDVRFreeSpace(freeSpace);
}

bool RdkStorageMgrApi::rdkStorage_isTSBEnabled()
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_isTSBEnabled();
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_setTSBEnabled(bool isEnabled)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_setTSBEnabled(isEnabled);
}

bool RdkStorageMgrApi::rdkStorage_isDVREnabled()
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_isDVREnabled();
}

bool RdkStorageMgrApi::rdkStorage_isSDCard()
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_isSDCard();
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_setDVREnabled(bool isEnabled)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_setDVREnabled(isEnabled);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getHealth(char* deviceId, eSTMGRHealthInfo* healthInfo)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getHealth(deviceId, healthInfo);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_RegisterEventCallback(fnSTMGR_EventCallback eventCallback)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_RegisterEventCallback(eventCallback);
}

eSTMGRReturns RdkStorageMgrApi::rdkStorage_getTSBPartitionMountPath(char* mountPath)
{
    EXPECT_NE(impl, nullptr);
    return impl->rdkStorage_getTSBPartitionMountPath(mountPath);
}

void RdkStorageMgrApi::rdkStorage_notifyMGRAboutFailure(eSTMGRErrorEvent failEvent)
{
    EXPECT_NE(impl, nullptr);
    impl->rdkStorage_notifyMGRAboutFailure(failEvent);
}

void (*rdkStorage_init)() = &RdkStorageMgrApi::rdkStorage_init;
eSTMGRReturns (*rdkStorage_getDeviceIds)(eSTMGRDeviceIDs*) = &RdkStorageMgrApi::rdkStorage_getDeviceIds;
eSTMGRReturns (*rdkStorage_getDeviceInfo)(char*, eSTMGRDeviceInfo*) = &RdkStorageMgrApi::rdkStorage_getDeviceInfo;
eSTMGRReturns (*rdkStorage_getDeviceInfoList)(eSTMGRDeviceInfoList*) = &RdkStorageMgrApi::rdkStorage_getDeviceInfoList;
eSTMGRReturns (*rdkStorage_getPartitionInfo)(char*, char*, eSTMGRPartitionInfo*) = &RdkStorageMgrApi::rdkStorage_getPartitionInfo;
eSTMGRReturns (*rdkStorage_getTSBStatus)(eSTMGRTSBStatus*) = &RdkStorageMgrApi::rdkStorage_getTSBStatus;
eSTMGRReturns (*rdkStorage_setTSBMaxMinutes)(unsigned int) = &RdkStorageMgrApi::rdkStorage_setTSBMaxMinutes;
eSTMGRReturns (*rdkStorage_getTSBMaxMinutes)(unsigned int*) = &RdkStorageMgrApi::rdkStorage_getTSBMaxMinutes;
eSTMGRReturns (*rdkStorage_getTSBCapacityMinutes)(unsigned int*) = &RdkStorageMgrApi::rdkStorage_getTSBCapacityMinutes;
eSTMGRReturns (*rdkStorage_getTSBCapacity)(unsigned long long*) = &RdkStorageMgrApi::rdkStorage_getTSBCapacity;
eSTMGRReturns (*rdkStorage_getTSBFreeSpace)(unsigned long long*) = &RdkStorageMgrApi::rdkStorage_getTSBFreeSpace;
eSTMGRReturns (*rdkStorage_getDVRCapacity)(unsigned long long*) = &RdkStorageMgrApi::rdkStorage_getDVRCapacity;
eSTMGRReturns (*rdkStorage_getDVRFreeSpace)(unsigned long long*) = &RdkStorageMgrApi::rdkStorage_getDVRFreeSpace;
bool (*rdkStorage_isTSBEnabled)() = &RdkStorageMgrApi::rdkStorage_isTSBEnabled;
eSTMGRReturns (*rdkStorage_setTSBEnabled)(bool) = &RdkStorageMgrApi::rdkStorage_setTSBEnabled;
bool (*rdkStorage_isDVREnabled)() = &RdkStorageMgrApi::rdkStorage_isDVREnabled;
bool (*rdkStorage_isSDCard)() = &RdkStorageMgrApi::rdkStorage_isSDCard;
eSTMGRReturns (*rdkStorage_setDVREnabled)(bool) = &RdkStorageMgrApi::rdkStorage_setDVREnabled;
eSTMGRReturns (*rdkStorage_getHealth)(char*, eSTMGRHealthInfo*) = &RdkStorageMgrApi::rdkStorage_getHealth;
eSTMGRReturns (*rdkStorage_RegisterEventCallback)(fnSTMGR_EventCallback) = &RdkStorageMgrApi::rdkStorage_RegisterEventCallback;
eSTMGRReturns (*rdkStorage_getTSBPartitionMountPath)(char*) = &RdkStorageMgrApi::rdkStorage_getTSBPartitionMountPath;
void (*rdkStorage_notifyMGRAboutFailure)(eSTMGRErrorEvent) = &RdkStorageMgrApi::rdkStorage_notifyMGRAboutFailure;