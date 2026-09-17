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

// GTest-controllable stand-in for the dsVideoDevice HAL (rdk-halif-device_settings).
// entservices-devicesettings links this in place of the real libds-hal so that
// FrameRate's L2 test can control DeviceSettingsVideoDeviceImpl's behavior the
// same way libusbApi/libUSBApiImplMock lets UsbMassStorage's L2 test control UsbDevice.
//
// dsGetVideoDevice/dsVideoDeviceInit/dsVideoDeviceTerm/dsSetDFC are called directly
// (link-time) by DeviceSettingsVideoDeviceImpl. dsSetFRFMode/dsGetFRFMode/
// dsGetCurrentDisplayframerate/dsSetDisplayframerate/dsRegisterFrameratePreChangeCB/
// dsRegisterFrameratePostChangeCB are resolved at runtime via dlopen("libds-hal.so.0")
// + dlsym() — this library's SONAME is set to libds-hal.so.0 so dlopen() resolves
// to this same already-loaded module and finds these same mocked symbols.

#include <gmock/gmock.h>

// dsError_t/dsVideoZoom_t must already be visible from whichever header the including
// translation unit brought in first: the real rdk-halif-device_settings dsVideoDevice.h
// (for the standalone ds-hal build) or the legacy libds "devicesettings.h" mock that
// entservices-testframework/Tests/L2Tests force-includes for every other L2 test.
// Re-including either set of headers here would redefine those types under a
// different tag name and fail to compile, so only the two callback typedefs that
// neither of those already-included headers may provide are declared locally
// (signatures per rdk-halif-device_settings/include/dsVideoDevice.h). Repeating an
// identical typedef is legal in C/C++, so this is safe even if already declared.
typedef void (*dsRegisterFrameratePreChangeCB_t)(unsigned int tSecond);
typedef void (*dsRegisterFrameratePostChangeCB_t)(unsigned int tSecond);

class DsVideoDeviceHalMock {
public:
    virtual ~DsVideoDeviceHalMock() = default;

    MOCK_METHOD(dsError_t, dsVideoDeviceInit, ());
    MOCK_METHOD(dsError_t, dsVideoDeviceTerm, ());
    MOCK_METHOD(dsError_t, dsGetVideoDevice, (int index, intptr_t* handle));
    MOCK_METHOD(dsError_t, dsSetDFC, (intptr_t handle, dsVideoZoom_t dfc));
    MOCK_METHOD(dsError_t, dsSetFRFMode, (intptr_t handle, int frfmode));
    MOCK_METHOD(dsError_t, dsGetFRFMode, (intptr_t handle, int* frfmode));
    MOCK_METHOD(dsError_t, dsGetCurrentDisplayframerate, (intptr_t handle, char* framerate));
    MOCK_METHOD(dsError_t, dsSetDisplayframerate, (intptr_t handle, char* framerate));
    MOCK_METHOD(dsError_t, dsRegisterFrameratePreChangeCB, (dsRegisterFrameratePreChangeCB_t cbFunc));
    MOCK_METHOD(dsError_t, dsRegisterFrameratePostChangeCB, (dsRegisterFrameratePostChangeCB_t cbFunc));
    MOCK_METHOD(dsError_t, dsHdmiInSelectZoomMode, (dsVideoZoom_t requestedZoomMode));

    static void setImpl(DsVideoDeviceHalMock* impl);
    static DsVideoDeviceHalMock* getImpl();
};
