/*
 * Lamp driver
 */

#include <string.h>
#include "lamps.h"
#include "hal.h"

#define NUM_COLOURS 3
#define NUM_LAMPS   13

#define LED_GPTD GPTD3
#define LED_PORT GPIOC
#define LED_PAD  13

/* 20mA rating per colour per lamp
 * max 7.5mA per lamp to limit current usage to ~100mA
 * therefore max 1/8 of 0xFF per colour channel per lamp
 */
#define MASK 0xFF >> 3 // 0xFF * 2^-3

/* Global state - do not access directly
 * Use getter/setter functions
 */
static mutex_t lamps_state_mtx;
static uint8_t lamps_state[NUM_LAMPS * NUM_COLOURS] = {0};

/* WS2812B timer config */
static const GPTConfig lamp_gpt_cfg;

/*
 *
 */
static void ws2812b_sendarray(size_t datlen)
{
  /* Source: https://cpldcpu.wordpress.com/2014/01/14/light_ws2812-library-v2-0-part-i-understanding-the-ws2812/
   * 		(Accessed 1/1/2019)
   * 0: |{-- 62.5ns to 563ns --}{-------}|(1063ns<period<9us)
   * 1: |{--       >625ns       --}{----}|(1063ns<period<9us)
   * Reset: >9us
   *
   * LEDs appear to operate in 208ns timesteps
   * e.g.
   * 0: 100000
   * 1: 111110
   * Reset: >45 * {0}
   */
  chDbgAssert(datlen <= NUM_COLOURS*NUM_LAMPS, "ws2812b array too long");

  size_t byte_id;
  int i;
  uint8_t mask;
  chSysLock();
  for(byte_id = 0; byte_id < datlen; byte_id++)
  {
    for(i = 7; i >= 0; i--)
    {
      mask = 1 << i;
      if(lamps_state[byte_id] & mask)
      {
	// Send 1
	palSetPad(LED_PORT, LED_PAD);
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
	//gptPolledDelay(&LED_GPTD, 20);
	gptPolledDelay(&LED_GPTD, 2);
	palClearPad(LED_PORT, LED_PAD);
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
	//gptPolledDelay(&LED_GPTD, 10);
      }
      else
      {
	// Send 0
	palSetPad(LED_PORT, LED_PAD);
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
	//gptPolledDelay(&LED_GPTD, 2);
	palClearPad(LED_PORT, LED_PAD);
	//gptPolledDelay(&LED_GPTD, 20);
	gptPolledDelay(&LED_GPTD, 2);
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
      }
    }
  }
  chSysUnlock();
  chThdSleepMicroseconds(50);
}

void lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b)
{
  chDbgAssert(id!=NUM_LAMPS, "Invalid lamp ID");
  gptStopTimer(&LED_GPTD);
  chMtxLock(&lamps_state_mtx);

  lamps_state[id * NUM_COLOURS] = g & MASK;
  lamps_state[id * NUM_COLOURS + 1] = r & MASK;
  lamps_state[id * NUM_COLOURS + 2] = b & MASK;

  ws2812b_sendarray(NUM_COLOURS*(id+1));

  chMtxUnlock(&lamps_state_mtx);
}

void lamps_set_bulk(uint8_t *buf, uint8_t len, uint8_t offset)
{
  chDbgAssert(offset + len <= NUM_LAMPS * NUM_COLOURS,
              "offset + len too large to fit inside lamp state array");
  chMtxLock(&lamps_state_mtx);

  memcpy(lamps_state + offset, buf, len);

  // Apply mask to limit current per colour channel per lamp
  for(size_t i = offset; i < offset + len; i++)
  {
    lamps_state[i] &= MASK;
  }

  ws2812b_sendarray(offset + len);

  chMtxUnlock(&lamps_state_mtx);
}

void lamps_clear(void)
{
  chMtxLock(&lamps_state_mtx);

  memset(lamps_state, 0, sizeof(lamps_state));
  ws2812b_sendarray(sizeof(lamps_state));

  chMtxUnlock(&lamps_state_mtx);
}

void lamps_test(void)
{
  for(uint8_t lamp = 0; lamp < NUM_LAMPS; lamp++)
  {
    lamps_set_single(lamp, 0xF, 0x00, 0x00);
    chThdSleepMilliseconds(200);
    lamps_set_single(lamp, 0x00, 0xF, 0x00);
    chThdSleepMilliseconds(200);
    lamps_set_single(lamp, 0x00, 0x00, 0xF);
    chThdSleepMilliseconds(200);
    lamps_set_single(lamp, 0xF, 0x00, 0x00);
  }
//  lamps_set_single(LAMP_COMP_ACTY, 0x0F, 0x00, 0x00);
//  chThdSleepSeconds(3);
//  lamps_set_single(LAMP_OPR_ERR, 0x00, 0x0F, 0x00);
//  chThdSleepSeconds(3);
//  lamps_set_single(LAMP_KEY_REL, 0x00, 0x00, 0x0F);
//  chThdSleepSeconds(3);
  lamps_clear();
}

void lamps_init(void)
{
  static const GPTConfig lamp_gpt_cfg = {
  .frequency = 48000000,
  .callback = NULL,
  };

  gptStart(&LED_GPTD, &lamp_gpt_cfg);

  chMtxObjectInit(&lamps_state_mtx);

  // Clear LEDs
  lamps_set_single(NUM_LAMPS-1, 0, 0, 0);
}
