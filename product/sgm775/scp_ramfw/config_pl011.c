/*
 * Arm SCP/MCP Software
 * Copyright (c) 2017-2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "clock_devices.h"
#include "system_mmap.h"

#include <mod_pl011.h>

#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_macros.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>

static const struct fwk_element pl011_element_table[] = {
    [0] = {
        .name = "board-uart1",
        .data =
            &(struct mod_pl011_device_config){
                .reg_base = BOARD_UART1_BASE,
                .baud_rate_bps = 115200,
                .clock_rate_hz = 24 * FWK_MHZ,
                .clock_id = FWK_ID_ELEMENT_INIT(
                    FWK_MODULE_IDX_CLOCK,
                    CLOCK_DEV_IDX_FCMCLK),
                .pd_id = FWK_ID_NONE_INIT,
            },
    },

    [1] = { 0 },
};

static const struct fwk_element *get_pl011_table(fwk_id_t module_id)
{
    return pl011_element_table;
}

struct fwk_module_config config_pl011 = {
    .elements = FWK_MODULE_DYNAMIC_ELEMENTS(get_pl011_table),
};
