#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "uart.h"
#include "clock.h"
#include "error.h"
#include "pwm.h"
#include "utils.h"

#include "vendor/fixedptc/fixedptc.h"

void Error_Handler(void);

typedef struct {
    // settable by user:
    fixedpt gamma;
    fixedpt val;
    fixedpt fade_speed;

    // computed:
    fixedpt actual;
    fixedpt linear;
    int duty;
} chan_t;

typedef struct {
    chan_t channels[2];
} state_t;

void default_state(state_t* state) {
    for (size_t i = 0; i < length(state->channels); i++) {
        state->channels[i].val = fixedpt_rconst(0.5);
        state->channels[i].fade_speed = fixedpt_rconst(2.0);
        state->channels[i].gamma = fixedpt_rconst(2.2);
        state->channels[i].actual = fixedpt_rconst(0.0);
    }
}

chan_t* resolve_chan(state_t* state, uint8_t* chan_name) {
    if (string_eq(chan_name, str("ch1"))) {
        return &state->channels[0];
    }
    if (string_eq(chan_name, str("ch2"))) {
        return &state->channels[1];
    }

    return NULL;
}

fixedpt* resolve_float_field(chan_t* chan, uint8_t* field_name) {
    if (string_eq(field_name, str("gamma"))) {
        return &chan->gamma;
    }
    if (string_eq(field_name, str("val"))) {
        return &chan->val;
    }
    if (string_eq(field_name, str("fade_speed"))) {
        return &chan->fade_speed;
    }
    return NULL;
}

void validate_float_field(fixedpt* field, chan_t* chan) {
    switch ((size_t)field - (size_t)chan) {
        case offsetof(chan_t, gamma):
            clamp(field, fixedpt_rconst(1.0), fixedpt_rconst(16.0));
            break;
        case offsetof(chan_t, val):
            clamp(field, fixedpt_rconst(0.0), fixedpt_rconst(1.0));
            break;
        case offsetof(chan_t, fade_speed):
            clamp(field, fixedpt_rconst(0.0), fixedpt_rconst(255.0));
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

void print_float_field(uint8_t* section_name, uint8_t* field_name, fixedpt field) {
    print_field(section_name, field_name, str_fixedpt(field));
}

bool handle_set(state_t* state, uint8_t** args) {
    if (!args[0] || !args[1] || !args[2]) {
        return false;
    }

    chan_t* chan = resolve_chan(state, args[0]);
    if (!chan) {
        return false;
    }

    fixedpt* field = resolve_float_field(chan, args[1]);
    if (field) {
        *field = parse_fixedpt(args[2]);
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

    fixedpt* field = resolve_float_field(chan, args[1]);
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

    pwm_init();

    uart_init();
}

void bump_val(fixedpt* val, fixedpt speed, fixedpt target) {
    fixedpt delta = fixedpt_mul(speed, fixedpt_rconst(0.001));
    if (target - *val >= 0) {
        *val += delta;
        clamp_max(val, target);
    } else {
        *val -= delta;
        clamp_min(val, target);
    }
}

void update_channel(size_t chan_index, chan_t* chan) {
    bump_val(&chan->actual, chan->fade_speed, chan->val);

    chan->linear = fixedpt_pow(chan->actual, chan->gamma);
    chan->duty = scale_int(PWM_PERIOD, chan->linear);

    pwm_set(chan_index, chan->duty);
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
        uart_queue(str_uint(i + 1));
        uart_queue(str("\r\n"));
        uart_queue(str("  gamma: "));
        uart_queue(str_fixedpt(state->channels[i].gamma));
        uart_queue(str("\r\n"));
        uart_queue(str("  val: "));
        uart_queue(str_fixedpt(state->channels[i].val));
        uart_queue(str("\r\n"));
        uart_queue(str("  fade speed: "));
        uart_queue(str_fixedpt(state->channels[i].fade_speed));
        uart_queue(str("\r\n"));
        uart_queue(str("\r\n"));
        uart_queue(str("  actual: "));
        uart_queue(str_fixedpt(state->channels[i].actual));
        uart_queue(str("\r\n"));
        uart_queue(str("  linear: "));
        uart_queue(str_fixedpt(state->channels[i].linear));
        uart_queue(str("\r\n"));
        uart_queue(str("  duty: "));
        uart_queue(str_uint(state->channels[i].duty));
        uart_queue(str(" / "));
        uart_queue(str_uint(PWM_PERIOD));
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

#if debug_enabled
    static uint16_t debug_counter;
    if (debug_counter % 1000 == 0) {
        debug_info(&state);
        debug_counter = 0;
    }
    debug_counter++;
#endif
}

int main(void) {
    default_state(&state);
    init();

    uart_queue(str("hello\r\n"));

    uart_begin_receive();
    while (1)
    {
        HAL_Delay(1);
        uint8_t* msg = uart_receive_poll();
        if (msg) {
            handle_msg(&state, msg);
            uart_receive_done();
        }

        uart_transmit();
    }
}
