/*
Copyright 2021 gregorio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "oled.h"
#include "neves7.h"

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}

void change_oled_mode(void) {
    oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
}

void render_layer_section(void) {
    // Layer indicators

    oled_set_cursor(oled_max_chars()-21, 1);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("PAD"), false);
            break;
        case 1:
            oled_write_P(PSTR("CALC"), false);
            break;
        case 2:
            oled_write_P(PSTR("02"), false);
            break;
        case 3:
            oled_write_P(PSTR("03"), false);
            break;
        default:
            oled_write_P(PSTR("? "), false);
            break;
    }
}

void render_encoder_section(void) {

    oled_set_cursor(oled_max_chars()-7, 0);
    oled_write_P(PSTR("ENC"), false);
    switch (encoder_mode) {
        default:
        case ENC_MODE_VOLUME:
            oled_write_P(PSTR("VOL "), false);
            break;
        case ENC_MODE_MEDIA:
            oled_write_P(PSTR("MEDI"), false);
            break;
        case ENC_MODE_BRIGHTNESS:
            oled_write_P(PSTR("BRIT"), false);
            break;
    }
}

void render_leds_section(void) {

    led_t led_state = host_keyboard_led_state();

    oled_set_cursor(oled_max_chars()-21, 0);
    oled_write_P(led_state.caps_lock ? PSTR("Cap(x) ") : PSTR("Cap( ) "), false);
    oled_write_P(led_state.num_lock ? PSTR("Num(x) ") : PSTR("Num( ) "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("Scr(x)") : PSTR("Scr( )"), false);
}

void render_mode_section(void) {
}

void render_calc_section(void) {
    if (oled_mode == OLED_MODE_CALC) {
        oled_set_cursor(oled_max_chars()-strlen(calc_buffer), 2);
        oled_write(calc_buffer, false);
        oled_set_cursor(oled_max_chars()-strlen(calc_result_buffer), 3);
        oled_write(calc_result_buffer, false);
    }
}

static void render_logo(void) {
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void render_frame(void) {
    if (oled_logo_expired) {
        render_leds_section();
        render_layer_section();
        if (oled_mode == OLED_MODE_DEFAULT) {
          //empty
        } else if (oled_mode == OLED_MODE_CALC) {
            render_calc_section();
        } else if (oled_mode == OLED_MODE_OFF) {
            if (is_oled_on()) {
                oled_off();
            }
        }
    } else {
        render_logo();
        oled_logo_expired = timer_elapsed(oled_logo_timer) > OLED_LOGO_TIMEOUT;
    }
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    if (timer_elapsed(oled_frame_timer) > OLED_FRAME_TIMEOUT) {
        oled_clear();
        oled_frame_timer = timer_read();
        render_frame();
    }

    if (get_highest_layer(layer_state) == 1) {
        oled_mode = OLED_MODE_CALC;
    } else if (get_highest_layer(layer_state) == 2) {
        if (IS_LAYER_ON(1)) {
            oled_mode = OLED_MODE_CALC;
        } else {
            oled_mode = OLED_MODE_DEFAULT;
        }
    } else if (get_highest_layer(layer_state) == 3) {
        oled_mode = OLED_MODE_OFF;
    } else {
        oled_mode = OLED_MODE_DEFAULT;
    }
    return false;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    oled_logo_timer = timer_read();
    oled_frame_timer = timer_read();
    return rotation;
}
