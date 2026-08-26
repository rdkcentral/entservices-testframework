/*
 * Mock uploadstblogs.h for native/L1/L2 test builds.
 */

#ifndef UPLOADSTBLOGS_H
#define UPLOADSTBLOGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uploadstblogs_types.h"

int uploadstblogs_run(const UploadSTBLogsParams* params);
int uploadstblogs_execute(int argc, char** argv);

#ifdef __cplusplus
}
#endif

#endif /* UPLOADSTBLOGS_H */
