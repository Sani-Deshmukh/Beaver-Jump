#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "strarray.h"
#include "mystr.h"

ssize_t mystr_indexof(const char *str, const char sep, size_t start)
{
    int size = strlen(str);
    for (int i = start; i < size; i++)
    {
        if (str[i] == sep)
        {
            return i;
        }
    }
    return -1;
}

strarray_t *mystr_split(const char *str, const char sep)
{
    // counting total number words
    size_t len = strlen(str);
    const char *ptr = str;

    size_t num_words = 0;
    while (*ptr != '\0')
    {
        // Skip leading spaces
        while (*ptr == sep)
        {
            ptr++;
        }
        if (*ptr != '\0')
        {
            num_words++;
            // Skip the word
            while (*ptr != sep && *ptr != '\0')
            {
                ptr++;
            }
        }
    }
    // create object
    strarray_t *result = strarray_init(num_words);

    // splitting strings
    size_t lastIndex = 0;
    size_t arrayIndex = 0;
    // skip leading seps
    while (str[lastIndex] == sep)
    {
        lastIndex++;
    }
    while (lastIndex < len && mystr_indexof(str, sep, lastIndex) != -1)
    {
        // skip leading seps
        while (str[lastIndex] == sep)
        {
            lastIndex++;
        }
        ssize_t index = mystr_indexof(str, sep, lastIndex);
        size_t word_length;
        if (index == -1) {  break;}
        else {
            word_length = index - lastIndex;
        }

        if (word_length > 0)
        {
            char *word = malloc(sizeof(char) * (word_length + 1));
            strncpy(word, str + lastIndex, word_length);
            word[word_length] = '\0';
            result->data[arrayIndex] = word;
            arrayIndex++;
        }
        lastIndex = index + 1;
    }
    
    // handle last word
    int wordLength = len - lastIndex;
    if (wordLength > 0)
    {
        char *word = malloc(sizeof(char) * (wordLength + 1));
        strncpy(word, str + lastIndex, wordLength);
        word[wordLength] = '\0';
        result->data[arrayIndex] = word;
    }

    return result;
}
