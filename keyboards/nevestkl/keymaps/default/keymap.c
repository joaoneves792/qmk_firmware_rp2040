// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "uart.h"
#include "raw_hid.h"

#define QK_IS_BASIC(kc) (kc > QK_BASIC && kc <= QK_BASIC_MAX)

#define _BL 0
#define _FN 1
#define _ESP 2
#define _VIM 3

uint8_t rgb_current_layer = _BL;
uint8_t g_vim_count = 0;

extern keyrecord_t last_record;
extern uint8_t     last_mods;

enum custom_keycodes {
    QMKDOOM = SAFE_RANGE,
    KC_REP,
    KC_RREP,
    KC_VIMC0,
    KC_VIMC1,
    KC_VIMC2,
    KC_VIMC3,
    KC_VIMC4,
    KC_VIMC5,
    KC_VIMC6,
    KC_VIMC7,
    KC_VIMC8,
    KC_VIMC9,
    KC_DBELL,
    KC_SHELLY1,
    KC_SHELLY2,
    KC_ESPREG0,
    KC_ESPREG1,
    KC_ESPREG2,
    KC_ESPREG3,
    KC_ESPREG4,
    KC_ESPREG5,
    KC_ESPREG6,
    KC_ESPREG7,
    KC_ESPREG8,
    KC_ESPREG9,
    QK_SA,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        KC_PSCR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS,
        SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  SC_RSPC, KC_ENT,
        SC_LCPO, KC_LGUI, SC_LAPO, KC_SPC, SC_RAPC, MO(_FN), QK_REP, SC_RCPC, KC_LEFT, KC_DOWN,  KC_UP, KC_RGHT, KC_BSPC,
        KC_NO, KC_NO, KC_NO, KC_PSCR, KC_SCRL, KC_PAUS, KC_DEL, KC_INS, KC_HOME, KC_PGUP, KC_DEL, KC_END, KC_PGDN
    ),
    [_FN] = LAYOUT(
        QK_REBOOT, QK_BOOTLOADER, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_OUTPUT_USB, QK_OUTPUT_BLUETOOTH, 
        _______, KC_ESPREG1, KC_ESPREG2, KC_ESPREG3, KC_ESPREG4, KC_ESPREG5, KC_ESPREG6, KC_ESPREG7, KC_ESPREG8, KC_ESPREG9, KC_ESPREG0, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        TG(_ESP), _______, UG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,TG(_VIM), _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ESP] = LAYOUT(
        KC_DBELL, KC_SHELLY1, KC_SHELLY2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        TG(_ESP), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_V, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_VIM] = LAYOUT(
        QMKDOOM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, KC_VIMC1, KC_VIMC2, KC_VIMC3, KC_VIMC4, KC_VIMC5, KC_VIMC6, KC_VIMC7, KC_VIMC8, KC_VIMC9, KC_VIMC0, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        TG(_VIM), QK_SA, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______,TG(_VIM), _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const uint8_t keycode_to_ascii_lut[58] PROGMEM = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0x0D, 0x1B, 0x08, 0x09, ' ', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/'};
#define SEND_STRING_ESP(str)  for(int esplen = 0; esplen < strlen(str); esplen++){ uart_write(str[esplen]); }; 

bool process_vimcount(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed && (QK_IS_BASIC(keycode) )){
      if ( g_vim_count > 1 ){ 
        layer_state_t saved_layer_state = layer_state;
        uint8_t saved_mods = (get_mods() | get_weak_mods());
        for(;g_vim_count > 1; g_vim_count--){
            clear_keyboard();
            layer_clear();

            register_mods(saved_mods);
            //SEND_STRING("", SS_TAP(keycode));

            //record->event.pressed = true;
            //process_record(record); 
            //wait_ms(50);
            //record->event.pressed = false;
            //process_record(record);
            //wait_ms(50);

            clear_keyboard();
            layer_state = saved_layer_state;
        }


        return false;
      }
    }
    return true;
}

void process_doom(void){
    //SEND_STRING_DELAY("The code you write makes you a programmer. The code you delete makes you a good one. The code you don't have to write makes you a great one.", 50);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" Wake up, Neo...", 50);
    SEND_STRING_DELAY(" \b \b \b", 200);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" The Matrix has you...", 50);
    SEND_STRING_DELAY(" \b \b \b", 200);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" Follow the white rabbit.", 50);
    SEND_STRING_DELAY(" \b \b \b", 200);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" 671tch iN Th3 M4trix.", 0);
    SEND_STRING_DELAY("  ", 244);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" 671tch iN Th3 M4trix.", 0);
    SEND_STRING_DELAY("  ", 244);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" 671tch iN Th3 M4trix.", 0);
}


bool process_esp(uint8_t keycode, keyrecord_t *record){
    if (!(record->event.pressed) && keycode < 58){
      uint8_t ascii = keycode_to_ascii_lut[(uint8_t)keycode];

      //Order is important! 
      //(Ctrl+Alt+P = DLE)
      //(Ctrl+Alt+Q = DC1)
      //(Ctrl+Alt+R = DC2)
      if (get_mods() & MOD_MASK_CTRL){
        ascii &= 0b00001111; 
      }
      if (get_mods() & MOD_BIT(KC_RALT)){
        ascii ^= 0b00010000;
      }
      if (get_mods() & MOD_BIT(KC_LALT)){
        ascii ^= 0b00010000;
      }
      if (get_mods() & MOD_BIT(KC_LSFT)){
        ascii ^= 0b00100000;
      }
      if (get_mods() & MOD_BIT(KC_RSFT)){
        ascii ^= 0b00100000;
      }
      uart_write(ascii);
    }

    return false;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
    if (!(record->event.pressed) && keycode == KC_DBELL){
      uart_write(0x07); //Ascii BEL
    }

    if ( layer_state_is(_ESP) && QK_IS_BASIC(keycode)) {
      return process_esp(keycode, record);
    }
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /*if ( layer_state_is(_ESP) && QK_IS_BASIC(keycode)) {
      return process_esp(keycode, record);
    }*/
    switch (keycode) {
      case QMKDOOM:
          if (record->event.pressed) {
            process_doom();
          }
          return false;
      case KC_SHELLY1:
          if (record->event.pressed){
            SEND_STRING_ESP("shelly 1;");
          }
          return false;
      case KC_SHELLY2:
          if (record->event.pressed){
            SEND_STRING_ESP("shelly 2;");
          }
          return false;
      case KC_ESPREG0:
      case KC_ESPREG1:
      case KC_ESPREG2:
      case KC_ESPREG3:
      case KC_ESPREG4:
      case KC_ESPREG5:
      case KC_ESPREG6:
      case KC_ESPREG7:
      case KC_ESPREG8:
      case KC_ESPREG9:
        if (record->event.pressed){
          char buffer[32];
          snprintf(buffer, 32, ">k get %d;", keycode - KC_ESPREG0);
          SEND_STRING_ESP(buffer);
        }
        return false;
      case KC_VIMC0:
      case KC_VIMC1:
      case KC_VIMC2:
      case KC_VIMC3:
      case KC_VIMC4:
      case KC_VIMC5:
      case KC_VIMC6:
      case KC_VIMC7:
      case KC_VIMC8:
      case KC_VIMC9:
        g_vim_count = keycode - KC_VIMC0;
        layer_off(_VIM);
      default:
        return true;
    }
    return true;
};

void keyboard_post_init_user(void) {
  uart_init(9600);
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Your code goes here
    // `data` is a pointer to the buffer containing the received HID report
    // `length` is the length of the report - always `RAW_EPSIZE`
    for(uint8_t i = 0; i < length; i++){
      if(data[i] == 0){
        break;
      }
      //raw_hid_send(data, length);
      uart_write(data[i]);
    }
}

void housekeeping_task_user(void) {
  static uint32_t last_mouse_report = 0;
  if ( uart_available()){
    uint8_t c = uart_read();
    if(c == 0x12){ //DC2 -> mouse
      report_mouse_t mr;
      mr.buttons = uart_read();
      mr.x = ((uint16_t)uart_read() << 8 ) | uart_read();
      mr.y = ((uint16_t)uart_read() << 8 ) | uart_read();
      mr.v = uart_read();
      mr.h = 0;
      if(last_mouse_report + 8 < timer_read32()){
        host_mouse_send(&mr);
        last_mouse_report = timer_read32();
      }
    }else if(c == 0x13){ //DC3 -> qmk console
      uprintf("%c", uart_read());
    }else{
      send_char(c); 
    }
  }
  //if( g_vim_count > 0){
  //  g_vim_count--;
  //  register_weak_mods(last_mods);
  //  process_record(&last_record);
  //  unregister_weak_mods(last_mods);
  //}
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FN:
        rgb_current_layer = _FN;
        break;
    case _VIM:
        rgb_current_layer = _VIM;
        break;
    case _ESP:
        rgb_current_layer = _ESP;
        break;
    default: //  for any other layers, or the default layer
        rgb_current_layer = _BL;
        break;
    }
  return state;
}
