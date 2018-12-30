/*
 * Key matrix driver
 */
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "ch.h"

#define BUTTON_NUM_ROWS        4
#define BUTTON_NUM_COLS        5

/* Button IDs */
typedef enum button_id
{
  BUTTON_PLUS = 0,
  BUTTON_7,
  BUTTON_8,
  BUTTON_9,
  BUTTON_CLR,
  BUTTON_MINUS,
  BUTTON_4,
  BUTTON_5,
  BUTTON_6,
  BUTTON_PRO,
  BUTTON_0,
  BUTTON_1,
  BUTTON_2,
  BUTTON_3,
  BUTTON_KEY_REL,
  BUTTON_VERB,
  BUTTON_NOUN,
  BUTTON_INVALID,  // gap in matrix
  BUTTON_RSET,
  BUTTON_ENTR,
  NUM_BUTTONS
}ButtonId;

/*
 * Convert row & column to button ID
 *
 * row -- row number
 * col -- column number
 * returns -- button id
 */
extern uint8_t button_id(uint8_t row, uint8_t col);

/*
 * Convert button ID to row & column number
 *
 * id -- button id
 * row -- pointer to location to store row number
 * col -- pointer to location to store col number
 */
extern void button_row_col(uint8_t id, uint8_t *row, uint8_t *col);

/*
 * Return the state of the button indexed by ID number
 *
 * id -- button id
 * returns -- button state (false if not pressed i.e open circuit)
 */
bool buttons_get_state_id(uint8_t id);

/*
 * Return the state of the button indexed by row and column number
 *
 * row -- row no.
 * col -- col no.
 * returns -- button state (false if not pressed i.e open circuit)
 */
bool buttons_get_state_rc(uint8_t row, uint8_t col);

/*
 * Set up buttons driver
 *
 * button_mbox -- pointer to button state change mailbox
 */
void buttons_init(void *button_mbox);

#endif /* BUTTONS_H_ */
