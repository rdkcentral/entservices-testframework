# DeviceSettings HAL Mocks

## Overview

This directory contains GMock-based mocks for the DeviceSettings HAL (Hardware Abstraction Layer). These mocks allow E2E testing with full control and verification of HAL interactions.

## Architecture

### Mock Structure

Each HAL module has its own mock:
- **DsAudioMock** - Audio HAL functions (dsAudio.h)
- **DsVideoDeviceMock** - Video Device HAL functions (dsVideoDevice.h)
- **DsVideoPortMock** - Video Port HAL functions (dsVideoPort.h) [TODO]
- **DsDisplayMock** - Display HAL functions (dsDisplay.h) [TODO]
- **DsFPDMock** - Front Panel Display HAL functions (dsFPD.h) [TODO]
- **DsHdmiInMock** - HDMI Input HAL functions (dsHdmiIn.h) [TODO]

### How It Works

1. **Mock Interface**: Each mock provides a GMock interface (e.g., `DsAudioHalMock`)
2. **API Class**: An API class manages the mock instance (e.g., `DsAudioApi`)
3. **HAL Functions**: Actual HAL functions (e.g., `dsSetStereoAuto`) delegate to the mock
4. **Dynamic Loading**: DeviceSettings uses `dlopen("libds-hal.so.0")` to load the mock library
5. **Symbol Resolution**: `dlsym()` finds the HAL functions which delegate to mocks

## Usage in Tests

### Basic Setup

```cpp
#include "DsAudioMock.h"
#include "DsVideoDeviceMock.h"

using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::DoAll;

class MyTest : public ::testing::Test {
protected:
    // Mock instances
    NiceMock<DsAudioHalMock> audioMock;
    NiceMock<DsVideoDeviceHalMock> videoDeviceMock;
    
    void SetUp() override {
        // Register mocks
        DsAudioApi::setImpl(&audioMock);
        DsVideoDeviceApi::setImpl(&videoDeviceMock);
        
        // Set up default expectations
        ON_CALL(audioMock, dsAudioPortInit())
            .WillByDefault(Return(dsERR_NONE));
        ON_CALL(audioMock, dsGetAudioPort(_, _, _))
            .WillByDefault(DoAll(SetArgPointee<2>(1), Return(dsERR_NONE)));
    }
    
    void TearDown() override {
        // Unregister mocks
        DsAudioApi::setImpl(nullptr);
        DsVideoDeviceApi::setImpl(nullptr);
    }
};
```

### E2E Test Example

```cpp
TEST_F(MyTest, TestSetStereoAuto) {
    // Arrange: Set expectations
    EXPECT_CALL(audioMock, dsSetStereoAuto(1, 1))
        .Times(1)
        .WillOnce(Return(dsERR_NONE));
    
    // Act: Call DeviceSettings API
    // This will internally call dsSetStereoAuto via dlsym
    deviceSettings->SetStereoAuto(handle, true);
    
    // Assert: Verify mock was called
    // GMock automatically verifies EXPECT_CALL
}
```

### Verifying Parameters

```cpp
TEST_F(MyTest, TestFramerateChange) {
    std::string capturedFramerate;
    
    // Capture the framerate parameter
    EXPECT_CALL(videoDeviceMock, dsSetDisplayframerate(_, _))
        .WillOnce([&](intptr_t handle, const char* framerate) {
            capturedFramerate = framerate;
            return dsERR_NONE;
        });
    
    // Act
    deviceSettings->SetDisplayFramerate("60");
    
    // Assert
    EXPECT_EQ("60", capturedFramerate);
}
```

### Simulating HAL Errors

```cpp
TEST_F(MyTest, TestHALError) {
    // Simulate HAL failure
    EXPECT_CALL(audioMock, dsSetStereoAuto(_, _))
        .WillOnce(Return(dsERR_OPERATION_FAILED));
    
    // Act & Assert
    auto result = deviceSettings->SetStereoAuto(handle, true);
    EXPECT_NE(Core::ERROR_NONE, result);
}
```

## Benefits Over Stubs

### Stubs (Old Approach)
- ❌ No verification of calls
- ❌ No parameter validation
- ❌ No E2E testing
- ❌ Can't simulate errors
- ✅ Simple implementation

### Mocks (New Approach)
- ✅ Full call verification
- ✅ Parameter validation
- ✅ E2E testing support
- ✅ Error simulation
- ✅ Behavior customization
- ✅ Test isolation

## Implementation Status

### Completed ✅
- ✅ DsAudioMock (25+ functions) - Audio port control, stereo mode, volume, mute, compression
- ✅ DsVideoDeviceMock (12+ functions) - Framerate control, HDR capabilities, FRF/DFC
- ✅ DsVideoPortMock (40+ functions) - HDCP, color depth, color space, HDR, EDID, resolution
- ✅ DsDisplayMock (6+ functions) - Display management, EDID, aspect ratio
- ✅ DsFPDMock (15+ functions) - Front panel display, LED control, text display
- ✅ DsHdmiInMock (15+ functions) - HDMI input selection, scaling, callbacks
- ✅ CMake build integration with GMock
- ✅ dlopen/dlsym support
- ✅ Complete migration from DsHalStubs.cpp

## Building

The mocks are built as part of the `libds-hal.so` library:

```bash
cmake -S entservices-testframework/Tests/mocks/devicesettings \
      -B build/ds-hal \
      -DCMAKE_INSTALL_PREFIX=/path/to/install \
      -DCMAKE_CXX_FLAGS="-I/path/to/rdk-halif-device_settings/include"
cmake --build build/ds-hal
cmake --install build/ds-hal
```

## Migration Guide

### From Stubs to Mocks

1. **Include the mock header**:
   ```cpp
   #include "DsAudioMock.h"
   ```

2. **Create mock instance**:
   ```cpp
   NiceMock<DsAudioHalMock> audioMock;
   ```

3. **Register the mock**:
   ```cpp
   DsAudioApi::setImpl(&audioMock);
   ```

4. **Set expectations**:
   ```cpp
   EXPECT_CALL(audioMock, dsSetStereoAuto(_, _))
       .WillOnce(Return(dsERR_NONE));
   ```

5. **Cleanup**:
   ```cpp
   DsAudioApi::setImpl(nullptr);
   ```

## Notes

- Mocks use GMock's `NiceMock` to avoid warnings for unexpected calls
- Default behavior returns `dsERR_NONE` for most functions
- Mocks are thread-safe via the API class
- Only one mock instance per HAL module should be active at a time
