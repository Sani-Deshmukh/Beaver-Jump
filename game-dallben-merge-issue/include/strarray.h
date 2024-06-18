#ifndef __STRARRAY_H
#define __STRARRAY_H

#include <stddef.h>

/**
 * A dynamically-sized array of strings.
 * 
 * The `data` field is a pointer to an array of strings, which are themselves
 * pointers to nul-terminated arrays of characters.
 * 
 * The `length` field is the number of strings in the array.
 * 
 * All the strings and the array itself are heap-allocated and should be freed.
 */
typedef struct strarray {
    char **data;
    size_t length;
} strarray_t;

/**
 * Allocates a new strarray_t with the given length.
 * 
 * Both the returned struct and the data pointer are separate heap allocations,
 * so this function requires multiple calls to malloc.
 * 
 * The `data` field is a pointer to an array of strings, which are initialized 
 * to NULL.
 * 
 * The `length` field is the number of strings in the array and matches the
 * given length.
 */
strarray_t *strarray_init(size_t length);

/**
 * Frees the given strarray_t, it's data, and all the strings inside it.
 * 
 * Each string in the array is freed using free, then the data pointer, and
 * finally the struct itself. Note that this means it is invalid to call this
 * function on a strarray_t which has elements that were not heap-allocated.
 */
void strarray_free(strarray_t *arr);

#endif /* __STRARRAY_H */
