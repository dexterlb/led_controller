#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "uart.h"
#include "clock.h"
#include "error.h"
#include "pwm.h"
#include "utils.h"

void Error_Handler(void);

GPIO_InitTypeDef   gpio;

typedef struct {
    // settable by user:
    float gamma;
    float val;
    float ratio;
    float fade_speed;

    // internal:
    float actual_a;
    float actual_b;
} chan_t;

typedef struct {
    chan_t channels[1];
} state_t;

void default_state(state_t* state) {
    for (size_t i = 0; i < length(state->channels); i++) {
        state->channels[i].gamma = 2.2;
        state->channels[i].val = 0.5;
        state->channels[i].ratio = 0.5;
        state->channels[i].fade_speed = 2.0;
        state->channels[i].actual_a = 0.0;
        state->channels[i].actual_b = 0.0;
    }
}

chan_t* resolve_chan(state_t* state, uint8_t* chan_name) {
    if (string_eq(chan_name, str("ch1"))) {
        return &state->channels[0];
    }

    return NULL;
}

float* resolve_float_field(chan_t* chan, uint8_t* field_name) {
    if (string_eq(field_name, str("gamma"))) {
        return &chan->gamma;
    }
    if (string_eq(field_name, str("val"))) {
        return &chan->val;
    }
    if (string_eq(field_name, str("ratio"))) {
        return &chan->ratio;
    }
    if (string_eq(field_name, str("fade_speed"))) {
        return &chan->fade_speed;
    }
    return NULL;
}

void validate_float_field(float* field, chan_t* chan) {
    switch ((size_t)field - (size_t)chan) {
        case offsetof(chan_t, gamma):
            clamp(field, 1.0, 16.0);
            break;
        case offsetof(chan_t, val):
        case offsetof(chan_t, ratio):
            clamp(field, 0.0, 1.0);
            break;
        case offsetof(chan_t, fade_speed):
            clamp(field, 0.0, 65536.0);
            break;
    }
}

void print_field(uint8_t* section_name, uint8_t* field_name, uint8_t* field_content) {
    uart_queue(str("val "));
    uart_queue(section_name);
    uart_queue(str(" "));
    uart_queue(field_name);
    uart_queue(str(" "));
    uart_queue(field_content);
    uart_queue(str("\r\n"));
}

void print_float_field(uint8_t* section_name, uint8_t* field_name, float field) {
    print_field(section_name, field_name, str_float_fixed(field));
}

bool handle_set(state_t* state, uint8_t** args) {
    if (!args[0] || !args[1] || !args[2]) {
        return false;
    }

    chan_t* chan = resolve_chan(state, args[0]);
    if (!chan) {
        return false;
    }

    float* field = resolve_float_field(chan, args[1]);
    if (field) {
        *field = parse_float_fixed(args[2]);
        validate_float_field(field, chan);
        print_float_field(args[0], args[1], *field);
        return true;
    }

    return false;
}

bool handle_get(state_t* state, uint8_t** args) {
    if (!args[0] || !args[1]) {
        return false;
    }

    chan_t* chan = resolve_chan(state, args[0]);
    if (!chan) {
        return false;
    }

    float* field = resolve_float_field(chan, args[1]);
    if (field) {
        print_float_field(args[0], args[1], *field);
        return true;
    }

    return false;
}

void handle_msg(state_t* state, uint8_t* msg) {
    uint8_t* args[5];
    split_string(args, msg, ' ', length(args) - 1);

    if (!args[0]) {
        Error_Handler();
        return;
    }

    if (string_eq(args[0], str("set"))) {
        if (handle_set(state, &args[1])) {
            return;
        }
    } else if (string_eq(args[0], str("get"))) {
        if (handle_get(state, &args[1])) {
            return;
        }
    }

    uart_queue(str("unable to parse: "));
    for (int i = 0; args[i] != NULL; i++) {
        uart_queue(args[i]);
        if (args[i + 1] != NULL) {
            uart_queue(str(" "));
        }
    }
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

void bump_val(float* val, float speed, float target) {
    float delta = speed * 0.001;
    if (target - *val >= 0) {
        *val += delta;
        clamp_max(val, target);
    } else {
        *val -= delta;
        clamp_min(val, target);
    }
}

void pwm_set_chan(size_t index, uint32_t duty_a, uint32_t duty_b) {
    switch (index) {
        case 0:
            pwm_set(11, duty_a);
            pwm_set(12, duty_b);
            break;
    }
}

void update_channel(size_t chan_index, chan_t* chan) {
    float target_a = chan->val * chan->ratio;
    float target_b = chan->val * (1.0 - chan->ratio);
    bump_val(&chan->actual_a, chan->fade_speed, target_a);
    bump_val(&chan->actual_b, chan->fade_speed, target_b);
    pwm_set_chan(
        chan_index,
        powf(chan->actual_a, chan->gamma) * PWM_PERIOD,
        powf(chan->actual_b, chan->gamma) * PWM_PERIOD
    );
}

void update(state_t* state) {
    for (size_t i = 0; i < length(state->channels); i++) {
        update_channel(i, &state->channels[i]);
    }
}

void debug_info(state_t* state) {
    uart_queue(str("\r\n"));
    for (size_t i = 0; i < length(state->channels); i++) {
        uart_queue(str("channel "));
        uart_queue(str_int(i + 1));
        uart_queue(str("\r\n"));
        uart_queue(str("  gamma: "));
        uart_queue(str_float_fixed(state->channels[i].gamma));
        uart_queue(str("\r\n"));
        uart_queue(str("  val: "));
        uart_queue(str_float_fixed(state->channels[i].val));
        uart_queue(str("\r\n"));
        uart_queue(str("  ratio: "));
        uart_queue(str_float_fixed(state->channels[i].ratio));
        uart_queue(str("\r\n"));
        uart_queue(str("  fade speed: "));
        uart_queue(str_float_fixed(state->channels[i].fade_speed));
        uart_queue(str("\r\n"));
        uart_queue(str("\r\n"));
        uart_queue(str("  actual A: "));
        uart_queue(str_float_fixed(state->channels[i].actual_a));
        uart_queue(str("\r\n"));
        uart_queue(str("  actual B: "));
        uart_queue(str_float_fixed(state->channels[i].actual_b));
        uart_queue(str("\r\n"));
        uart_queue(str("\r\n"));
        uart_queue(str("  linear A: "));
        uart_queue(str_float_fixed(powf(state->channels[i].actual_a, state->channels[i].gamma)));
        uart_queue(str("\r\n"));
        uart_queue(str("  linear B: "));
        uart_queue(str_float_fixed(powf(state->channels[i].actual_b, state->channels[i].gamma)));
        uart_queue(str("\r\n"));
    }
}

state_t state;

void systick() {
    static uint16_t update_counter;
    if (update_counter % update_interval_ms == 0) {
        update(&state);
        update_counter = 0;
    }
    update_counter++;

    // static uint16_t debug_counter;
    // if (debug_counter % 1000 == 0) {
    //     debug_info(&state);
    //     debug_counter = 0;
    // }
    // debug_counter++;
}

int main(void) {
    default_state(&state);
    init();

    uart_queue(str("hello\r\n"));
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
        uint8_t* msg = uart_receive_poll();
        if (msg) {
            handle_msg(&state, msg);
            uart_receive_done();
        }

        uart_transmit();
    }
}
