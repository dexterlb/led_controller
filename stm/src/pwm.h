#pragma once

// 1465Hz at 48MHz clock
#define PWM_PERIOD 0x7fff
#define PWM_PRESCALER 1

void pwm_init();
void pwm_set(uint8_t channel, uint32_t value);
