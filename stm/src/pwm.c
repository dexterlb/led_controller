#include "error.h"
#include "main.h"
#include "pwm.h"


void pwm_msp_init_tim3(TIM_HandleTypeDef* htim) {
    GPIO_InitTypeDef   GPIO_InitStruct;
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void pwm_msp_init_tim1(TIM_HandleTypeDef* htim) {
    GPIO_InitTypeDef   GPIO_InitStruct;
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void pwm_msp_init_tim14(TIM_HandleTypeDef* htim) {
    GPIO_InitTypeDef   GPIO_InitStruct;
    __HAL_RCC_TIM14_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Alternate = GPIO_AF4_TIM14;
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

TIM_HandleTypeDef  Tim1Handle;
TIM_HandleTypeDef  Tim3Handle;
TIM_HandleTypeDef  Tim14Handle;
TIM_OC_InitTypeDef pwmConfig;

static void pwm_init_timer(TIM_HandleTypeDef* handle) {
    handle->Init.Prescaler         = PWM_PRESCALER;
    handle->Init.Period            = PWM_PERIOD;
    handle->Init.ClockDivision     = 0;
    handle->Init.CounterMode       = TIM_COUNTERMODE_UP;
    handle->Init.RepetitionCounter = 0;
    handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    __HAL_TIM_MOE_ENABLE(handle);
    if (HAL_TIM_PWM_Init(handle) != HAL_OK) {
        error();
    }
}

void pwm_init() {
    Tim1Handle.Instance = TIM1;
    Tim3Handle.Instance = TIM3;
    Tim14Handle.Instance = TIM14;

    pwmConfig.OCMode       = TIM_OCMODE_PWM1;
    pwmConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
    pwmConfig.OCFastMode   = TIM_OCFAST_DISABLE;
    pwmConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
    pwmConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    pwmConfig.OCIdleState  = TIM_OCIDLESTATE_SET;

    pwm_init_timer(&Tim1Handle);
    pwm_init_timer(&Tim3Handle);
    pwm_init_timer(&Tim14Handle);
}

static void pwm_start(TIM_HandleTypeDef* handle, uint8_t channel_handle, uint32_t value) {
    pwmConfig.Pulse = value;
    if (HAL_TIM_PWM_ConfigChannel(handle, &pwmConfig, channel_handle) != HAL_OK) {
        error();
    }

    if (HAL_TIM_PWM_Start(handle, channel_handle) != HAL_OK) {
        error();
    }
}

void pwm_set(uint8_t chan, uint32_t value) {
    switch(chan) {
        case 31:
            pwm_start(&Tim3Handle, TIM_CHANNEL_1, value);
            return;
        case 32:
            pwm_start(&Tim3Handle, TIM_CHANNEL_2, value);
            return;
        case 34:
            pwm_start(&Tim3Handle, TIM_CHANNEL_4, value);
            return;
        case 12:
            pwm_start(&Tim1Handle, TIM_CHANNEL_2, value);
            return;
        case 13:
            pwm_start(&Tim1Handle, TIM_CHANNEL_3, value);
            return;
        case 141:
            pwm_start(&Tim14Handle, TIM_CHANNEL_1, value);
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
    if (htim->Instance == TIM1) {
        pwm_msp_init_tim1(htim);
        return;
    }
    if (htim->Instance == TIM14) {
        pwm_msp_init_tim14(htim);
        return;
    }
    error();
}
