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

// Minimal mock of Android's <utils/RefBase.h> for host-side unit tests.
// The mock android::sp<T> (see StrongPointer.h) uses std::shared_ptr for
// ownership, so RefBase here is only a lightweight base class kept to preserve
// the familiar class hierarchy (IBinder/IInterface derive from RefBase).

#pragma once

#include <utils/StrongPointer.h>

namespace android {

class RefBase {
public:
    virtual ~RefBase() = default;
};

} // namespace android
