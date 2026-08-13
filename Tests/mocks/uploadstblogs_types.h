/*
 * Mock uploadstblogs_types.h for native/L1/L2 test builds.
 */

#ifndef UPLOADSTBLOGS_TYPES_H
#define UPLOADSTBLOGS_TYPES_H

#include <stdbool.h>

typedef enum {
    TRIGGER_SCHEDULED = 0,
    TRIGGER_MANUAL = 1,
    TRIGGER_REBOOT = 2,
    TRIGGER_CRASH = 3,
    TRIGGER_DEBUG = 4,
    TRIGGER_ONDEMAND = 5,
    TRIGGER_MEMCAPTURE = 6
} TriggerType;

typedef struct {
    int flag;
    int dcm_flag;
    bool upload_on_reboot;
    const char* upload_protocol;
    const char* upload_http_link;
    TriggerType trigger_type;
    bool rrd_flag;
    const char* rrd_file;
    bool uploadlogsnow_mode;
} UploadSTBLogsParams;

#endif /* UPLOADSTBLOGS_TYPES_H */
