/*
 * nvram.h
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#ifndef INCLUDE_NVRAM_H_
#define INCLUDE_NVRAM_H_

#include <stm32f10x.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

uint16_t nvram_read(uint8_t addr);
void nvram_write(uint8_t addr, uint16_t data);

__END_DECLS

#ifdef __cplusplus

class NVRAMCell
{
private:
	uint8_t addr;

public:
	NVRAMCell(uint8_t addr);
	uint16_t operator = (uint16_t value);
	operator uint16_t(void);
};

class NVRAMClass
{
public:
	NVRAMClass(void);
	NVRAMCell operator [] (uint8_t addr);
};

extern NVRAMClass NVRAM;

#endif


#endif /* INCLUDE_NVRAM_H_ */
