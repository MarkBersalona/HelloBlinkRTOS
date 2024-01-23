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
  xSemaphoreTake(xDiagnosticMutex, portMAX_DELAY);\
  sprintf(gucDiagnosticOutput, __VA_ARGS__);\
  sl_iostream_write(sl_iostream_vcom_handle, gucDiagnosticOutput, strlen(gucDiagnosticOutput));\
  xSemaphoreGive(xDiagnosticMutex);\
}

#define LED_INSTANCE               sl_led_led0

// For FreeRTOS items
#define MAIN_TASK_STACK_SIZE      configMINIMAL_STACK_SIZE
#define MAIN_TASK_PRIO            20
#define MAIN_QUEUE_COUNT          (256)
#define INPUT_TASK_STACK_SIZE     configMINIMAL_STACK_SIZE
#define INPUT_TASK_PRIO           20
#define INPUT_QUEUE_COUNT         (256)
#define OUTPUT_TASK_STACK_SIZE    configMINIMAL_STACK_SIZE
#define OUTPUT_TASK_PRIO          20
#define OUTPUT_QUEUE_COUNT        (256)
#define EXAMPLE_USE_STATIC_ALLOCATION      1

// Task periods
#define MAIN_TASK_PERIOD_MS   (100)
#define INPUT_TASK_PERIOD_MS  (100)
#define OUTPUT_TASK_PERIOD_MS (100)

//
// Intertask message IDs
//
typedef enum Intertask_messages
{
  msgid_NOP = 0,

  // for HelloBlinkRTOS
  msgid_MAIN_INPUT_TEST,  // no payload
  msgid_MAIN_OUTPUT_TEST,  // no payload
  msgid_MAIN_OUTPUT_LED_ON,  // no payload
  msgid_MAIN_OUTPUT_LED_OFF,  // no payload
} Intertask_message_ID;

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
