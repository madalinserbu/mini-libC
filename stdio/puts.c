/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int puts(const char *str) {
    int len = 0;
    while (str[len]) {
        len++;
    }
    // Write the string to standard output (file descriptor 1)
    int result = write(1, str, len);
    if (result == -1) {
        // Return -1 on write error
        return -1;
    }

    result = write(1, "\n", 1);
    if (result == -1) {
        return -1;
    }

    return 0;
}
