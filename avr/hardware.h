#pragma once

#define PWM_FREQ 1000

#define BAUDRATE 57600
#define UART_CRLF

// port direction settings:
// 1 - out, 0 - in   v bits v
//                   76543210
#define DDRB_STATE 0b00011000
#define DDRC_STATE 0b00000000
#define DDRD_STATE 0b00000010

// pullup settings:
// 1 - on, 0 - off    v bits v
//                    76543210
#define PORTB_STATE 0b00000000
#define PORTD_STATE 0b00000000

#define LED_PORT PORTB
#define LED_BIT 3

#define SWITCH_0_PORT PORTB
#define SWITCH_0_PIN 0

#define SWITCH_1_PORT PORTB
#define SWITCH_1_PIN 1

#define SWITCH_2_PORT PORTB
#define SWITCH_2_PIN 2

#define SWITCH_3_PORT PORTB
#define SWITCH_3_PIN 3

#define SWITCH_4_PORT PORTB
#define SWITCH_4_PIN 4

#define SWITCH_5_PORT PORTB
#define SWITCH_5_PIN 5