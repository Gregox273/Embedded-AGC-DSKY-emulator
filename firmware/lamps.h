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
 * Set lamp colour
 *
 * id      -- lamp id
 * g       -- green channel value
 * r       -- red channel value
 * b       -- blue channel value
 * returns -- false if invalid id, else true
 */
bool lamps_set_single(LampId id, uint8_t g, uint8_t r, uint8_t b);

/*
 * Safely buffer into lamp state array, then set lamps
 *
 * buf     -- pointer to bytes buffer
 * len     -- number of bytes in buffer
 * offset  -- position to insert the first byte in lamp state array
 * returns -- false if len + offset exceeds size of lamp state array, else true
 */
bool lamps_set_bulk(uint8_t *buf, uint8_t len, uint8_t offset);

/*
 * Initialise lamps driver
 */
void lamps_init(void);

#endif /* __LAMPS_H__ */
