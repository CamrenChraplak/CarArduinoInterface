#include "gps.h"

// gps object
TinyGPSPlus gps;

// string recieved from gps
String gpsString = "";

/**
 * boolean getSpeed(double *speed, byte gpsData)
 * 
 * Gets speed from gps
 * 
 * Input:
 * 		double *speed: speed from gps
 * 		byte gpsData: byte read from serial
 * 
 * Returns:
 * 		boolean: if speed is updated
 */
boolean getSpeed(double *speed, byte gpsData) {

	// stores whether speed is updated
	boolean updated = false;

	// adds recent character to current recieved string
	gpsString += (char)gpsData;

	if ((char)gpsData == '\n') {

		// tests if speed value is updated
		if (gpsString.indexOf("GPVTG") > 0) {

			// stores updated speex
			*speed = gps.speed.mph();
			updated = true;

			if (__DEBUG_PRINT__) {
				Serial.print(*speed);
				Serial.print(",\t");
				Serial.println(gps.satellites.value());
			}
		}

		// resets recieved string
		gpsString = "";
	}

	return updated;
}

/**
 * boolean updateGPS(double *speed)
 * 
 * Updates gps values
 * 
 * Input:
 * 		double *speed: speed from gps
 * 
 * Returns:
 * 		boolean: if speed is updated
 */
boolean updateGPS(double *speed) {

	if (Serial.available() > 0) {

		// updates recieved string
		byte gpsData = Serial.read();
		gps.encode(gpsData);

		return getSpeed(speed, gpsData);
	}

	return false;
}