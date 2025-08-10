# nevestkl

![nevestkl](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [joaonevestkl92](https://github.com/joaonevestkl92)
* Hardware Supported: rp2040
* Hardware Availability: none, this is handwired

This is a modded gmmk v1 tkl.
- rp2040 qmk keyboard and usb controller
- esp32s3 for displays / shell / wifi / ble / sdcard
- nrf52840 for esb/gazell and other 2.4Ghz protocols

repos for esp32 and nrf firmware:

[esp32 - tkldisp](https://github.com/joaoneves792/tkldisp)

[nrf52 - tklnrf52](https://github.com/joaoneves792/tklnrf52)

rp2040:
![20250810_083143](https://github.com/user-attachments/assets/65aa5497-ddd2-4a46-87b6-1cd5fdae91ca)

esp32:
![20250810_082833](https://github.com/user-attachments/assets/76ec41cf-9a4c-4675-a16c-8d486553a0db)

nrf52:
![20250810_092316](https://github.com/user-attachments/assets/9d95dcd2-1121-414a-8cef-59c20278490e)



Make example for this keyboard (after setting up your build environment):

    make nevestkl:default

Flashing example for this keyboard:

    make nevestkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
