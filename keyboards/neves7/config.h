// Copyright 2022 ziptyze (@ziptyze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN        GP1
#define I2C1_SDA_PIN        GP0
#define I2C_DRIVER I2CD0
#define OLED_BRIGHTNESS 64
#define OLED_FONT_H "keyboards/1upkeyboards/pi40/lib/glcdfont.c"


#define AUTO_SHIFT_TIMEOUT 250
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_ALPHA
#define NO_AUTO_SHIFT_NUMERIC
#define NO_AUTO_SHIFT_SPECTIAL

#define DEBOUNCE 10
