#pragma once

void uart_init();
void uart_queue(uint8_t* data);
void uart_begin_receive();
void uart_transmit();

