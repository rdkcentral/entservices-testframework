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

/**
 * @file civetweb_lite.cpp
 *
 * Stub implementations of the mg_* functions used by CivetWebWSClient.cpp.
 *
 * These stubs are compiled into the LinchpinWebSocketClient OBJECT target
 * when building with RDK_SERVICES_L1_TEST=ON, replacing the real civetweb_lite
 * shared library so that WPEFrameworkLinchpinClientProxyImplementation.so can be
 * built and linked without the real civetweb_lite being present.
 *
 * All stubs are no-ops or return safe sentinel values.  Tests exercise the
 * LinchpinClientProxy plugin through the LinchpinService mock (LinchpinService.h /
 * LinchpinServiceMock.h) which operates at a higher level than these C-API
 * symbols, so no behavioural expectations are placed on them.
 */

#include "as_civetweb.h"
#include "mock_civetweb_control.h"

#include <chrono>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

/* -------------------------------------------------------------------------
 * Connected-state simulation (opt-in, see mock_civetweb_control.h)
 *
 * Default behaviour is unchanged: the connect stubs report failure so plugin
 * code stays offline. When a test calls MockCivetWeb::EnableConnection(true),
 * the connect stubs hand back a live fake connection, outgoing subscribe /
 * publish requests are auto-acknowledged, and MockCivetWeb::InjectServerMessage
 * can push broker frames into the registered data handler.
 * ---------------------------------------------------------------------- */
namespace {

struct FakeConnection {
    struct mg_connection*      handle;
    mg_websocket_data_handler  dataFunc;
    mg_websocket_close_handler closeFunc;
    void*                      userData;
};

std::mutex                  g_mockMutex;
bool                        g_connectionEnabled = false;
std::vector<FakeConnection> g_connections;

// Minimal string-value extractor for the controlled JSON the plugin emits, e.g.
// {"operation":"subscribe","requestId":"<uuid>",...}. Avoids a JSON dependency
// in the stub. Returns empty if the key or a string value is not found.
std::string extractJsonStringField(const std::string& json, const std::string& key)
{
    const std::string needle = "\"" + key + "\"";
    size_t pos = json.find(needle);
    if (pos == std::string::npos) {
        return {};
    }
    pos = json.find(':', pos + needle.size());
    if (pos == std::string::npos) {
        return {};
    }
    ++pos;
    while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) {
        ++pos;
    }
    if (pos >= json.size() || json[pos] != '"') {
        return {};
    }
    ++pos;
    const size_t end = json.find('"', pos);
    if (end == std::string::npos) {
        return {};
    }
    return json.substr(pos, end - pos);
}

void deliverFrame(mg_websocket_data_handler dataFunc,
                  struct mg_connection*     handle,
                  void*                     userData,
                  const std::string&        msg)
{
    if (dataFunc != nullptr) {
        std::vector<char> buf(msg.begin(), msg.end());
        buf.push_back('\0');
        dataFunc(handle, MG_WEBSOCKET_OPCODE_TEXT, buf.data(), msg.size(), userData);
    }
}

// Emulate civetweb's asynchronous handling of an outgoing frame for a fake
// connection: close frames trigger the close handler on a detached thread (so
// the caller's mutex, held during DisconnectFromServer, is released first), and
// subscribe/publish requests receive a delayed success ListenAck.
void handleOutgoingFrame(struct mg_connection* conn, int opcode, const char* data, size_t data_len)
{
    mg_websocket_data_handler  dataFunc  = nullptr;
    mg_websocket_close_handler closeFunc = nullptr;
    void*                      userData  = nullptr;
    struct mg_connection*      handle    = nullptr;
    bool                       enabled   = false;

    {
        std::lock_guard<std::mutex> lock(g_mockMutex);
        enabled = g_connectionEnabled;
        for (const auto& c : g_connections) {
            if (c.handle == conn) {
                dataFunc  = c.dataFunc;
                closeFunc = c.closeFunc;
                userData  = c.userData;
                handle    = c.handle;
                break;
            }
        }
    }

    if (handle == nullptr) {
        return; // Not a fake connection; nothing to emulate.
    }

    const int op = opcode & 0xf;

    if (op == MG_WEBSOCKET_OPCODE_CONNECTION_CLOSE) {
        if (closeFunc != nullptr) {
            std::thread([closeFunc, handle, userData]() {
                closeFunc(handle, userData);
            }).detach();
        }
        return;
    }

    if (enabled && (op == MG_WEBSOCKET_OPCODE_TEXT || op == MG_WEBSOCKET_OPCODE_BINARY) && data != nullptr) {
        const std::string out(data, data_len);
        const std::string requestId = extractJsonStringField(out, "requestId");
        const std::string operation = extractJsonStringField(out, "operation");
        if (!requestId.empty() && !operation.empty()) {
            const std::string ack = "{\"type\":\"ListenAck\",\"requestId\":\"" + requestId +
                                    "\",\"operation\":\"" + operation +
                                    "\",\"statusCode\":\"0\",\"statusMessage\":\"OK\"}";
            // Delay so the caller can register the pending request before the ack lands.
            std::thread([dataFunc, handle, userData, ack]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                deliverFrame(dataFunc, handle, userData, ack);
            }).detach();
        }
    }
}

} // namespace

extern "C" {

/* -------------------------------------------------------------------------
 * Library init / exit
 * ---------------------------------------------------------------------- */

unsigned mg_init_library(unsigned features)
{
    /* Report all requested features as initialised. */
    return features;
}

unsigned mg_exit_library(void)
{
    return 1u;
}

/* -------------------------------------------------------------------------
 * WebSocket client connect
 * ---------------------------------------------------------------------- */

struct mg_connection *mg_connect_websocket_client_secure(
    const struct mg_client_options *client_options,
    char *error_buffer,
    size_t error_buffer_size,
    const char *path,
    const char *origin,
    mg_websocket_data_handler data_func,
    mg_websocket_close_handler close_func,
    void *user_data)
{
    (void)client_options;
    (void)path;
    (void)origin;
    (void)data_func;
    (void)close_func;
    (void)user_data;

    {
        std::lock_guard<std::mutex> lock(g_mockMutex);
        if (g_connectionEnabled) {
            struct mg_connection* handle = reinterpret_cast<struct mg_connection*>(new int(0));
            g_connections.push_back(FakeConnection{handle, data_func, close_func, user_data});
            return handle;
        }
    }

    if (error_buffer && error_buffer_size > 0) {
        std::strncpy(error_buffer, "mock: connection not supported in L1 test build",
                     error_buffer_size - 1u);
        error_buffer[error_buffer_size - 1u] = '\0';
    }
    return nullptr;
}

struct mg_connection *mg_connect_websocket_client_sky(
    const char *host,
    int port,
    int use_ssl,
    char *error_buffer,
    size_t error_buffer_size,
    const char *path,
    const char *origin,
    const char *extra_headers,
    mg_websocket_data_handler data_func,
    mg_websocket_close_handler close_func,
    void *user_data)
{
    (void)host;
    (void)port;
    (void)use_ssl;
    (void)path;
    (void)origin;
    (void)extra_headers;
    (void)data_func;
    (void)close_func;
    (void)user_data;

    {
        std::lock_guard<std::mutex> lock(g_mockMutex);
        if (g_connectionEnabled) {
            struct mg_connection* handle = reinterpret_cast<struct mg_connection*>(new int(0));
            g_connections.push_back(FakeConnection{handle, data_func, close_func, user_data});
            return handle;
        }
    }

    if (error_buffer && error_buffer_size > 0) {
        std::strncpy(error_buffer, "mock: connection not supported in L1 test build",
                     error_buffer_size - 1u);
        error_buffer[error_buffer_size - 1u] = '\0';
    }
    return nullptr;
}

/* -------------------------------------------------------------------------
 * WebSocket write / close
 * ---------------------------------------------------------------------- */

int mg_websocket_write(struct mg_connection *conn,
                       int opcode,
                       const char *data,
                       size_t data_len)
{
    handleOutgoingFrame(conn, opcode, data, data_len);
    return static_cast<int>(data_len);
}

int mg_websocket_client_write(struct mg_connection *conn,
                              int opcode,
                              const char *data,
                              size_t data_len)
{
    handleOutgoingFrame(conn, opcode, data, data_len);
    return static_cast<int>(data_len);
}

void mg_close_connection(struct mg_connection *conn)
{
    if (conn == nullptr) {
        return;
    }

    bool found = false;
    {
        std::lock_guard<std::mutex> lock(g_mockMutex);
        for (auto it = g_connections.begin(); it != g_connections.end(); ++it) {
            if (it->handle == conn) {
                g_connections.erase(it);
                found = true;
                break;
            }
        }
    }

    if (found) {
        delete reinterpret_cast<int*>(conn);
    }
}

/* -------------------------------------------------------------------------
 * URL encoding
 * ---------------------------------------------------------------------- */

int mg_url_encode(const char *src, char *dst, size_t dst_len)
{
    if (!src || !dst || dst_len == 0u) {
        return -1;
    }
    /* Trivial pass-through — sufficient for test builds where no real
     * network traffic is generated. */
    const size_t src_len = std::strlen(src);
    if (src_len >= dst_len) {
        dst[0] = '\0';
        return -1;
    }
    std::memcpy(dst, src, src_len);
    dst[src_len] = '\0';
    return static_cast<int>(src_len);
}

} /* extern "C" */

namespace MockCivetWeb {

void EnableConnection(bool enable)
{
    std::lock_guard<std::mutex> lock(g_mockMutex);
    g_connectionEnabled = enable;
}

void Reset()
{
    std::lock_guard<std::mutex> lock(g_mockMutex);
    g_connectionEnabled = false;
    // Forget any tracked connections. Open handles are freed later via
    // mg_close_connection during connection teardown; callers must only Reset
    // when no connection is currently open.
    g_connections.clear();
}

int InjectServerMessage(const std::string& message)
{
    std::vector<FakeConnection> snapshot;
    {
        std::lock_guard<std::mutex> lock(g_mockMutex);
        snapshot = g_connections;
    }

    for (const auto& c : snapshot) {
        deliverFrame(c.dataFunc, c.handle, c.userData, message);
    }

    return static_cast<int>(snapshot.size());
}

} // namespace MockCivetWeb
