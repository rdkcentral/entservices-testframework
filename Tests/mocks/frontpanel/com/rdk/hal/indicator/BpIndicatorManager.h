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

    ::android::binder::Status getIndicatorIds(::std::vector<IIndicator::Id>* result) override
    {
        auto* local = static_cast<IIndicatorManager*>(m_remote->queryLocalInterface(IIndicatorManager::descriptor));
        if (local != nullptr) {
            return local->getIndicatorIds(result);
        }
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    ::android::binder::Status getIndicator(const IIndicator::Id& id, ::android::sp<IIndicator>* result) override
    {
        auto* local = static_cast<IIndicatorManager*>(m_remote->queryLocalInterface(IIndicatorManager::descriptor));
        if (local != nullptr) {
            return local->getIndicator(id, result);
        }
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    int32_t getInterfaceVersion() override { return 0; }
    std::string getInterfaceHash() override { return {}; }
};

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com