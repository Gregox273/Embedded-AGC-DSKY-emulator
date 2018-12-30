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

//void test_hardware(void)
//{
//
//}

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

  /*
   * Test
   */
//  displays_set_row(0, 01234);
//  displays_set_row(1, -98765);
//  displays_set_row(1, 13579);
//  displays_set_verb(45);
//  displays_set_noun(23);
//  displays_set_prog(01);
    displays_set_row(0, 88888);
    displays_set_row(1, -88888);
    displays_set_row(1, 88888);
    displays_set_verb(88);
    displays_set_noun(88);
    displays_set_prog(88);
  //test_hardware();

  /*
   * Main loop
   */
  while (true) {
    chThdSleepSeconds(1);
  }
  return 0;
}
