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

#ifndef __RDK_STORAGE_MGR_H__
#define __RDK_STORAGE_MGR_H__

#define RDK_STMGR_MAX_DEVICES 10
#define RDK_STMGR_MAX_STRING_LENGTH 128
#define RDK_STMGR_PARTITION_LENGTH 256
#define RDK_STMGR_DIAGNOSTICS_LENGTH 256
#define RDK_STMGR_DIAGNOSTICS_BLOB_LENGTH 2048
#define RDK_STMGR_MAX_DIAGNOSTIC_ATTRIBUTES 20

typedef enum _stmgr_ReturnCode {
	RDK_STMGR_RETURN_SUCCESS = 0,
	RDK_STMGR_RETURN_GENERIC_FAILURE = -1,
	RDK_STMGR_RETURN_INIT_FAILURE = -2,
	RDK_STMGR_RETURN_INVALID_INPUT = -3,
	RDK_STMGR_RETURN_UNKNOWN_FAILURE = -4
} eSTMGRReturns;

typedef enum _stmgr_DeviceType {
	RDK_STMGR_DEVICE_TYPE_HDD = 0,
	RDK_STMGR_DEVICE_TYPE_SDCARD,
	RDK_STMGR_DEVICE_TYPE_USB,
	RDK_STMGR_DEVICE_TYPE_FLASH,
	RDK_STMGR_DEVICE_TYPE_NVRAM,
	RDK_STMGR_DEVICE_TYPE_EMMCCARD,
	RDK_STMGR_DEVICE_TYPE_MAX
} eSTMGRDeviceType;

typedef enum _stmgr_DeviceStatus {
	RDK_STMGR_DEVICE_STATUS_OK = 0,
	RDK_STMGR_DEVICE_STATUS_READ_ONLY = (1 << 0),
	RDK_STMGR_DEVICE_STATUS_NOT_PRESENT = (1 << 1),
	RDK_STMGR_DEVICE_STATUS_NOT_QUALIFIED = (1 << 2),
	RDK_STMGR_DEVICE_STATUS_DISK_FULL = (1 << 3),
	RDK_STMGR_DEVICE_STATUS_READ_FAILURE = (1 << 4),
	RDK_STMGR_DEVICE_STATUS_WRITE_FAILURE = (1 << 5),
	RDK_STMGR_DEVICE_STATUS_UNKNOWN = (1 << 6)
} eSTMGRDeviceStatus;

typedef enum _stmgr_TSBStatus {
	RDK_STMGR_TSB_STATUS_OK = 0,
	RDK_STMGR_TSB_STATUS_READ_ONLY = (1 << 0),
	RDK_STMGR_TSB_STATUS_NOT_PRESENT = (1 << 1),
	RDK_STMGR_TSB_STATUS_NOT_QUALIFIED = (1 << 2),
	RDK_STMGR_TSB_STATUS_DISK_FULL = (1 << 3),
	RDK_STMGR_TSB_STATUS_READ_FAILURE = (1 << 4),
	RDK_STMGR_TSB_STATUS_WRITE_FAILURE = (1 << 5),
	RDK_STMGR_TSB_STATUS_UNKNOWN = (1 << 6)
} eSTMGRTSBStatus;

typedef enum _stmgr_events {
	RDK_STMGR_EVENT_STATUS_CHANGED = 100,
	RDK_STMGR_EVENT_TSB_ERROR,
	RDK_STMGR_EVENT_HEALTH_WARNING,
	RDK_STMGR_EVENT_DEVICE_FAILURE
} eSTMGREvents;

typedef enum _stmgr_ErrorEvent {
	RDK_STMGR_TSB_WRITE_FAILURE = 100,
	RDK_STMGR_TSB_UNKNOWN_FAILURE
} eSTMGRErrorEvent;

typedef struct _stmgr_DeviceIds {
	unsigned short m_numOfDevices;
	char m_deviceIDs[RDK_STMGR_MAX_DEVICES][RDK_STMGR_MAX_STRING_LENGTH];
} eSTMGRDeviceIDs;

typedef struct _stmgr_DeviceInfo {
	char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];
	eSTMGRDeviceType m_type;
	unsigned long long m_capacity;
	eSTMGRDeviceStatus m_status;
	char m_partitions[RDK_STMGR_PARTITION_LENGTH];
	char m_manufacturer[RDK_STMGR_MAX_STRING_LENGTH];
	char m_model[RDK_STMGR_MAX_STRING_LENGTH];
	char m_serialNumber[RDK_STMGR_MAX_STRING_LENGTH];
	char m_firmwareVersion[RDK_STMGR_MAX_STRING_LENGTH];
	char m_hwVersion[RDK_STMGR_MAX_STRING_LENGTH];
	char m_ifATAstandard[RDK_STMGR_MAX_STRING_LENGTH];
	bool m_hasSMARTSupport;
} eSTMGRDeviceInfo;

typedef struct _stmgr_DeviceInfos {
	unsigned short m_numOfDevices;
	eSTMGRDeviceInfo m_devices[RDK_STMGR_MAX_DEVICES];
} eSTMGRDeviceInfoList;

typedef struct _stmgr_PartitionInfo {
	char m_partitionId[RDK_STMGR_MAX_STRING_LENGTH];
	char m_name[RDK_STMGR_MAX_STRING_LENGTH];
	char m_mountPath[RDK_STMGR_MAX_STRING_LENGTH];
	char m_format[RDK_STMGR_MAX_STRING_LENGTH];
	eSTMGRDeviceStatus m_status;
	unsigned long long m_capacity;
	unsigned long long m_freeSpace;
	bool m_isTSBSupported;
	bool m_isDVRSupported;
} eSTMGRPartitionInfo;

typedef struct _stmgr_DiagnosticsAttributes {
	char m_name[RDK_STMGR_MAX_STRING_LENGTH];
	char m_value[RDK_STMGR_MAX_STRING_LENGTH];
} eSTMGRDiagAttributes;

typedef struct _stmgr_DiagnosticsAttributeList {
	unsigned short m_numOfAttributes;
	eSTMGRDiagAttributes m_diagnostics[RDK_STMGR_MAX_DIAGNOSTIC_ATTRIBUTES];
} eSTMGRDiagAttributesList;

typedef struct _stmgr_Health {
	char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];
	eSTMGRDeviceType m_deviceType;
	bool m_isOperational;
	bool m_isHealthy;
	union {
		eSTMGRDiagAttributesList m_list;
		char m_blob[RDK_STMGR_DIAGNOSTICS_BLOB_LENGTH];
	} m_diagnostics;
	eSTMGRDiagAttributesList m_lifetimesList;
	eSTMGRDiagAttributesList m_firstExceededConfiguredLife;
	eSTMGRDiagAttributesList m_firstExceededMaxLife;
	eSTMGRDiagAttributesList m_healthStatesList;
} eSTMGRHealthInfo;

typedef struct _stmgr_EventMessage {
	eSTMGREvents m_eventType;
	char m_deviceID[RDK_STMGR_MAX_STRING_LENGTH];
	eSTMGRDeviceType m_deviceType;
	eSTMGRDeviceStatus m_deviceStatus;
	char m_description[RDK_STMGR_MAX_STRING_LENGTH];
	char m_diagnostics[RDK_STMGR_DIAGNOSTICS_LENGTH];
} eSTMGREventMessage;

typedef struct _stmgr_CallBackData {
	bool isSDCard;
	char mountPath[200];
} eSTMGRCallBackData;

typedef void (*fnSTMGR_EventCallback)(eSTMGREventMessage*);

class RdkStorageMgrApiImpl {
public:
	virtual ~RdkStorageMgrApiImpl() = default;

	virtual void rdkStorage_init() = 0;
	virtual eSTMGRReturns rdkStorage_getDeviceIds(eSTMGRDeviceIDs*) = 0;
	virtual eSTMGRReturns rdkStorage_getDeviceInfo(char*, eSTMGRDeviceInfo*) = 0;
	virtual eSTMGRReturns rdkStorage_getDeviceInfoList(eSTMGRDeviceInfoList*) = 0;
	virtual eSTMGRReturns rdkStorage_getPartitionInfo(char*, char*, eSTMGRPartitionInfo*) = 0;
	virtual eSTMGRReturns rdkStorage_getTSBStatus(eSTMGRTSBStatus*) = 0;
	virtual eSTMGRReturns rdkStorage_setTSBMaxMinutes(unsigned int) = 0;
	virtual eSTMGRReturns rdkStorage_getTSBMaxMinutes(unsigned int*) = 0;
	virtual eSTMGRReturns rdkStorage_getTSBCapacityMinutes(unsigned int*) = 0;
	virtual eSTMGRReturns rdkStorage_getTSBCapacity(unsigned long long*) = 0;
	virtual eSTMGRReturns rdkStorage_getTSBFreeSpace(unsigned long long*) = 0;
	virtual eSTMGRReturns rdkStorage_getDVRCapacity(unsigned long long*) = 0;
	virtual eSTMGRReturns rdkStorage_getDVRFreeSpace(unsigned long long*) = 0;
	virtual bool rdkStorage_isTSBEnabled() = 0;
	virtual eSTMGRReturns rdkStorage_setTSBEnabled(bool) = 0;
	virtual bool rdkStorage_isDVREnabled() = 0;
	virtual bool rdkStorage_isSDCard() = 0;
	virtual eSTMGRReturns rdkStorage_setDVREnabled(bool) = 0;
	virtual eSTMGRReturns rdkStorage_getHealth(char*, eSTMGRHealthInfo*) = 0;
	virtual eSTMGRReturns rdkStorage_RegisterEventCallback(fnSTMGR_EventCallback) = 0;
	virtual eSTMGRReturns rdkStorage_getTSBPartitionMountPath(char*) = 0;
	virtual void rdkStorage_notifyMGRAboutFailure(eSTMGRErrorEvent) = 0;
};

class RdkStorageMgrApi {
protected:
	static RdkStorageMgrApiImpl* impl;

public:
	static void setImpl(RdkStorageMgrApiImpl* newImpl);
	static void rdkStorage_init();
	static eSTMGRReturns rdkStorage_getDeviceIds(eSTMGRDeviceIDs*);
	static eSTMGRReturns rdkStorage_getDeviceInfo(char*, eSTMGRDeviceInfo*);
	static eSTMGRReturns rdkStorage_getDeviceInfoList(eSTMGRDeviceInfoList*);
	static eSTMGRReturns rdkStorage_getPartitionInfo(char*, char*, eSTMGRPartitionInfo*);
	static eSTMGRReturns rdkStorage_getTSBStatus(eSTMGRTSBStatus*);
	static eSTMGRReturns rdkStorage_setTSBMaxMinutes(unsigned int);
	static eSTMGRReturns rdkStorage_getTSBMaxMinutes(unsigned int*);
	static eSTMGRReturns rdkStorage_getTSBCapacityMinutes(unsigned int*);
	static eSTMGRReturns rdkStorage_getTSBCapacity(unsigned long long*);
	static eSTMGRReturns rdkStorage_getTSBFreeSpace(unsigned long long*);
	static eSTMGRReturns rdkStorage_getDVRCapacity(unsigned long long*);
	static eSTMGRReturns rdkStorage_getDVRFreeSpace(unsigned long long*);
	static bool rdkStorage_isTSBEnabled();
	static eSTMGRReturns rdkStorage_setTSBEnabled(bool);
	static bool rdkStorage_isDVREnabled();
	static bool rdkStorage_isSDCard();
	static eSTMGRReturns rdkStorage_setDVREnabled(bool);
	static eSTMGRReturns rdkStorage_getHealth(char*, eSTMGRHealthInfo*);
	static eSTMGRReturns rdkStorage_RegisterEventCallback(fnSTMGR_EventCallback);
	static eSTMGRReturns rdkStorage_getTSBPartitionMountPath(char*);
	static void rdkStorage_notifyMGRAboutFailure(eSTMGRErrorEvent);
};

extern void (*rdkStorage_init)();
extern eSTMGRReturns (*rdkStorage_getDeviceIds)(eSTMGRDeviceIDs*);
extern eSTMGRReturns (*rdkStorage_getDeviceInfo)(char*, eSTMGRDeviceInfo*);
extern eSTMGRReturns (*rdkStorage_getDeviceInfoList)(eSTMGRDeviceInfoList*);
extern eSTMGRReturns (*rdkStorage_getPartitionInfo)(char*, char*, eSTMGRPartitionInfo*);
extern eSTMGRReturns (*rdkStorage_getTSBStatus)(eSTMGRTSBStatus*);
extern eSTMGRReturns (*rdkStorage_setTSBMaxMinutes)(unsigned int);
extern eSTMGRReturns (*rdkStorage_getTSBMaxMinutes)(unsigned int*);
extern eSTMGRReturns (*rdkStorage_getTSBCapacityMinutes)(unsigned int*);
extern eSTMGRReturns (*rdkStorage_getTSBCapacity)(unsigned long long*);
extern eSTMGRReturns (*rdkStorage_getTSBFreeSpace)(unsigned long long*);
extern eSTMGRReturns (*rdkStorage_getDVRCapacity)(unsigned long long*);
extern eSTMGRReturns (*rdkStorage_getDVRFreeSpace)(unsigned long long*);
extern bool (*rdkStorage_isTSBEnabled)();
extern eSTMGRReturns (*rdkStorage_setTSBEnabled)(bool);
extern bool (*rdkStorage_isDVREnabled)();
extern bool (*rdkStorage_isSDCard)();
extern eSTMGRReturns (*rdkStorage_setDVREnabled)(bool);
extern eSTMGRReturns (*rdkStorage_getHealth)(char*, eSTMGRHealthInfo*);
extern eSTMGRReturns (*rdkStorage_RegisterEventCallback)(fnSTMGR_EventCallback);
extern eSTMGRReturns (*rdkStorage_getTSBPartitionMountPath)(char*);
extern void (*rdkStorage_notifyMGRAboutFailure)(eSTMGRErrorEvent);

#endif