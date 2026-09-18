# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2026 RDK Management
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

# Standalone project producing a GTest-controllable stand-in for libds-hal
# (rdk-halif-device_settings), for consumers that need to build the real
# entservices-devicesettings plugin as a test dependency (see FrameRate's
# L1/L2 workflows). Invoke directly, e.g.:
#   cmake -S entservices-testframework/Tests/mocks/devicesettings -B build/ds-hal \
#         -DCMAKE_INSTALL_PREFIX=<prefix> -DCMAKE_CXX_FLAGS="-I<rdk-halif-device_settings headers>"
#   cmake --build build/ds-hal --target install
cmake_minimum_required(VERSION 3.8)
project(ds-hal CXX)

# Find GTest/GMock for mock support
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    # Try to find googletest in common locations
    find_path(GTEST_INCLUDE_DIR gmock/gmock.h
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        /usr/include
        /usr/local/include
    )
    if(GTEST_INCLUDE_DIR)
        set(GMOCK_INCLUDE_DIRS ${GTEST_INCLUDE_DIR})
    endif()
endif()

add_library(ds-hal SHARED
    DsAudioMock.cpp
    DsVideoDeviceMock.cpp
    DsVideoPortMock.cpp
    DsDisplayMock.cpp
    DsFPDMock.cpp
    DsHdmiInMock.cpp
)

target_include_directories(ds-hal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
    ${GMOCK_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

set_target_properties(ds-hal PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    # dVideoDeviceImpl.h resolves several VideoDevice symbols at runtime via
    # dlopen(RDK_DSHAL_NAME)/dlsym() where RDK_DSHAL_NAME == "libds-hal.so.0".
    # SOVERSION 0 makes CMake produce libds-hal.so -> libds-hal.so.0 (the SONAME
    # embedded in the binary) -> libds-hal.so.0.0.0, so dlopen("libds-hal.so.0")
    # resolves to this same already-linked module instead of a separate file.
    VERSION 0.0.0
    SOVERSION 0
)

install(TARGETS ds-hal DESTINATION lib)
install(FILES 
    DsAudioMock.h
    DsVideoDeviceMock.h
    DsVideoPortMock.h
    DsDisplayMock.h
    DsFPDMock.h
    DsHdmiInMock.h
    DsVideoDeviceHalMock.h 
    DESTINATION include
)
