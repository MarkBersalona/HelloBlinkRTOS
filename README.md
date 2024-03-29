# HelloBlinkRTOS

## Executive Summary
This project was developed **to become familiar with the Silicon Labs Simplicity Studio 5 IDE** and its utility in developing embedded software for SiLabs microcontrollers. The intent was to compare it to the STMicroelectronics STM32CubeIDE and its libraries and documentation for STM32 microprocessors, used in Temperature Display, 400 Cellular/Sentry, Temperature Sensor Display and future STM32-based Sentinel products.

Target device at the moment is a SparkFun MGM240P Thing Plus board. Its processor is the SiLabs MGM240P Multi-Protocol Wireless Module, which itself is based on the EFR32MG24 microcontroller.

<img src="MGM240P_Thing_Plus.jpg" alt="SparkFun MGM240P Thing Plus" />

The first project I've built, HelloBlinkRTOS, does the following "simple" things
- Send debug output out a serial port (8N1, 115200 baud)
- Blink its Status LED
- Use FreeRTOS task(s)

As of 2024.01.20 *I much prefer STM32CubeIDE and STM32CubeProgrammer* over the IDEs from NXP and Silicon Labs.

## Getting the board up and running

After I installed Simplicity Studio 5 on my GreenStarfish Linux laptop, I loaded the example **blink_kernel_freertos** project, compiled and loaded it onto the board - LED blinked. I modified the blink period and rebuilt the project: LED blinked faster, **confirming the IDE build/install process**. Additionally, this project used FreeRTOS tasking to control the LED blinking.

Next, the example **iostream_usart_baremetal** project involved input and output over the board's serial port. I wired up a harness to connect power, ground and the serial TX/RX pins on the board to the Sensaphone serial debug board to **confirm input and output on the serial port**.

<img src="20240120 SparkFun ThingPlusMatter HelloBlinkRTOS.jpg" alt="Sentry Simulator hooked up" />


Much like the Sentry Simulator project for the NXP IDE and evaluation board, the first project I tried to build from scratch in Simplicity Studio should have included hooks for a serial port and an LED, but somehow did not. Again, I wound up **copying and pasting from the aforementioned Simplicity Studio example projects**.


### Initial impressions
- Silicon Labs Simplicity Studio IDE makes example projects and demos more accessible than in STM32CubeIDE.
- Adding/modifying FreeRTOS items like tasks, queues and semaphores/mutexes is done by copying/pasting or otherwise manually typing into code; it requires more FreeRTOS expertise. In contrast, STM32CubeIDE offers graphical selectors and other GUI items; it requires less FreeRTOS expertise.
- Although there is a main.c, **the code of HelloBlinkRTOS is in and will be in app.c**.

**TIP**: In Simplicity Studio, in the project's file/directory tree, look in the *gecko_sdk_x.x.x* directory to find what software components and their supporting functions are available.

**TIP**: There's a Silicon Labs GitHub repository full of peripheral examples. The Simplicity Studio examples seem to concentrate on the assorted wireless connectivity options, like Bluetooth or Zigbee; these peripheral examples are more mundane microcontroller examples like how to set up and use GPIO or a watchdog timer. See [https://github.com/SiliconLabs/peripheral_examples](https://github.com/SiliconLabs/peripheral_examples)

**WARNING**: When instantiating FreeRTOS items (tasks, mutexes, queues, etc.) be sure to use the static (versus dynamic) version of the creating routines, so allocated memory will be static instead of dynamic.
- For now with a small application, shouldn't run out of RAM in case dynamic memory is allocated
- Might need to reserve static buffers for the static memory allocation
- Yet another configuration item that must be configured completely manually, instead of being given a simple choice and being initialized correctly by the rebuilt application, like how STM32CubeIDE does it. Yeah, it's my job as an embedded software engineer to make it happen, but it's just another possible way to misconfigure firmware.

### TODO things to add
- accept simple Diagnostic commands from the debug serial port
- recognize/debounce button press via TBD I/O pin through Input task, i.e. simulate Reset-To-Defaults button (assuming a free I/O pin is available; wire up a switch to it)
- if a real-time clock is available, use it for at least elapsed times

## Version history

### 2024.01.25 v0.1.1

Searching the software components for 'watchdog', of the 4 examples given, only the third-party Amazon FreeRTOS > Common I/O > IoT Watchdog installed and compiled initially without any crazy errors. Still no hooks for initializing or using a watchdog, but at least it pulled in **em_wdog.c and .h files** in the Gecko directory tree.

- gecko_sdk_4.3.2 > platform > em_lib

Copied the example initWDG() contents into Watchdog_init() in HelloBlinkRTOS, modified it to 32k cycles for an approximate 30 second timeout, #included em_cmu.h and em_wdog.h. Lo and behold: reboots after 32 seconds! Specify 8k cycles: reboots after 8 seconds!

In MainTask() loop, pet the watchdog with **WDOGn_Feed(DEFAULT_WDOG)**, and the watchdog reset is avoided.

Then add test code in MainTask() to hang in a tight loop after 10 seconds.
- Input and Output tasks are still able to run. After all, only Main task is hung.
- But since Main task is hung and no longer petting the watchdog, the watchdog reset eventually triggers a reboot. Good!

#### Demo debug output
```
=================================<=>=================================
                      SparkFun Thing Plus Matter
                           HelloBlinkRTOS
                               v0.1.1
                             2024.01.25
=================================<=>=================================
MainTask: Initializing...
InputTask: Initializing...
OutputTask: Initializing...
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED ON message from Main
OutputTask: Received LED OFF message from Main
MainTask: No messages
InputTask: No messages
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED ON message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
MainTask: No messages
InputTask: No messages
OutputTask: Received LED OFF message from Main
MainTask: *** WARNING *** Waiting here in tight loop for watchdog reset...
InputTask: No messages
OutputTask: No messages



=================================<=>=================================
                      SparkFun Thing Plus Matter
                           HelloBlinkRTOS
                               v0.1.1
                             2024.01.25
=================================<=>=================================
MainTask: Initializing...
InputTask: Initializing...
OutputTask: Initializing...
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
```

### 2024.01.23 v0.1.0

<img src="HelloBlinkRTOS SW block diagram.png" alt="HelloBlinkRTOS SW block diagram" />


- More FreeRTOS items
  - Input and Output tasks as well as Main task
  - Each task has a message queue
  - Diagnostic serial port output governed by a Diagnostic mutex
- Use Diagnostic mutex in LOG() macro
- Move call to PrintStartupBanner() to MainTask(): can't use an RTOS item until it's been instantiated in RTOS_init()
- LED governed by Output task, commanded by Main task

#### Demo debug output
```
=================================<=>=================================
                      SparkFun Thing Plus Matter
                           HelloBlinkRTOS
                               v0.1.0
                             2024.01.23
=================================<=>=================================
MainTask: Initializing...
InputTask: Initializing...
OutputTask: Initializing...
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED ON message from Main
OutputTask: Received LED OFF message from Main
MainTask: No messages
InputTask: No messages
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED ON message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
MainTask: No messages
InputTask: No messages
OutputTask: Received LED OFF message from Main
OutputTask: Received LED ON message from Main
OutputTask: Received LED OFF message from Main
OutputTask: Received LED OFF message from Main
InputTask: Received test message from Main
OutputTask: Received LED OFF message from Main
MainTask: No messages
OutputTask: Received LED ON message from Main
OutputTask: Received LED OFF message from Main
```


### 2024.01.22 v0.0.2
- Instead of using the LED toggle routine, call the routines to turn LED on and to turn LED off; also investigate the values associated with LED state.
- Call osDelay() instead of vTaskDelay(), to avoid the need to convert msec to ticks.
- Rename blink_task() as MainTask(); rename blink_init() as RTOS_init() - in preparation for more RTOS items soon.

#### Demo debug output
```
=================================<=>=================================
                      SparkFun Thing Plus Matter                     
                           HelloBlinkRTOS                            
                               v0.0.2 
                             2024.01.22   
=================================<=>=================================
MainTask: lucBlinkCounter=1 	 LED is OFF 	 ltLEDState=0
MainTask: lucBlinkCounter=2 	 LED is OFF 	 ltLEDState=0
MainTask: lucBlinkCounter=3 	 LED is OFF 	 ltLEDState=0
MainTask: lucBlinkCounter=4 	 LED is ON  	 ltLEDState=1
MainTask: lucBlinkCounter=1 	 LED is OFF 	 ltLEDState=0
MainTask: lucBlinkCounter=2 	 LED is OFF 	 ltLEDState=0
MainTask: lucBlinkCounter=3 	 LED is OFF 	 ltLEDState=0
MainTask: lucBlinkCounter=4 	 LED is ON  	 ltLEDState=1
```

### 2024.01.20 v0.0.1
First working project, derived by copying and pasting the example projects 'blink_kernel_freertos' and 'iostream_usart_baremetal' into a newly-created project. Although I tried specifying the status LED and serial port when creating the new project, ultimately I needed to view the project files of the examples to figure out what software components to include. Still, needed to copy and paste the #include files, so *why bother with specifying software components?*

I copied and adapted the PrintStartupBanner() routine and gconfig.h file from the 400 Cellular project, as well as the LOG() macro to print debug output out the serial port.

#### Demo debug output
```
=================================<=>=================================
                      SparkFun Thing Plus Matter                     
                           HelloBlinkRTOS                            
                               v0.0.1 
                             2024.01.20   
=================================<=>=================================
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
blink_task: LED toggled...
```
