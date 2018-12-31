/*
 * 7 segment display driver
 */

#include "displays.h"
#include "hal.h"
#include "mcp23s08.h"

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

/*
 * Convert column number to column line
 *
 * col -- column number
 * returns -- line (pin) assigned to column
 */
static ioline_t col_lookup(uint8_t col)
{
  chDbgAssert(col < DISPLAYS_NUM_COLS, "Invalid display column number");
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

/*
 * Convert row & column number to display id
 *
 * row    -- row no.
 * col    -- column no.
 * return -- display id
 */
static inline uint8_t displays_id(uint8_t row, uint8_t col)
{
  chDbgAssert(row < DISPLAYS_NUM_ROWS, "Invalid display row number");
  chDbgAssert(col < DISPLAYS_NUM_COLS, "Invalid display column number");
  return row * DISPLAYS_NUM_COLS + col;
}

/*
 * Convert display id to row & column number
 *
 * id  -- id number
 * row -- row no. storage location
 * col -- column no. storage location
 */
static inline void displays_row_col(uint8_t id, uint8_t *row, uint8_t *col)
{
  chDbgAssert(id < DISPLAYS_NUM_COLS*DISPLAYS_NUM_ROWS, "Invalid display ID");
  *row = id / DISPLAYS_NUM_COLS;
  *col = id % DISPLAYS_NUM_COLS;
}

/*
 * Convert digit 0-9 (255 to blank display) to 7 seg display state
 *
 * digit   -- digit 0-9 (255 to blank display)
 * returns -- state byte for 7 seg display
 */
static DisplayState digit_to_7_seg(uint8_t digit)
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
    case(255):
      return N_B;
    default:
      return N_ERR;
  }
}

/*
 * Set one digit and the next, with val 0-99
 *
 * row    -- digit row number
 * col    -- column number of first digit (sets col and col+1 position)
 * val    -- numerical value to set (0-99)
 */
static void displays_set_2_digits(uint8_t row, uint8_t col, uint8_t val)
{
  chDbgAssert(row < DISPLAYS_NUM_ROWS, "Invalid display row number");
  chDbgAssert(col < DISPLAYS_NUM_COLS, "Invalid display column number");
  chDbgAssert(val < 100, "Invalid input (0-99 required)");
  displays_set_state_rc(row, col, digit_to_7_seg(val/10));
  displays_set_state_rc(row, col+1, digit_to_7_seg(val%10));
}

/*
 * Quick 10^n function
 *
 * n       -- exponent
 * returns -- 10^n
 */
static int32_t quick_pow10(uint8_t n)
{
  chDbgAssert(n < 10, "Invalid exponent (0-9 required)");
  static int32_t pow10[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
  };

  return pow10[n];
}

DisplayState displays_get_state_rc(uint8_t row, uint8_t col)
{
  chDbgAssert(row < DISPLAYS_NUM_ROWS, "Invalid display row number");
  chDbgAssert(col < DISPLAYS_NUM_COLS, "Invalid display column number");
  chMtxLock(&displays_state_mtx);
  uint8_t ret = displays_state[row][col];
  chMtxUnlock(&displays_state_mtx);
  return ret;
}

DisplayState displays_get_state_id(uint8_t id)
{
  chDbgAssert(id < DISPLAYS_NUM_COLS*DISPLAYS_NUM_ROWS, "Invalid display ID");
  uint8_t row, col;
  displays_row_col(id, &row, &col);
  return displays_get_state_rc(row, col);
}

void displays_set_state_rc(uint8_t row, uint8_t col, DisplayState state)
{
  chDbgAssert(row < DISPLAYS_NUM_ROWS, "Invalid display row number");
  chDbgAssert(col < DISPLAYS_NUM_COLS, "Invalid display column number");
  chMtxLock(&displays_state_mtx);
  displays_state[row][col] = state;
  chMtxUnlock(&displays_state_mtx);
}

void displays_set_state_id(uint8_t id, DisplayState state)
{
  chDbgAssert(id < DISPLAYS_NUM_COLS*DISPLAYS_NUM_ROWS, "Invalid display ID");
  uint8_t row, col;
  displays_row_col(id, &row, &col);
  displays_set_state_rc(row, col, state);
}

void displays_set_verb(uint8_t val)
{
  chDbgAssert(val < 100, "Invalid input (0-99 required)");
  const uint8_t row = 1;
  const uint8_t col = 5;
  displays_set_2_digits(row, col, val);
}

void displays_set_noun(uint8_t val)
{
  chDbgAssert(val < 100, "Invalid input (0-99 required)");
  const uint8_t row = 2;
  const uint8_t col = 5;
  displays_set_2_digits(row, col, val);
}

void displays_set_prog(uint8_t val)
{
  chDbgAssert(val < 100, "Invalid input (0-99 required)");
  const uint8_t row = 0;
  const uint8_t col = 5;
  displays_set_2_digits(row, col, val);
}

void displays_set_line(uint8_t line, int32_t val)
{
  chDbgAssert(line < 3, "Invalid line number (0-2 required)");
  chDbgAssert(val < 99999 && val > -99999, "val contains too many digits");
  DisplayState plus_minus;
  uint32_t val_abs;
  if(val<0)
  {
    plus_minus = N_M;
    val_abs = -val;
  }
  else
  {
    plus_minus = N_P;
    val_abs = val;
  }

  for(uint8_t i = 0; i < 5; i++)
  {
    uint8_t digit = (val_abs%quick_pow10(5-i)) / quick_pow10(4-i);
    displays_set_state_rc(line, i, digit_to_7_seg(digit));
  }

  displays_set_state_rc(line, 7, plus_minus);
  //return true;
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

void displays_test(void)
{
  displays_set_line(0, 88888);
  displays_set_line(1, -88888);
  displays_set_line(1, 88888);
  displays_set_verb(88);
  displays_set_noun(88);
  displays_set_prog(88);
  chThdSleepSeconds(2);
  int8_t plus = 1;
  for(uint8_t i = 0; i < 10; i++)
  {
    displays_set_line(0, plus*11111*i);
    displays_set_line(1, plus*11111*i);
    displays_set_line(2, plus*11111*i);
    displays_set_verb(11*i);
    displays_set_noun(11*i);
    displays_set_prog(11*i);
    plus = -plus;
    chThdSleepMilliseconds(500);
  }
  displays_set_line(0, 88888);
  displays_set_line(1, -88888);
  displays_set_line(1, 88888);
  displays_set_verb(88);
  displays_set_noun(88);
  displays_set_prog(88);
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
