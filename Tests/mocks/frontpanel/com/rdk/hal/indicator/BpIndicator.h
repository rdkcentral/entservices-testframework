#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/indicator/IIndicator.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

class BpIndicator : public ::android::BpInterface<IIndicator> {
public:
    explicit BpIndicator(const ::android::sp<::android::IBinder>& binder)
        : ::android::BpInterface<IIndicator>(binder)
    {
    }

    ::android::binder::Status getCapabilities(Capabilities* result) override
    {
        auto* local = static_cast<IIndicator*>(m_remote->queryLocalInterface(IIndicator::descriptor));
        if (local != nullptr) {
            return local->getCapabilities(result);
        }
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    ::android::binder::Status set(const ::android::String16& state, bool* result) override
    {
        auto* local = static_cast<IIndicator*>(m_remote->queryLocalInterface(IIndicator::descriptor));
        if (local != nullptr) {
            return local->set(state, result);
        }
        return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
    }
    ::android::binder::Status get(::android::String16* result) override
    {
        auto* local = static_cast<IIndicator*>(m_remote->queryLocalInterface(IIndicator::descriptor));
        if (local != nullptr) {
            return local->get(result);
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