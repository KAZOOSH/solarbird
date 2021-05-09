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
		Bird.playMelody( i );
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
	static unsigned char melodyStartIndex = -1;

	// get new start index that is different from last one
	unsigned char newIndex = random( 0, Bird.numMelodies );
	if ( newIndex == melodyStartIndex ) {
		melodyStartIndex = newIndex + 2;
	}
	else {
		melodyStartIndex = newIndex;
	}

	// play 2-4 consecutive melodies
	int count = random( 2, 4+1 );
	for ( int i = 0; i < count; i++ ) {
		LEDs::on();
		Bird.playMelody( (melodyStartIndex+i) % Bird.numMelodies );
		LEDs::off();
		delay( random( 0, 100 ) );
	}

	// wait 1-5s
	delay( random( 1000, 5000 ) );
}
