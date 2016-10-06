/*
 * sketch.cpp
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#include <Arduino.h>

void setup(void)
{
	pinMode(LED, OUTPUT);
	Serial.begin(115200);

	Serial.println("Ready.");

	pinMode(8, OUTPUT);
	analogWrite(8, 0x80);
}

uint8_t led_status = 0;
uint32_t last_time = 0;

void loop(void)
{
	if (millis() - last_time >= 500)
	{
		last_time += 500;
		led_status = !led_status;
		digitalWrite(LED, led_status);
	}

	analogWrite(8, (millis() >> 2) & 0xff);

	while (Serial.available())
	{
		Serial.write(Serial.read());
	}
}
