// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	// /* TODO: Implement strcpy(). */
	if (destination == NULL || source == NULL) {
        return NULL;
    }
	int i = 0;
	while (1) {
		destination[i] = source[i];
		if (destination[i] == '\0') {
			break;
		}
		i++;
	}
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	if (destination == NULL || source == NULL) {
        return NULL;
    }
	size_t i = 0;
	while (i < len) {
		destination[i] = source[i];
		if (destination[i] == '\0') {
			break;
		}
		i++;
	}
	// Null-terminate until the end
	for (; len--; *destination++ = '\0')
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	// Check for null pointers
    if (destination == NULL || source == NULL) {
        return NULL;
    }
    // Move the destination pointer to the end of the destination string
    while (*destination++) {
        // Continue iterating through the destination string until the
		// null terminator is reached
    }
    // Decrement the pointer to the last character of the original
	// destination string
    --destination;
    // Concatenate the source string to the destination string
    while (*destination++ = *source++) {
        // Copy characters from the source to the destination until the source
		// string's null terminator is reached
    }
    // Return a pointer to the end of the concatenated string
    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	if (destination == NULL || source == NULL) {
        return NULL;
    }
    size_t dest_len = strlen(destination);
    size_t i;
    // Determine the length of source up to 'num' characters or until a null terminator is reached
    for (i = 0; i < len && source[i] != '\0'; i++) {
        // Concatenate source characters to destination
        destination[dest_len + i] = source[i];
    }
    // Null-terminate the concatenated string
    destination[dest_len + i] = '\0';
    return destination;
}


int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
    while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

int strncmp(const char *str1, const char *str2, size_t len) {
	/* TODO: Implement strncmp(). */
    // Iterate through the strings while there are characters to compare and they are equal
    while (len > 0 && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        len--;
    }

    // Check if the strings are equal up to 'len' characters or both strings end
    if (len == 0 || (*str1 == '\0' && *str2 == '\0')) {
        return 0;  // Strings are equal up to 'len' characters or both are equal until the end.
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	while (*str != '\0') {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }

    // If the character is not found, return NULL
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	const char *last = NULL;
    while (*str != '\0') {
        if (*str == c) {
            last = str;
        }
        str++;
    }
    // If the character is found, return a pointer to the last occurrence of 'c'
    if (last != NULL) {
        return (char *)last;
    }
	return NULL;
}

char *strstr(const char *haystack, const char *needle) {
	/* TODO: Implement strstr(). */
    // Handle the edge case where the needle is an empty string
    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        // Check if the current substring of haystack matches the needle
        while (*h == *n && *n !=  '\0') {
            h++;
            n++;
        }

        // If the entire needle is found in haystack, return a pointer to its location
        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }

    // If the needle is not found in the haystack, return NULL
    return NULL;
}


char *strrstr(const char *haystack, const char *needle) {
	/* TODO: Implement strrstr(). */
    if (*needle == '\0') {
        return (char *)(haystack + strlen(haystack));
    }

    const char *last = NULL;

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        // Check if the current substring of haystack matches the needle
        while (*h == *n && *n != '\0') {
            h++;
            n++;
        }

        // If the entire needle is found in haystack, update the last pointer
        if (*n == '\0') {
            last = haystack;
        }

        haystack++;
    }

    if (last != NULL) {
        return (char *)last;
    }

    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	char *dest = (char *)destination;
    const char *src = (const char *)source;
    while (num--) *dest++ = *src++;
	return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;

    // Handle overlapping memory regions
    if (dest > src && dest < src + num) {
        // Copy in reverse to avoid overwriting source data prematurely
        for (size_t i = num; i > 0; i--) {
            dest[i - 1] = src[i - 1];
        }
    } else {
        // Non-overlapping memory regions, safe to use memcpy
        for (size_t i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    }

    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
    const unsigned char *p1 = (const unsigned char *)ptr1;
    const unsigned char *p2 = (const unsigned char *)ptr2;

    for (size_t i = 0; i < num; i++) {
        if (p1[i] < p2[i]) {
            return -1;
        } else if (p1[i] > p2[i]) {
            return 1;
        }
    }

    return 0;
}

void *memset(void *source, int value, size_t num) {
    unsigned char *p = (unsigned char *)source;
    unsigned char v = (unsigned char)value;

    for (size_t i = 0; i < num; i++) {
        p[i] = v;
    }

    return source;
}

