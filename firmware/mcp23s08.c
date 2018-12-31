/*
 * MCP23S08 driver
 */

#include "mcp23s08.h"

#define MCP23S08_FIXED_ADDR 0b01000000
#define MCP23S08_READ  1
#define MCP23S08_WRITE 0

void mcp23s08_send(SPIDriver *spidrv, SPIConfig *spicfg, void *txbuf,
                   size_t len)
{
  spiAcquireBus(spidrv);
  spiStart(spidrv, spicfg);
  spiSelect(spidrv);

  spiSend(spidrv, len, txbuf);

  spiUnselect(spidrv);
  spiReleaseBus(spidrv);
}

void mcp23s08_write_reg(SPIDriver *spidrv, SPIConfig *spicfg, uint8_t device_addr,
                        MCP23S08RegAddr reg_addr, uint8_t reg)
{
  const uint8_t buflen = 3;
  uint8_t buf[buflen];
  // Opcode
  buf[0] = MCP23S08_FIXED_ADDR | ((device_addr<<1) & 0b110) | MCP23S08_WRITE;
  // Register address
  buf[1] = reg_addr;
  // Data
  buf[2] = reg;
  mcp23s08_send(spidrv, spicfg, buf, buflen);
}

//void mcp23s08_write_iocon(SPIDriver *spidrv, SPIConfig *spicfg, uint8_t addr,
//                          IOCONCfg *cfg)
//{
//  const uint8_t buflen = 3;
//  uint8_t buf[buflen];
//  // Opcode
//  buf[0] = MCP23S08_FIXED_ADDR | (addr<<1 & 0b110) | MCP23S08_WRITE;
//  // Register address
//  buf[1] = IOCON_ADDR;
//  // Data
//  buf[2] = 0;
//  if(cfg->SEQOP) buf[2] |= 1 << 5;
//  if(cfg->DISSLW) buf[2] |= 1 << 4;
//  if(cfg->HAEN) buf[2] |= 1 << 3;
//  if(cfg->ODR) buf[2] |= 1 << 2;
//  if(cfg->INTPOL) buf[2] |= 1 << 1;
//
//  mcp23s08_send(spidrv, spicfg, buf, buflen);
//}

void mcp23s08_init(SPIDriver **spidrv, SPIConfig **spicfg, uint8_t *addr,
                   uint8_t num_devices)
{
  for(uint16_t i = 0; i < num_devices; i++)
  {
    // Set all pins to outputs
    mcp23s08_write_reg(spidrv[i], spicfg[i], addr[i], MCP23S08_IODIR_ADDR, 0x00);
  }
}
