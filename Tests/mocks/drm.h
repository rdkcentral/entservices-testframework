#pragma once

#if __has_include(<libdrm/drm.h>)
#include <libdrm/drm.h>
#else
#include_next <drm.h>
#endif