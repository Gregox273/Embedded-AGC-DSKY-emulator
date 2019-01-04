/*
 * Lamp driver
 */
#ifndef __LAMPS_H__
#define __LAMPS_H__

#include "ch.h"

typedef enum lamp_id
{
  LAMP_COMP_ACTY = 0,
  LAMP_OPR_ERR,
  LAMP_KEY_REL,
  LAMP_STBY,
  LAMP_NO_ATT,
  LAMP_UPLINK_ACTY,
  LAMP_TEMP,
  LAMP_GIMBAL_LOCK,
  LAMP_PROG,
  LAMP_RESTART,
  LAMP_TRACKER,
  LAMP_ALT,
  LAMP_VEL,
  NUM_LAMPS
}LampId;

/*
 * Update lamps (blocking, takes max ~500us)
 *
 * num_lamps -- number of bytes to send
 */
void lamps_refresh(uint8_t num_lamps);

/*
 * Set lamp colour
 *
 * id  -- lamp id
 * g   -- green channel value
 * r   -- red channel value
 * b   -- blue channel value
 * returns -- number of colours * number of LEDs in the chain to refresh
 */
uint8_t lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b);

/*
 * Bulk modify the lamps_state array to set multiple lamps at once
 *
 * buf     -- pointer to buffer to copy into lamps_state
 * len     -- length of buffer to copy
 * offset  -- offset of start address (start copying here in lamps_state)
 * returns -- number of colours * number of LEDs in the chain to refresh
 */
uint8_t lamps_set_bulk(uint8_t *buf, uint8_t len, uint8_t offset);

/*
 * Turn off all lamps
 * 
 * returns -- number of colours * number of LEDs in the chain to refresh
 */
uint8_t lamps_clear(void);

/*
 * Test lamps
 */
void lamps_test(void);

/*
 * Initialise lamps driver
 */
void lamps_init(void);

#endif /* __LAMPS_H__ */
