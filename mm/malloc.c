// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size) {
	/* TODO: Implement malloc(). */
    // Calculate the total size needed for the memory block, including the size of the mem_list structure
	size_t total_size = size + sizeof(struct mem_list);
    // Use mmap to allocate memory
    void *memory = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (memory == MAP_FAILED) {
        return NULL;
    }
    // Initialize the memory list structure
	struct mem_list *mem_item = (struct mem_list *)memory;
    mem_item->start = memory + sizeof(struct mem_list); // Set the start address to after the mem_list structure
    mem_item->len = size;
    // Add the allocated memory block to the memory list
	if (mem_list_add(mem_item->start, size) != 0) {
        munmap(memory, total_size); // Free memory in case of error
        return NULL;
    }
    return mem_item->start;
}
void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	// Calculate the total size needed for the memory block
    size_t total_size = nmemb * size;
    // Call the custom malloc function to allocate memory
    void *memory = malloc(total_size);
    if (memory != NULL) {
        // Initialize the allocated memory to zero
        memset(memory, 0, total_size);
    }
    return memory;
}

void free(void *ptr) {
	/* TODO: Implement free(). */
    // Find the memory block in the memory list
    struct mem_list *block = mem_list_find(ptr);

    if (block != NULL) {
        // Remove the memory block from the memory list
		mem_list_del(ptr);
        // Unmap the memory block to deallocate it
        size_t total_size = block->len + sizeof(struct mem_list);
        munmap(block, total_size);
    }
	return ;
}
void *realloc(void *ptr, size_t size) {
	/* TODO: Implement realloc(). */
    // If the pointer is NULL, this is equivalent to malloc
    if (ptr == NULL) {
        return malloc(size);
    }
    // Find the memory block in the memory list
    struct mem_list *block = mem_list_find(ptr);
    if (block != NULL) {
        // Calculate the total size needed for the new memory block
        size_t total_size = size + sizeof(struct mem_list);
        // Check if the existing block is large enough
        if (block->len >= size) {
            return ptr; // The existing block is sufficient, no reallocation needed
        }
        // Attempt to extend the existing memory block
        void *new_ptr = mremap(ptr, block->len + sizeof(struct mem_list), total_size, 0);
        if (new_ptr != MAP_FAILED) {
            // Update the length in the memory list
            block->len = size;
            return new_ptr;
        } else {
            // Extending the existing block failed, allocate a new block and copy data
            void *new_memory = malloc(size);
            if (new_memory != NULL) {
                memcpy(new_memory, ptr, block->len);
                free(ptr);
            }
            return new_memory;
        }
    }
    return NULL; // Invalid pointer, unable to reallocate
}
void *reallocarray(void *ptr, size_t nmemb, size_t size) {
	/* TODO: Implement reallocarray(). */
    // Calculate the total size needed for the array
    size_t total_size = nmemb * size;

    // Call the custom realloc function to resize the memory block
    return realloc(ptr, total_size);
}
