// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
	/* TODO: Implement mmap(). */
    off_t result = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if (result == -1) {
        switch (errno) {
            case EINVAL:
                return MAP_FAILED;
            case EACCES:
                return MAP_FAILED;
            case EPERM:
                return MAP_FAILED;
            default:
                return MAP_FAILED;
        }
    }

    return (void *)result;
}
void *mremap(void *old_address, size_t old_size, size_t new_size, int flags) {
	/* TODO: Implement mremap(). */
    off_t result = syscall(__NR_mremap, old_address, old_size, new_size, flags);

    if (result == -1) {
        switch (errno) {
            case EINVAL:
                return MAP_FAILED;
            case EPERM:
                return MAP_FAILED;
            default:
                return MAP_FAILED;
        }
    }

    return (void *)result;
}

int munmap(void *addr, size_t length) {
	/* TODO: Implement munmap(). */
    off_t result = syscall(__NR_munmap, addr, length);

    if (result == -1) {
        switch (errno) {
            case EINVAL:
                return -1; // Invalid argument
            case EACCES:
                return -1; // Permission denied
            case EPERM:
                return -1; // Operation not permitted
            default:
                return -1;
        }
    }

    return 0; // Return 0 on success
}
