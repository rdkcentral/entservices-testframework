#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/indicator/IIndicator.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <string>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

class IIndicatorManager : public ::android::IInterface {
public:
    DECLARE_META_INTERFACE(IndicatorManager)

    static const ::std::string& serviceName();
    virtual ::android::binder::Status getIndicatorIds(
        ::std::vector<IIndicator::Id>* result) = 0;
    virtual ::android::binder::Status getIndicator(
        const IIndicator::Id& indicatorId,
        ::android::sp<IIndicator>* result) = 0;
    virtual int32_t getInterfaceVersion() = 0;
    virtual std::string getInterfaceHash() = 0;
};

class IIndicatorManagerDefault : public IIndicatorManager {
public:
    ::android::IBinder* onAsBinder() override { return nullptr; }
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