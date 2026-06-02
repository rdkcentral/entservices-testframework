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


#ifndef AS_CIVETWEB_CONFIG_H
#define AS_CIVETWEB_CONFIG_H

/*----------------------------------------------------------------------------*/
/*------------------- AS specific civetweb configurations---------------------*/
/*----------------------------------------------------------------------------*/


#define NO_CGI

#define NO_FILES
#define NO_FILESYSTEMS

#define NO_NONCE_CHECK

#define USE_WEBSOCKET

#define MG_EXTERNAL_FUNCTION_mg_cry_internal_impl
#define MG_EXTERNAL_FUNCTION_log_access

// #define DEBUG

/**
 * Dynamic SSL library loading has been disabled in favor of static linking.
 * This is done by defining NO_SSL_DL. This change improves security and
 * simplifies deployment, but requires that the SSL library (e.g., OpenSSL)
 * is available at build time and cannot be swapped at runtime. Ensure that
 * the appropriate SSL libraries are present on the target system.
 */
#define NO_SSL_DL
#define OPENSSL_API_3_0

#define AS_ENABLE_SSL_DUMP 0

#define AS_CHANGES

/*----------------------------------------------------------------------------*/

#endif //AS_CIVETWEB_CONFIG_H