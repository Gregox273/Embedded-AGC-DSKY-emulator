/*
 * MCP23S08 driver
 */

#ifndef MCP23S08_H_
#define MCP23S08_H_

#include <stdint.h>
#include "ch.h"
#include "hal.h"

typedef enum mcp23s08_regaddr
{
  MCP23S08_IODIR_ADDR = 0x00,
  MCP23S08_IOCON_ADDR = 0x05,
  MCP23S08_GPIO_ADDR = 0x09,
  MCP23S08_OLAT_ADDR = 0x0A
}MCP23S08RegAddr;

/*
 * Send bytes to mcp23s08
 *
 * spidrv -- pointer to SPIDriver e.g. &SPID1
 * spicfg -- pointer to SPIConfig struct
 * txbuf  -- pointer to transmit buffer
 * len    -- number of bytes in transmit buffer
 */
void mcp23s08_send(SPIDriver *spidrv, SPIConfig *spicfg, void *txbuf,
                   size_t len);

/*
 * Write to mcp23s08 register
 *
 * spidrv      -- pointer to SPIDriver e.g. &SPID1
 * spicfg      -- pointer to SPIConfig struct
 * device_addr -- mcp23s08 device address (set using A1, A0 pins)
 * reg_addr    -- mcp23s08 register address
 * reg         -- byte to write to register
 */
void mcp23s08_write_reg(SPIDriver *spidrv, SPIConfig *spicfg, uint8_t device_addr,
                        MCP23S08RegAddr reg_addr, uint8_t reg);

/*
 * Initialise mcp23s08 driver
 *
 * spidrv      -- pointer to array of SPIDriver pointers (one entry per mcp23s08 device)
 * spicfg      -- pointer to array of SPIConfig pointers
 * addr        -- pointer to array of device addresses
 * num_devices -- number of mcp23s08 devices present i.e. number of entries in the arrays
 */
void mcp23s08_init(SPIDriver **spidrv, SPIConfig **spicfg, uint8_t *addr,
                   uint8_t num_devices);

#endif /* MCP23S08_H_ */
