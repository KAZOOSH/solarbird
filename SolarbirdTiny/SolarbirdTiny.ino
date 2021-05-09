// nick@bitfasching.de, Kazoosh, 2021
// For ATtiny85 @ 8 MHz

#define PIN_PIEZO_A 3
#define PIN_PIEZO_B 4
#define PIN_LED_1_ANODE 0
#define PIN_LED_2_ANODE 1
#define PIN_LED_CATHODES 2

const bool lightLEDsWhenPlaying = true;


// High-level access to I/O and system features //

#include "system/leds.h"
#include "system/piezo.h"
#include "system/lowpower.h"


// Bird voices //

#include "voices/blackbird.h"
Blackbird Bird;


// Main logic //

void setup()
{
	// wait to make sure programmer is high-Z
	delay( 10 );

	// startup test: flash LEDs
	LEDs::on();
	delay( 250 );
	LEDs::off();
	delay( 250 );

	// startup test: play all melodies once with fixed delay in between
	for ( int i = 0; i < Bird.numMelodies; i++ ) {
		Bird.playSingleMelody( i, lightLEDsWhenPlaying );
		delay( 1000 );
	}

	// initialize random number generator with external source of randomness
	delay( 1000 );
	pinMode( PIN_PIEZO_A, INPUT );
	randomSeed( analogRead( PIN_PIEZO_A ) );
}

void loop()
{
	// play melodies
	Bird.play( lightLEDsWhenPlaying );

	// wait 1-10s
	int seconds = random( 1, 10+1 );
	for ( int i = 0; i < seconds; i++ ) {
		LowPower::sleepOneSecond();
	}
}
