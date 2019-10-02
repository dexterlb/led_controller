#include "error.h"
#include "main.h"
#include "pwm.h"


void pwm_msp_init_tim3(TIM_HandleTypeDef* htim) {
    GPIO_InitTypeDef   GPIO_InitStruct;
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* Configure PB.04 (TIM3_Channel1), PB.05 (TIM3_Channel2), PB.00 (TIM3_Channel3),
       PB.01 (TIM3_Channel4) in output, push-pull, alternate function mode
       */
    /* Common configuration for all channels */
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL3;
    // GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL3;
    // HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL3, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

TIM_HandleTypeDef  TimHandle;
TIM_OC_InitTypeDef sConfig;

void pwm_init() {
    TimHandle.Instance = TIM3;

    TimHandle.Init.Prescaler         = PWM_PRESCALER;
    TimHandle.Init.Period            = PWM_PERIOD;
    TimHandle.Init.ClockDivision     = 0;
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    TimHandle.Init.RepetitionCounter = 0;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK) {
        error();
    } 
    sConfig.OCMode       = TIM_OCMODE_PWM1;
    sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
    sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
    sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
    sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
}

static void pwm_start(TIM_TypeDef* instance, uint8_t channel_handle, uint32_t value) {
    TimHandle.Instance = instance;
    sConfig.Pulse = value;
    if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, channel_handle) != HAL_OK) {
        error();
    }

    if (HAL_TIM_PWM_Start(&TimHandle, channel_handle) != HAL_OK) {
        error();
    }
}

void pwm_set(uint8_t chan, uint32_t value) {
    switch(chan) {
        case 1:
            pwm_start(TIM3, TIM_CHANNEL_1, value);
            return;
        case 2:
            pwm_start(TIM3, TIM_CHANNEL_2, value);
            return;
        case 4:
            pwm_start(TIM3, TIM_CHANNEL_4, value);
            return;
    }
    error();
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3) {
        pwm_msp_init_tim3(htim);
        return;
    }
    error();
}
