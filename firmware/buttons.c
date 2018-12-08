/*
 * Key matrix driver
 */

#include "ch.h"
#include "hal.h"

#include "buttons.h"

#define DEBOUNCE_CYCLES 3  // Number of row passes used to debounce button
#define ROW_PERIOD      5  // ms

ioline_t row_lookup(uint8_t row)
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

ioline_t col_lookup(uint8_t col)
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

THD_WORKING_AREA(waButtons, 128);
THD_FUNCTION(button_thd_func, arg)
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
        if (button_status[row][col] < DEBOUNCE_CYCLES)
        {
          button_status[row][col] += palReadLine(col);
        }
        else
        {
          button_status[row][col] = 0;
          msg_t pressed_button = row * BUTTON_NUM_COLS + col;
          chMBPostTimeout(mbox, pressed_button, TIME_INFINITE);
        }
      }

      palClearLine(row_lookup(row));
      chThdSleepMilliseconds(ROW_PERIOD);
    }
  }
}
