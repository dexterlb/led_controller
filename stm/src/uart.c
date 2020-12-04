#include "main.h"
#include "error.h"

#include <stdbool.h>

UART_HandleTypeDef uart1;

__IO ITStatus uart_ready = RESET;

// TODO: these can be circular buffers to save memory
// TODO: also, we can make it store multiple messages

uint8_t uart_receive_buf;
uint8_t rec[100];
uint8_t rec_i = 0;
uint8_t send[100];
uint8_t send_i = 0;
uint8_t local_send_buf[sizeof(send)];
uint8_t local_recv_buf[sizeof(rec)];
bool pending_received_msg = false;

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();


    __HAL_RCC_USART1_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_2;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*##-3- Configure the NVIC for UART ########################################*/
    /* NVIC for USART */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /*##-1- Reset peripherals ##################################################*/
    // HAL_RCC_USART1_FORCE_RESET();
    // HAL_RCC_USART1_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure UART Tx as alternate function  */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
    /* Configure UART Rx as alternate function  */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

    /*##-3- Disable the NVIC for UART ##########################################*/
    HAL_NVIC_DisableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void) {
    HAL_UART_IRQHandler(&uart1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    uart_ready = SET;
}

void uart_begin_receive() {
    if(HAL_UART_Receive_IT(&uart1, &uart_receive_buf, 1) != HAL_OK) {
        Error_Handler();
    }
}

void uart_queue(uint8_t* data) {
    for (int i = 0; data[i] != '\0'; i++) {
        send[send_i] = data[i];
        send_i++;
        if (send_i >= sizeof(send)) {
            Error_Handler();
        }
    }
}

void uart_transmit() {
    int i;

    if (send_i > 0) {
        for (i = 0; i < send_i; i++) {
            local_send_buf[i] = send[i];
        }

        send_i = 0;
        while (uart_ready != SET) {  }
        uart_ready = RESET;

        if (HAL_UART_Transmit_IT(&uart1, local_send_buf, i) != HAL_OK) {
            Error_Handler();
        }
    }
}

void uart_receive_async(void (*handler)(uint8_t*)) {
    if (pending_received_msg) {
        handler(local_recv_buf);
        pending_received_msg = false;
    }
}

uint8_t* uart_receive_poll() {
    if (pending_received_msg) {
        return local_recv_buf;
    } else {
        return NULL;
    }
}

void uart_receive_done() {
    pending_received_msg = false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if (uart_receive_buf == '\r' || uart_receive_buf == '\n' || uart_receive_buf == '\0') {
        if (rec_i != 0) {
            if (!pending_received_msg) {
                for (int i = 0; i < rec_i; i++) {
                    local_recv_buf[i] = rec[i];
                }
                local_recv_buf[rec_i] = '\0';
                pending_received_msg = true;
            } // skip the message if we haven't processed the previous one ;(
            rec_i = 0;
        }
    } else {
        rec[rec_i] = uart_receive_buf;
        if (rec_i < sizeof(rec) - 1) {
            // truncate messages which are too long
            rec_i++;
        }
    }
    uart_begin_receive();
}

void uart_init() {
    uart1.Instance            = USART1;
    uart1.Init.BaudRate       = 115200;
    uart1.Init.WordLength     = UART_WORDLENGTH_8B;
    uart1.Init.StopBits       = UART_STOPBITS_1;
    uart1.Init.Parity         = UART_PARITY_NONE;
    uart1.Init.Mode           = UART_MODE_TX_RX;
    uart1.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
    uart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&uart1) != HAL_OK) {
        Error_Handler();
    }

    uart_ready = SET;
}
