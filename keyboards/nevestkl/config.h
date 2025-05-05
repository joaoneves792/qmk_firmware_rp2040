// Copyright 2022 ziptyze (@ziptyze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
#define OLED_DISPLAY_128X32
*/
#define I2C1_SCL_PIN        GP15
#define I2C1_SDA_PIN        GP14
#define I2C_DRIVER I2CD1


#define SERIAL_USART_DRIVER vendor
#define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20
#define SERIAL_USART_SPEED 9600
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP16     // USART TX pin
#define SERIAL_USART_RX_PIN GP17    // USART RX pin


#define UART_TX_PIN GP16
#define UART_RX_PIN GP17
/*
#define OLED_BRIGHTNESS 64
#define OLED_FONT_H "keyboards/1upkeyboards/pi40/lib/glcdfont.c"



#define AUTO_SHIFT_TIMEOUT 250
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_ALPHA
#define NO_AUTO_SHIFT_NUMERIC
#define NO_AUTO_SHIFT_SPECTIAL

#define DEBOUNCE 10
*/
#define LCPO_KEYS KC_LCTL, KC_LSFT, KC_LBRC
#define RCPC_KEYS KC_RCTL, KC_LSFT, KC_RBRC
#define LAPO_KEYS KC_LALT, KC_TRNS, KC_LBRC
#define RAPC_KEYS KC_RALT, KC_TRNS, KC_RBRC

#define USE_FRANMEBUFFER

#define NO_AUTO_SHIFT_ALPHA

#include "config_led.h"
