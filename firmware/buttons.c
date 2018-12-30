/*
 * Key matrix driver
 */

#include "hal.h"
#include "buttons.h"

#define DEBOUNCE_CYCLES 3  // Number of row passes used to debounce button
#define ROW_PERIOD      5  // ms

/* Global state - do not access directly
 * Use getter/setter functions
 */
static mutex_t buttons_state_mtx;
static bool buttons_state[BUTTON_NUM_ROWS][BUTTON_NUM_COLS];

static ioline_t row_lookup(uint8_t row)
{
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

static ioline_t col_lookup(uint8_t col)
{
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

static inline uint8_t button_id(uint8_t row, uint8_t col)
{
  return row * BUTTON_NUM_COLS + col;
}

static inline void button_row_col(uint8_t id, uint8_t *row, uint8_t *col)
{
  *row = id / BUTTON_NUM_COLS;
  *col = id % BUTTON_NUM_COLS;
}

bool buttons_get_state_rc(uint8_t row, uint8_t col)
{
  chMtxLock(&buttons_state_mtx);
  bool ret = buttons_state[row][col];
  chMtxUnlock(&buttons_state_mtx);
  return ret;
}

bool buttons_get_state_id(uint8_t id)
{
  uint8_t row, col;
  button_row_col(id, &row, &col);
  return buttons_get_state_rc(row, col);
}

static void button_set_state_rc(uint8_t row, uint8_t col, bool state)
{
  chMtxLock(&buttons_state_mtx);
  buttons_state[row][col] = state;
  chMtxUnlock(&buttons_state_mtx);
}

static void button_set_state_id(uint8_t id, bool state)
{
  uint8_t row, col;
  button_row_col(id, &row, &col);
  button_set_state_rc(row, col, state);
}

static THD_WORKING_AREA(waButtons, 256);
static THD_FUNCTION(buttons_thd_func, arg)
{
  mailbox_t* mbox = (mailbox_t*)arg;
  uint8_t button_status[BUTTON_NUM_ROWS][BUTTON_NUM_COLS];

  while (true)
  {
    for(uint8_t row = 0; row < BUTTON_NUM_ROWS; row++)
    {
      palSetLine(row_lookup(row));

      for(uint8_t col = 0; col < BUTTON_NUM_COLS; col++)
      {
        bool pinstate = palReadLine(col);
        if(pinstate != buttons_get_state_rc(row, col))
        {
          // Button state changed
          if (button_status[row][col] < DEBOUNCE_CYCLES)
          {
            button_status[row][col]++;
          }
          else
          {
            // Pin state has remained constant for DEBOUNCE_CYCLES cycles
            // Assume finished bouncing
            button_status[row][col] = 0;
            button_set_state_rc(row, col, pinstate);
            msg_t pressed_button = button_id(row, col);
            // Indicate button changed state
            chMBPostTimeout(mbox, pressed_button, TIME_INFINITE);
          }
        }
        else
        {
          // Button state has not changed
          button_status[row][col] = 0;  // Reset counter
        }
      }

      palClearLine(row_lookup(row));
      chThdSleepMilliseconds(ROW_PERIOD);
    }
  }
}

void buttons_init(void *button_mbox)
{
  chMtxObjectInit(&buttons_state_mtx);
  chThdCreateStatic(waButtons, sizeof(waButtons), NORMALPRIO, buttons_thd_func,
                    button_mbox);
}
