/*
 * Lamp driver
 */

#include <string.h>
#include "lamps.h"
#include "ws2812.h"

#define NUM_COLOURS 3

/* 20mA rating per colour per lamp
 * max 7.5mA per lamp to limit current usage to ~100mA
 * therefore max 1/8 of 0xFF per colour channel per lamp
 */
#define MASK 0xFF >> 3 // 0xFF * 2^-3

/* Global state - do not access directly
 * Use getter/setter functions
 */
static mutex_t lamps_state_mtx;
static uint8_t lamps_state[NUM_LAMPS * NUM_COLOURS];

bool lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b)
{
  if(id==NUM_LAMPS) return false;  // Invalid input

  chMtxLock(&lamps_state_mtx);

  lamps_state[id * NUM_COLOURS] = g & MASK;
  lamps_state[id * NUM_COLOURS + 1] = r & MASK;
  lamps_state[id * NUM_COLOURS + 2] = b & MASK;

  ws2812_sendarray(lamps_state, NUM_COLOURS*(id+1));

  chMtxUnlock(&lamps_state_mtx);

  return true;
}


bool lamps_set_bulk(uint8_t *buf, uint8_t len, uint8_t offset)
{
  // Check inputs
  if(offset + len > NUM_LAMPS * NUM_COLOURS) return false;

  chMtxLock(&lamps_state_mtx);

  memcpy(lamps_state + offset, buf, len);

  // Apply mask
  for(size_t i = offset; i < offset + len; i++)
  {
    lamps_state[i] &= MASK;
  }

  ws2812_sendarray(lamps_state, offset + len);

  chMtxUnlock(&lamps_state_mtx);

  return true;
}

void lamps_test(void)
{
  for(uint8_t lamp = 0; lamp < NUM_LAMPS; lamp++)
  {
    lamps_set_single(lamp, 0x1F, 0x00, 0x00);
    chThdSleepMilliseconds(500);
    lamps_set_single(lamp, 0x00, 0x1F, 0x00);
    chThdSleepMilliseconds(500);
    lamps_set_single(lamp, 0x00, 0x00, 0x1F);
    chThdSleepMilliseconds(500);
  }
}

void lamps_init(void)
{
  chMtxObjectInit(&lamps_state_mtx);
}
