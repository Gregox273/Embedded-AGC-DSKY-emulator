/*
 * Key matrix driver
 */
#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <stdbool.h>
#include "ch.h"

#define BUTTON_NUM_ROWS        4
#define BUTTON_NUM_COLS        5

bool buttons_get_state_id(uint8_t id);

bool buttons_get_state_rc(uint8_t row, uint8_t col);

extern THD_WORKING_AREA(waButtons, 128);
THD_FUNCTION(button_thd_func, arg);

#endif /* __BUTTONS_H__ */
