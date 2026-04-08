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
#ifndef _RDKX_LOGGER_H_
#define _RDKX_LOGGER_H_

#include <stdio.h>

/* Log option flags */
#define XLOG_OPTS_DATE      (1 << 0)
#define XLOG_OPTS_TIME      (1 << 1)
#define XLOG_OPTS_LF        (1 << 2)
#define XLOG_OPTS_MOD_NAME  (1 << 3)
#define XLOG_OPTS_LEVEL     (1 << 4)
#define XLOG_OPTS_COLOR     (1 << 5)

/* Module IDs */
#define XLOG_MODULE_ID_CTRLM   0
#define XLOG_MODULE_ID_VSDK    1
#define XLOG_MODULE_ID_XRAUDIO 2

#ifndef XLOG_MODULE_ID
#define XLOG_MODULE_ID XLOG_MODULE_ID_CTRLM
#endif

/* Logging macros - map to printf for stub builds */
#define XLOGD_INFO(...)   printf(__VA_ARGS__)
#define XLOGD_DEBUG(...)  printf(__VA_ARGS__)
#define XLOGD_ERROR(...)  printf(__VA_ARGS__)
#define XLOGD_WARN(...)   printf(__VA_ARGS__)
#define XLOGD_FATAL(...)  printf(__VA_ARGS__)

#define XLOG_INFO(...)    printf(__VA_ARGS__)
#define XLOG_DEBUG(...)   printf(__VA_ARGS__)
#define XLOG_ERROR(...)   printf(__VA_ARGS__)
#define XLOG_WARN(...)    printf(__VA_ARGS__)

#endif /* _RDKX_LOGGER_H_ */
