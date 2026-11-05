// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Raw HID (VIA/Vial) over the wireless module.
// The original vendor code redirected raw_hid_send() by source line number
// (md_raw.h). Newer QMK routes raw_hid_send() through host_driver_t.send_raw_hid,
// so the wireless driver implements that hook instead (see wireless.c).

#ifdef RAW_ENABLE

#    include "quantum.h"
#    include "wireless.h"
#    include "usb_descriptor.h"

void wireless_send_raw_hid(uint8_t *data, uint8_t length) {

    if (length != RAW_EPSIZE) {
        return;
    }

    md_send_raw(data, length);
}

void md_receive_raw_cb(uint8_t *data, uint8_t length) {
    void raw_hid_receive(uint8_t * data, uint8_t length);

    raw_hid_receive(data, length);
}

#endif
