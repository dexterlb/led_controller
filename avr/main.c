#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "hardware.h"
#include "simple_uart.h"
#include "bit_operations.h"

static inline void timer1_init() {

}

static inline void init() {
    _delay_ms(100);

    DDRB = DDRB_STATE;
    DDRD = DDRD_STATE;

    PORTB = PORTB_STATE;
    PORTD = PORTD_STATE;

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
