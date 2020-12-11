#include "error.h"
#include "main.h"
#include "pwm.h"
#include "utils.h"

#include <stdbool.h>

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

typedef struct {
    TIM_HandleTypeDef* timer_handle;
    uint8_t chan_handle;
    bool is_started;
    bool align_right;
    bool polarity_low;
} pwm_chan_t;

pwm_chan_t all_channels[] = {
    {
        .timer_handle = &Tim1Handle,
        .chan_handle = TIM_CHANNEL_2,
    },
    {
        .timer_handle = &Tim1Handle,
        .chan_handle = TIM_CHANNEL_3,
        .align_right = true,
    },
};

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

static void pwm_start(pwm_chan_t* chan, uint32_t value) {
    if (chan->align_right) {
        value = PWM_PERIOD - value;
    }

    if (!chan->is_started) {
        pwmConfig.Pulse = value;

        bool polarity_low = chan->polarity_low;
        if (chan->align_right) {
            polarity_low = !polarity_low;
        }
        if (polarity_low) {
            pwmConfig.OCPolarity = TIM_OCPOLARITY_LOW;
        } else {
            pwmConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
        }

        if (HAL_TIM_PWM_ConfigChannel(chan->timer_handle, &pwmConfig, chan->chan_handle) != HAL_OK) {
            error();
        }

        if (HAL_TIM_PWM_Start(chan->timer_handle, chan->chan_handle) != HAL_OK) {
            error();
        }

        chan->is_started = true;
    } else {
        __HAL_TIM_SET_COMPARE(chan->timer_handle, chan->chan_handle, value);
    }
}

void pwm_set(uint8_t chan, uint32_t value) {
    if (chan >= length(all_channels)) {
        error();
    }
    pwm_start(&all_channels[chan], value);
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
