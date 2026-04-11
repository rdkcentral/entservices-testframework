/* If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2023 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

#include <string>
#include <sstream>

#include "Module.h"
#include "L2Tests.h"
#include <interfaces/IL2Test.h>

#define API_VERSION_NUMBER_MAJOR 1
#define API_VERSION_NUMBER_MINOR 0
#define API_VERSION_NUMBER_PATCH 0
#define TEST_LOG(x, ...)                                                                                                                                        \
    fprintf(stderr, "\033[v_secure_system1;32m[%s:%d](%s)<PID:%d><TID:%d>" x "\n\033[0m", __FILE__, __LINE__, __FUNCTION__, getpid(), gettid(), ##__VA_ARGS__); \
    fflush(stderr);

// Declare __gcov_flush as weak symbol so we can call it when coverage is enabled
// without causing linking errors when coverage is disabled
#ifdef __GNUC__
extern "C" void __gcov_flush(void) __attribute__((weak));
#endif

using namespace WPEFramework;

namespace WPEFramework {
namespace Plugin {

SERVICE_REGISTRATION(L2Tests, API_VERSION_NUMBER_MAJOR, API_VERSION_NUMBER_MINOR, API_VERSION_NUMBER_PATCH);

L2Tests::L2Tests()
{
    ::testing::InitGoogleTest();
}

L2Tests::~L2Tests()
{
    TEST_LOG("L2 test plugin is terminating\n");
}

const string L2Tests::Initialize(PluginHost::IShell* /* service */)
{
    return string();
}

void L2Tests::Deinitialize(PluginHost::IShell* /* service */)
{
}

Core::hresult L2Tests::PerformL2Tests(const string& parameters, string& response)
{
    // Optionally parse parameters (e.g., as JSON) to set gtest filter
    // Example: {"test_suite_list":"MySuite.*"}
    if (!parameters.empty()) {
        // Simple JSON parsing for "test_suite_list"
        size_t keyPos = parameters.find("\"test_suite_list\"");
        if (keyPos != std::string::npos) {
            size_t colonPos = parameters.find(":", keyPos);
            size_t quotePos1 = parameters.find("\"", colonPos + 1);
            size_t quotePos2 = parameters.find("\"", quotePos1 + 1);
            if (quotePos1 != std::string::npos && quotePos2 != std::string::npos) {
                std::string filter = parameters.substr(quotePos1 + 1, quotePos2 - quotePos1 - 1);
                ::testing::GTEST_FLAG(filter) = filter;
                TEST_LOG("Parameters passed for gtest filter: %s\n", filter.c_str());
            }
        }
    }

    int status = RUN_ALL_TESTS();
    TEST_LOG("Completed running L2 tests and running status = %d\n", status);

    // Flush gcov coverage data immediately after tests complete, before Thunder shutdown
    // This ensures coverage data is written even if Thunder crashes during cleanup
    #ifdef __GNUC__
    if (__gcov_flush) {
        __gcov_flush();
        TEST_LOG("Coverage data flushed from Thunder process\n");
    }
    #endif

    // Optionally, return status as a JSON string
    std::ostringstream oss;
    oss << "{\"status\":" << status << "}";
    response = oss.str();

    return (status == 0) ? Core::ERROR_NONE : Core::ERROR_GENERAL;
}

} // namespace Plugin
} // namespace WPEFramework