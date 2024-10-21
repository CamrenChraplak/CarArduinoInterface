#include <Arduino.h>

#include "carpins.h"

// used to store attributes for audio buttons
class AudioButton {

    private:

        // button pin
        int pin = -1;

        // button active state
        boolean state = false;

        // button audio press count
        int pressCount = 0;

        // time wen button pressed
        unsigned long timeCount = 0;

    public:

        AudioButton(int buttonPin, int buttonPressCount);
        boolean isPressed();
        boolean isReleased();
        int getPin();
        void sendSignal();
};