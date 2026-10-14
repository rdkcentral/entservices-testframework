#pragma once

#include <binder/Parcel.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

class Capabilities : public ::android::Parcelable {
public:
    ::std::vector<::android::String16> supportedStates;

    ::android::Parcelable::Stability getStability() const override
    {
        return ::android::Parcelable::Stability::STABILITY_VINTF;
    }

    ::android::status_t readFromParcel(const ::android::Parcel* parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* parcel) const final;
};

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com