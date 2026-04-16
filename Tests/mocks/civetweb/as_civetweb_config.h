/**
 * @file
 * @brief CivetWeb client configuration
 *
 * @copyright Copyright (c) 2022 Sky UK. All rights reservered.
 *
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