// nick@bitfasching.de, Kazoosh, 2021
// For ATtiny85 @ 8 MHz

#define PIN_PIEZO_A 3
#define PIN_PIEZO_B 4
#define PIN_LED_1_ANODE 0
#define PIN_LED_2_ANODE 1
#define PIN_LED_CATHODES 2


// High-level IO //

#include "io/leds.h"
#include "io/piezo.h"


// Bird voices //

#include "voices/blackbird.h"
Blackbird Bird;


// Main logic //

void setup()
{
	// wait to make sure programmer is high-Z
	delay( 10 );

	// startup test: play all melodies once with fixed delay in between
	for ( int i = 0; i < Bird.numMelodies; i++ ) {
		LEDs::on();
		Bird.playSingleMelody( i );
		LEDs::off();
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
	LEDs::on();
	Bird.play();
	LEDs::off();

	// wait 1-5s
	delay( random( 2000, 10000 ) );
}
