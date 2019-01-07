# Hardware Notes
* STM32F072RBT6 48MHz microcontroller based on ARM Cortex-M0 core. 48MHz appears to be too slow to run the emulator and 
DSKY in realtime...
* MPU9250 IMU present on SPI2 bus (firmware can communicate with device but it has not yet been incorporated into the 
AGC emulation).
* Powered via Micro USB (<500mA current consumption at any time, so can be powered from e.g. a USB port on a computer).
* Microcontroller can be flashed over USB using DFU, or via Serial Wire Debug (SWD).
* TPS62132 switching regulator (5V USB to 3.3V) - high efficiency reduces overall current consumption.
* MCP23S08 SPI I/O expanders used to drive 7 segment displays in a multiplexed array.
  * Three displays are illuminated at a time, striking a balance between brightness and current consumption.
* Push buttons are multiplexed in a key matrix to reduce I/O pin usage.
* WS2812B LEDs arranged in a chain, allowing them to be driven from a single output pin. Each LED internally handles PWM
for red, green and blue channels.
  * Todo: drive LEDs using DMA instead of blocking the processor. This technique appears to be better documented on 
  STM32F3 and STM32F4 microcontrollers.
* UART port exposed (2.54mm header) to allow for future modifications/experimentation.