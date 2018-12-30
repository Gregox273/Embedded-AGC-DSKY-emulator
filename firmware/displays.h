/*
 * 7 segment display driver
 */
#ifndef DISPLAYS_H_
#define DISPLAYS_H_

#include "ch.h"

#define DISPLAYS_NUM_ROWS        3
#define DISPLAYS_NUM_COLS        7

uint8_t displays_get_state_rc(uint8_t row, uint8_t col);
uint8_t displays_get_state_id(uint8_t id);
void displays_set_state_rc(uint8_t row, uint8_t col, uint8_t state);
void displays_set_state_id(uint8_t id, uint8_t state);

bool displays_set_verb(uint8_t val);
bool displays_set_noun(uint8_t val);
bool displays_set_prog(uint8_t val);
bool displays_set_row(uint8_t row, int32_t val);

void displays_init(void);

#endif /* DISPLAYS_H_ */
