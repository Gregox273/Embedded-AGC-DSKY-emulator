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

//#define TEST

//static binary_semaphore_t agc_bsem;
static agc_t *State;
thread_reference_t main_thread_ref = NULL;

void test_buttons(void)
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

void agc_init(agc_t *State)
{
//  // Clear i/o channels.
//    for (int i = 0; i < NUM_CHANNELS; i++)
//      State->InputChannel[i] = 0;
//    State->InputChannel[030] = 037777;
//    State->InputChannel[031] = 077777;
//    State->InputChannel[032] = 077777;
//    State->InputChannel[033] = 077777;
//
//    // Clear erasable memory.
//    for (int Bank = 0; Bank < 8; Bank++)
//      for (int j = 0; j < 0400; j++)
//        State->Erasable[Bank][j] = 0;
//    State->Erasable[0][RegZ] = 04000;	// Initial program counter.
//
//    // Set up the CPU state variables that aren't part of normal memory.
//    State->CycleCounter = 0;
//    State->ExtraCode = 0;
//    State->AllowInterrupt = 0;
//    State->PendFlag = 0;
//    State->PendDelay = 0;
//    State->ExtraDelay = 0;
  State->CheckParity = 0;
  memset(&State->Parities, 0, sizeof(State->Parities));

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
    State->AllowInterrupt = 1; // The GOJAM sequence enables interrupts
    State->InterruptRequests[8] = 1;	// DOWNRUPT.
    //State->RegA16 = 0;
    State->PendFlag = 0;
    State->PendDelay = 0;
    State->ExtraDelay = 0;
    //State->RegQ16 = 0;

    State->OutputChannel7 = 0;
    for (int j = 0; j < 16; j++)
      State->OutputChannel10[j] = 0;
    State->IndexValue = 0;
    for (int j = 0; j < 1 + NUM_INTERRUPT_TYPES; j++)
      State->InterruptRequests[j] = 0;
    State->InIsr = 0;
    State->SubstituteInstruction = 0;
    State->DownruptTimeValid = 1;
    State->DownruptTime = 0;
    State->Downlink = 0;

    State->NightWatchman = 0;
    State->NightWatchmanTripped = 0;
    State->RuptLock = 0;
    State->NoRupt = 0;
    State->TCTrap = 0;
    State->NoTC = 0;
    State->ParityFail = 0;

    State->WarningFilter = 0;
    State->GeneratedWarning = 0;

    State->RestartLight = 0;
    State->Standby = 0;
    State->SbyPressed = 0;
    State->SbyStillPressed = 0;

    State->NextZ = 0;
    State->ScalerCounter = 0;
    State->ChannelRoutineCount = 0;

    State->DskyTimer = 0;
    State->DskyFlash = 0;
    State->DskyChannel163 = 0;

    State->TookBZF = 0;
    State->TookBZMF = 0;

    State->Trap31A = 0;
    State->Trap31B = 0;
    State->Trap32 = 0;
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
  (void)gptd;
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
//  displays_set_line(0, 12345);
//  displays_set_line(1, -67890);
//  displays_set_line(2, 13579);
//  displays_set_verb(02);
//  displays_set_noun(46);
//  displays_set_prog(80);
//  chThdSleepMilliseconds(500);


  /*
   * Main loop
   */
  gptStartContinuous(&GPTD3, 562);  // AGC clock is 1024kHz / 12

  uint32_t agc_counter = 0;

  while (true)
  {
    // gptPolledDelay(&GPTD3, 562);
    agc_engine(State);
    if(agc_counter%16==0)
    {
      #ifdef TEST
      displays_set_line(2, (agc_counter/16)%100000);
      #endif
      displays_state_machine();  // Clock displays state machine every 10 cycles
    }
    if(agc_counter%128==0)
    {
      buttons_state_machine();  // Clock buttons state machine
      #ifdef TEST
      test_buttons();
      #endif
    }
#ifdef TEST
    if(agc_counter%8192==0)
    {
      //gptStopTimer(&GPTD3);
      chSysLock();
      lamps_refresh(lamps_set_single(LAMP_COMP_ACTY, 0x0F, 0x00, 0x00));  // Test lamp
      chSysUnlock();
      //gptStartContinuous(&GPTD3, 562);  // AGC clock is 1024kHz / 12
    }
    else if(agc_counter%8192==4096)
    {
      //gptStopTimer(&GPTD3);
      chSysLock();
      lamps_refresh(lamps_set_single(LAMP_COMP_ACTY, 0x00, 0x0F, 0x00));  // Test lamp
      chSysUnlock();
      //gptStartContinuous(&GPTD3, 562);  // AGC clock is 1024kHz / 12
    }
#endif

    agc_counter++;

    chSysLock();
    chThdSuspendTimeoutS(&main_thread_ref, TIME_US2I(2000));  // Long timeout so should be visible when something is wrong...
    //chSysUnlock();
  }

  return 0;
}
