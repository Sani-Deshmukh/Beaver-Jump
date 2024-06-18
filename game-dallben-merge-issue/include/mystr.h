#ifndef __MYSTR_H
#define __MYSTR_H

#include <unistd.h>
#include "strarray.h"

/**
 * Returns the index of the first occurrence of sep in str starting from start.
 * 
 * If sep is not found, returns -1.
 * 
 * Example:
 * ```
 * assert(strindexof("hello", 'l', 0) == 2);
 * assert(strindexof("hello", 'l', 3) == 3);
 * assert(strindexof("hello", 'l', 4) == -1);
 * ```
 */
ssize_t mystr_indexof(const char *str, const char sep, size_t start);

/**
 * Splits a string into an array of strings using sep as the delimiter. Leading,
 * trailing, and repeated seperators should eliminated (i.e., there should be no
 * empty strings in the output).
 * 
 * The original string is not modified. The returned array and the strings
 * inside it are heap-allocated and should be freed by the caller using
 * `strarray_free` when they are no longer needed.
 */
strarray_t *mystr_split(const char *str, const char sep);

#endif /* __MYSTR_H */
