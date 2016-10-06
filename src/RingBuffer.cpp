/*
 * RingBuffer.cpp
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#include <RingBuffer.h>
#include <string.h>

RingBuffer::RingBuffer(void)
{
	memset((void *)(buffer), 0, SERIAL_BUFFER_SIZE);
	head = 0;
	tail = 0;
}

int RingBuffer::putch(uint8_t c)
{
	uintptr_t i = (head + 1) % SERIAL_BUFFER_SIZE;

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != tail)
	{
		buffer[head] = c;
		head = i;
		return 0;
	}
	else
	{
		return -1;
	}
}

int RingBuffer::getch(void)
{
	int ch = peekch();

	if (ch >= 0)
	{
		tail = (tail + 1) % SERIAL_BUFFER_SIZE;
	}

	return ch;
}

int RingBuffer::peekch(void)
{
	if (tail != head)
	{
		return buffer[tail];
	}
	else
	{
		return -1;
	}
}

size_t RingBuffer::flen(void)
{
	return (SERIAL_BUFFER_SIZE + head - tail) % SERIAL_BUFFER_SIZE;
}
