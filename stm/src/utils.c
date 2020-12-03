#include "utils.h"

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
