/*
 * nvram.cpp
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#include <system.h>
#include <Arduino.h>
#include <NVRAM.h>
#include <stm32f10x_bkp.h>

uint16_t nvram_read(uint8_t addr)
{
	if (addr > 41)
		return 0;

	return BKP_ReadBackupRegister(addr * 4 + 4);
}

void nvram_write(uint8_t addr, uint16_t data)
{
	if (addr > 41)
		return;

	BKP_WriteBackupRegister(addr * 4 + 4, data);
}

NVRAMClass::NVRAMClass(void) {}

NVRAMCell NVRAMClass::operator [] (uint8_t addr)
{
	return NVRAMCell(addr);
}

NVRAMCell::NVRAMCell(uint8_t addr)
{
	this->addr = addr;
}

uint16_t NVRAMCell::operator = (uint16_t value)
{
	nvram_write(addr, value);
	return value;
}

NVRAMCell::operator uint16_t (void)
{
	return nvram_read(addr);
}
