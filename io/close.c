// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
    // Use the syscall function to invoke the sys_close system call
    long ret = syscall(__NR_close, fd);

    // Check for errors and set errno if necessary
    if (ret >= 0)
        return 0;
    else
    {
        errno = -ret;
        return -1; // Return -1 to indicate an error
    }
}
