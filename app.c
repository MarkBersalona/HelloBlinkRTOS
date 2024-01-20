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
#include <stdio.h>
#include <string.h>
#include "em_chip.h"
#include "sl_iostream.h"
#include "sl_iostream_init_instances.h"
#include "sl_iostream_handles.h"
#include "sl_simple_led.h"
#include "sl_simple_led_instances.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gconfig.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#ifndef BUFSIZE
#define BUFSIZE    80
#endif

#define LOG(...) {\
  sprintf(gucDiagnosticOutput, __VA_ARGS__);\
  sl_iostream_write(sl_iostream_vcom_handle, gucDiagnosticOutput, strlen(gucDiagnosticOutput));\
}

#ifndef LED_INSTANCE
#define LED_INSTANCE               sl_led_led0
#endif

#ifndef TOOGLE_DELAY_MS
#define TOOGLE_DELAY_MS            1000
//// TEST MAB 2024.01.20 #define TOOGLE_DELAY_MS            200
#endif

#ifndef BLINK_TASK_STACK_SIZE
#define BLINK_TASK_STACK_SIZE      configMINIMAL_STACK_SIZE
#endif

#ifndef BLINK_TASK_PRIO
#define BLINK_TASK_PRIO            20
#endif

#ifndef EXAMPLE_USE_STATIC_ALLOCATION
#define EXAMPLE_USE_STATIC_ALLOCATION      1
#endif


/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

/* Input buffer */
static char buffer[BUFSIZE];
static char gucDiagnosticOutput[1000];

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void blink_task(void *arg);
void PrintStartupBanner(void);


/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  //printf("Hello world\r\n");
//  /* Prevent buffering of output/input.*/
//#if !defined(__CROSSWORKS_ARM) && defined(__GNUC__)
//  setvbuf(stdout, NULL, _IONBF, 0);   /*Set unbuffered mode for stdout (newlib)*/
//  setvbuf(stdin, NULL, _IONBF, 0);   /*Set unbuffered mode for stdin (newlib)*/
//#endif

//  /* Output on vcom usart instance */
//  const char str1[] = "Hello world\r\n\r\n";
//  sl_iostream_write(sl_iostream_vcom_handle, str1, strlen(str1));
//
//  /* Setting default stream */
//  sl_iostream_set_default(sl_iostream_vcom_handle);
//  const char str2[] = "This is output on the default stream\r\n";
//  sl_iostream_write(SL_IOSTREAM_STDOUT, str2, strlen(str2));
//
//  /* Using printf */
//  printf("Hello world, via printf\r\n\r\n");

  // Using LOG
  //LOG("%s: Hello world, via LOG\r\n\r\n", __FUNCTION__);
  PrintStartupBanner();

  // Kick off blink task
  blink_init();
}

/***************************************************************************//**
 * Initialize blink example.
 ******************************************************************************/
void blink_init(void)
{
  TaskHandle_t xHandle = NULL;

#if (EXAMPLE_USE_STATIC_ALLOCATION == 1)

  static StaticTask_t xTaskBuffer;
  static StackType_t  xStack[BLINK_TASK_STACK_SIZE];

  // Create Blink Task without using any dynamic memory allocation
  xHandle = xTaskCreateStatic(blink_task,
                              "blink task",
                              BLINK_TASK_STACK_SIZE,
                              ( void * ) NULL,
                              tskIDLE_PRIORITY + 1,
                              xStack,
                              &xTaskBuffer);

  // Since puxStackBuffer and pxTaskBuffer parameters are not NULL,
  // it is impossible for xHandle to be null. This check is for
  // rigorous example demonstration.
  EFM_ASSERT(xHandle != NULL);

#else

  BaseType_t xReturned = pdFAIL;

  // Create Blink Task using dynamic memory allocation
  xReturned = xTaskCreate(blink_task,
                          "blink task",
                          BLINK_TASK_STACK_SIZE,
                          ( void * ) NULL,
                          tskIDLE_PRIORITY + 1,
                          &xHandle);

  // Unlike task creation using static allocation, dynamic task creation can very likely
  // fail due to lack of memory. Checking the return value is relevant.
  EFM_ASSERT(xReturned == pdPASS);

#endif
}

/*******************************************************************************
 * Blink task.
 ******************************************************************************/
static void blink_task(void *arg)
{
  (void)&arg;

  //Use the provided calculation macro to convert milliseconds to OS ticks
  const TickType_t xDelay = pdMS_TO_TICKS(TOOGLE_DELAY_MS);;

  while (1) {
    //Wait for specified delay
    vTaskDelay(xDelay);

    // Toggle led
    sl_led_toggle(&LED_INSTANCE);
    LOG("%s: LED toggled...\r\n", __FUNCTION__);
  }
}
/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}



/***************************************************************************//**
 * Print startup banner
 ******************************************************************************/
void PrintStartupBanner(void)
{
  LOG("\r\n\r\n\r\n");
  LOG("=================================<=>=================================\r\n");
  LOG("                      SparkFun Thing Plus Matter                     \r\n");
  LOG("                           HelloBlinkRTOS                            \r\n");
  LOG("                               v%s.%s.%s \r\n", VERSION_A,VERSION_B,VERSION_C);
  LOG("                             %s   \r\n", VERSION_DATE);
  LOG("=================================<=>=================================\r\n");
}
// end PrintStartupBanner
