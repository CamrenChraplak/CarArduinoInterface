#include "button.h"

// audio high time interval
#define HIGHTIME 100
// audio low time interval
#define LOWTIME 200

// stores pin for current button
int activeButton = -1;

/**
 * Button(int buttonPin, int buttonPressCount)
 * 
 * Initializes button object
 * 
 * Input:
 *      int buttonPin: pin number of button
 *      int buttonPressCount: amount of times to toggle audio input
 * 
 * Returns:
 * 		void
 */
AudioButton::AudioButton(int buttonPin, int buttonPressCount) {
    this -> pin = buttonPin;
    this -> pressCount = buttonPressCount;
}

/**
 * boolean isPressed()
 * 
 * Tests if the button is being pressed
 * 
 * Returns:
 * 		boolean: if button is being pressed
 */
boolean AudioButton::isPressed() {

    // makes sure button is going from inactive to active
    if (!(this -> state) && digitalRead(this -> pin) == HIGH && activeButton == -1) {

        // sets button as active
        activeButton = this -> pin;
        this -> state = true;
        this -> timeCount = millis();

        if (__DEBUG_PRINT__) {
            Serial.print("ON: ");
            Serial.println(this -> pressCount);
        }

        return true;

    }

    return false;
}

/**
 * boolean isReleased()
 * 
 * Tests if the button is being released
 * 
 * Returns:
 * 		boolean: if button is being released
 */
boolean AudioButton::isReleased() {

    // makes sure button is going from active to inactive
    if (this -> state && digitalRead(this -> pin) == LOW) {

        // sets button as released
        this -> state = false;
        return true;

    }

    return false;
}

/**
 * int getPin()
 * 
 * Gets pin number of button
 * 
 * Returns:
 * 		int: button pin number
 */
int AudioButton::getPin() {
    return this -> pin;
}

/**
 * void sendSignal()
 * 
 * Sends audio signal to control music
 * 
 * Returns:
 * 		void
 */
void AudioButton::sendSignal() {

    if (this -> pressCount < 0 || this -> pressCount > 3) {

        // invalid trigger count
        if (__DEBUG_PRINT__) {
            Serial.println("INVALID TRIGGER COUNT!");
        }
        return;
    }
    else if (this -> pin == activeButton) {

        // gets button press pulse from time
        int pulse = ((int)(millis() - this -> timeCount) - HIGHTIME) / (HIGHTIME + LOWTIME);

        if (pulse >= this -> pressCount) {
            // button has pulsed enough

            // sets button to inactive
            this -> timeCount = 0;
            digitalWrite(SIGNALPIN, LOW);
            activeButton = -1;

        }
        else {
            // button pulses in progress

            // gets time eleapsed
            int elapsed = ((int)(millis() - this -> timeCount) - HIGHTIME) % (HIGHTIME + LOWTIME);

            // sets signal pin based on time elapsed
            if (elapsed <= HIGHTIME) {
                digitalWrite(SIGNALPIN, HIGH);
            }
            else {
                digitalWrite(SIGNALPIN, LOW);
            }
        }
    }
}