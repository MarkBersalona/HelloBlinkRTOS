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
#include "semphr.h"
#include "queue.h"
#include "gconfig.h"
#include "app.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/


/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// Diagnostic output buffer
static char gucDiagnosticOutput[1000];

//
// FreeRTOS mutexes
//
StaticSemaphore_t xDiagnosticMutexBuffer;
SemaphoreHandle_t xDiagnosticMutex;

//
// FreeRTOS queues
//
StaticQueue_t xMainQueueBuffer;
uint8_t gucMainQueueStorage[MAIN_QUEUE_COUNT * sizeof(uint8_t)];
QueueHandle_t xMainQueueHandle;

//
// FreeRTOS tasks
//
StaticTask_t xMainTaskBuffer;
StackType_t  xMainStack[MAIN_TASK_STACK_SIZE];


/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

//
// FreeRTOS tasks
//
static void MainTask(void *arg);

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

  // Create RTOS objects and tasks
  RTOS_init();
}

/***************************************************************************//**
 * Initialize RTOS items
 ******************************************************************************/
void RTOS_init(void)
{
  TaskHandle_t xMainHandle = NULL;

#if (EXAMPLE_USE_STATIC_ALLOCATION == 1)


  /////////////////////////////
  //
  // Create mutexes
  //
  /////////////////////////////
  //xDiagnosticMutex = xSemaphoreCreateMutex();
  xDiagnosticMutex = xSemaphoreCreateMutexStatic(&xDiagnosticMutexBuffer);

  /////////////////////////////
  //
  // Create queues
  //
  /////////////////////////////
  xMainQueueHandle = xQueueCreateStatic(MAIN_QUEUE_COUNT, sizeof(uint8_t), gucMainQueueStorage, &xMainQueueBuffer);

  /////////////////////////////
  //
  // Create tasks
  //
  /////////////////////////////

  // Create Main Task without using any dynamic memory allocation
  xMainHandle = xTaskCreateStatic(MainTask,
                                  "Main task",
                                  MAIN_TASK_STACK_SIZE,
                                  ( void * ) NULL,
                                  osPriorityNormal,
                                  xMainStack,
                                  &xMainTaskBuffer);

  // Since puxStackBuffer and pxTaskBuffer parameters are not NULL,
  // it is impossible for xHandle to be null. This check is for
  // rigorous example demonstration.
  EFM_ASSERT(xMainHandle != NULL);

#else

  BaseType_t xReturned = pdFAIL;

  // Create Main Task using dynamic memory allocation
  xReturned = xTaskCreate(MainTask,
                          "Main task",
                          MAIN_TASK_STACK_SIZE,
                          ( void * ) NULL,
                          tskIDLE_PRIORITY + 1,
                          &xHandle);

  // Unlike task creation using static allocation, dynamic task creation can very likely
  // fail due to lack of memory. Checking the return value is relevant.
  EFM_ASSERT(xReturned == pdPASS);

#endif
}


/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}


/***************************************************************************//**
 * Print startup banner to Diagnostic output
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


/*******************************************************************************
 * Main task
 ******************************************************************************/
static void MainTask(void *arg)
{
  (void)&arg;
  uint8_t lucBlinkCounter=0;
  sl_led_state_t ltLEDState;

  //Use the provided calculation macro to convert milliseconds to OS ticks
  //const TickType_t xDelay = pdMS_TO_TICKS(MAIN_TASK_PERIOD_MS);;

  while (1)
  {
    ///////////////
    //
    // Toggle led
    //
    ///////////////
    ++lucBlinkCounter;
    if (lucBlinkCounter >= 4)
    {
      sl_led_turn_on(&LED_INSTANCE);
      ltLEDState = sl_led_get_state(&LED_INSTANCE);
      LOG("%s: lucBlinkCounter=%d \t LED is ON  \t ltLEDState=%d\r\n", __FUNCTION__, lucBlinkCounter, ltLEDState);
      lucBlinkCounter = 0;
    }
    else
    {
      sl_led_turn_off(&LED_INSTANCE);
      ltLEDState = sl_led_get_state(&LED_INSTANCE);
      LOG("%s: lucBlinkCounter=%d \t LED is OFF \t ltLEDState=%d\r\n", __FUNCTION__, lucBlinkCounter, ltLEDState);
    }

    ////////////////
    //
    // Task delay
    //
    ////////////////
    //// TEST MAB 2024.01.22 vTaskDelay(xDelay);
    osDelay(MAIN_TASK_PERIOD_MS);
  }
}

