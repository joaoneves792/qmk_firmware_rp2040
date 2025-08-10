# neves7

![neves7](imgur.com image replace me!)

rp2040 based numpad
- 3d-printed and handwired on a perfboard
- USB-C
- 3xUSB-A hub
- OLED Display with calculator/converter
- Encoder Knob for volume/brightness

* Keyboard Maintainer: [joaoneves792](https://github.com/joaoneves792)
* Hardware Supported: rp2040
* Hardware Availability: none, this is handwired


![20241207_210919](https://github.com/user-attachments/assets/1cefce3d-09f2-4ca3-9888-4cc77338a2cc)

![20241201_164906](https://github.com/user-attachments/assets/df5c5c56-7d3f-413c-a911-1d61984d37b2)

![20241117_215821](https://github.com/user-attachments/assets/a927122e-9ecf-452a-afbc-a1d9985ee689)

Make example for this keyboard (after setting up your build environment):


    make neves7:default

Flashing example for this keyboard:

    make neves7:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
