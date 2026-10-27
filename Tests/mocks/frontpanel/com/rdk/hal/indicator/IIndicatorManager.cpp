#include <com/rdk/hal/indicator/IIndicatorManager.h>
#include <com/rdk/hal/indicator/BpIndicatorManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(IndicatorManager, "com.rdk.hal.indicator.IIndicatorManager")

const ::std::string& IIndicatorManager::serviceName()
{
    static const ::std::string value("indicator");
    return value;
}

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com