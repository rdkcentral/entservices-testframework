#include "frontpanel/com/rdk/hal/indicator/IndicatorServiceMock.h"

#include <dsFPD.h>

namespace {

const char* aidlState(const dsFPDLedState_t state)
{
    switch (state) {
    case dsFPD_LED_DEVICE_ACTIVE: return "ACTIVE";
    case dsFPD_LED_DEVICE_STANDBY: return "STANDBY";
    case dsFPD_LED_DEVICE_WPS_CONNECTING: return "WPS_CONNECTING";
    case dsFPD_LED_DEVICE_WPS_CONNECTED: return "WPS_CONNECTED";
    case dsFPD_LED_DEVICE_WPS_ERROR: return "WPS_ERROR";
    case dsFPD_LED_DEVICE_FACTORY_RESET: return "FULL_SYSTEM_RESET";
    case dsFPD_LED_DEVICE_USB_UPGRADE: return "USB_UPGRADE";
    case dsFPD_LED_DEVICE_SOFTWARE_DOWNLOAD_ERROR: return "SOFTWARE_DOWNLOAD_ERROR";
    case dsFPD_LED_DEVICE_NONE: return "NONE";
    default: return nullptr;
    }
}

bool dsState(const ::android::String16& state, dsFPDLedState_t& result)
{
    struct StateEntry {
        const char* name;
        dsFPDLedState_t state;
    };
    constexpr StateEntry entries[] = {
        { "ACTIVE", dsFPD_LED_DEVICE_ACTIVE },
        { "STANDBY", dsFPD_LED_DEVICE_STANDBY },
        { "WPS_CONNECTING", dsFPD_LED_DEVICE_WPS_CONNECTING },
        { "WPS_CONNECTED", dsFPD_LED_DEVICE_WPS_CONNECTED },
        { "WPS_ERROR", dsFPD_LED_DEVICE_WPS_ERROR },
        { "FULL_SYSTEM_RESET", dsFPD_LED_DEVICE_FACTORY_RESET },
        { "USB_UPGRADE", dsFPD_LED_DEVICE_USB_UPGRADE },
        { "SOFTWARE_DOWNLOAD_ERROR", dsFPD_LED_DEVICE_SOFTWARE_DOWNLOAD_ERROR }
    };
    for (const auto& entry : entries) {
        if (state == ::android::String16(entry.name)) {
            result = entry.state;
            return true;
        }
    }
    return false;
}

::android::binder::Status dsStatus(const dsError_t status)
{
    return (status == dsERR_NONE)
        ? ::android::binder::Status::ok()
        : ::android::binder::Status::fromServiceSpecificError(static_cast<int32_t>(status));
}

} // namespace

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

::android::binder::Status IndicatorMock::getCapabilities(Capabilities* result)
{
    unsigned int supported = 0;
    dsError_t status = dsERR_GENERAL;
    try {
        status = dsFPGetSupportedLEDStates(&supported);
    } catch (...) {
        return ::android::binder::Status::fromServiceSpecificError(dsERR_GENERAL);
    }
    if (status != dsERR_NONE) {
        return dsStatus(status);
    }

    const dsFPDLedState_t states[] = {
        dsFPD_LED_DEVICE_ACTIVE,
        dsFPD_LED_DEVICE_STANDBY,
        dsFPD_LED_DEVICE_WPS_CONNECTING,
        dsFPD_LED_DEVICE_WPS_CONNECTED,
        dsFPD_LED_DEVICE_WPS_ERROR,
        dsFPD_LED_DEVICE_FACTORY_RESET,
        dsFPD_LED_DEVICE_USB_UPGRADE,
        dsFPD_LED_DEVICE_SOFTWARE_DOWNLOAD_ERROR
    };
    for (const auto state : states) {
        if ((supported & (1u << state)) != 0) {
            result->supportedStates.emplace_back(aidlState(state));
        }
    }
    return ::android::binder::Status::ok();
}

::android::binder::Status IndicatorMock::set(const ::android::String16& state, bool* result)
{
    dsFPDLedState_t dsStateValue;
    if (!dsState(state, dsStateValue)) {
        *result = false;
        return ::android::binder::Status::fromServiceSpecificError(android::BAD_VALUE);
    }

    dsError_t status = dsERR_GENERAL;
    try {
        status = dsFPSetLEDState(dsStateValue);
    } catch (...) {
        *result = false;
        return ::android::binder::Status::fromServiceSpecificError(dsERR_GENERAL);
    }
    *result = (status == dsERR_NONE);
    return dsStatus(status);
}

::android::binder::Status IndicatorMock::get(::android::String16* result)
{
    dsFPDLedState_t state = dsFPD_LED_DEVICE_NONE;
    dsError_t status = dsERR_GENERAL;
    try {
        status = dsFPGetLEDState(&state);
    } catch (...) {
        return ::android::binder::Status::fromServiceSpecificError(dsERR_GENERAL);
    }
    if (status != dsERR_NONE) {
        return dsStatus(status);
    }

    const char* name = aidlState(state);
    if (name == nullptr) {
        *result = ::android::String16("UNSUPPORTED");
        return ::android::binder::Status::ok();
    }
    *result = ::android::String16(name);
    return ::android::binder::Status::ok();
}

IndicatorManagerMock::IndicatorManagerMock()
    : _indicator(::android::sp<IndicatorMock>::make())
{
}

::android::binder::Status IndicatorManagerMock::getIndicatorIds(std::vector<IIndicator::Id>* result)
{
    IIndicator::Id id;
    id.value = 0;
    result->push_back(id);
    return ::android::binder::Status::ok();
}

::android::binder::Status IndicatorManagerMock::getIndicator(const IIndicator::Id& id, ::android::sp<IIndicator>* result)
{
    if (id.value != 0) {
        return ::android::binder::Status::fromServiceSpecificError(android::BAD_VALUE);
    }
    *result = _indicator;
    return ::android::binder::Status::ok();
}

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com

namespace android {
namespace mock_internal {

sp<IBinder> indicatorService()
{
    static sp<com::rdk::hal::indicator::IndicatorManagerMock> manager =
        sp<com::rdk::hal::indicator::IndicatorManagerMock>::make();
    static sp<IBinder> binder = sp<com::rdk::hal::indicator::IndicatorManagerBinder>::make(manager);
    return binder;
}

} // namespace mock_internal
} // namespace android