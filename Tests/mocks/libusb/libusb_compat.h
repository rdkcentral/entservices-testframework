/* This software is licensed by RDK Management under the GNU Lesser General
 * Public License version 2.1 only, as per COPYING.LGPL and subject to any
 * additional licenses included in this file.
 * Please use the following copyright for source under this directory:
 *
 * Copyright 2025  RDK Management
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, version 2.1
 * of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.

 * Copyright 2001 Johannes Erdfelt <johannes@erdfelt.com>
 * Copyright 2007-2008 Daniel Drake <dsd@gentoo.org>
 * Copyright 2012 Pete Batard <pete@akeo.ie>
 * Copyright 2012-2023 Nathan Hjelm <hjelmn@cs.unm.edu>
 * Copyright © 2014-2020 Chris Dickens <christopher.a.dickens@gmail.com>
 * For more information, please visit: https://libusb.info
 * libusb is licensed under the LGPL License, Version 2.1 or greater
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
