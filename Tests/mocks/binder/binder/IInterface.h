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

// Minimal mock of Android's <binder/IInterface.h> for host-side unit tests.
// Provides IInterface, BpInterface, interface_cast<> and the
// DECLARE_META_INTERFACE / (DO_NOT_DIRECTLY_USE_ME_)IMPLEMENT_META_INTERFACE
// macros used by the auto-generated-style frontpanel AIDL mocks.

#pragma once

#include <binder/IBinder.h>
#include <utils/RefBase.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

class IInterface : public virtual RefBase {
public:
    IInterface() = default;
    virtual ~IInterface() = default;

protected:
    virtual IBinder* onAsBinder() = 0;
};

// If this is a proxy for the requested interface, return it; otherwise build a
// proxy around the binder. The mock resolves straight to the Bp* proxy.
template <typename INTERFACE>
inline sp<INTERFACE> interface_cast(const sp<IBinder>& obj)
{
    return INTERFACE::asInterface(obj);
}

template <typename INTERFACE>
class BpInterface : public INTERFACE {
public:
    explicit BpInterface(const sp<IBinder>& remote) : m_remote(remote) {}

    const sp<IBinder>& remote() const { return m_remote; }

protected:
    IBinder* onAsBinder() override { return m_remote.get(); }

    sp<IBinder> m_remote;
};

} // namespace android

#define DECLARE_META_INTERFACE(INTERFACE)                                                        \
public:                                                                                          \
    static const ::android::String16 descriptor;                                                 \
    static ::android::sp<I##INTERFACE> asInterface(const ::android::sp<::android::IBinder>& obj); \
    virtual const ::android::String16& getInterfaceDescriptor() const;                            \
    I##INTERFACE();                                                                               \
    virtual ~I##INTERFACE();

#define DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(INTERFACE, NAME)                          \
    const ::android::String16 I##INTERFACE::descriptor(NAME);                                     \
    const ::android::String16& I##INTERFACE::getInterfaceDescriptor() const                       \
    {                                                                                             \
        return I##INTERFACE::descriptor;                                                          \
    }                                                                                             \
    ::android::sp<I##INTERFACE> I##INTERFACE::asInterface(                                        \
            const ::android::sp<::android::IBinder>& obj)                                         \
    {                                                                                             \
        ::android::sp<I##INTERFACE> intr;                                                         \
        if (obj != nullptr) {                                                                     \
            intr = ::android::sp<Bp##INTERFACE>::make(obj);                                       \
        }                                                                                         \
        return intr;                                                                              \
    }                                                                                             \
    I##INTERFACE::I##INTERFACE() {}                                                               \
    I##INTERFACE::~I##INTERFACE() {}

#define IMPLEMENT_META_INTERFACE(INTERFACE, NAME) \
    DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(INTERFACE, NAME)
