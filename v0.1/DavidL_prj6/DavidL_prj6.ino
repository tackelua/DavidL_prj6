/*
	Name:       DavidL_prj6.ino
	Created:	08-Aug-18 13:55:20
	Author:     GITH\tacke

====================================

	ATtiny 85 digispark board.

	Pin0 (button) push=high
	Pin1 (led1)
	Pin2 (led2)

	led1 (high) at power on

	when (button) push (high),	led1 (low)

	led2 (high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 4 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	repeat
	led2 (high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 4 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
	(high) for LONG_HIGH, (low) delay SHORT_LOW
	(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,

	when button release (low),
	led1 (high)
	led2 (low)

	so when button push, led1 turn off and led2 blinking 4 time than stay on 15 second,
	than blinking 2 time than stay on for 15, than blinking 2 time than stay on for 15,
	than blinking 2 time than stay on for 15, thank repeat ALL blinking pattern from 4 blinking.
	When button release led1 turn on and led2 turn off.
*/

#define VERSION 0.1

#include "JC_Button.h"

#define BUTTON	0
#define LED1	1
#define LED2	2

#define LONG_HIGH	15000
#define SHORT_HIGH	120
#define SHORT_LOW	80

#define dbTime		10
#define puEnable	false
#define invert		false
Button myBtn(BUTTON, dbTime, puEnable, invert);

#define DEBUG Serial

void led1(bool stt) {
	static bool stt1 = HIGH;
	if (stt1 != stt) {
		stt1 = stt;
		digitalWrite(LED1, stt1);
		//DEBUG.print("LED1: ");
		//DEBUG.println(stt1);
		//DEBUG.println();
	}
}
void led2(bool stt) {
	static bool stt2 = LOW;
	if (stt2 != stt) {
		stt2 = stt;
		digitalWrite(LED2, stt2);
	}
}

void wait(unsigned long ms) {
	unsigned long t = millis();
	while (myBtn.isPressed() && millis() - t < ms) {
		myBtn.read();
		delay(1);
	}
}

void processLed2() {
	//DEBUG.println("processLed2");
	myBtn.read();
	while (myBtn.isPressed()) {
		/*
		led2 (high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 4 time,
		(high) for LONG_HIGH, (low) delay SHORT_LOW
		(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
		(high) for LONG_HIGH, (low) delay SHORT_LOW
		(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
		(high) for LONG_HIGH, (low) delay SHORT_LOW
		(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
		(high) for LONG_HIGH, (low) delay SHORT_LOW
		(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
		*/

		//led2 (high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 4 time,
		for (byte i = 0; i < 4; i++)
		{
			led2(HIGH);
			wait(SHORT_HIGH);
			led2(LOW);
			wait(SHORT_LOW);
		}

		//Repeat 4 times
		//(high) for LONG_HIGH, (low) delay SHORT_LOW
		//(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
		for (byte i = 0; i < 4; i++)
		{
			led2(HIGH);
			wait(LONG_HIGH);
			led2(LOW);
			wait(SHORT_LOW);

			//(high) delay SHORT_HIGH, (low) delay SHORT_LOW, repeat 2 time,
			for (byte j = 0; j < 2; j++)
			{
				led2(HIGH);
				wait(SHORT_HIGH);
				led2(LOW);
				wait(SHORT_LOW);
			}
		}
	}
}

void setup() {
	//DEBUG.begin(74880);
	myBtn.begin();
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	digitalWrite(LED1, HIGH);
	digitalWrite(LED2, LOW);
	//DEBUG.println("START");
}

void loop() {
	myBtn.read();
	if (myBtn.isReleased()) {
		//DEBUG.println("Release");
		led1(HIGH);
		led2(LOW);
	}
	if (myBtn.isPressed()) {
		//DEBUG.println("Press");
		led1(LOW);
		processLed2();
	}
}