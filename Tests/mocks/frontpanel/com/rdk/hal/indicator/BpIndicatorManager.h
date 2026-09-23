#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/indicator/IIndicatorManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

class BpIndicatorManager : public ::android::BpInterface<IIndicatorManager> {
public:
    explicit BpIndicatorManager(const ::android::sp<::android::IBinder>& binder)
        : ::android::BpInterface<IIndicatorManager>(binder)
    {
    }

    ::android::binder::Status getIndicatorIds(::std::vector<IIndicator::Id>*) override
    {
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    ::android::binder::Status getIndicator(const IIndicator::Id&, ::android::sp<IIndicator>*) override
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