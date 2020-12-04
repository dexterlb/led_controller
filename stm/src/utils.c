#include "utils.h"
#include "cfg.h"

#include <stdlib.h>

void split_string(uint8_t* into[], uint8_t* s, uint8_t token, size_t n) {
    for (size_t i = 0; i < n + 1; i++) {
        into[i] = NULL;
    }

    size_t arg_index = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
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

float parse_float_fixed(uint8_t* s) {
    if (!s) {
        return 0.0;
    }

    return (float)atoi((char*)s) / (float)float_denom;
}

uint8_t* str_float_fixed(float f) {
    return str_int(f * float_denom);
}

float parse_float(uint8_t* num, uint8_t* denom) {
    if (!num || !denom) {
        return 0.0;
    }

    return (float)atoi((char*)num) / (float)atoi((char*)denom);
}

#define max_len 10

uint8_t* str_float(float f) {
    // TODO: doesn't work for negatives
    static uint8_t buf[max_len + 1];

    buf[max_len] = '\0';

    int l = (int)f;
    int r = (int)(f * 1000.0);

    int i;
    for (i = 0; i < 3; i++) {
        buf[max_len - i - 1] = '0' + (r % 10);
        r /= 10;
    }
    buf[max_len - 3 - 1] = '.';
    for (i = max_len - 4 - 1; i >= 0 && l != 0; i--) {
        buf[i] = '0' + (l % 10);
        l /= 10;
    }

    return &buf[i + 1];
}

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

bool string_eq(uint8_t* a, uint8_t* b) {
    int i;

    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return (a[i] == '\0' && b[i] == '\0');
}

void clamp(float* v, float min, float max) {
    if (*v > max) {
        *v = max;
    }
    if (*v < min){
        *v = min;
    }
}
