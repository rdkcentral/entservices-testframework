/*
 * Mock uploadstblogs implementation for native/L1/L2 test builds.
 */

#include "uploadstblogs.h"

int uploadstblogs_run(const UploadSTBLogsParams* params)
{
    (void)params;
    return 0;
}

int uploadstblogs_execute(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    return 0;
}
