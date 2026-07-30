/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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

// File: mock_civetweb_control.h
//
// Test-only control surface for the civetweb_lite stub (civetweb_lite.cpp).
//
// By default the stub reports connection failure so plugin code stays in its
// offline/queued paths. Tests that need to exercise the connected code path
// (e.g. delivery of a broker NotifyMessage through the real LinchpinService)
// can opt in with EnableConnection(true) and then inject server frames.
//
// These symbols live in the same translation unit as the mg_* stubs, i.e. in
// the plugin's LinchpinWebSocketClient object that is built into the plugin
// under L2/L1 test builds. They are intended for use only from an in-process
// test (not the L2_TEST_OOP_RPC mode).

#ifndef MOCK_CIVETWEB_CONTROL_H
#define MOCK_CIVETWEB_CONTROL_H

#include <string>

namespace MockCivetWeb {

// Enable/disable the connected-state simulation. When enabled, the websocket
// connect stubs return a live fake connection and subscribe/publish requests
// are auto-acknowledged with a success ListenAck. Default: disabled.
void EnableConnection(bool enable);

// Disable the simulation and forget all registered fake connections. Call at
// the start of a test; do not call while a connection is still open, as the
// owning fake handle is freed later via mg_close_connection during teardown.
void Reset();

// Deliver 'message' to every live fake connection's data handler as a websocket
// TEXT frame, as if it had arrived from the broker. Returns the number of
// connections the message was delivered to.
int InjectServerMessage(const std::string& message);

} // namespace MockCivetWeb

#endif // MOCK_CIVETWEB_CONTROL_H
