/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Minimal mock of Android's <binder/IServiceManager.h> for host-side unit
// tests. defaultServiceManager() returns a stub that hands back null binders;
// the LEDControl plugin tolerates this by reporting the indicator service as
// unavailable, which keeps the constructor path compilable and safe.

#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

class IServiceManager : public IInterface {
public:
    virtual sp<IBinder> getService(const String16& name) const = 0;
    virtual sp<IBinder> checkService(const String16& name) const = 0;
    virtual sp<IBinder> waitForService(const String16& name) = 0;
};

namespace mock_internal {

class MockServiceManager : public IServiceManager {
public:
    sp<IBinder> getService(const String16& /*name*/) const override { return sp<IBinder>(); }
    sp<IBinder> checkService(const String16& /*name*/) const override { return sp<IBinder>(); }
    sp<IBinder> waitForService(const String16& /*name*/) override { return sp<IBinder>(); }

protected:
    IBinder* onAsBinder() override { return nullptr; }
};

} // namespace mock_internal

inline sp<IServiceManager> defaultServiceManager()
{
    static sp<IServiceManager> instance = sp<mock_internal::MockServiceManager>::make();
    return instance;
}

} // namespace android
