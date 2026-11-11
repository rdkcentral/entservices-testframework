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

// Minimal mock of Android's <utils/StrongPointer.h> for host-side unit tests.
// android::sp<T> is backed by std::shared_ptr so lifetime and polymorphic
// deletion behave correctly without pulling in the real libutils RefBase.

#pragma once

#include <cstddef>
#include <memory>
#include <utility>

namespace android {

template <typename T>
class sp {
public:
    sp() = default;
    sp(std::nullptr_t) {}
    explicit sp(T* other) : m_ptr(other) {}

    sp(const sp& other) = default;
    sp(sp&& other) noexcept = default;
    sp& operator=(const sp& other) = default;
    sp& operator=(sp&& other) noexcept = default;

    template <typename U>
    sp(const sp<U>& other) : m_ptr(other.m_ptr) {}
    template <typename U>
    sp(sp<U>&& other) noexcept : m_ptr(std::move(other.m_ptr)) {}

    template <typename U>
    sp& operator=(const sp<U>& other) { m_ptr = other.m_ptr; return *this; }

    sp& operator=(std::nullptr_t) { m_ptr.reset(); return *this; }

    T* operator->() const { return m_ptr.get(); }
    T& operator*() const { return *m_ptr; }
    T* get() const { return m_ptr.get(); }

    void clear() { m_ptr.reset(); }

    explicit operator bool() const { return static_cast<bool>(m_ptr); }

    // Construct the pointed-to object in place, mirroring android::sp<T>::make().
    template <typename... Args>
    static sp<T> make(Args&&... args)
    {
        sp<T> result;
        result.m_ptr = std::make_shared<T>(std::forward<Args>(args)...);
        return result;
    }

    bool operator==(std::nullptr_t) const { return m_ptr == nullptr; }
    bool operator!=(std::nullptr_t) const { return m_ptr != nullptr; }

    template <typename U>
    bool operator==(const sp<U>& other) const { return get() == other.get(); }
    template <typename U>
    bool operator!=(const sp<U>& other) const { return get() != other.get(); }

private:
    template <typename U> friend class sp;
    std::shared_ptr<T> m_ptr;
};

template <typename T>
inline bool operator==(std::nullptr_t, const sp<T>& rhs) { return rhs == nullptr; }
template <typename T>
inline bool operator!=(std::nullptr_t, const sp<T>& rhs) { return rhs != nullptr; }

} // namespace android
