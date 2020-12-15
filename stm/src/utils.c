#include "utils.h"
#include "cfg.h"

#include <stdlib.h>

void split_string(uint8_t* into[], uint8_t* s, uint8_t token, size_t n) {
    for (size_t i = 0; i < n + 1; i++) {
        into[i] = NULL;
    }

    size_t arg_index = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == token) {
            s[i] = '\0';
            arg_index++;
            continue;
        }

        if (into[arg_index] == NULL) {
            into[arg_index] = &s[i];
        }

        if (arg_index >= n - 1) {
            break;
        }
    }
}

fixedpt parse_fixedpt_pair(uint8_t* whole, uint8_t* frac) {
    if (!whole || !frac) {
        return fixedpt_rconst(0.0);
    }

    fixedpt result = fixedpt_fromint(atoi((char*)whole));
    fixedpt acc = fixedpt_rconst(0.1);
    for (size_t i = 0; frac[i] != '\0'; i++) {
        result += fixedpt_mul(acc, fixedpt_fromint(frac[i] - '0'));
        acc = fixedpt_mul(acc, fixedpt_rconst(0.1));
    }

    return result;
}

fixedpt parse_fixedpt(uint8_t* input) {
    uint8_t* parts[3];
    split_string(parts, input, '.', 2);
    if (parts[1] == NULL) {
        return parse_fixedpt_pair(parts[0], str(""));
    }
    return parse_fixedpt_pair(parts[0], parts[1]);
}

#define max_len 10

uint8_t* str_int(int n) {
    static uint8_t buf[max_len + 1];
    buf[max_len] = '\0';

    bool neg = n < 0;
    if (neg) {
        n = -n;
    }

    int i;
    for (i = 0; i < max_len - 1 && (n != 0 || i == 0); i++) {
        buf[max_len - i - 1] = '0' + (n % 10);
        n /= 10;
    }
    if (neg) {
        buf[max_len - i - 1] = '-';
        i++;
    }

    return &buf[max_len - i];
}

uint8_t* str_uint(uint32_t n) {
    static uint8_t buf[max_len + 1];
    buf[max_len] = '\0';

    int i;
    for (i = 0; i < max_len - 1 && (n != 0 || i == 0); i++) {
        buf[max_len - i - 1] = '0' + (n % 10);
        n /= 10;
    }

    return &buf[max_len - i];
}

uint8_t* str_fixedpt(fixedpt f) {
    return (uint8_t*)fixedpt_cstr(f, 4);
}

bool string_eq(uint8_t* a, uint8_t* b) {
    int i;

    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return (a[i] == '\0' && b[i] == '\0');
}

void clamp(fixedpt* v, fixedpt min, fixedpt max) {
    clamp_min(v, min);
    clamp_max(v, max);
}

void clamp_min(fixedpt* v, fixedpt min) {
    if (*v < min){
        *v = min;
    }
}

void clamp_max(fixedpt* v, fixedpt max) {
    if (*v > max){
        *v = max;
    }
}

uint32_t scale_int(uint32_t a, fixedpt v) {
    return (uint32_t)(((uint64_t)v * (uint64_t)a) / (1 << FIXEDPT_FBITS));
}
