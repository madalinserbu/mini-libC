// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
    mode_t mode = 0; // Default mode

    // If O_CREAT flag is set, interpret the third argument as mode
    if (flags & O_CREAT)
    {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    // Use the syscall function to invoke the sys_open system call
    long ret = syscall(__NR_open, filename, flags, mode);

    // Check for errors and set errno if necessary
    if (ret >= 0)
        return ret;
    else
    {
        errno = -ret;
        return -1;
    }
}
