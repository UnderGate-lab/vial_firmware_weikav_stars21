# WEIKAV STELLA 21 / STARS 21 (Vial, tri-mode wireless)

21-key numpad with USB / Bluetooth / 2.4 GHz connectivity.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986) (original), Vial port by Nobu
* Hardware Supported: WEIKAV STELLA 21, WEIKAV STARS 21 (MCU: WB32FQ95)
* Hardware Availability: [WEIKAV](http://www.weikavcn.com)

The vendor readme says the `stella21` source should be used for the Stars21; this port follows that.

## Build

    make weikav/stella21:vial

## Flashing

Bootloader: `wb32-dfu` (in the chip's ROM, so it can't be overwritten).

* **Bootmagic:** hold the top-left key (matrix `[0,0]`) and plug in USB. This also clears EEPROM.
  With the battery connected, turn the power switch off first: the MCU must actually restart.
* **Vial:** Security → Reboot to bootloader (requires unlock).
* **Hardware:** short the BOOT0 pads on the PCB (fallback).

Vial unlock combo: top-left key `[0,0]` + Enter `[4,3]` (physical positions).

## Wireless keys (Vial "User" tab)

| Index | Key | Action |
|---|---|---|
| 0 | USB | Switch to wired |
| 1–3 | BT1–BT3 | Switch Bluetooth host; hold 3 s to pair |
| 4–5 | BT4, BT5 | Defined but not implemented |
| 6 | 2.4G | Switch to 2.4 GHz dongle; hold 3 s to pair |

Default keymap: Fn = top-right key. Fn+7 = BT1, Fn+8 = BT2, Fn+9 = 2.4G, Fn+NumLock = USB.

## Changes from the vendor source

The vendor tree was based on QMK from around 2024. Changes needed to run it on current vial-qmk:

* `keymaps/vial/` added (VialRGB enabled); `keymaps/via/` removed.
* `keyboard.json`: matrix columns reduced from 17 to the 4 actually used (C1, C2, C3, A0); the other 13 were left over from the Stars80. Matches the vendor's VIA definition (6×4).
* `RGB_*` keycodes replaced with `RM_*`. In current QMK, `RGB_*` are aliases for RGB Light (underglow) and have no effect with RGB Matrix.
* `config.h`: `UART_TX_PAL_MODE` / `UART_RX_PAL_MODE` defined explicitly (moved out of `uart.h` upstream; value unchanged).
* `common/wireless/transport.c`: `keyboard_protocol` (removed upstream) replaced with `usb_device_state_set_protocol()`.
* `common/wireless/md_raw.*`: the vendor redirected `raw_hid_send()` by source line number. It is now implemented through `host_driver_t.send_raw_hid`, so Vial over wireless keeps working.
* Custom keycode order in `vial.json` now matches the firmware. In the vendor's VIA JSON the list was out of order (e.g. "BT_HOST1" actually sent USB).

Tested on hardware: wired, Vial, Bluetooth pairing, wake from STOP mode. Not yet tested: 2.4 GHz, Vial over wireless.

## License

GPL-2.0-or-later, same as QMK. The wireless driver (`keyboards/weikav/common/wireless`) is by Su (@isuua) and is GPL-2.0-or-later, as stated in each file's SPDX header.
