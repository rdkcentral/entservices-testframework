#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/indicator/Capabilities.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <cstdint>
#include <string>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

class IIndicator : public ::android::IInterface {
public:
    DECLARE_META_INTERFACE(Indicator)

    class Id : public ::android::Parcelable {
    public:
        int32_t value = 0;

        ::android::Parcelable::Stability getStability() const override
        {
            return ::android::Parcelable::Stability::STABILITY_VINTF;
        }

        ::android::status_t readFromParcel(const ::android::Parcel* parcel) final;
        ::android::status_t writeToParcel(::android::Parcel* parcel) const final;
    };

    virtual ::android::binder::Status getCapabilities(Capabilities* result) = 0;
    virtual ::android::binder::Status set(const ::android::String16& state, bool* result) = 0;
    virtual ::android::binder::Status get(::android::String16* result) = 0;
    virtual int32_t getInterfaceVersion() = 0;
    virtual std::string getInterfaceHash() = 0;
};

class IIndicatorDefault : public IIndicator {
public:
    ::android::IBinder* onAsBinder() override { return nullptr; }
    ::android::binder::Status getCapabilities(Capabilities*) override
    {
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    ::android::binder::Status set(const ::android::String16&, bool*) override
    {
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    ::android::binder::Status get(::android::String16*) override
    {
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    int32_t getInterfaceVersion() override { return 0; }
    std::string getInterfaceHash() override { return {}; }
};

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com