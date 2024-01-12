// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
    // Use the syscall function to invoke the sys_truncate system call
    int ret = syscall(__NR_truncate, path, length);

    // Check for errors and set errno if necessary
    if (ret >= 0)
        return ret;
    else
    {
        errno = -ret;
        ret = -1;
    }
    return -1;
}
