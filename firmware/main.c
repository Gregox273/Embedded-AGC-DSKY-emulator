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
#include "buttons.h"
#include "displays.h"
#include "lamps.h"

#include "yaAGC.h"
#include "agc_engine.h"
#include "agc_symtab.h"

static binary_semaphore_t agc_bsem;
static agc_t *State;
thread_reference_t main_thread_ref = NULL;

void test_buttons()
{
  uint8_t row, col;
  for(uint8_t i = 0; i < NUM_BUTTONS; i++)
  {
    if(buttons_get_state_id(i))
    {
      button_row_col(i, &row, &col);
      displays_set_line(0, row);
      displays_set_line(1, col);
      return; // Only show first pressed button
    }
  }
}

void test_hardware(mailbox_t *button_mbox)
{
  displays_test();
  //lamps_test();
  //test_buttons(button_mbox);
  // TODO: test mpu9250
}

void agc_init(agc_t *State)
{
  // Clear i/o channels.
    for (int i = 0; i < NUM_CHANNELS; i++)
      State->InputChannel[i] = 0;
    State->InputChannel[030] = 037777;
    State->InputChannel[031] = 077777;
    State->InputChannel[032] = 077777;
    State->InputChannel[033] = 077777;

    // Clear erasable memory.
    for (int Bank = 0; Bank < 8; Bank++)
      for (int j = 0; j < 0400; j++)
        State->Erasable[Bank][j] = 0;
    State->Erasable[0][RegZ] = 04000;	// Initial program counter.

    // Set up the CPU state variables that aren't part of normal memory.
    State->CycleCounter = 0;
    State->ExtraCode = 0;
    State->AllowInterrupt = 0;
    State->PendFlag = 0;
    State->PendDelay = 0;
    State->ExtraDelay = 0;
}

/*
 * yaAGC
 */
#define CORE_SIZE (044 * 02000)
#ifdef __embedded__
// Stuff that's missing.  Figure it out later.
int __errno;
int atexit(void (*function)(void)) { return (0); };
#endif

static void gpt_cb(GPTDriver *gptd)
{
  chSysLockFromISR();
  chThdResumeI(&main_thread_ref, MSG_OK);
  chSysUnlockFromISR();
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
  lamps_init();
  displays_init();

  /*
   * yaAGC init
   */

  static const GPTConfig agc_gpt_cfg = {
    .frequency = 48000000,
    .callback = gpt_cb,
  };
  gptStart(&GPTD3, &agc_gpt_cfg);

  State = chHeapAlloc(NULL, sizeof(agc_t));
  agc_init(State);

  /*
   * Test
   */
  //test_hardware(&button_mbox);
  displays_set_line(0, 12345);
  displays_set_line(1, -67890);
  displays_set_line(2, 13579);
  displays_set_verb(02);
  displays_set_noun(46);
  displays_set_prog(80);
  chThdSleepMilliseconds(500);

  /*
   * Main loop
   */
  gptStartContinuous(&GPTD3, 562);//4000);//562);  // AGC clock is 1024kHz / 12

  uint32_t agc_counter = 0;

  while (true)
  {
   // gptPolledDelay(&GPTD3, 562);
    agc_engine(State);
    if(agc_counter%16==0)
    {
      displays_set_line(2, (agc_counter/16)%100000);
      displays_state_machine();  // Clock displays state machine every 10 cycles
    }
    if(agc_counter%128==0)
    {
      buttons_state_machine();  // Clock buttons state machine
      test_buttons();
    }

    agc_counter++;

    chSysLock();
    msg_t msg = chThdSuspendTimeoutS(&main_thread_ref, TIME_US2I(2000));  // Long timeout so should be visible when something is wrong...
    //chSysUnlock();
  }

  return 0;
}
