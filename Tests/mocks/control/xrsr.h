/*
 * If not stated otherwise in this file or this component's license file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
#ifndef _XRSR_H_
#define _XRSR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <openssl/ssl.h>
#include "xr_timestamp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XRSR_SAT_TOKEN_LEN_MAX     (2048)
#define XRSR_QUERY_STRING_QTY_MAX  (16)
#define XRSR_SESSION_BY_TEXT_MAX   (256)
#define XRSR_DST_PARAM_LEN_MAX    (256)

/* Source types */
typedef enum {
    XRSR_SRC_RCU_PTT           = 0,
    XRSR_SRC_RCU_FF            = 1,
    XRSR_SRC_MICROPHONE        = 2,
    XRSR_SRC_MICROPHONE_TAP    = 3,
    XRSR_SRC_INVALID           = 4
} xrsr_src_t;

/* Audio format bitmask */
typedef enum {
    XRSR_AUDIO_FORMAT_PCM              = (1 << 0),
    XRSR_AUDIO_FORMAT_PCM_32_BIT       = (1 << 1),
    XRSR_AUDIO_FORMAT_PCM_32_BIT_MULTI = (1 << 2),
    XRSR_AUDIO_FORMAT_PCM_RAW          = (1 << 3),
    XRSR_AUDIO_FORMAT_ADPCM            = (1 << 4),
    XRSR_AUDIO_FORMAT_OPUS             = (1 << 5),
    XRSR_AUDIO_FORMAT_OPUS_XVP         = (1 << 6)
} xrsr_audio_format_t;

/* Session end reasons */
typedef enum {
    XRSR_SESSION_END_REASON_EOS                = 0,
    XRSR_SESSION_END_REASON_TERMINATE          = 1,
    XRSR_SESSION_END_REASON_EOT                = 2,
    XRSR_SESSION_END_REASON_DISCONNECT_REMOTE  = 3,
    XRSR_SESSION_END_REASON_ERROR_AUDIO_BEGIN  = 4,
    XRSR_SESSION_END_REASON_ERROR_AUDIO_DURATION = 5,
    XRSR_SESSION_END_REASON_INVALID            = 6
} xrsr_session_end_reason_t;

/* Stream from/until */
typedef enum {
    XRSR_STREAM_FROM_BEGINNING = 0,
    XRSR_STREAM_FROM_KEYWORD   = 1,
    XRSR_STREAM_FROM_INVALID   = 2
} xrsr_stream_from_t;

typedef enum {
    XRSR_STREAM_UNTIL_END_OF_STREAM   = 0,
    XRSR_STREAM_UNTIL_END_OF_SPEECH   = 1,
    XRSR_STREAM_UNTIL_END_OF_KEYWORD  = 2,
    XRSR_STREAM_UNTIL_INVALID         = 3
} xrsr_stream_until_t;

/* Power modes */
typedef enum {
    XRSR_POWER_MODE_FULL  = 0,
    XRSR_POWER_MODE_LOW   = 1,
    XRSR_POWER_MODE_SLEEP = 2
} xrsr_power_mode_t;

/* Keyword detector result */
typedef enum {
    XRSR_KWD_RESULT_DETECTED    = 0,
    XRSR_KWD_RESULT_NOT_DETECTED = 1,
    XRSR_KWD_RESULT_INVALID     = 2
} xrsr_keyword_detector_result_t;

/* Certificate type */
typedef struct {
    const char *pem_cert;
    const char *pem_key;
    const char *pem_ca;
} xrsr_cert_t;

/* Destination parameters */
typedef struct {
    char url[XRSR_DST_PARAM_LEN_MAX];
} xrsr_dst_params_t;

/* Route */
typedef struct {
    xrsr_src_t         src;
    xrsr_dst_params_t  dst_params;
    xrsr_audio_format_t supported_formats;
    xrsr_stream_from_t  stream_from;
    xrsr_stream_until_t stream_until;
} xrsr_route_t;

/* Session config */
typedef struct {
    bool   detect_keyword;
    bool   has_stream;
    bool   push_to_talk;
    xrsr_stream_from_t stream_from;
} xrsr_session_config_out_t;

typedef struct {
    struct {
        xrsr_cert_t client_cert;
    } http;
    struct {
        xrsr_cert_t client_cert;
    } ws;
} xrsr_session_config_in_t;

typedef struct {
    int    dummy;
} xrsr_session_config_update_t;

/* Stream and session stats */
typedef struct {
    uint32_t packets_processed;
    uint32_t packets_lost;
    uint32_t samples_processed;
    uint32_t samples_lost;
    double   snr_peak;
    double   snr_mean;
} xrsr_stream_stats_t;

typedef struct {
    xrsr_session_end_reason_t session_end_reason;
    xrsr_stream_stats_t       stream_stats;
} xrsr_session_stats_t;

/* Callback function pointer types */
typedef void (*xrsr_callback_session_config_t)(xrsr_src_t src, xrsr_session_config_in_t *config_in, xrsr_session_config_out_t *config_out, void *user_data);
typedef bool (*xrsr_handler_send_t)(const void *data, size_t size, void *user_data);

/* Handlers */
typedef struct {
    void  (*session_begin)(void *data, xrsr_src_t src, xrsr_session_config_out_t *config, xrsr_callback_session_config_t callback, rdkx_timestamp_t *timestamp);
    void  (*session_end)(void *data, xrsr_src_t src, xrsr_session_stats_t *stats, rdkx_timestamp_t *timestamp);
    void  (*stream_begin)(void *data, xrsr_src_t src, rdkx_timestamp_t *timestamp);
    void  (*stream_kwd)(void *data, xrsr_src_t src, xrsr_keyword_detector_result_t result, bool detector_active, xrsr_session_config_in_t *config_in, rdkx_timestamp_t *timestamp);
    void  (*stream_end)(void *data, xrsr_src_t src, xrsr_stream_stats_t *stats, rdkx_timestamp_t *timestamp);
    void  (*connected)(void *data, xrsr_handler_send_t send, void *param);
    void  (*disconnected)(void *data, bool retry);
    void  (*recv_msg)(void *data, const void *msg, size_t msg_len);
    void  (*source_error)(void *data, xrsr_src_t src);
    void  *data;
} xrsr_handlers_t;

/* Config */
typedef struct {
    const char *vsdk_config;
    const char *host_name;
    int         dummy;
} xrsr_config_t;

/* Functions */
bool             xrsr_open(const xrsr_route_t *routes, unsigned int route_qty, const xrsr_handlers_t *handlers, xrsr_src_t src);
void             xrsr_close(void);
bool             xrsr_route(const xrsr_route_t *routes, unsigned int route_qty, const xrsr_handlers_t *handlers, xrsr_src_t src);
void             xrsr_session_terminate(void);
xrsr_config_t   *xrsr_config_get(void);
void             xrsr_power_mode_set(xrsr_power_mode_t power_mode);
void             xrsr_privacy_mode_set(bool enable);
const char      *xrsr_src_str(xrsr_src_t src);
const char      *xrsr_session_end_reason_str(xrsr_session_end_reason_t reason);

#ifdef __cplusplus
}
#endif

#endif /* _XRSR_H_ */
