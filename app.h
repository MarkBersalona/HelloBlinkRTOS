/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef APP_H
#define APP_H

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define LOG(...) {\
  sprintf(gucDiagnosticOutput, __VA_ARGS__);\
  sl_iostream_write(sl_iostream_vcom_handle, gucDiagnosticOutput, strlen(gucDiagnosticOutput));\
}

#define LED_INSTANCE               sl_led_led0

// For FreeRTOS items
#define MAIN_TASK_STACK_SIZE      configMINIMAL_STACK_SIZE
#define MAIN_TASK_PRIO            20
#define MAIN_QUEUE_COUNT          (256)
#define EXAMPLE_USE_STATIC_ALLOCATION      1

// Task periods
#define MAIN_TASK_PERIOD_MS (1000)

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void);

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);

/***************************************************************************//**
 * Initialize RTOS items
 ******************************************************************************/
void RTOS_init(void);

#endif  // APP_H
