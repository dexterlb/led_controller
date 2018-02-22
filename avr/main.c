#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

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

void process_line(char* line) {
    uart_write_string("you said: ");
    uart_write_string(line);
    uart_write_newline();
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
