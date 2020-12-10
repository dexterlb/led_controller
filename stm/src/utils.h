#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

#include "vendor/fixedptc/fixedptc.h"

#define length(array) (sizeof(array)/sizeof(*(array)))

// split the string 's' by the given 'token', storing the resulting pointers.
// inserts '\0' chars in place of the tokens in the original string.
// into 'into', up to a maximum of 'n'.
// 'into' must have a size of at least 'n + 1', so that a terminating NULL
// can be inserted. segfaults if s is NULL.
void split_string(uint8_t* into[], uint8_t* s, uint8_t token, size_t n);

static inline uint8_t* str(char* arg) {
    return (uint8_t*)arg;
}

// checks if two strings are equal
bool string_eq(uint8_t* a, uint8_t* b);

// parse a fixed point number in the format '123.456'
fixedpt parse_fixedpt(uint8_t* str);

// int to string
uint8_t* str_int(int n);

// uint to string
uint8_t* str_uint(uint32_t n);

// fixedpt to string
uint8_t* str_fixedpt(fixedpt f);

uint32_t scale_int(uint32_t a, fixedpt v);

void clamp(fixedpt* v, fixedpt min, fixedpt max);
void clamp_min(fixedpt* v, fixedpt min);
void clamp_max(fixedpt* v, fixedpt max);
