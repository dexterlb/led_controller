#pragma once

#define PWM_PERIOD ((uint32_t)(666 - 1))
#define PWM_PRESCALER ((uint32_t)(SystemCoreClock / 16000000) - 1)

void pwm_init();
void pwm_set(uint8_t channel, uint32_t value);
