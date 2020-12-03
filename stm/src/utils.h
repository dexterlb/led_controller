#pragma once

#include <stdint.h>
#include <sys/types.h>

#define length(array) (sizeof(array)/sizeof(*(array)))

// split the string 's' by the given 'token', storing the resulting pointers
// into 'into', up to a maximum of 'n'.
// 'into' must have a size of at least 'n + 1', so that a terminating NULL
// can be inserted.
void split_string(uint8_t* into[], uint8_t* s, uint8_t token, size_t n);

static inline uint8_t* str(char* arg) {
    return (uint8_t*)arg;
}
