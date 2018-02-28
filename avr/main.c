#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <stdbool.h>
#include <stdlib.h>

#include "hardware.h"
#include "simple_uart.h"
#include "bit_operations.h"

#define TIMER_TOP (F_CPU / PWM_FREQ)
#define BRIGHTNESS_MAX 0xffff

static inline void timer1_init() {
    // COMXX:   set at 0, clear on compare
    // WGMXX:   Fast PWM, top at ICR1
    // CSXX:    No prescaler

    TCCR1A =
        ( (1 << COM1A1)
        | (0 << COM1A0)
        | (1 << COM1B1)
        | (0 << COM1B0)
        | (1 << WGM11)
        | (0 << WGM10)
        );

    TCCR1B =
        ( (0 << ICNC1)
        | (0 << ICES1)
        | (1 << WGM13)
        | (1 << WGM12)
        | (0 << CS12)
        | (0 << CS11)
        | (1 << CS10)
        );

    ICR1 = TIMER_TOP;
}

void set_brightness(uint8_t block, uint32_t brightness) {
    uint16_t compare_value;

    if (brightness == 0) {
        compare_value = 0;
    } else if (brightness >= BRIGHTNESS_MAX) {
        compare_value = TIMER_TOP;
    } else {
        compare_value = (uint16_t)(((uint32_t)brightness * (uint32_t)TIMER_TOP) / BRIGHTNESS_MAX);
    }

    if (block == PWM_A_BLOCK) {
        if (compare_value == 0) {
            clearbit(TCCR1A, COM1A1);
            clearbit(PORTB, 3);
        } else if (compare_value >= TIMER_TOP || brightness >= BRIGHTNESS_MAX) {
            clearbit(TCCR1A, COM1A1);
            setbit(PORTB, 3);
        } else {
            clearbit(PORTB, 3);
            setbit(TCCR1A, COM1A1);
            OCR1A = compare_value;
        }
    }
    if (block == PWM_B_BLOCK) {
        if (compare_value == 0) {
            clearbit(TCCR1A, COM1B1);
            clearbit(PORTB, 4);
        } else if (compare_value >= TIMER_TOP || brightness >= BRIGHTNESS_MAX) {
            clearbit(TCCR1A, COM1B1);
            setbit(PORTB, 4);
        } else {
            setbit(TCCR1A, COM1B1);
            clearbit(PORTB, 4);
            OCR1B = compare_value;
        }
    }
}

void set_power(uint8_t switch_id, bool value) {
    switch(switch_id) {
        case 0: setbitval(SWITCH_0_PORT, SWITCH_0_BIT, value); return;
        case 1: setbitval(SWITCH_1_PORT, SWITCH_1_BIT, value); return;
        case 2: setbitval(SWITCH_2_PORT, SWITCH_2_BIT, value); return;
        case 3: setbitval(SWITCH_3_PORT, SWITCH_3_BIT, value); return;
        case 4: setbitval(SWITCH_4_PORT, SWITCH_4_BIT, value); return;
        case 5: setbitval(SWITCH_5_PORT, SWITCH_5_BIT, value); return;
        default: return;
    }
}

void set_led(uint8_t led_id, bool value) {
    switch(led_id) {
        case 0: setbitval(LED_0_PORT, LED_0_BIT, value); return;
        case 1: setbitval(LED_1_PORT, LED_1_BIT, value); return;
        default: return;
    }
}

static inline void init() {
    _delay_ms(100);

    DDRB = DDRB_STATE;
    DDRD = DDRD_STATE;

    PORTB = PORTB_STATE;
    PORTD = PORTD_STATE;

    set_brightness(0, 0);
    set_brightness(1, 0);

    timer1_init();

    uart_init();
    uart_enable_interrupt();

    sei();

    _delay_ms(100);
}

static inline void soft_reset()
{
    wdt_enable(WDTO_30MS);
    for(;;);
}

char* trim_prefix(char* s, char* prefix) {
    size_t i = 0;
    for (; prefix[i] != '\0'; i++) {
        if (s[i] != prefix[i]) {
            return NULL;
        }
        if (s[i] == '\0') {
            return NULL;
        }
    }

    return &s[i];
}

uint16_t current_brightness[2] = {};
bool current_power[6] = {};

void update_brightness(uint8_t block, uint16_t brightness) {
    current_brightness[block] = brightness;
    set_brightness(block, brightness);
}

void update_power(uint8_t switch_id, bool power) {
    current_power[switch_id] = power;
    set_power(switch_id, power);
}

void report(char item, uint8_t id) {
    char buf[10];
    uart_write_string("%status ");
    uart_write_byte(item);
    utoa(id, buf, 10);
    uart_write_string(buf);
    uart_write_byte('=');
    if (item == 'b') {
        utoa(current_brightness[id], buf, 10);
        uart_write_string(buf);
    } else {
        if (current_power[id]) {
            uart_write_byte('1');
        } else {
            uart_write_byte('0');
        }
    }
    uart_write_newline();
}

void process_set(char* arg) {
    if (arg[0] == '\0' || arg[1] == '\0' || arg[2] != '=' || arg[3] == '\0') {
        return;
    }

    uint8_t id = arg[1] - '0';

    uint16_t value = atoi(&arg[3]);

    switch(arg[0]) {
        case 'b':
            update_brightness(id, value);
            break;
        case 's':
            update_power(id, value);
            break;
        case 'l':
            set_led(id, value);
            break;
        default:
            uart_write_string("unknown key\n");
            return;
    }

    report(arg[0], id);
}

void process_command(char* command) {
    char* arg;

    if ((arg = trim_prefix(command, "set ")) != NULL) {
        process_set(arg);
    }
}

void process_line(char* line) {
    if (line[0] == '%') {
        process_command(&line[1]);
    }
}

// received char on uart
ISR(USART_RX_vect) {
    static char buf[50];
    static uint8_t i = 0;

    char c = uart_read_byte();

    if (c == '\n' || c == '\r') {
        buf[i] = '\0';
        if (i != 0) {
            process_line(buf);
        }
        i = 0;
    } else {
        buf[i] = c;
        if (i < sizeof(buf) - 1) {
            i++;
        }
    }
}


int main()
{
    init();

    for (;;) {
    }
    return 0;
}
