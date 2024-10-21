#include "audio.h"

// audio buttons
AudioButton playButton(PLAYPIN, 1);
AudioButton reverseButton(REVERSEPIN, 3);
AudioButton forwardButton(FORWARDPIN, 2);
AudioButton buttons[] = {playButton, forwardButton, reverseButton};

const int ButtonSize = (int)(sizeof(buttons) / sizeof(AudioButton));

/**
 * void initAudio()
 * 
 * Initializes audio pins
 * 
 * Returns:
 * 		void
 */
void initAudio() {

    // inits audio buttons
    for (int i = 0; i < ButtonSize; i++) {
        pinMode(buttons[i].getPin(), INPUT);
    }
}

/**
 * void toggleAudio()
 * 
 * Toggles audio control
 * 
 * Returns:
 * 		void
 */
void toggleAudio() {

	// loops through each button action
	for (int i = 0; i < ButtonSize; i++) {
		buttons[i].isPressed();
		buttons[i].sendSignal();
		buttons[i].isReleased();
	}
}