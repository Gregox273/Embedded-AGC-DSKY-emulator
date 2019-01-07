/*
 * Key matrix driver
 */

#include "hal.h"
#include "buttons.h"

#define DEBOUNCE_CYCLES 3  // Number of row passes used to debounce button
//#define ROW_PERIOD      10  // ms

/* Global state - do not access directly
 * Use getter/setter functions
 */
static bool buttons_state[BUTTON_NUM_ROWS][BUTTON_NUM_COLS];

/*
 * Global variable for communicating with yaAGC
 */
uint8_t button_pressed = NUM_BUTTONS;  // Button press 'interrupt' for yaAGC

/*
 * Convert row number to row line
 *
 * row -- row number
 * returns -- line (pin) assigned to row
 */
static ioline_t row_lookup(uint8_t row)
{
  chDbgAssert(row < BUTTON_NUM_ROWS, "Invalid button row number");
  switch (row)
  {
    case 0:
      return LINE_BR1;

    case 1:
      return LINE_BR2;

    case 2:
      return LINE_BR3;

    default:
      return LINE_BR4;
  }
}

/*
 * Convert column number to column line
 *
 * col -- column number
 * returns -- line (pin) assigned to column
 */
static ioline_t col_lookup(uint8_t col)
{
  chDbgAssert(col < BUTTON_NUM_COLS, "Invalid button column number");
  switch (col)
  {
    case 0:
      return LINE_BC1;

    case 1:
      return LINE_BC2;

    case 2:
      return LINE_BC3;

    case 3:
      return LINE_BC4;

    default:
      return LINE_BC5;
  }
}

/*
 * Set button state (after reading from relevant pin)
 *
 * row -- row number
 * col -- column number
 * state -- button state (true if pressed i.e. closed circuit)
 */
static void button_set_state_rc(uint8_t row, uint8_t col, bool state)
{
  chDbgAssert(row < BUTTON_NUM_ROWS, "Invalid button row number");
  chDbgAssert(col < BUTTON_NUM_COLS, "Invalid button column number");
  //chMtxLock(&buttons_state_mtx);
  buttons_state[row][col] = state;
  //chMtxUnlock(&buttons_state_mtx);
}

/*
 * Set button state (after reading from relevant pin)
 *
 * id -- button id
 * state -- button state (true if pressed i.e. closed circuit)
 */
static void button_set_state_id(uint8_t id, bool state)
{
  chDbgAssert(id < NUM_BUTTONS, "Invalid button ID");
  uint8_t row, col;
  button_row_col(id, &row, &col);
  button_set_state_rc(row, col, state);
}

inline uint8_t button_id(uint8_t row, uint8_t col)
{
  chDbgAssert(row < BUTTON_NUM_ROWS, "Invalid button row number");
  chDbgAssert(col < BUTTON_NUM_COLS, "Invalid button column number");
  return row * BUTTON_NUM_COLS + col;
}

inline void button_row_col(uint8_t id, uint8_t *row, uint8_t *col)
{
  chDbgAssert(id < NUM_BUTTONS, "Invalid button ID");
  *row = id / BUTTON_NUM_COLS;
  *col = id % BUTTON_NUM_COLS;
}

bool buttons_get_state_rc(uint8_t row, uint8_t col)
{
  chDbgAssert(row < BUTTON_NUM_ROWS, "Invalid button row number");
  chDbgAssert(col < BUTTON_NUM_COLS, "Invalid button column number");
  //chMtxLock(&buttons_state_mtx);
  bool ret = buttons_state[row][col];
  //chMtxUnlock(&buttons_state_mtx);
  return ret;
}

bool buttons_get_state_id(uint8_t id)
{
  chDbgAssert(id < NUM_BUTTONS, "Invalid button ID");
  uint8_t row, col;
  button_row_col(id, &row, &col);
  return buttons_get_state_rc(row, col);
}

void buttons_state_machine(void)
{
  static uint8_t button_count[BUTTON_NUM_ROWS][BUTTON_NUM_COLS] = {0};
  static uint8_t row = 0;

  ioline_t row_line = row_lookup(row);
  palSetLine(row_line);
  for(uint8_t col = 0; col < BUTTON_NUM_COLS; col++)
  {
    bool pinstate = palReadLine(col_lookup(col));
    if(pinstate != buttons_get_state_rc(row, col))
    {
      // Button state changed
      if (button_count[row][col] < DEBOUNCE_CYCLES)
      {
	button_count[row][col]++;
      }
      else
      {
	// Pin state has remained constant for DEBOUNCE_CYCLES cycles
	// Assume finished bouncing
	button_count[row][col] = 0;
	button_set_state_rc(row, col, pinstate);
	if(pinstate) button_pressed = button_id(row, col);
      }
    }
    else
    {
      // Button state has not changed
      button_count[row][col] = 0;  // Reset counter
    }
  }
  palClearLine(row_line);
  row = (row + 1)%BUTTON_NUM_ROWS;
}
