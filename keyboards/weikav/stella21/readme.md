# WEIKAV STELLA 21 / STARS 21 (Vial, tri-mode wireless)

> [!WARNING]
> **Supported hardware: only the original WEIKAV Stars21 (non-Plus) PCB shown below.**
>
> Several boards are sold under the "Stars21" name, and their PCBs differ. **Not supported:**
> - **Stars21 Plus**
> - **Stars21-S / S21-HS** (USB Product ID `0xE543`)
> - **Other PCB revisions** (e.g. with the DFU pads in a different location)
>
> Flashing this firmware on another board has been reported to leave it stuck in DFU mode or with no keys responding.
> Before flashing, compare your PCB with the photos below. If it is different, get the stock firmware for your revision from your seller or WEIKAV ([weikav.com/waikv-software](https://weikav.com/waikv-software/)).
> Background: [issue #1 in qmk_firmware_weikav_stars21](https://github.com/UnderGate-lab/qmk_firmware_weikav_stars21/issues/1#issuecomment-4713265965).
>
> 対応基板は、下の写真と同じ **WEIKAV Stars21（Plusではない無印）** のPCBだけです。Stars21 Plus、Stars21-S（PID `0xE543`）、そのほかのリビジョンには書き込まないでください。

<p>
<img src="https://github.com/user-attachments/assets/5d4c9ea0-de82-4130-9682-934a4d43d8b6" width="30%" alt="Supported Stars21 PCB (1)">
<img src="https://github.com/user-attachments/assets/fd387993-1c9a-4c5b-b201-9847eadf059d" width="30%" alt="Supported Stars21 PCB (2)">
<img src="https://github.com/user-attachments/assets/5342b88b-fd6e-46b3-94ff-fa3fad7a64cb" width="30%" alt="Supported Stars21 PCB (3)">
</p>


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
