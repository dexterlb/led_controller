#pragma once

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_SIZE 24
typedef uint8_t queue_index_t;

typedef struct {
    uint8_t arr[QUEUE_SIZE];
    uint8_t left_index;
    uint8_t right_index;
} queue_t;


bool queue_push(queue_t* q, uint8_t data);
uint8_t queue_peek(queue_t* q);
bool queue_empty(queue_t* q);
void queue_pop(queue_t* q);
