/*
 * 7 segment display driver
 */
#ifndef DISPLAYS_H_
#define DISPLAYS_H_

#include "ch.h"

#define DISPLAYS_NUM_ROWS        3
#define DISPLAYS_NUM_COLS        8

typedef enum display_state
{
  //        degfcba
  N_0   = 0b1101111,
  N_1   = 0b0000110,
  N_2   = 0b1110011,
  N_3   = 0b1010111,
  N_4   = 0b0011110,
  N_5   = 0b1011101,
  N_6   = 0b1111101,
  N_7   = 0b0000111,
  N_8   = 0b1111111,
  N_9   = 0b1011111,
  N_B   = 0b0000000,  // Blank
  // plus-minus symbols
  N_P   = 0b1100011,
  N_M   = 0b1000010,
  N_ERR = 0b0010000   // Invalid digit
  //        degfcba
}DisplayState;

/*
 * Get 7 segment display state
 *
 * row     -- display row number
 * col     -- display column number
 * returns -- 7 segment display state
 */
DisplayState displays_get_state_rc(uint8_t row, uint8_t col);

/*
 * Get 7 segment display state
 *
 * id      -- display ID number
 * returns -- 7 segment display state
 */
DisplayState displays_get_state_id(uint8_t id);

/*
 * Set 7 segment display state
 *
 * row   -- display row number
 * col   -- display column number
 * state -- desired display state
 *          (set bits correspond to lit segments in order degfcba)
 */
void displays_set_state_rc(uint8_t row, uint8_t col, DisplayState state);

/*
 * Set 7 segment display state
 *
 * id    -- display id number
 * state -- desired display state
 *          (set bits correspond to lit segments in order degfcba)
 */
void displays_set_state_id(uint8_t id, DisplayState state);

/*
 * Set VERB display
 *
 * val     -- numerical value to display
 * returns -- true if valid input
 */
bool displays_set_verb(uint8_t val);

/*
 * Set NOUN display
 *
 * val     -- numerical value to display
 * returns -- true if valid input
 */
bool displays_set_noun(uint8_t val);

/*
 * Set PROG display
 *
 * val     -- numerical value to display
 * returns -- true if valid input
 */
bool displays_set_prog(uint8_t val);

/*
 * Set one of the three rows of 5 displays
 *
 * row     -- row number to set
 * val     -- numerical value to display
 * returns -- true if valid input
 */
bool displays_set_row(uint8_t row, int32_t val);

/*
 * Initialise display driver (including mcp23s08)
 */
void displays_init(void);

/*
 * Test display hardware & driver e.g. on startup
 */
void displays_test(void);

#endif /* DISPLAYS_H_ */
