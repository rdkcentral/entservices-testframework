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

// Minimal mock of Android's <binder/Status.h> for host-side unit tests.

#pragma once

#include <cstdint>
#include <string>

#include <binder/Parcel.h>
#include <utils/Errors.h>

namespace android {
namespace binder {

class Status {
public:
    enum Exception {
        EX_NONE                 = 0,
        EX_ILLEGAL_ARGUMENT     = -3,
        EX_ILLEGAL_STATE        = -5,
        EX_SERVICE_SPECIFIC     = -8,
        EX_TRANSACTION_FAILED   = -129,
    };

    Status() = default;

    static Status ok() { return Status(); }

    static Status fromStatusT(status_t status)
    {
        Status result;
        result.m_errorCode = status;
        return result;
    }

    static Status fromExceptionCode(int32_t exceptionCode)
    {
        Status result;
        result.m_exceptionCode = exceptionCode;
        return result;
    }

    static Status fromServiceSpecificError(int32_t serviceSpecificErrorCode)
    {
        Status result;
        result.m_exceptionCode = EX_SERVICE_SPECIFIC;
        result.m_errorCode = serviceSpecificErrorCode;
        return result;
    }

    bool isOk() const { return m_exceptionCode == EX_NONE && m_errorCode == OK; }
    int32_t exceptionCode() const { return m_exceptionCode; }
    status_t transactionError() const { return m_errorCode; }
    int32_t serviceSpecificErrorCode() const { return m_errorCode; }

private:
    int32_t  m_exceptionCode = EX_NONE;
    status_t m_errorCode = OK;
};

} // namespace binder
} // namespace android
