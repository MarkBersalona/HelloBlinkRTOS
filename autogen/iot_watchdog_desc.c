/***************************************************************************//**
 * @file    iot_watchdog_desc.c.jinja
 * @brief   Watchdog instance descriptors - auto-generated file.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

/*******************************************************************************
 *                               INCLUDES
 ******************************************************************************/

/* standard C */
#include "stddef.h"

/* Watchdog driver layer */
#include "iot_watchdog_desc.h"


/* instance wdog config */
#include "iot_watchdog_cfg_wdog.h"


/*******************************************************************************
 *                            DESCRIPTOR LIST
 ******************************************************************************/

IotWatchdogDescriptor_t iot_watchdog_desc[] = {


  /* instance wdog config */
  {
    /* instance number */
    .lInstNum           = IOT_WATCHDOG_CFG_WDOG_INST_NUM,

    /* selected peripheral */
    .em_instance        = IOT_WATCHDOG_CFG_WDOG_PERIPHERAL,
    .em_instance_no     = IOT_WATCHDOG_CFG_WDOG_PERIPHERAL_NO,

    /* WDOG0 clock and IRQ signals */
#if IOT_WATCHDOG_CFG_WDOG_PERIPHERAL_NO == 0
#if (_SILICON_LABS_32B_SERIES < 2)
    .cmu_clock          = cmuClock_HFLE,
#else
    .cmu_clock          = cmuClock_WDOG0,
#endif
    .irq_num            = WDOG0_IRQn,
#endif

    /* WDOG1 clock and IRQ signals */
#if IOT_WATCHDOG_CFG_WDOG_PERIPHERAL_NO == 1
#if (_SILICON_LABS_32B_SERIES < 2)
    .cmu_clock          = cmuClock_HFLE,
#else
    .cmu_clock          = cmuClock_WDOG1,
#endif
    .irq_num            = WDOG1_IRQn,
#endif
  },

};

/*******************************************************************************
 *                         iot_watchdog_desc_get
 ******************************************************************************/

IotWatchdogDescriptor_t *iot_watchdog_desc_get(int32_t lInstNum)
{
  int32_t lInstCount = sizeof(iot_watchdog_desc)/sizeof(IotWatchdogDescriptor_t);
  int32_t lInstCur   = 0;

  for (lInstCur = 0; lInstCur < lInstCount; lInstCur++) {
    if (iot_watchdog_desc[lInstCur].lInstNum == lInstNum) {
      return &iot_watchdog_desc[lInstCur];
    }
  }

  return NULL;
}
