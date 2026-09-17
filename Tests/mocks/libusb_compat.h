/*
 * If not stated otherwise in this file or this component's LICENSE
 * file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the GNU Lesser General Public License, version 2.1 or later.
 * See the COPYING file at the root directory of this project for the complete license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBUSB_COMPAT_H
#define LIBUSB_COMPAT_H

#include <libusb-1.0/libusb.h>

/**
 * Compatibility wrapper for libusb_init_context()
 * 
 * This function was added in libusb 1.0.16 but may not be available
 * in older libusb-1.0 versions. This wrapper maps it to libusb_init()
 * which is available in all versions.
 */
static inline int libusb_init_context(libusb_context **ctx, 
                                      const struct libusb_init_option *options, 
                                      int num_options)
{
    /* Ignore options and num_options parameters for compatibility */
    (void)options;
    (void)num_options;
    
    /* Use libusb_init which is available in older versions */
    return libusb_init(ctx);
}

#endif /* LIBUSB_COMPAT_H */
