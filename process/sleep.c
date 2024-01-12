/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <time.h>

int nanosleep(const struct timespec *req, struct timespec *rem) {
    int result = syscall(__NR_nanosleep, req, rem);
    if (result == -1) {
        if (errno == EINTR) {
            // The sleep was interrupted by a signal, and there's time
            // remaining.
            return -1;
        } else {
            // An error occurred during sleep.
            return -1;
        }
    }

    return 0;
}

unsigned int sleep(unsigned int seconds) {
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    // Call custom_nanosleep with the requested time and a placeholder for the
    // remaining time
    int result = nanosleep(&req, &rem);

    if (result == -1) {
        // The sleep was interrupted; calculate and return the remaining time
        // in seconds
        unsigned int remaining_seconds = rem.tv_sec;

        // If there are remaining nanoseconds, round up to the next second
        if (rem.tv_nsec > 0) {
            remaining_seconds += 1;
        }

        return remaining_seconds;
    }

    // The sleep completed successfully, return 0
    return 0;
}
