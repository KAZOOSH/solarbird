// nick@bitfasching.de, Kazoosh, 2021
// For ATtiny85 @ 8 MHz

#define PIN_PIEZO_A 3
#define PIN_PIEZO_B 4
#define PIN_LED_1_ANODE 0
#define PIN_LED_2_ANODE 1
#define PIN_LED_CATHODES 2

const bool runStartupTest = true;
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

	if ( runStartupTest )
	{
		// startup test: flash LEDs
		LEDs::on();
		delay( 250 );
		LEDs::off();
		delay( 500 );

		// startup test: play all melodies once with fixed delay in between
		for ( int i = 0; i < Bird.numMelodies; i++ ) {
			Bird.playSingleMelody( i, lightLEDsWhenPlaying );
			delay( 1000 );
		}

		delay( 1000 );
	}

	// initialize random number generator with external source of randomness
	pinMode( PIN_LED_1_ANODE, INPUT ); delay( 10 );
	randomSeed( analogRead( PIN_LED_1_ANODE ) );
}

void loop()
{
	// play melodies
	Bird.play( lightLEDsWhenPlaying );

	// wait 2-20s
	LowPower::sleepSeconds( random( 2, 20+1 ) );
}
