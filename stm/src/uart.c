#include "main.h"
#include "error.h"

UART_HandleTypeDef uart1;

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();


  __HAL_RCC_USART1_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = GPIO_PIN_9;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART1;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
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

void init_uart() {
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
}
