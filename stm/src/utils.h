#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

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

// parse a rational number from a numerator and denominator
float parse_float(uint8_t* num, uint8_t* denom);

// parse a float represented as an integer, multiplied by float_denom (in cfg.h)
float parse_float_fixed(uint8_t* s);

// int to string
uint8_t* str_int(int n);

// float to string
uint8_t* str_float(float f);

// float to string, represented as an integer, multiplied by float_denom (in cfg.h)
uint8_t* str_float_fixed(float f);

void clamp(float* v, float min, float max);
void clamp_min(float* v, float min);
void clamp_max(float* v, float max);
