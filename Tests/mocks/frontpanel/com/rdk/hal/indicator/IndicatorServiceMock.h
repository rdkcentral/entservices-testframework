#pragma once

#include <binder/IBinder.h>
#include <binder/Status.h>
#include <com/rdk/hal/indicator/IIndicatorManager.h>
#include <com/rdk/hal/indicator/IIndicator.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {

class IndicatorMock : public IIndicator {
public:
    ::android::binder::Status getCapabilities(Capabilities* result) override;
    ::android::binder::Status set(const ::android::String16& state, bool* result) override;
    ::android::binder::Status get(::android::String16* result) override;
    int32_t getInterfaceVersion() override { return 1; }
    std::string getInterfaceHash() override { return {}; }

protected:
    ::android::IBinder* onAsBinder() override { return nullptr; }
};

class IndicatorManagerMock : public IIndicatorManager {
public:
    IndicatorManagerMock();

    ::android::binder::Status getIndicatorIds(std::vector<IIndicator::Id>* result) override;
    ::android::binder::Status getIndicator(const IIndicator::Id& id, ::android::sp<IIndicator>* result) override;
    int32_t getInterfaceVersion() override { return 1; }
    std::string getInterfaceHash() override { return {}; }

private:
    ::android::sp<IndicatorMock> _indicator;

protected:
    ::android::IBinder* onAsBinder() override { return nullptr; }
};

class IndicatorManagerBinder : public ::android::IBinder {
public:
    explicit IndicatorManagerBinder(const ::android::sp<IndicatorManagerMock>& manager)
        : _manager(manager)
    {
    }

    void* queryLocalInterface(const ::android::String16& descriptor) const override
    {
        return (descriptor == IIndicatorManager::descriptor) ? _manager.get() : nullptr;
    }

private:
    ::android::sp<IndicatorManagerMock> _manager;
};

} // namespace indicator
} // namespace hal
} // namespace rdk
} // namespace com