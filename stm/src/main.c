#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "uart.h"
#include "clock.h"
#include "error.h"
#include "pwm.h"

void Error_Handler(void);

extern UART_HandleTypeDef uart1;
GPIO_InitTypeDef   gpio;

__IO ITStatus UartReady = RESET;

uint8_t uart_receive_buf;
uint8_t rec[100];
uint8_t rec_i = 0;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    UartReady = SET;
    rec_i = 0;
}

void uart_begin_receive() {
    if(HAL_UART_Receive_IT(&uart1, &uart_receive_buf, 1) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    rec[rec_i] = uart_receive_buf;
    uart_begin_receive();
    rec_i++;
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

    pwm_init();

    init_uart();
    UartReady = SET;
}

int main(void) {
    init();

    pwm_set(1, 333);
    pwm_set(2, 600);
    pwm_set(4, 20);

    uart_begin_receive();
    while (1)
    {
        HAL_Delay(800);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
        HAL_Delay(200);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

        while (UartReady != SET) {  }

        if (rec_i > 0) {
            UartReady = RESET;
            if (HAL_UART_Transmit_IT(&uart1, rec, rec_i) != HAL_OK) {
                Error_Handler();
            }
        }
    }
}
