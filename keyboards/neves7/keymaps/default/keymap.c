// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │Num│ / │ * │ = │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │ - │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ + │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │Ent│
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Enc│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_NUM,        KC_KP_SLASH,    KC_KP_ASTERISK,    KC_KP_EQUAL,
        KC_KP_7,       KC_KP_8,        KC_KP_9,           KC_KP_MINUS,
        KC_KP_4,       KC_KP_5,        KC_KP_6,           KC_KP_PLUS,
        KC_KP_1,       KC_KP_2,        KC_KP_3,           KC_KP_ENTER,
        KC_KP_0,       TG(1),          KC_KP_DOT,         ENC_PRESS
    ),
    [1] = LAYOUT(
        KC_C,          KC_SLSH,        CL_STAR,           CL_BACK,
        KC_7,          KC_8,           KC_9,              KC_MINS,
        KC_4,          KC_5,           KC_6,              CL_PLUS,
        KC_1,          KC_2,           KC_3,              CL_TYPE,
        KC_0,          TG(1),          KC_DOT,            KC_TRNS
    )
};

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CL_STAR:
            return true;
        case CL_PLUS:
            return true;
        case KC_MINS:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case CL_STAR:
            if(shifted)
              calcInput('^');
            else
              calcInput('*');
            break;
        case KC_MINS:
            if(shifted)
              calcInput('(');
            else
              calcInput('-');
            break;
        case CL_PLUS:
            if(shifted)
              calcInput(')');
            else
              calcInput('+');
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
