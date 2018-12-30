/*
 * MCP23S08 driver
 */

#ifndef MCP23S08_H_
#define MCP23S08_H_

#include <stdint.h>
#include "ch.h"
#include "hal.h"

#define MCP23S08_IODIR_ADDR 0x00
//#define MCP23S08_IOCON_ADDR 0x05
#define MCP23S08_GPIO_ADDR 0x09
#define MCP23S08_OLAT_ADDR 0x0A

//typedef struct iocon_cfg
//{
//  bool SEQOP;
//  bool DISSLW;
//  bool HAEN;
//  bool ODR;
//  bool INTPOL;
//}IOCONCfg;

void mcp23s08_send(SPIDriver *spidrv, SPIConfig *spicfg, void *txbuf,
                   size_t len);

void mcp23s08_write_reg(SPIDriver *spidrv, SPIConfig *spicfg, uint8_t device_addr,
                          uint8_t reg_addr, uint8_t reg);

void mcp23s08_init(SPIDriver **spidrv, SPIConfig **spicfg, uint8_t *addr,
                   uint8_t num_devices);

#endif /* MCP23S08_H_ */
