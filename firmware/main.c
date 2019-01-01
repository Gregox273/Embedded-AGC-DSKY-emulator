/*
  	File modified by Gregory Brooks 2018
  	(based on ChibiOS STM32F072RBT6 demo)

    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
//#include "agc_engine.h"
#include "buttons.h"
#include "displays.h"
//#include "lamps.h"

void test_buttons(mailbox_t *button_mbox)
{
  while(true)
  {
    static msg_t button;
    chMBFetchTimeout(button_mbox, &button, TIME_INFINITE);
    if((button&0xFF)==BUTTON_ENTR) break;  // Move on to next test
    if((bool)(button >> 8))
    {
      uint8_t row, col;
      button_row_col((uint8_t)button, &row, &col);
      displays_set_line(0, row);
      displays_set_line(1, col);
    }
  }
}

void test_hardware(mailbox_t *button_mbox)
{
  displays_test();
  //chThdSleepSeconds(3);
  //lamps_test();
  test_buttons(button_mbox);
  // TODO: test mpu9250
}

/*
 * Application entry point.
 */
int main(void)
{
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Setup
   */
  mailbox_t button_mbox;
  msg_t button_mbox_buffer[20];
  chMBObjectInit(&button_mbox, button_mbox_buffer, sizeof(button_mbox_buffer)/sizeof(msg_t));
  buttons_init((void *)&button_mbox);

  displays_init();
  //lamps_init();

  /*
   * Test
   */
  test_hardware(&button_mbox);

  /*
   * Main loop
   */
  while (true) {
    chThdSleepSeconds(1);
  }
  return 0;
}
