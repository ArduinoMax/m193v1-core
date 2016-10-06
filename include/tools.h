/*
 * tools.h
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#ifndef INCLUDE_TOOLS_H_
#define INCLUDE_TOOLS_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdint.h>

__BEGIN_DECLS

void stopPWM(uint8_t pin);
uint8_t getPinMode(uint8_t pin);
void analogSetMaximumValue(uint16_t value);

__END_DECLS


#endif /* INCLUDE_TOOLS_H_ */
