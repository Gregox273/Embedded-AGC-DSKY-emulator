/*
 * Key matrix driver
 */
#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "ch.h"

#define BUTTON_NUM_ROWS        4
#define BUTTON_NUM_COLS        5

extern THD_WORKING_AREA(waButtons, 128);
THD_FUNCTION(button_thd_func, arg);

#endif /* __BUTTONS_H__ */
