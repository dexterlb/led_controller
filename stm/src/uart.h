#pragma once

// initialise uart
void uart_init();

// queue data for transmission
void uart_queue(uint8_t* data);

// start the receive interrupt
void uart_begin_receive();

// transmit all queued data
void uart_transmit();

// handle received messages
void uart_receive(void (*handler)(uint8_t*));

