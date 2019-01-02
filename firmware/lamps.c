/*
 * Lamp driver
 * Based on WS28281 DMA driver by Omri Iluz
 * https://github.com/omriiluz/WS2812B-LED-Driver-ChibiOS
 * (Accessed 1/1/2019)
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

/* Global state - do not access directly
 * Use getter/setter functions
 */
static uint32_t *lamps_state;
static uint32_t *fb;
static GPIO_TypeDef *sPort;
static uint32_t sMask0;  // Clear pin C13
static uint32_t sMask1;  // Set pin C13
uint8_t* dma_source;
#define NUM_SUB 3  // Number of time periods per bit

static void setColor(uint8_t color, uint32_t *buf){
//  int i;
//  for (i=0;i<8;i++){
//    buf[i]=((color<<i)&0b10000000?0x0:mask);
//  }
  for(int i = 0; i < 8; i++)
  {
    if((color<<i)&0b10000000)
    {
      // Send one
      buf[NUM_SUB*i] = sMask1;
      buf[NUM_SUB*i+1] = sMask1;
      buf[NUM_SUB*i+2] = sMask0;
    }
    else
    {
      // Send zero
      buf[NUM_SUB*i] = sMask1;
      buf[NUM_SUB*i+1] = sMask0;
      buf[NUM_SUB*i+2] = sMask0;
    }
  }
}

void lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b)
{
  chDbgAssert(id!=NUM_LAMPS, "Invalid lamp ID");

  setColor(g & MASK, lamps_state + (id * 8 * NUM_COLOURS));
  setColor(r & MASK, lamps_state + (id * 8 * NUM_COLOURS) + 8);
  setColor(b & MASK, lamps_state + (id * 8 * NUM_COLOURS) + 16);

}

//void lamps_set_bulk(uint8_t *buf, uint8_t len, uint8_t offset)
//{
//  chDbgAssert(offset + len <= NUM_LAMPS * NUM_COLOURS,
//              "offset + len too large to fit inside lamp state array");
//  gptStopTimer(&GPTD3);
//  chMtxLock(&lamps_state_mtx);
//
//  memcpy(lamps_state + offset, buf, len);
//
//  // Apply mask to limit current per colour channel per lamp
//  for(size_t i = offset; i < offset + len; i++)
//  {
//    lamps_state[i] &= MASK;
//  }
//
//  ws2812b_sendarray(offset + len);
//
//  chMtxUnlock(&lamps_state_mtx);
//}

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
  /*
   * Based on post by Kai
   * http://www.chibios.com/forum/viewtopic.php?t=2419
   * Accessed 2/1/2019
   */
  sPort = GPIOC;
  sMask1 = 1 << GPIOC_LED_DIN;
  sMask0 = 1 << (GPIOC_LED_DIN + 16);

    static PWMConfig pwmc1 = {48000000,
			      20, /* 417ns period */
			      NULL,
			      { {PWM_OUTPUT_ACTIVE_HIGH, NULL},
				{PWM_OUTPUT_DISABLED, NULL},
				{PWM_OUTPUT_DISABLED, NULL},
				{PWM_OUTPUT_DISABLED, NULL}},
				STM32_TIM_CR2_CCDS,
				STM32_TIM_DIER_UDE, };
  dma_source = chHeapAlloc(NULL, 2);
  size_t num_elem = NUM_SUB*((NUM_LAMPS * NUM_COLOURS * 8)+20);
  fb = chHeapAlloc(NULL, num_elem);
  lamps_state=fb;
  for(size_t j = 0; j < num_elem; j++) fb[j] = 0;
  dma_source[0] = sMask0;
  dma_source[1] = sMask1;

  pwmStart(&PWMD1, &pwmc1);
  pwmEnableChannel(&PWMD1, 0, 10);
  PWMD1.tim->CR1 |= STM32_TIM_CR1_CMS(0x01);
  PWMD1.tim->RCR = 0x01;
  PWMD1.tim->DIER |= STM32_TIM_DIER_UDE;

  // DMA stream 6, triggered by channel1 pwm signal. if FB indicates, reset output value early to indicate "0" bit to ws2812
  osalSysLock();
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_TIM1_DMA_RMP;
  dmaStreamAllocate(STM32_DMA1_STREAM6, 0, NULL, NULL);
  dmaStreamSetPeripheral(STM32_DMA1_STREAM6, &(sPort->BSRR));
  dmaStreamSetMemory0(STM32_DMA1_STREAM6, fb);
  dmaStreamSetTransactionSize(STM32_DMA1_STREAM6, num_elem);
  dmaStreamSetMode(
      STM32_DMA1_STREAM6,
      STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_MINC | STM32_DMA_CR_PSIZE_WORD
      | STM32_DMA_CR_MSIZE_WORD | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(0));
  osalSysUnlock();

  dmaStreamEnable(STM32_DMA1_STREAM6);
}
