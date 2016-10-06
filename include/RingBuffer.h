/*
 * RingBuffer.h
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#include <stdint.h>
#include <sys/types.h>

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer, in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE 128
#endif

#ifdef __cplusplus

class RingBuffer
{
private:
    volatile uint8_t buffer[SERIAL_BUFFER_SIZE] ;
    volatile uintptr_t head ;
    volatile uintptr_t tail ;

public:
    RingBuffer(void);
    int putch(uint8_t c);
    int getch(void);
    int peekch(void);
    size_t flen(void);
};

#endif

#endif /* _RING_BUFFER_ */
