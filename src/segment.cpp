#include "segment.h"

// initializes digit segment
void setupSeg(struct segment *seg, int segPins[SEGPINCOUNT]);

// sets digit segment
void setSeg(struct segment *seg, int number);

/*const int zero[SEGPINCOUNT] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
const int one[SEGPINCOUNT] = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW};
const int two[SEGPINCOUNT] = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH};
const int three[SEGPINCOUNT] = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH};
const int four[SEGPINCOUNT] = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH};
const int five[SEGPINCOUNT] = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH};
const int six[SEGPINCOUNT] = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH};
const int seven[SEGPINCOUNT] = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW};
const int eight[SEGPINCOUNT] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
const int nine[SEGPINCOUNT] = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH};
const int invalid[SEGPINCOUNT] = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH};
const int digits[11][SEGPINCOUNT] = {{zero}, {one}, {two}, {three}, {four}, {five},
		{six}, {seven}, {eight}, {nine}, {invalid}};*/

const int digits[11][SEGPINCOUNT] = {
	{HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},
	{LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},
	{HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},
	{HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},
	{LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},
	{HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},
	{HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},
	{HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},
	{HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},
	{HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH},
	{LOW, LOW, LOW, LOW, LOW, LOW, HIGH}
};

// seven segment display
struct segment {
	int pins[SEGPINCOUNT];
	int state[SEGPINCOUNT];
};

// segments 2 and 3
struct segment seg2;
struct segment seg3;

/**
 * void initSeg()
 * 
 * Initializes seven segment display
 * 
 * Returns:
 * 		void
 */
void initSeg() {
    
    // seven segment pins
	int pins2[] = {SEG2A, SEG2B, SEG2C, SEG2D, SEG2E, SEG2F, SEG2G};
	int pins3[] = {SEG3A, SEG3B, SEG3C, SEG3D, SEG3E, SEG3F, SEG3G};

	// initializes seven segment display
	setupSeg(&seg2, pins2);
	setupSeg(&seg3, pins3);
	setSeg(&seg2, -1);
	setSeg(&seg3, -1);
}

/**
 * void setupSeg(struct segment *seg, int segPins[SEGPINCOUNT])
 * 
 * Initializes seven segment digit display
 * 
 * Input:
 * 		struct segment *seg: segment display to target
 * 		int segPins[SEGPINCOUNT]: segment pin numbers
 * 
 * Returns:
 * 		void
 */
void setupSeg(struct segment *seg, int segPins[SEGPINCOUNT]) {

	// sets up pins to be outputs
	for (int i = 0; i < SEGPINCOUNT; i++) {

		seg -> pins[i] = segPins[i];
		pinMode(seg -> pins[i], OUTPUT);
		seg -> state[i] = LOW;

	}
}

/**
 * void setSeg(struct segment *seg, int number)
 * 
 * Sets digit on seven segment display
 * 
 * Input:
 * 		struct segment *seg: segment display to target
 * 		int number: number to display
 * 
 * Returns:
 * 		void
 */
void setSeg(struct segment *seg, int number) {

	if (number < 0 || number > 9) {

        // sets digit to invalid
		number = 10;

		if (__DEBUG_PRINT__) {
			Serial.println("INVALID NUMBER!");
		}

	}

	// toggles seven segment leds
	for (int i = 0; i < SEGPINCOUNT; i++) {

		if (digits[number][i] != seg -> state[i]) {
			digitalWrite(seg -> pins[i], digits[number][i]);
			seg -> state[i] = digits[number][i];
		}
		

	}
}

/**
 * void dispNum(int number)
 * 
 * Displays number to seven segment
 * 
 * Input:
 * 		int number: number to display
 * 
 * Returns:
 * 		void
 */
void dispNum(int number) {

	
	if (number < 0 || number > 99) {

        // shows invalid number
		setSeg(&seg2, -1);
		setSeg(&seg3, -1);

	}
	else {

        // shows valid number
		const int ones = number % 10;
		const int tens = (number - ones) / 10;

		setSeg(&seg2, tens);
		setSeg(&seg3, ones);

	}
}