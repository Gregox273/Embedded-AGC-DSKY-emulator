/*
 * Lamp driver
 */

#include <string.h>
#include "lamps.h"
#include "hal.h"

#define NUM_COLOURS 3
#define NUM_LAMPS   13

/* 20mA rating per colour per lamp
 * max 7.5mA per lamp to limit current usage to ~100mA
 * therefore max 1/8 of 0xFF per colour channel per lamp
 */
#define MASK 0xFF >> 3 // 0xFF * 2^-3

/*
 * For ws2812b state machine
 */
#define LAMP_BIT_MASK_RESET    0b10000000
#define WS2812B_BIT_MASK_RESET 0b01000000
#define WS2812B_NUM_RESET 20  // = number of reset 'bytes'

typedef enum ws2812b_state
{
  WS2812B_RESET = 0,
  WS2812B_TX_0 = 0b1000000,
  WS2812B_TX_1 = 0b1111110,
}WS2812BState;

/* Global state - do not access directly
 * Use getter/setter functions
 */
static mutex_t lamps_state_mtx;
static uint8_t lamps_state[NUM_LAMPS * NUM_COLOURS] = {0};

/*
 * WS2812B driver state variables
 */
static size_t lamp_buf_len;
static size_t lamp_byte_cursor;
static uint8_t lamp_bit_mask;
static uint8_t ws2812b_bit_mask;
static WS2812BState ws2812b_state;

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

  /*
   * Generate raw tx buffer based on timing rules above
   * Each bit represents pin state for one 208ns cycle
   */
//  ws2812b_buf_len = datlen * 6 + 14;  // Allow space for reset at start and end
//  uint8_t buf[ws2812b_buf_len];
//  ws2812b_buf_addr = &buf;
  lamp_buf_len = datlen + WS2812B_NUM_RESET*2;  // Plus reset bytes at start and end
  lamp_byte_cursor = 0;  // Count up to buf_len-1
  lamp_bit_mask = LAMP_BIT_MASK_RESET;
  ws2812b_bit_mask = WS2812B_BIT_MASK_RESET;
  ws2812b_state = WS2812B_RESET;

  gptStartContinuous(&GPTD3, 5); // Every 416ns
}

//static uint8_t ws2812b_0_1[] = {0b100000, 0b111110};
//static uint8_t *ws2812b_cur_byte_addr;
//static size_t ws2812b_buf_len;
//static size_t ws2812b_byte_cursor;
//static uint8_t ws2812b_bit_mask;
static void lamp_gpt_cb(GPTDriver *gptd)
{
//  if(lamp_byte_cursor >= lamp_buf_len)
//  {
//    // Finished sending buffer
//    //gptStopTimerI(gptd);
//    return;
//  }
//  if(!ws2812b_bit_mask)
//  {
//    // Finished sending one bit, prepare to send next
//    ws2812b_bit_mask = WS2812B_BIT_MASK_RESET;
//    lamp_bit_mask >>=1;
//    if(!lamp_bit_mask)
//    {
//      // Finished sending one byte
//      lamp_bit_mask = LAMP_BIT_MASK_RESET;
//      lamp_byte_cursor++;
//      if(lamp_byte_cursor >= lamp_buf_len)
//      {
//	// Finished sending buffer
//	//gptStopTimerI(gptd);
//	return;
//      }
//    }
//
//    if(lamp_byte_cursor < WS2812B_NUM_RESET || lamp_byte_cursor >= lamp_buf_len - WS2812B_NUM_RESET)
//    {
//      ws2812b_state = WS2812B_RESET;
//    }
//    else if(lamp_bit_mask & lamps_state[lamp_byte_cursor-1])
//    {
//      ws2812b_state = WS2812B_TX_1;
//    }
//    else
//    {
//      ws2812b_state = WS2812B_TX_0;
//    }
//  }
//  if(ws2812b_state & ws2812b_bit_mask)
//  {
//    palSetPad(GPIOC, GPIOC_LED_DIN);//pal_lld_setport(GPIOC, 1<<GPIOC_LED_DIN);
//  }
//  else
//  {
//    palClearPad(GPIOC, GPIOC_LED_DIN);//pal_lld_clearport(GPIOC, 1<<GPIOC_LED_DIN);
//  }
//
//  ws2812b_bit_mask >>= 1;
  return;
}

void lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b)
{
  chDbgAssert(id!=NUM_LAMPS, "Invalid lamp ID");
  gptStopTimer(&GPTD3);
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
  gptStopTimer(&GPTD3);
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

void lamps_test(void)
{
//  for(uint8_t lamp = 0; lamp < NUM_LAMPS; lamp++)
//  {
//    lamps_set_single(lamp, 0x1F, 0x00, 0x00);
//    chThdSleepMilliseconds(500);
//    lamps_set_single(lamp, 0x00, 0x1F, 0x00);
//    chThdSleepMilliseconds(500);
//    lamps_set_single(lamp, 0x00, 0x00, 0x1F);
//    chThdSleepMilliseconds(500);
//  }
  lamps_set_single(LAMP_COMP_ACTY, 0x00, 0x1F, 0x00);
  chThdSleepSeconds(3);
}

void lamps_init(void)
{
  static const GPTConfig lamp_gpt_cfg = {
  .frequency = 750000,
  .callback = lamp_gpt_cb,
  };

  gptStart(&GPTD3, &lamp_gpt_cfg);

  chMtxObjectInit(&lamps_state_mtx);
}
