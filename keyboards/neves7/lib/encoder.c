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

#include "neves7.h"

extern uint8_t calc_precision;

void change_encoder_mode(bool reverse) {
    if (reverse) {
        if (encoder_mode == 0) {
            encoder_mode = _NUM_ENCODER_MODES - 1;
        } else {
            encoder_mode = encoder_mode - 1;
        }
    } else {
        encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;
    }
}

void change_calc_base(bool reverse) {
    if (reverse) {
        if (calc_base == 0) {
            calc_base = _NUM_CALC_BASES - 1;
        } else {
            calc_base = calc_base - 1;
        }
    } else {
        calc_base = (calc_base + 1) % _NUM_CALC_BASES;
    }
}

uint16_t handle_encoder_cw(void) {
    uint16_t mapped_code = 0;

    switch (get_highest_layer(layer_state)) {
      default:
      case 0: //PAD MODE
        switch (encoder_mode) {
            default:
            case ENC_MODE_VOLUME:
                mapped_code = KC_VOLU;
                break;
            case ENC_MODE_BRIGHTNESS:
                mapped_code = KC_BRIGHTNESS_UP;
                break;
        }
        break;

      case 1: //Calculator mode
        switch (encoder_mode) {
            default:
            case ENC_MODE_VOLUME:
                calc_precision = ( calc_precision + 1 ) % 10;
                calcUpdate();
                break;
            case ENC_MODE_BRIGHTNESS:
                change_calc_base(false);
                calcUpdate();
                break;
        }
        break;
      }
    return mapped_code;
}

uint16_t handle_encoder_ccw(void) {
    uint16_t mapped_code = 0;

    switch (get_highest_layer(layer_state)) {
      default:
      case 0: //PAD MODE
        switch (encoder_mode) {
            default:
            case ENC_MODE_VOLUME:
                mapped_code = KC_VOLD;
                break;
            case ENC_MODE_BRIGHTNESS:
                mapped_code = KC_BRIGHTNESS_DOWN;
                break;
        }
        break;
      case 1: //Calculator mode
        switch (encoder_mode) {
            default:
            case ENC_MODE_VOLUME:
                calc_precision = (calc_precision == 0)? 10 : calc_precision;
                calc_precision = ( calc_precision - 1 ) % 10;
                calcUpdate();
                break;
            case ENC_MODE_BRIGHTNESS:
                change_calc_base(true);
                calcUpdate();
                break;
        }
        break;
    }
    return mapped_code;
}

uint16_t handle_encoder_press(void) {
    uint16_t mapped_code = 0;
    change_encoder_mode(false);

    //switch (encoder_mode) {
    //    default:
    //    case ENC_MODE_VOLUME:
    //        mapped_code = KC_MUTE;
    //        break;
    //    case ENC_MODE_MEDIA:
    //        mapped_code = KC_MEDIA_PLAY_PAUSE;
    //        break;
    //}

    return mapped_code;
}
