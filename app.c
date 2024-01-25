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
#include "em_cmu.h"
#include "em_wdog.h"

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
// Main task
StaticQueue_t xMainQueueBuffer;
uint8_t gucMainQueueStorage[MAIN_QUEUE_COUNT * sizeof(uint8_t)];
QueueHandle_t xMainQueueHandle;
// Input task
StaticQueue_t xInputQueueBuffer;
uint8_t gucInputQueueStorage[INPUT_QUEUE_COUNT * sizeof(uint8_t)];
QueueHandle_t xInputQueueHandle;
// Output task
StaticQueue_t xOutputQueueBuffer;
uint8_t gucOutputQueueStorage[OUTPUT_QUEUE_COUNT * sizeof(uint8_t)];
QueueHandle_t xOutputQueueHandle;

//
// FreeRTOS tasks
//
// Main task
StaticTask_t xMainTaskBuffer;
StackType_t  xMainStack[MAIN_TASK_STACK_SIZE];
// Input task
StaticTask_t xInputTaskBuffer;
StackType_t  xInputStack[INPUT_TASK_STACK_SIZE];
// Output task
StaticTask_t xOutputTaskBuffer;
StackType_t  xOutputStack[OUTPUT_TASK_STACK_SIZE];


/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

//
// FreeRTOS tasks
//
static void InputTask(void *arg);
static void MainTask(void *arg);
static void OutputTask(void *arg);

void PrintStartupBanner(void);
void Watchdog_init(void);


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

  // Create RTOS objects and tasks
  RTOS_init();

  // Initialize watchdog
  Watchdog_init();

}
// end app_init

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

/***************************************************************************//**
 * Initialize RTOS items
 ******************************************************************************/
void RTOS_init(void)
{
  TaskHandle_t xMainHandle = NULL;
  TaskHandle_t xInputHandle = NULL;
  TaskHandle_t xOutputHandle = NULL;

#if (EXAMPLE_USE_STATIC_ALLOCATION == 1)


  /////////////////////////////
  //
  // Create mutexes
  //
  /////////////////////////////
  xDiagnosticMutex = xSemaphoreCreateMutexStatic(&xDiagnosticMutexBuffer);

  /////////////////////////////
  //
  // Create queues
  //
  /////////////////////////////
  xMainQueueHandle   = xQueueCreateStatic(MAIN_QUEUE_COUNT,   sizeof(uint8_t), gucMainQueueStorage,   &xMainQueueBuffer);
  xInputQueueHandle  = xQueueCreateStatic(INPUT_QUEUE_COUNT,  sizeof(uint8_t), gucInputQueueStorage,  &xInputQueueBuffer);
  xOutputQueueHandle = xQueueCreateStatic(OUTPUT_QUEUE_COUNT, sizeof(uint8_t), gucOutputQueueStorage, &xOutputQueueBuffer);

  /////////////////////////////
  //
  // Create tasks
  //
  /////////////////////////////

  // Create tasks without using any dynamic memory allocation
  xMainHandle = xTaskCreateStatic(MainTask,
                                  "Main task",
                                  MAIN_TASK_STACK_SIZE,
                                  ( void * ) NULL,
                                  osPriorityNormal,
                                  xMainStack,
                                  &xMainTaskBuffer);
  xInputHandle = xTaskCreateStatic(InputTask,
                                  "Input task",
                                  INPUT_TASK_STACK_SIZE,
                                  ( void * ) NULL,
                                  osPriorityNormal,
                                  xInputStack,
                                  &xInputTaskBuffer);
  xOutputHandle = xTaskCreateStatic(OutputTask,
                                  "Output task",
                                  OUTPUT_TASK_STACK_SIZE,
                                  ( void * ) NULL,
                                  osPriorityNormal,
                                  xOutputStack,
                                  &xOutputTaskBuffer);

  // Since puxStackBuffer and pxTaskBuffer parameters are not NULL,
  // it is impossible for xHandle to be null. This check is for
  // rigorous example demonstration.
  EFM_ASSERT(xMainHandle != NULL);
  EFM_ASSERT(xInputHandle != NULL);
  EFM_ASSERT(xOutputHandle != NULL);

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
// end RTOS_init

/***************************************************************************//**
 * Initialize watchdog
 ******************************************************************************/
void Watchdog_init(void)
{
  //
  // Copied from Silicon Labs GitHub repository, peripheral example for Series 2 wdog
  // See https://github.com/SiliconLabs/peripheral_examples/tree/master/series2/wdog/wdog_led_toggle
  // main.c (or main_xg27.c), initWDOG()
  //

  // Enable clock for the WDOG module; has no effect on xG21
  CMU_ClockEnable(cmuClock_WDOG0, true);

  // Watchdog Initialize settings
  WDOG_Init_TypeDef wdogInit = WDOG_INIT_DEFAULT;
  CMU_ClockSelectSet(cmuClock_WDOG0, cmuSelect_ULFRCO); /* ULFRCO as clock source */
  wdogInit.debugRun = true;
  wdogInit.em3Run = true;
  //wdogInit.perSel = wdogPeriod_2k; // 2049 clock cycles of a 1kHz clock  ~2 seconds period
  //wdogInit.perSel = wdogPeriod_32k; // 32k clock cycles of a 1kHz clock  ~30 seconds period
  wdogInit.perSel = wdogPeriod_8k; // 8k clock cycles of a 1kHz clock  ~8 seconds period

  // Initializing watchdog with chosen settings
  WDOGn_Init(DEFAULT_WDOG, &wdogInit);
}
// end Watchdog_init


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
///
///                           TASKS
///
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 * Input task
 ******************************************************************************/
static void InputTask(void *arg)
{
  (void)&arg;
  uint32_t lulElapsedTime_msec = 0;
  uint32_t lulElapsedTime_Messages_msec = 0;
  UBaseType_t ltQueueWaitingCount;
  uint8_t lucMessageID;

  LOG("%s: Initializing...\r\n", __FUNCTION__);

  while (1)
  {
    lulElapsedTime_msec += MAIN_TASK_PERIOD_MS;
    if (lulElapsedTime_msec >= 4000000000) lulElapsedTime_msec = 0;
    lulElapsedTime_Messages_msec += INPUT_TASK_PERIOD_MS;

    //////////////////////////////////////////////
    //
    // Pull messages from the queue and process
    //
    //////////////////////////////////////////////
    ltQueueWaitingCount = uxQueueMessagesWaiting(xInputQueueHandle);
    if (ltQueueWaitingCount)
    {
      lulElapsedTime_Messages_msec = 0;
      //LOG("%s: Message waiting\r\n", __FUNCTION__);
      xQueueReceive(xInputQueueHandle, &lucMessageID, 20);
      //LOG("%s: Received message %d\r\n", __FUNCTION__, lucMessageID);
      switch (lucMessageID)
      {
        case msgid_MAIN_INPUT_TEST:
          LOG("%s: Received test message from Main\r\n", __FUNCTION__);
          break;
        default:
          LOG("%s: *** WARNING *** Received unknown message %d\r\n", __FUNCTION__, lucMessageID);
          break;
      }
    }
    else
    {
      if (lulElapsedTime_Messages_msec > 5000)
      {
        lulElapsedTime_Messages_msec = 0;
        LOG("%s: No messages\r\n", __FUNCTION__);
      }
    }

    ////////////////
    //
    // Task delay
    //
    ////////////////
    osDelay(INPUT_TASK_PERIOD_MS);
  }
}
// end InputTask

/*******************************************************************************
 * Main task
 ******************************************************************************/
static void MainTask(void *arg)
{
  (void)&arg;
  uint8_t lucBlinkCounter=0;
  //sl_led_state_t ltLEDState;
  uint32_t lulElapsedTime_msec = 0;
  uint32_t lulElapsedTimeSinceLED_msec = 0;
  uint32_t lulElapsedTime_Messages_msec = 0;
  UBaseType_t ltQueueWaitingCount;
  uint8_t lucMessageID;
  uint8_t lucMessageCommand;

  //Use the provided calculation macro to convert milliseconds to OS ticks
  //const TickType_t xDelay = pdMS_TO_TICKS(MAIN_TASK_PERIOD_MS);;

  PrintStartupBanner();
  LOG("%s: Initializing...\r\n", __FUNCTION__);

  while (1)
  {
    //////////////////////////////////////////////
    //
    // Pet the watchdog
    //
    //////////////////////////////////////////////
    WDOGn_Feed(DEFAULT_WDOG);

    //////////////////////////////////////////////
    //
    // Do timing updates
    //
    //////////////////////////////////////////////
    lulElapsedTime_msec += MAIN_TASK_PERIOD_MS;
    if (lulElapsedTime_msec >= 4000000000) lulElapsedTime_msec = 0;
    lulElapsedTimeSinceLED_msec += MAIN_TASK_PERIOD_MS;
    lulElapsedTime_Messages_msec += MAIN_TASK_PERIOD_MS;
    // Seconds counters
    if (lulElapsedTime_msec%1000 == 0)
    {

    }

    //////////////////////////////////////////////
    //
    // Pull messages from the queue and process
    //
    //////////////////////////////////////////////
    ltQueueWaitingCount = uxQueueMessagesWaiting(xMainQueueHandle);
    if (ltQueueWaitingCount)
    {
      lulElapsedTime_Messages_msec = 0;
      //LOG("%s: Message waiting\r\n", __FUNCTION__);
      xQueueReceive(xMainQueueHandle, &lucMessageID, 20);
      //LOG("%s: Received message %d\r\n", __FUNCTION__, lucMessageID);
      switch (lucMessageID)
      {
        case msgid_MAIN_INPUT_TEST:
        case msgid_MAIN_OUTPUT_TEST:
          LOG("%s: Received test message from Main??\r\n", __FUNCTION__);
          break;
        default:
          LOG("%s: *** WARNING *** Received unknown message %d\r\n", __FUNCTION__, lucMessageID);
          break;
      }
    }
    else
    {
      if (lulElapsedTime_Messages_msec > 5000)
      {
        lulElapsedTime_Messages_msec = 0;
        LOG("%s: No messages\r\n", __FUNCTION__);
      }
    }

    ///////////////
    //
    // TEST: After a fixed amount of time, hang here, wait for watchdog reset
    //
    ///////////////
    static uint32_t lulElapsedTime_To_Watchdog_msec;
    lulElapsedTime_To_Watchdog_msec += MAIN_TASK_PERIOD_MS;
    if (lulElapsedTime_To_Watchdog_msec >= 12000)
    {
      LOG("%s: *** WARNING *** Waiting here in tight loop for watchdog reset...\r\n", __FUNCTION__);
      osDelay(2000);
      for(;;){}
    }

    ///////////////
    //
    // TEST: Send a message to another task
    //
    ///////////////
    static uint32_t lulElapsedTime_SendMessage_msec;
    //static uint8_t lucMessageCommand;
    lulElapsedTime_SendMessage_msec += MAIN_TASK_PERIOD_MS;
    if (lulElapsedTime_SendMessage_msec >= 15000)
    {
      lulElapsedTime_SendMessage_msec = 0;
      lucMessageCommand = msgid_MAIN_INPUT_TEST;
      xQueueSendToBack(xInputQueueHandle,&lucMessageCommand , 20);
      //xQueueSendToBack(xMainQueueHandle,&lucMessageCommand , 20);
      //xQueueSendToBack(xOutputQueueHandle,&lucMessageCommand , 20);
    }

    ///////////////
    //
    // Toggle led
    //
    ///////////////
    if (lulElapsedTimeSinceLED_msec >= 1000)
    {
      lulElapsedTimeSinceLED_msec = 0;

      ++lucBlinkCounter;
      if (lucBlinkCounter >= 4)
      {
        //sl_led_turn_on(&LED_INSTANCE);
        //ltLEDState = sl_led_get_state(&LED_INSTANCE);
        //LOG("%s: lucBlinkCounter=%d \t LED is ON  \t ltLEDState=%d\r\n", __FUNCTION__, lucBlinkCounter, ltLEDState);
        lucMessageCommand = msgid_MAIN_OUTPUT_LED_ON;
        xQueueSendToBack(xOutputQueueHandle,&lucMessageCommand , 20);
        lucBlinkCounter = 0;
      }
      else
      {
        //sl_led_turn_off(&LED_INSTANCE);
        //ltLEDState = sl_led_get_state(&LED_INSTANCE);
        //LOG("%s: lucBlinkCounter=%d \t LED is OFF \t ltLEDState=%d\r\n", __FUNCTION__, lucBlinkCounter, ltLEDState);
        lucMessageCommand = msgid_MAIN_OUTPUT_LED_OFF;
        xQueueSendToBack(xOutputQueueHandle,&lucMessageCommand , 20);
      }
    }

    ////////////////
    //
    // Task delay
    //
    ////////////////
    osDelay(MAIN_TASK_PERIOD_MS);
  }
}
// end MainTask


/*******************************************************************************
 * Output task
 ******************************************************************************/
static void OutputTask(void *arg)
{
  (void)&arg;
  uint32_t lulElapsedTime_msec = 0;
  uint32_t lulElapsedTime_Messages_msec = 0;
  UBaseType_t ltQueueWaitingCount;
  uint8_t lucMessageID;

  LOG("%s: Initializing...\r\n", __FUNCTION__);

  while (1)
  {
    lulElapsedTime_msec += OUTPUT_TASK_PERIOD_MS;
    if (lulElapsedTime_msec >= 4000000000) lulElapsedTime_msec = 0;
    lulElapsedTime_Messages_msec += OUTPUT_TASK_PERIOD_MS;

    //////////////////////////////////////////////
    //
    // Pull messages from the queue and process
    //
    //////////////////////////////////////////////
    ltQueueWaitingCount = uxQueueMessagesWaiting(xOutputQueueHandle);
    if (ltQueueWaitingCount)
    {
      lulElapsedTime_Messages_msec = 0;
      //LOG("%s: Message waiting\r\n", __FUNCTION__);
      xQueueReceive(xOutputQueueHandle, &lucMessageID, 20);
      //LOG("%s: Received message %d\r\n", __FUNCTION__, lucMessageID);
      switch (lucMessageID)
      {
        case msgid_MAIN_OUTPUT_TEST:
          LOG("%s: Received test message from Main\r\n", __FUNCTION__);
          break;
        case msgid_MAIN_OUTPUT_LED_ON:
          LOG("%s: Received LED ON message from Main\r\n", __FUNCTION__);
          sl_led_turn_on(&LED_INSTANCE);
          break;
        case msgid_MAIN_OUTPUT_LED_OFF:
          LOG("%s: Received LED OFF message from Main\r\n", __FUNCTION__);
          sl_led_turn_off(&LED_INSTANCE);
          break;
        default:
          LOG("%s: *** WARNING *** Received unknown message %d\r\n", __FUNCTION__, lucMessageID);
          break;
      }
    }
    else
    {
      if (lulElapsedTime_Messages_msec > 5000)
      {
        lulElapsedTime_Messages_msec = 0;
        LOG("%s: No messages\r\n", __FUNCTION__);
      }
    }

    ////////////////
    //
    // Task delay
    //
    ////////////////
    osDelay(OUTPUT_TASK_PERIOD_MS);
  }
}
// end OutputTask

