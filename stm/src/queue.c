#include "queue.h"


bool queue_push(queue_t* q, uint8_t data) {
    queue_index_t r = (q->right_index + 1) % QUEUE_SIZE;
    if (r == q->left_index) {
        return false;
    }

    q->arr[r] = data;
    q->right_index = r;

    return true;
}

uint8_t queue_peek(queue_t* q) {
    return q->arr[q->left_index];
}

bool queue_empty(queue_t* q) {
    return (q->right_index == q->left_index);
}

void queue_pop(queue_t* q) {
    q->left_index = (q->left_index + 1) & QUEUE_SIZE;
}
