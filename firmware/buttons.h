/*
 * Key matrix driver
 */
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "ch.h"

#define BUTTON_NUM_ROWS        4
#define BUTTON_NUM_COLS        5

bool buttons_get_state_id(uint8_t id);
bool buttons_get_state_rc(uint8_t row, uint8_t col);

void buttons_init(void *button_mbox);

#endif /* BUTTONS_H_ */
