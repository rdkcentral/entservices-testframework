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

// Minimal mock of Android's <utils/String16.h> for host-side unit tests.
// The characters are stored as UTF-8 in a std::string which is sufficient for
// the equality/lookup semantics the LEDControl plugin relies on.

#pragma once

#include <cstddef>
#include <string>

namespace android {

class String16 {
public:
    String16() = default;
    String16(const char* value) : m_value(value ? value : "") {}
    String16(const char* value, size_t length) : m_value(value ? std::string(value, length) : "") {}
    explicit String16(const std::string& value) : m_value(value) {}

    String16(const String16&) = default;
    String16(String16&&) noexcept = default;
    String16& operator=(const String16&) = default;
    String16& operator=(String16&&) noexcept = default;

    bool operator==(const String16& other) const { return m_value == other.m_value; }
    bool operator!=(const String16& other) const { return m_value != other.m_value; }
    bool operator<(const String16& other) const { return m_value < other.m_value; }

    const char* c_str() const { return m_value.c_str(); }
    const char* string() const { return m_value.c_str(); }
    size_t size() const { return m_value.size(); }
    bool empty() const { return m_value.empty(); }

private:
    std::string m_value;
};

// A statically allocated variant of String16 in real Android; here it is just
// an alias so descriptor definitions that reference it keep compiling.
using StaticString16 = String16;

} // namespace android
