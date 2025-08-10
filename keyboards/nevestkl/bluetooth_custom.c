/*
Copyright 2019 Basic I/O Instruments(Scott Wei) <scot.wei@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "bluetooth.h"
#include "uart.h"
#include "progmem.h"
#include "wait.h"
#include "debug.h"
#include "usb_descriptor.h"
#include "report.h"

void bluetooth_init(void) {
    //uart_init(76800);
    uart_init(9600);
}

void bluetooth_task(void) {}

void bluetooth_send_keyboard(report_keyboard_t *report)
{
    uart_write(0x10); //ASCII DLE (data link escape)
    uart_write(0x1); //Keyboard
    uart_write(report->mods);
    const uint8_t keyboard_report_keys_count = 6;
    for (uint8_t i = 0; i < keyboard_report_keys_count; i++) {
        uart_write(report->keys[i]);
    }
}

void bluetooth_send_mouse(report_mouse_t *report)
{
    //uint8_t xpartA = (uint8_t)((report->x & 0xFF00) >> 8);
    //uint8_t xpartB = (uint8_t)(report->x & 0x00FF);
    //uint8_t ypartA = (uint8_t)((report->y & 0xFF00) >> 8);
    //uint8_t ypartB = (uint8_t)(report->y & 0x00FF);
    uart_write(0x10); //ASCII DLE (data link escape)
    uart_write(0x2); //Mouse
    //uart_write(report->buttons);
    //uart_write(xpartA);
    //uart_write(xpartB);
    //uart_write(ypartA);
    //uart_write(ypartB);
    //uart_write((uint8_t)report->v);
}

/*
+-----------------+-------------------+-------+
| Consumer Key    | Bit Map           | Hex   |
+-----------------+-------------------+-------+
| Home            | 00000001 00000000 | 01 00 |
| KeyboardLayout  | 00000010 00000000 | 02 00 |
| Search          | 00000100 00000000 | 04 00 |
| Snapshot        | 00001000 00000000 | 08 00 |
| VolumeUp        | 00010000 00000000 | 10 00 |
| VolumeDown      | 00100000 00000000 | 20 00 |
| Play/Pause      | 01000000 00000000 | 40 00 |
| Fast Forward    | 10000000 00000000 | 80 00 |
| Rewind          | 00000000 00000001 | 00 01 |
| Scan Next Track | 00000000 00000010 | 00 02 |
| Scan Prev Track | 00000000 00000100 | 00 04 |
| Random Play     | 00000000 00001000 | 00 08 |
| Stop            | 00000000 00010000 | 00 10 |
+-------------------------------------+-------+
#define CONSUMER2BLUEFRUIT(usage) \
    (usage == AUDIO_MUTE ? 0x00e2 : (usage == AUDIO_VOL_UP ? 0x00e9 : (usage == AUDIO_VOL_DOWN ? 0x00ea : (usage == TRANSPORT_NEXT_TRACK ? 0x00b5 : (usage == TRANSPORT_PREV_TRACK ? 0x00b6 : (usage == TRANSPORT_STOP ? 0x00b7 : (usage == TRANSPORT_STOP_EJECT ? 0x00b8 : (usage == TRANSPORT_PLAY_PAUSE ? 0x00b1 : (usage == AL_CC_CONFIG ? 0x0183 : (usage == AL_EMAIL ? 0x018c : (usage == AL_CALCULATOR ? 0x0192 : (usage == AL_LOCAL_BROWSER ? 0x0196 : (usage == AC_SEARCH ? 0x021f : (usage == AC_HOME ? 0x0223 : (usage == AC_BACK ? 0x0224 : (usage == AC_FORWARD ? 0x0225 : (usage == AC_STOP ? 0x0226 : (usage == AC_REFRESH ? 0x0227 : (usage == AC_BOOKMARKS ? 0x022a : 0)))))))))))))))))))
*/
void bluetooth_send_consumer(uint16_t usage) { }
