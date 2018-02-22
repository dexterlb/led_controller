#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <stdbool.h>
#include <stdlib.h>

#include "hardware.h"
#include "simple_uart.h"
#include "bit_operations.h"

const uint16_t TIMER_TOP = F_CPU / PWM_FREQ;
const float EPSILON = 0.00000001;

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

void set_brightness(uint8_t block, float brightness) {
    uint16_t compare_value;

    if (brightness < 0 + EPSILON) {
        compare_value = 0;
    } else if (brightness > 1 - EPSILON) {
        compare_value = TIMER_TOP;
    } else {
        compare_value = (uint16_t)(((float)TIMER_TOP) * brightness);
    }

    if (block == 0) {
        OCR1A = compare_value;
    }
    if (block == 1) {
        OCR1B = compare_value;
    }
}

void set_power(uint8_t switch_id, bool value) {
    uint8_t port;
    uint8_t pin;

    switch(switch_id) {
        case 0: pin = SWITCH_0_PIN; port = SWITCH_0_PORT; break;
        case 1: pin = SWITCH_1_PIN; port = SWITCH_1_PORT; break;
        case 2: pin = SWITCH_2_PIN; port = SWITCH_2_PORT; break;
        case 3: pin = SWITCH_3_PIN; port = SWITCH_3_PORT; break;
        case 4: pin = SWITCH_4_PIN; port = SWITCH_4_PORT; break;
        case 5: pin = SWITCH_5_PIN; port = SWITCH_5_PORT; break;
        default: return;
    }

    setbitval(port, pin, value);
}

static inline void init() {
    _delay_ms(100);

    DDRB = DDRB_STATE;
    DDRD = DDRD_STATE;

    PORTB = PORTB_STATE;
    PORTD = PORTD_STATE;

    timer1_init();
    set_brightness(0, 0.5);
    set_brightness(1, 0.7);

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

float current_brightness[2] = {};
bool current_power[6] = {};

void update_brightness(uint8_t block, float brightness) {
    current_brightness[block] = brightness;
    set_brightness(block, brightness);
}

void update_power(uint8_t switch_id, bool power) {
    current_power[switch_id] = power;
    set_power(switch_id, power);
}

void report_brightness(uint8_t block) {
    char buf[10];
    uart_write_string("%%status b");
    itoa(block, buf, 10);
    uart_write_string(buf);
    uart_write_string("=");
    dtostrf(current_brightness[block], 0, 4, buf);
    uart_write_string(buf);
    uart_write_string("\n");
}

void report_power(uint8_t switch_id) {
    char buf[10];
    uart_write_string("%%status s");
    itoa(switch_id, buf, 10);
    uart_write_string(buf);
    uart_write_string("=");
    itoa((int)current_power[switch_id], buf, 10);
    uart_write_string(buf);
    uart_write_string("\n");
}

void process_command(char* command) {
    char* arg;

    uint8_t id;
    float brightness;
    uint8_t power;

    if ((arg = trim_prefix(command, "set b")) != NULL) {
        if (command[0] != '\0' && command[1] == '=' && command[2] != '\0') {
            id = command[0] - '0';
            brightness = atof(&command[2]);

            if (id <= 1) {
                update_brightness(id, brightness);
                report_brightness(id);
                return;
            }
        }
    }
    /*
    if (sscanf(command, "get b%" SCNd8, &id) == 1 ) {
        if (id <= 1) {
            report_brightness(id);
            return;
        }
    }
    if (sscanf(command, "set s%" SCNd8 "=%" SCNd8, &id, &power) == 2 ) {
        if (id <= 5) {
            update_power(id, (power != 0));
            report_power(id);
            return;
        }
    }
    if (sscanf(command, "get s%" SCNd8, &id) == 1 ) {
        if (id <= 5) {
            report_power(id);
            return;
        }
    }
    */
}

void process_line(char* line) {
    uart_write_string("you said: ");
    uart_write_string(line);
    uart_write_newline();
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

    uart_write_string("hello!\n");

    for (;;) {
    }
    return 0;
}
