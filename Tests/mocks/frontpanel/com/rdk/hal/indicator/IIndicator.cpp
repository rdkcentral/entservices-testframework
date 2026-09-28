#include <com/rdk/hal/indicator/IIndicator.h>
#include <com/rdk/hal/indicator/BpIndicator.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(Indicator, "com.rdk.hal.indicator.IIndicator")

::android::status_t IIndicator::Id::readFromParcel(const ::android::Parcel* parcel)
{
    return parcel->readInt32(&value);
}

::android::status_t IIndicator::Id::writeToParcel(::android::Parcel* parcel) const
{
    return parcel->writeInt32(value);
}

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com