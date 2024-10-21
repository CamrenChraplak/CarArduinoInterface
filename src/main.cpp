#include <Arduino.h>

#include "main.h"

void setup() {

	// initializes serial
	Serial.begin(9600);

	// initialization
	initSeg();
	initAudio();

}

void loop() {

	toggleAudio();

	// displays new speed
	double speed = -1;

	if (updateGPS(&speed)) {

		dispNum((int)speed);

	}

}