#pragma once

// initialise uart
void uart_init();

// queue data for transmission
void uart_queue(uint8_t* data);

// start the receive interrupt
void uart_begin_receive();

// transmit all queued data
void uart_transmit();

// handle last received message
void uart_receive(void (*handler)(uint8_t*));

// async message handling: retreive the last received message; NULL if none.
uint8_t* uart_receive_poll();

// async message handling: call this when done with the message returned by uart_receive_poll()
void uart_receive_done();
