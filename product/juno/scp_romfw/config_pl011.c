/*
 * Arm SCP/MCP Software
 * Copyright (c) 2019-2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "juno_mmap.h"

#include <mod_pl011.h>

#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_macros.h>
#include <fwk_module.h>

static const struct fwk_element pl011_element_desc_table[] = {
    [0] = {
        .name = "board-uart1",
        .data =
            &(struct mod_pl011_device_config){
                .reg_base = FPGA_UART1_BASE,
                .baud_rate_bps = 115200,
                .clock_rate_hz = 24 * FWK_MHZ,

                /*
                 * The UART is usable as soon as the SYSTOP power domain is on.
                 * The SYSTOP power domain is enforced to be ON at the
                 * initialization of the Juno PPU module thus it is ON when the
                 * PL011 is started and there is no need to wait for a clock to
                 * be locked.
                 */
                .clock_id = FWK_ID_NONE_INIT,
                .pd_id = FWK_ID_NONE_INIT,
            },
    },

    [1] = { 0 },
};

static const struct fwk_element *get_pl011_table(fwk_id_t module_id)
{
    return pl011_element_desc_table;
}

struct fwk_module_config config_pl011 = {
    .elements = FWK_MODULE_DYNAMIC_ELEMENTS(get_pl011_table),
};
