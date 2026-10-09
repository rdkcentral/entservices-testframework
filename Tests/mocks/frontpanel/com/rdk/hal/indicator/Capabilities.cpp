#include <com/rdk/hal/indicator/Capabilities.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

::android::status_t Capabilities::readFromParcel(const ::android::Parcel* parcel)
{
    ::android::status_t status = ::android::OK;
    const size_t start = parcel->dataPosition();
    int32_t parcelableSize = 0;
    status = parcel->readInt32(&parcelableSize);
    if (status != ::android::OK || parcelableSize < 4) {
        return ::android::BAD_VALUE;
    }
    if (parcel->dataPosition() - start >= static_cast<size_t>(parcelableSize)) {
        parcel->setDataPosition(start + parcelableSize);
        return status;
    }
    status = parcel->readString16Vector(&supportedStates);
    parcel->setDataPosition(start + parcelableSize);
    return status;
}

::android::status_t Capabilities::writeToParcel(::android::Parcel* parcel) const
{
    const auto start = parcel->dataPosition();
    parcel->writeInt32(0);
    const auto status = parcel->writeString16Vector(supportedStates);
    if (status != ::android::OK) {
        return status;
    }
    const auto end = parcel->dataPosition();
    parcel->setDataPosition(start);
    parcel->writeInt32(end - start);
    parcel->setDataPosition(end);
    return status;
}

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com