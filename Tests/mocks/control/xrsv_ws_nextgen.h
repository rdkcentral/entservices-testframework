/*
 * Stub for xrsv_ws_nextgen.h - Voice WebSocket NextGen endpoint types
 *
 * Copyright 2024 RDK Management
 * Licensed under the Apache License, Version 2.0
 */
#ifndef _XRSV_WS_NEXTGEN_H_
#define _XRSV_WS_NEXTGEN_H_

#include "xrsr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *xrsv_ws_nextgen_object_t;

typedef enum {
    XRSV_WS_NEXTGEN_DEVICE_TYPE_STB = 0,
    XRSV_WS_NEXTGEN_DEVICE_TYPE_TV  = 1
} xrsv_ws_nextgen_device_type_t;

typedef struct {
    const char *url;
    const char *sat_token;
} xrsv_ws_nextgen_params_t;

typedef struct {
    void (*session_begin)(void *data, xrsr_src_t src, xrsr_session_config_out_t *config, xrsr_callback_session_config_t callback, rdkx_timestamp_t *timestamp);
    void (*session_end)(void *data, xrsr_src_t src, xrsr_session_stats_t *stats, rdkx_timestamp_t *timestamp);
    void (*stream_begin)(void *data, xrsr_src_t src, rdkx_timestamp_t *timestamp);
    void (*stream_end)(void *data, xrsr_src_t src, xrsr_stream_stats_t *stats, rdkx_timestamp_t *timestamp);
    void (*connected)(void *data, xrsr_handler_send_t send, void *param);
    void (*disconnected)(void *data, bool retry);
    void (*recv_msg)(void *data, const void *msg, size_t msg_len);
    void *data;
} xrsv_ws_nextgen_handlers_t;

typedef struct {
    xrsr_audio_format_t audio_format;
} xrsv_ws_nextgen_stream_params_t;

xrsv_ws_nextgen_object_t xrsv_ws_nextgen_create(const xrsv_ws_nextgen_params_t *params);
void                     xrsv_ws_nextgen_destroy(xrsv_ws_nextgen_object_t obj);
bool                     xrsv_ws_nextgen_handlers(xrsv_ws_nextgen_object_t obj, const xrsv_ws_nextgen_handlers_t *handlers);
void                     xrsv_ws_nextgen_update_init_app(xrsv_ws_nextgen_object_t obj, const char *init_app);
bool                     xrsv_ws_nextgen_send_msg(xrsv_ws_nextgen_object_t obj, const char *msg);
void                     xrsv_ws_nextgen_update_account_id(xrsv_ws_nextgen_object_t obj, const char *account_id);
void                     xrsv_ws_nextgen_update_device_id(xrsv_ws_nextgen_object_t obj, const char *device_id);
void                     xrsv_ws_nextgen_update_device_type(xrsv_ws_nextgen_object_t obj, xrsv_ws_nextgen_device_type_t type);
void                     xrsv_ws_nextgen_update_partner_id(xrsv_ws_nextgen_object_t obj, const char *partner_id);
void                     xrsv_ws_nextgen_update_experience(xrsv_ws_nextgen_object_t obj, const char *experience);
void                     xrsv_ws_nextgen_update_language(xrsv_ws_nextgen_object_t obj, const char *language);
void                     xrsv_ws_nextgen_update_mask_pii(xrsv_ws_nextgen_object_t obj, bool enable);
void                     xrsv_ws_nextgen_update_audio_profile(xrsv_ws_nextgen_object_t obj, const char *profile);
void                     xrsv_ws_nextgen_update_audio_model(xrsv_ws_nextgen_object_t obj, const char *model);
void                     xrsv_ws_nextgen_update_audio_rf_protocol(xrsv_ws_nextgen_object_t obj, const char *rf_protocol);

#ifdef __cplusplus
}
#endif

#endif /* _XRSV_WS_NEXTGEN_H_ */
