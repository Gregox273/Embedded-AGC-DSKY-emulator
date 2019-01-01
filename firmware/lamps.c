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
static mutex_t lamps_state_mtx;
static uint8_t *lamps_state;
static uint8_t *fb;
static GPIO_TypeDef *sPort;
static uint32_t sMask;
uint8_t* dma_source;
//static uint8_t lamps_state[NUM_LAMPS * NUM_COLOURS] = {0};

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

}

static void setColor(uint8_t color, uint8_t *buf,uint32_t mask){
  int i;
  for (i=0;i<8;i++){
    buf[i]=((color<<i)&0b10000000?0x0:mask);
  }
}

void lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b)
{
  chDbgAssert(id!=NUM_LAMPS, "Invalid lamp ID");
  chMtxLock(&lamps_state_mtx);

  setColor(g & MASK, lamps_state + (id * 8 * NUM_COLOURS), sMask);
  setColor(r & MASK, lamps_state + (id * 8 * NUM_COLOURS) + 8, sMask);
  setColor(b & MASK, lamps_state + (id * 8 * NUM_COLOURS) + 16, sMask);

  chMtxUnlock(&lamps_state_mtx);
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
//  for(uint8_t lamp = 0; lamp < NUM_LAMPS; lamp++)
//  {
//    lamps_set_single(lamp, 0x1F, 0x00, 0x00);
//    chThdSleepMilliseconds(500);
//    lamps_set_single(lamp, 0x00, 0x1F, 0x00);
//    chThdSleepMilliseconds(500);
//    lamps_set_single(lamp, 0x00, 0x00, 0x1F);
//    chThdSleepMilliseconds(500);
//  }
  lamps_set_single(LAMP_COMP_ACTY, 0x1F, 0x00, 0x00);
  chThdSleepSeconds(3);
}

void lamps_init(void)
{
  /*
   * Based on WS28281 DMA driver by Omri Iluz
   * https://github.com/omriiluz/WS2812B-LED-Driver-ChibiOS
   * (Accessed 1/1/2019)
   */
  chMtxObjectInit(&lamps_state_mtx);
  sPort = GPIOC;
  sMask = 1 << GPIOC_LED_DIN;

  // configure pwm timers -
  // timer 1 as master, active for data transmission and inactive to disable transmission during reset period (50uS)
  // timer 3 as slave, during active time creates a 1.25 uS signal, with duty cycle controlled by frame buffer values
  static PWMConfig pwmc1 = {48000000 / 60, /* 800Khz PWM clock frequency. 1/90 of PWMC3   */
			    (48000000 / 60) * 0.05, /*Total period is 50ms (20FPS), including sLeds cycles + reset length for ws2812b and FB writes  */
			    NULL,
			    { {PWM_OUTPUT_ACTIVE_HIGH, NULL},
			      {PWM_OUTPUT_DISABLED, NULL},
			      {PWM_OUTPUT_DISABLED, NULL},
			      {PWM_OUTPUT_DISABLED, NULL}},
			      TIM_CR2_MMS_2, /* master mode selection */
			      0, };
  /* master mode selection */
  static PWMConfig pwmc3 = {48000000,/* 48Mhz PWM clock frequency.   */
			    60, /* 90 cycles period (1.25 uS per period @48Mhz       */
			    NULL,
			    { {PWM_OUTPUT_ACTIVE_HIGH, NULL},
			      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
			      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
			      {PWM_OUTPUT_ACTIVE_HIGH, NULL}},
			      0,
			      0,
  };
  dma_source = chHeapAlloc(NULL, 1);
  fb = chHeapAlloc(NULL, ((NUM_LAMPS) * 24)+10);
  lamps_state=fb;
  for(int j = 0; j < NUM_LAMPS*NUM_COLOURS*8; j++) fb[j] = 0;
  dma_source[0] = sMask;

  // DMA stream 2, triggered by channel3 pwm signal. if FB indicates, reset output value early to indicate "0" bit to ws2812
  osalSysLock();

  dmaStreamAllocate(STM32_DMA2_STREAM1, 10, NULL, NULL);
  dmaStreamSetPeripheral(STM32_DMA2_STREAM1, &(sPort->BRR));
  dmaStreamSetMemory0(STM32_DMA2_STREAM1, fb);
  dmaStreamSetTransactionSize(STM32_DMA2_STREAM1, (NUM_LAMPS) * 24);
  dmaStreamSetMode(
      STM32_DMA2_STREAM1,
      STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_MINC | STM32_DMA_CR_PSIZE_BYTE
      | STM32_DMA_CR_MSIZE_BYTE | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(2));

  // DMA stream 7, triggered by pwm update event. output high at beginning of signal
  dmaStreamAllocate(STM32_DMA1_STREAM7, 10, NULL, NULL);
  dmaStreamSetPeripheral(STM32_DMA1_STREAM7, &(sPort->BSRR));
  dmaStreamSetMemory0(STM32_DMA1_STREAM7, dma_source);
  dmaStreamSetTransactionSize(STM32_DMA1_STREAM7, 1);
  dmaStreamSetMode(
      STM32_DMA1_STREAM7, STM32_DMA_CR_TEIE |
      STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE
      | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));

  // DMA stream 6, triggered by channel1 update event. reset output value late to indicate "1" bit to ws2812.
  // always triggers but no affect if dma stream 2 already change output value to 0
  dmaStreamAllocate(STM32_DMA1_STREAM6, 10, NULL, NULL);
  dmaStreamSetPeripheral(STM32_DMA1_STREAM6, &(sPort->BRR));
  dmaStreamSetMemory0(STM32_DMA1_STREAM6, dma_source);
  dmaStreamSetTransactionSize(STM32_DMA1_STREAM6, 1);
  dmaStreamSetMode(
      STM32_DMA1_STREAM6,
      STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE
      | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));

  osalSysUnlock();

  pwmStart(&PWMD1, &pwmc1);
  pwmStart(&PWMD3, &pwmc3);
  // set pwm3 as slave, triggerd by pwm1 oc1 event. disables pwmd1 for synchronization.
  PWMD3.tim->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_2 | TIM_SMCR_TS_0;
  PWMD1.tim->CR1 &= ~TIM_CR1_CEN;
  // set pwm values.
  // 28 (duty in ticks) / 90 (period in ticks) * 1.25uS (period in S) = 0.39 uS
  pwmEnableChannel(&PWMD3, 2, 28);
  // 58 (duty in ticks) / 90 (period in ticks) * 1.25uS (period in S) = 0.806 uS
  pwmEnableChannel(&PWMD3, 0, 58);
  // active during transfer of 90 cycles * sLeds * 24 bytes * 1/90 multiplier
  pwmEnableChannel(&PWMD1, 0, 90 * NUM_LAMPS * 24 / 90);
  // stop and reset counters for synchronization
  PWMD1.tim->CNT = 0;
  // Slave (TIM3) needs to "update" immediately after master (TIM2) start in order to start in sync.
  // this initial sync is crucial for the stability of the run
  PWMD3.tim->CNT = 89;
  PWMD3.tim->DIER |= TIM_DIER_CC3DE | TIM_DIER_CC1DE | TIM_DIER_UDE;

  dmaStreamEnable(STM32_DMA1_STREAM7);
  dmaStreamEnable(STM32_DMA1_STREAM6);
  dmaStreamEnable(STM32_DMA2_STREAM1);
  // all systems go! both timers and all channels are configured to resonate
  // in complete sync without any need for CPU cycles (only DMA and timers)
  // start pwm2 for system to start resonating
  PWMD1.tim->CR1 |= TIM_CR1_CEN;
}
