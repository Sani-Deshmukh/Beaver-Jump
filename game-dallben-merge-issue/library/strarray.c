#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "strarray.h"

/**
 * initializes the strarray object with a given length
 */
strarray_t *strarray_init(size_t length)
{
    strarray_t *out = malloc(sizeof(strarray_t));
    // check if this syntax is correct
    out->length = length;
    out->data = (char **)malloc(sizeof(char *) * length);
    for (size_t i = 0; i < length; i++)
    {
        out->data[i] = NULL;
    }
    return out;
}

/**
 * frees all the memory allocated to strarray
 */
void strarray_free(strarray_t *arr)
{
    (void)arr;
    for (size_t i = 0; i < arr->length; i++)
    {
        free(arr->data[i]);
    }
    free(arr->data);
    free(arr);
}
