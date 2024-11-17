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
     * │ 1 │ 2 │ 3 │   │
     * ├───┼───┼───┤Ent│
     * │ 0 │00 │ . │   │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_NUM,        KC_KP_SLASH,    KC_KP_ASTERISK,    KC_KP_EQUAL,
        KC_KP_7,       KC_KP_8,        KC_KP_9,           KC_KP_MINUS,
        KC_KP_4,       KC_KP_5,        KC_KP_6,           KC_KP_PLUS,
        KC_KP_1,       KC_KP_2,        KC_KP_3,           KC_KP_ENTER,
        KC_KP_0,       TG(1),        KC_KP_DOT,         KC_KP_DOT
    ),
    [1] = LAYOUT(
        KC_C,          KC_SLSH,        CL_STAR,           KC_EQL,
        KC_7,          KC_8,           KC_9,              KC_MINS,
        KC_4,          KC_5,           KC_6,              CL_PLUS,
        KC_1,          KC_2,           KC_3,              KC_EQL,
        KC_0,          TG(1),          KC_DOT,            KC_DOT
    )
};
