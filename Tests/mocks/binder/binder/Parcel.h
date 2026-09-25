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

// Minimal mock of Android's <binder/Parcel.h> for host-side unit tests.
// Only the (de)serialisation primitives referenced by the frontpanel AIDL
// mocks are provided; they are stubbed to succeed without real marshalling.

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <binder/Parcelable.h>
#include <utils/Errors.h>
#include <utils/String16.h>

namespace android {

class Parcel {
public:
    Parcel() = default;

    size_t dataPosition() const { return m_position; }
    void setDataPosition(size_t position) const { m_position = position; }

    status_t readInt32(int32_t* out) const
    {
        if (out != nullptr) {
            *out = 0;
        }
        return OK;
    }
    status_t writeInt32(int32_t /*value*/) { return OK; }

    status_t readBool(bool* out) const
    {
        if (out != nullptr) {
            *out = false;
        }
        return OK;
    }
    status_t writeBool(bool /*value*/) { return OK; }

    status_t readString16(String16* /*out*/) const { return OK; }
    status_t writeString16(const String16& /*value*/) { return OK; }

    status_t readString16Vector(std::vector<String16>* out) const
    {
        if (out != nullptr) {
            out->clear();
        }
        return OK;
    }
    status_t writeString16Vector(const std::vector<String16>& /*value*/) { return OK; }

private:
    mutable size_t m_position = 0;
};

} // namespace android
