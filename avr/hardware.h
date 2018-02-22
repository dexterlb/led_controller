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

#define SWITCH_PORTS {PORTB, PORTB, PORTB, PORTB, PORTB, PORTB}
#define SWITCH_PINS  {    1,     2,     3,     4,     5,     6}