/*
 * Copyright (C) 2026 RDK Management
 *
 * Licensed under the RDK-M LGPLv2
 * See the COPYING file at the root directory of this project.
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
