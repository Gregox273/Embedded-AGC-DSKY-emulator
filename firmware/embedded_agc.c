///*
// * Embedded AGC
// */
//
//#include "embedded_agc.h"
//#include "hal.h"
//
//#define CORE_SIZE (044 * 02000)
//
//static void agc_gpt_cb(GPTDriver *gptp)
//{
//  (void)gptp;
//  chSysLockFromISR();
//  chBSemSignalI(&agc_bsem);
//  chSysUnlockFromISR();
//}
//
//void embedded_agc_init(agc_t *State)
//{
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
//
//    chBSemObjectInit(&agc_bsem, true);
//    static const GPTConfig agc_gpt_cfg = {
//      .frequency = 1024000,  // AGC clock is 1024kHz / 12
//      .callback = NULL,
//      };
//
//    gptStart(&GPTD3, &agc_gpt_cfg);
//}
//
//#ifdef __embedded__
//// Stuff that's missing.  Figure it out later.
//int __errno;
//int atexit(void (*function)(void)) { return (0); };
//#endif
//
//
//
//
