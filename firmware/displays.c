/*
 * 7 segment display driver
 */

#include "displays.h"
#include "hal.h"
#include "mcp23s08.h"

/* State of each 7 segment display represented by a byte
 * Bit 6 (2nd MSB) represents state of segment A
 * Bit 0 (LSB) represents state of segment G
 */
////              abcdefg
//#define N_0   0b1111110
//#define N_1   0b0110000
//#define N_2   0b1101101
//#define N_3   0b1111001
//#define N_4   0b0110011
//#define N_5   0b1011011
//#define N_6   0b1011111
//#define N_7   0b1110000
//#define N_8   0b1111111
//#define N_9   0b1111011
//#define N_ERR 0b0000001
////              abcdefg

//              degfcba
#define N_0   0b1101111
#define N_1   0b0000110
#define N_2   0b1110011
#define N_3   0b1010111
#define N_4   0b0011110
#define N_5   0b1011101
#define N_6   0b1111101
#define N_7   0b0000111
#define N_8   0b1111111
#define N_9   0b1011111
#define N_ERR 0b0010000
//              degfcba

/*
 * Static parameters should only be used by the displays thread
 */
static SPIDriver *spid_0_1 = &SPID1;
static SPIDriver *spid_2 = &SPID2;
static SPIDriver *display_spid[DISPLAYS_NUM_ROWS];

static SPIConfig d1_spi_cfg = {
  .end_cb = NULL,
  .ssline = LINE_NCS_1,
  //.cr1    = SPI_CR1_BR_1| SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA
  .cr1    = SPI_CR1_BR_2
};

static SPIConfig d2_spi_cfg = {
  .end_cb = NULL,
  .ssline = LINE_NCS_2,
  //.cr1    = SPI_CR1_BR_1| SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA
  .cr1    = SPI_CR1_BR_2
};

static SPIConfig d3_spi_cfg = {
  .end_cb = NULL,
  .ssline = LINE_NCS_3,
  //.cr1    = SPI_CR1_BR_1| SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA
  .cr1    = SPI_CR1_BR_2
};
static SPIConfig *spi_cfgs[DISPLAYS_NUM_ROWS];
static uint8_t spi_addr[DISPLAYS_NUM_ROWS];

/* Global state - do not access directly"
 * Use getter/setter functions
 */
static mutex_t displays_state_mtx;
static uint8_t displays_state[DISPLAYS_NUM_ROWS][DISPLAYS_NUM_COLS];

static ioline_t col_lookup(uint8_t col)
{
  switch (col)
  {
    case 0:
      return LINE_CO1;

    case 1:
      return LINE_CO2;

    case 2:
      return LINE_CO3;

    case 3:
      return LINE_CO4;

    case 4:
      return LINE_CO5;

    case 5:
      return LINE_CO6;

    case 6:
      return LINE_CO7;

    default:
      return LINE_CO8;
  }
}

static inline uint8_t displays_id(uint8_t row, uint8_t col)
{
  return row * DISPLAYS_NUM_COLS + col;
}

static inline void displays_row_col(uint8_t id, uint8_t *row, uint8_t *col)
{
  *row = id / DISPLAYS_NUM_COLS;
  *col = id % DISPLAYS_NUM_COLS;
}

static uint8_t digit_to_7_seg(uint8_t digit)
{
  switch(digit)
  {
    case(0):
      return N_0;
    case(1):
      return N_1;
    case(2):
      return N_2;
    case(3):
      return N_3;
    case(4):
      return N_4;
    case(5):
      return N_5;
    case(6):
      return N_6;
    case(7):
      return N_7;
    case(8):
      return N_8;
    case(9):
      return N_9;
    default:
      return N_ERR;
  }
}

static bool displays_set_2_digits(uint8_t row, uint8_t col, uint8_t val)
{
  uint8_t val_s = val % 100;  // Sanitise input
  displays_set_state_rc(row, col, digit_to_7_seg(val_s/10));
  displays_set_state_rc(row, col+1, digit_to_7_seg(val_s%10));
  return (val_s == val);
}

static int32_t quick_pow10(uint8_t n)
{
  static int32_t pow10[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
  };

  return pow10[n];
}

uint8_t displays_get_state_rc(uint8_t row, uint8_t col)
{
  chMtxLock(&displays_state_mtx);
  uint8_t ret = displays_state[row][col];
  chMtxUnlock(&displays_state_mtx);
  return ret;
}

uint8_t displays_get_state_id(uint8_t id)
{
  uint8_t row, col;
  displays_row_col(id, &row, &col);
  return displays_get_state_rc(row, col);
}

void displays_set_state_rc(uint8_t row, uint8_t col, uint8_t state)
{
  chMtxLock(&displays_state_mtx);
  displays_state[row][col] = state;
  chMtxUnlock(&displays_state_mtx);
}

void displays_set_state_id(uint8_t id, uint8_t state)
{
  uint8_t row, col;
  displays_row_col(id, &row, &col);
  displays_set_state_rc(row, col, state);
}

bool displays_set_verb(uint8_t val)
{
  const uint8_t row = 1;
  const uint8_t col = 5;
  return displays_set_2_digits(row, col, val);
}

bool displays_set_noun(uint8_t val)
{
  const uint8_t row = 2;
  const uint8_t col = 5;
  return displays_set_2_digits(row, col, val);
}

bool displays_set_prog(uint8_t val)
{
  const uint8_t row = 0;
  const uint8_t col = 5;
  return displays_set_2_digits(row, col, val);
}

bool displays_set_row(uint8_t row, int32_t val)
{
  //TODO: handle sign
  if(row > 2) return false;
  uint32_t val_s;
  if(val<0)
  {
    val_s = -val % 1000000;
  }
  else
  {
    val_s = val % 1000000;
  }

  for(uint8_t i = 0; i < 5; i++)
  {
    uint8_t digit = (val_s%quick_pow10(5-i)) / quick_pow10(4-i);
    displays_set_state_rc(row, i, digit_to_7_seg(digit));
  }
  return true;
}

static THD_WORKING_AREA(waDisplays, 256);
static THD_FUNCTION(displays_thd_func, arg)
{
  (void)arg;
  while(true)
  {
    for(uint8_t col = 0; col < DISPLAYS_NUM_COLS; col++)
    {
      for(uint8_t row = 0; row < DISPLAYS_NUM_ROWS; row++)
      {
        mcp23s08_write_reg(display_spid[row], spi_cfgs[row], spi_addr[row], MCP23S08_OLAT_ADDR, displays_get_state_rc(row, col));
      }

      ioline_t line_col = col_lookup(col);
      palSetLine(line_col);
      chThdSleepMicroseconds(1000);
      palClearLine(line_col);
    }
  }
}

void displays_init(void)
{
  chMtxObjectInit(&displays_state_mtx);

  display_spid[0] = spid_0_1;
  display_spid[1] = spid_0_1;
  display_spid[2] = spid_2;

  spi_cfgs[0] = &d1_spi_cfg;
  spi_cfgs[1] = &d2_spi_cfg;
  spi_cfgs[2] = &d3_spi_cfg;

  // Set in hardware (two address pins)
  spi_addr[0] = 0b00;
  spi_addr[1] = 0b01;
  spi_addr[2] = 0b11;

  mcp23s08_init(display_spid, spi_cfgs, spi_addr, 3);

  chThdCreateStatic(waDisplays, sizeof(waDisplays), NORMALPRIO, displays_thd_func, NULL);
}
