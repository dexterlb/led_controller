#pragma once

#define PWM_FREQ 1000

// #define BAUDRATE 57600
// #define UART_CRLF
#define BAUDRATE 9600

// port direction settings:
// 1 - out, 0 - in   v bits v
//                   76543210
#define DDRB_STATE 0b00011111
#define DDRC_STATE 0b00000000
#define DDRD_STATE 0b01111110

// pullup settings:
// 1 - on, 0 - off    v bits v
//                    76543210
#define PORTB_STATE 0b00000000
#define PORTD_STATE 0b00000000

#define LED_0_PORT PORTB
#define LED_0_BIT 1

#define LED_1_PORT PORTB
#define LED_1_BIT 2

#define PWM_A_BLOCK 1
#define PWM_B_BLOCK 0

#define SWITCH_0_PORT PORTD
#define SWITCH_0_BIT 6

#define SWITCH_1_PORT PORTB
#define SWITCH_1_BIT 0

#define SWITCH_2_PORT PORTD
#define SWITCH_2_BIT 3

#define SWITCH_3_PORT PORTD
#define SWITCH_3_BIT 2

#define SWITCH_4_PORT PORTD
#define SWITCH_4_BIT 5

#define SWITCH_5_PORT PORTD
#define SWITCH_5_BIT 4