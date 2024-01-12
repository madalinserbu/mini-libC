// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
    // Use the syscall function to invoke the sys_fstat system call
    int ret = syscall(__NR_fstat, fd, st);

    // Check for errors and set errno if necessary
    if (ret < 0)
    {
        errno = -ret;
        return -1;
    }

    return 0; // Return 0 to indicate success
}
