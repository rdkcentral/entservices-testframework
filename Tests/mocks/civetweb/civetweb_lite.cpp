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

#include <cstring>

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
    (void)conn;
    (void)opcode;
    (void)data;
    (void)data_len;
    return 0;
}

int mg_websocket_client_write(struct mg_connection *conn,
                              int opcode,
                              const char *data,
                              size_t data_len)
{
    (void)conn;
    (void)opcode;
    (void)data;
    (void)data_len;
    return 0;
}

void mg_close_connection(struct mg_connection *conn)
{
    (void)conn;
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
    const size_t copy_len = (src_len < dst_len - 1u) ? src_len : dst_len - 1u;
    std::memcpy(dst, src, copy_len);
    dst[copy_len] = '\0';
    return static_cast<int>(copy_len);
}

} /* extern "C" */
