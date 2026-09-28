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

// Minimal mock of Android's <binder/Parcelable.h> for host-side unit tests.

#pragma once

#include <cstdint>

#include <utils/Errors.h>

namespace android {

class Parcel;

class Parcelable {
public:
    enum Stability : int32_t {
        STABILITY_LOCAL = 0,
        STABILITY_VINTF = 1,
    };

    virtual ~Parcelable() = default;

    virtual status_t writeToParcel(Parcel* parcel) const = 0;
    virtual status_t readFromParcel(const Parcel* parcel) = 0;

    virtual Stability getStability() const { return STABILITY_LOCAL; }
};

} // namespace android
