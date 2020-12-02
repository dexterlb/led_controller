#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "uart.h"
#include "clock.h"
#include "error.h"
#include "pwm.h"

void Error_Handler(void);

GPIO_InitTypeDef   gpio;

uint8_t* str(char* arg) {
    return (uint8_t*)arg;
}

void uart_handle_msg(uint8_t* msg) {
    uart_queue(str("msg: "));
    uart_queue(msg);
    uart_queue(str("\r\n"));
}

void init(void)
{
    HAL_Init();

    init_clock();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &gpio);

    // pwm_init();

    uart_init();
}

int main(void) {
    init();

    // for (uint32_t v = 0; true; v = (v + 1000) % PWM_PERIOD) {
    //     pwm_set(31, v);
    //     pwm_set(32, v);
    //     pwm_set(34, v);
    //     pwm_set(12, v);
    //     pwm_set(13, v);
    //     pwm_set(141, v);
    //     HAL_Delay(500);
    //     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
    //     HAL_Delay(500);
    //     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
    // }

    uart_begin_receive();
    while (1)
    {
        // HAL_Delay(800);
        // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
        // HAL_Delay(200);
        // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
        uart_receive(uart_handle_msg);
        uart_transmit();
    }
}
