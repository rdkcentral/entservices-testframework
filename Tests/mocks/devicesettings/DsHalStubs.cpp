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

// Stand-in for libds-hal (rdk-halif-device_settings) used when building the real
// entservices-devicesettings plugin as a test dependency. Built with SONAME
// libds-hal.so.0 so it satisfies both:
//  - link-time symbols required by dVideoDeviceImpl.h/dAudioImpl.h/dDisplayImpl.h/
//    dFPDImpl.h/dHdmiInImpl.h/dHostImpl.h/dVideoPortImpl.h (find_library(... NAMES ds-hal)), and
//  - the dlopen(RDK_DSHAL_NAME)/dlsym() runtime resolution used by dVideoDeviceImpl.h
//    for dsSetFRFMode/dsGetFRFMode/dsGetCurrentDisplayframerate/dsSetDisplayframerate/
//    dsRegisterFrameratePreChangeCB/dsRegisterFrameratePostChangeCB (dlopen resolves to
//    this same already-loaded module because the SONAME matches).
//
// Only the VideoDevice domain (what FrameRate exercises) is behaviorally controllable
// via DsVideoDeviceHalMock. All other HAL domains (Audio, Display, FPD, HdmiIn, Host,
// VideoPort) are fixed, safe no-op stubs — just enough for DeviceSettingsImp to
// construct/initialize without crashing; their actual return values are not meant to
// be asserted on by tests.

#include "DsVideoDeviceHalMock.h"

#include "dsAudio.h"
#include "dsDisplay.h"
#include "dsFPD.h"
#include "dsHost.h"
#include "dsVideoPort.h"

namespace {
DsVideoDeviceHalMock* g_dsVideoDeviceHalMockImpl = nullptr;
}

void DsVideoDeviceHalMock::setImpl(DsVideoDeviceHalMock* impl)
{
    g_dsVideoDeviceHalMockImpl = impl;
}

DsVideoDeviceHalMock* DsVideoDeviceHalMock::getImpl()
{
    return g_dsVideoDeviceHalMockImpl;
}

extern "C" {

// ---- VideoDevice: gmock-controlled (FrameRate's L2 test drives these) ----

dsError_t dsVideoDeviceInit()
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsVideoDeviceInit() : dsERR_NONE;
}

dsError_t dsVideoDeviceTerm()
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsVideoDeviceTerm() : dsERR_NONE;
}

dsError_t dsGetVideoDevice(int index, intptr_t* handle)
{
    if (g_dsVideoDeviceHalMockImpl) {
        return g_dsVideoDeviceHalMockImpl->dsGetVideoDevice(index, handle);
    }
    if (handle) { *handle = 0; }
    return dsERR_NONE;
}

dsError_t dsSetDFC(intptr_t handle, dsVideoZoom_t dfc)
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsSetDFC(handle, dfc) : dsERR_NONE;
}

dsError_t dsGetDFC(intptr_t /*handle*/, dsVideoZoom_t* dfc)
{
    if (dfc) { *dfc = dsVIDEO_ZOOM_FULL; }
    return dsERR_NONE;
}

dsError_t dsSetFRFMode(intptr_t handle, int frfmode)
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsSetFRFMode(handle, frfmode) : dsERR_NONE;
}

dsError_t dsGetFRFMode(intptr_t handle, int* frfmode)
{
    if (g_dsVideoDeviceHalMockImpl) {
        return g_dsVideoDeviceHalMockImpl->dsGetFRFMode(handle, frfmode);
    }
    if (frfmode) { *frfmode = 0; }
    return dsERR_NONE;
}

dsError_t dsGetCurrentDisplayframerate(intptr_t handle, char* framerate)
{
    if (g_dsVideoDeviceHalMockImpl) {
        return g_dsVideoDeviceHalMockImpl->dsGetCurrentDisplayframerate(handle, framerate);
    }
    if (framerate) { framerate[0] = '\0'; }
    return dsERR_NONE;
}

dsError_t dsSetDisplayframerate(intptr_t handle, char* framerate)
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsSetDisplayframerate(handle, framerate) : dsERR_NONE;
}

dsError_t dsRegisterFrameratePreChangeCB(dsRegisterFrameratePreChangeCB_t cbFunc)
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsRegisterFrameratePreChangeCB(cbFunc) : dsERR_NONE;
}

dsError_t dsRegisterFrameratePostChangeCB(dsRegisterFrameratePostChangeCB_t cbFunc)
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsRegisterFrameratePostChangeCB(cbFunc) : dsERR_NONE;
}

dsError_t dsHdmiInSelectZoomMode(dsVideoZoom_t requestedZoomMode)
{
    return g_dsVideoDeviceHalMockImpl ? g_dsVideoDeviceHalMockImpl->dsHdmiInSelectZoomMode(requestedZoomMode) : dsERR_NONE;
}

// Resolved via dlopen()/dlsym() by dVideoDeviceImpl.h — provided as safe no-ops so
// GetHDRCapabilities/GetSupportedVideoCodingFormats/GetCodecInfo/DisableHDR degrade
// to their "function not available" fallback paths instead of failing dlsym().
dsError_t dsGetHDRCapabilities(intptr_t /*handle*/, int* capabilities)
{
    if (capabilities) { *capabilities = 0; }
    return dsERR_NONE;
}

dsError_t dsGetSupportedVideoCodingFormats(intptr_t /*handle*/, unsigned int* supported_formats)
{
    if (supported_formats) { *supported_formats = 0; }
    return dsERR_NONE;
}

dsError_t dsGetVideoCodecInfo(intptr_t /*handle*/, dsVideoCodingFormat_t /*codec*/, dsVideoCodecInfo_t* info)
{
    if (info) { info->num_entries = 0; }
    return dsERR_NONE;
}

dsError_t dsForceDisableHDRSupport(intptr_t /*handle*/, bool /*disable*/)
{
    return dsERR_NONE;
}

// ---- Audio: fixed no-op stubs — not exercised by FrameRate tests ----

dsError_t dsAudioPortInit() { return dsERR_NONE; }
dsError_t dsAudioPortTerm() { return dsERR_NONE; }
dsError_t dsGetAudioPort(dsAudioPortType_t /*type*/, int /*index*/, intptr_t* handle)
{
    if (handle) { *handle = 0; }
    return dsERR_NONE;
}
dsError_t dsGetStereoMode(intptr_t /*handle*/, dsAudioStereoMode_t* /*stereoMode*/) { return dsERR_OPERATION_NOT_SUPPORTED; }
dsError_t dsSetStereoMode(intptr_t /*handle*/, dsAudioStereoMode_t /*mode*/) { return dsERR_NONE; }
dsError_t dsGetAudioLevel(intptr_t /*handle*/, float* level)
{
    if (level) { *level = 0.0f; }
    return dsERR_NONE;
}
dsError_t dsSetAudioMute(intptr_t /*handle*/, bool /*mute*/) { return dsERR_NONE; }
dsError_t dsIsAudioMute(intptr_t /*handle*/, bool* muted)
{
    if (muted) { *muted = false; }
    return dsERR_NONE;
}
dsError_t dsIsAudioPortEnabled(intptr_t /*handle*/, bool* enabled)
{
    if (enabled) { *enabled = false; }
    return dsERR_NONE;
}

// ---- Display: fixed no-op stubs ----

dsError_t dsDisplayInit() { return dsERR_NONE; }
dsError_t dsDisplayTerm() { return dsERR_NONE; }
dsError_t dsGetDisplay(dsVideoPortType_t /*vType*/, int /*index*/, intptr_t* handle)
{
    if (handle) { *handle = 0; }
    return dsERR_NONE;
}
dsError_t dsGetDisplayAspectRatio(intptr_t /*handle*/, dsVideoAspectRatio_t* /*aspectRatio*/) { return dsERR_OPERATION_NOT_SUPPORTED; }
dsError_t dsGetEDID(intptr_t /*handle*/, dsDisplayEDID_t* /*edid*/) { return dsERR_OPERATION_NOT_SUPPORTED; }
dsError_t dsRegisterDisplayEventCallback(intptr_t /*handle*/, dsDisplayEventCallback_t /*cb*/) { return dsERR_NONE; }

// ---- FPD: fixed no-op stubs ----

dsError_t dsFPInit() { return dsERR_NONE; }
dsError_t dsFPTerm() { return dsERR_NONE; }
dsError_t dsSetFPBrightness(dsFPDIndicator_t /*eIndicator*/, dsFPDBrightness_t /*eBrightness*/) { return dsERR_NONE; }
dsError_t dsGetFPBrightness(dsFPDIndicator_t /*eIndicator*/, dsFPDBrightness_t* /*pBrightness*/) { return dsERR_OPERATION_NOT_SUPPORTED; }
dsError_t dsSetFPColor(dsFPDIndicator_t /*eIndicator*/, dsFPDColor_t /*eColor*/) { return dsERR_NONE; }
dsError_t dsGetFPColor(dsFPDIndicator_t /*eIndicator*/, dsFPDColor_t* /*pColor*/) { return dsERR_OPERATION_NOT_SUPPORTED; }
dsError_t dsSetFPDMode(dsFPDMode_t /*eMode*/) { return dsERR_NONE; }

// ---- HdmiIn: fixed no-op stubs (dsHdmiInSelectZoomMode above is gmock-controlled) ----

dsError_t dsHdmiInInit() { return dsERR_NONE; }
dsError_t dsHdmiInTerm() { return dsERR_NONE; }
dsError_t dsHdmiInRegisterConnectCB(dsHdmiInConnectCB_t /*CBFunc*/) { return dsERR_NONE; }
dsError_t dsHdmiInGetNumberOfInputs(uint8_t* pNumberOfinputs)
{
    if (pNumberOfinputs) { *pNumberOfinputs = 0; }
    return dsERR_NONE;
}

// ---- Host: fixed no-op stubs ----

dsError_t dsHostInit() { return dsERR_NONE; }
dsError_t dsHostTerm() { return dsERR_NONE; }

// ---- VideoPort: fixed no-op stubs ----

dsError_t dsVideoPortInit() { return dsERR_NONE; }
dsError_t dsVideoPortTerm() { return dsERR_NONE; }
dsError_t dsIsDisplayConnected(intptr_t /*handle*/, bool* connected)
{
    if (connected) { *connected = false; }
    return dsERR_NONE;
}
dsError_t dsGetVideoPort(dsVideoPortType_t /*type*/, int /*index*/, intptr_t* handle)
{
    if (handle) { *handle = 0; }
    return dsERR_NONE;
}
dsError_t dsIsVideoPortEnabled(intptr_t /*handle*/, bool* enabled)
{
    if (enabled) { *enabled = false; }
    return dsERR_NONE;
}
dsError_t dsEnableVideoPort(intptr_t /*handle*/, bool /*enabled*/) { return dsERR_NONE; }
dsError_t dsIsVideoPortActive(intptr_t /*handle*/, bool* active)
{
    if (active) { *active = false; }
    return dsERR_NONE;
}
dsError_t dsGetResolution(intptr_t /*handle*/, dsVideoPortResolution_t* /*resolution*/) { return dsERR_OPERATION_NOT_SUPPORTED; }
dsError_t dsSetResolution(intptr_t /*handle*/, dsVideoPortResolution_t* /*resolution*/) { return dsERR_NONE; }
dsError_t dsSetPreferredColorDepth(intptr_t /*handle*/, dsDisplayColorDepth_t /*colorDepth*/) { return dsERR_NONE; }
dsError_t dsEnableHDCP(intptr_t /*handle*/, bool /*contentProtect*/, char* /*hdcpKey*/, size_t /*keySize*/) { return dsERR_NONE; }
dsError_t dsIsHDCPEnabled(intptr_t /*handle*/, bool* pContentProtected)
{
    if (pContentProtected) { *pContentProtected = false; }
    return dsERR_NONE;
}
dsError_t dsSetBackgroundColor(intptr_t /*handle*/, dsVideoBackgroundColor_t /*color*/) { return dsERR_NONE; }

} // extern "C"
