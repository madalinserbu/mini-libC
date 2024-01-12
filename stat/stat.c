// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
    // Use the syscall function to invoke the sys_stat system call
    int ret = syscall(__NR_stat, path, buf);

    // Check for errors and set errno if necessary
    if (ret < 0)
    {
        errno = -ret;
        return -1;
    }

    return 0;
}
