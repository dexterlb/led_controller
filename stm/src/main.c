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
uint8_t send[100];
uint8_t send_i = 0;
uint8_t local_send_buf[sizeof(send)];

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    UartReady = SET;
}

void uart_begin_receive() {
    if(HAL_UART_Receive_IT(&uart1, &uart_receive_buf, 1) != HAL_OK) {
        Error_Handler();
    }
}

uint8_t* str(char* arg) {
    return (uint8_t*)arg;
}

void uart_queue(uint8_t* data) {
    for (int i = 0; data[i] != '\0'; i++) {
        send[send_i] = data[i];
        send_i++;
    }
}

void uart_transmit() {
    int i;

    if (send_i > 0) {
        for (i = 0; i < send_i; i++) {
            local_send_buf[i] = send[i];
        }

        send_i = 0;
        while (UartReady != SET) {  }
        UartReady = RESET;

        if (HAL_UART_Transmit_IT(&uart1, local_send_buf, i) != HAL_OK) {
            Error_Handler();
        }
    }
}

void process_msg(uint8_t* msg) {
    uart_queue(str("msg: "));
    uart_queue(msg);
    uart_queue(str("\r\n"));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if (uart_receive_buf == '\r' || uart_receive_buf == '\n' || uart_receive_buf == '\0') {
        if (rec_i != 0) {
            rec[rec_i] = '\0';
            process_msg(rec);
            rec_i = 0;
        }
    } else {
        rec[rec_i] = uart_receive_buf;
        rec_i++;
    }
    uart_begin_receive();
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

    init_uart();
    UartReady = SET;
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
        uart_transmit();
    }
}
