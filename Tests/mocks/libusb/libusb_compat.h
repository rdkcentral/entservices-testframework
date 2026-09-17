/*
* Partial copy of Public libusb header file libusb.h which is:
* Copyright 2001 Johannes Erdfelt <johannes@erdfelt.com>
* Copyright 2007-2008 Daniel Drake <dsd@gentoo.org>
* Copyright 2012 Pete Batard <pete@akeo.ie>
* Copyright 2012-2023 Nathan Hjelm <hjelmn@cs.unm.edu>
* Copyright © 2014-2020 Chris Dickens <christopher.a.dickens@gmail.com>
* For more information, please visit: https://libusb.info
* libusb is licensed under the LGPL License, Version 2.1 or greater
* (https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt)
* Changes to add extra mock function prototypes
* Copyright 2025 RDK Management
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
