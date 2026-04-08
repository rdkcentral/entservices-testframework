/*
 * Stub for xrsv_http.h - Voice HTTP endpoint types
 *
 * Copyright 2024 RDK Management
 * Licensed under the Apache License, Version 2.0
 */
#ifndef _XRSV_HTTP_H_
#define _XRSV_HTTP_H_

#include "xrsr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *xrsv_http_object_t;

typedef struct {
    const char *url;
    const char *sat_token;
} xrsv_http_params_t;

typedef struct {
    void (*session_begin)(void *data, xrsr_src_t src, xrsr_session_config_out_t *config, xrsr_callback_session_config_t callback, rdkx_timestamp_t *timestamp);
    void (*session_end)(void *data, xrsr_src_t src, xrsr_session_stats_t *stats, rdkx_timestamp_t *timestamp);
    void (*stream_begin)(void *data, xrsr_src_t src, rdkx_timestamp_t *timestamp);
    void (*stream_end)(void *data, xrsr_src_t src, xrsr_stream_stats_t *stats, rdkx_timestamp_t *timestamp);
    void (*connected)(void *data, xrsr_handler_send_t send, void *param);
    void (*disconnected)(void *data, bool retry);
    void (*recv_msg)(void *data, const void *msg, size_t msg_len);
    void *data;
} xrsv_http_handlers_t;

typedef struct {
    const char *transcription;
} xrsv_http_recv_msg_t;

xrsv_http_object_t xrsv_http_create(const xrsv_http_params_t *params);
void               xrsv_http_destroy(xrsv_http_object_t obj);
bool               xrsv_http_handlers(xrsv_http_object_t obj, const xrsv_http_handlers_t *handlers);
void               xrsv_http_update_device_id(xrsv_http_object_t obj, const char *device_id);
void               xrsv_http_update_partner_id(xrsv_http_object_t obj, const char *partner_id);
void               xrsv_http_update_experience(xrsv_http_object_t obj, const char *experience);
void               xrsv_http_update_language(xrsv_http_object_t obj, const char *language);
void               xrsv_http_update_mask_pii(xrsv_http_object_t obj, bool enable);

#ifdef __cplusplus
}
#endif

#endif /* _XRSV_HTTP_H_ */
