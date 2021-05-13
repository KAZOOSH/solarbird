// nick@bitfasching.de, Kazoosh, 2021

class Blackbird
{
	public:

		Blackbird() {}

		static const unsigned char numMelodies = 6;

		void static playSingleMelody( unsigned char melodySelector, bool lightLEDs=false )
		{
			Piezo::on();
			if ( lightLEDs ) {
				LEDs::glow();
			}

			switch ( melodySelector )
			{
				case 0:
					for ( int i = 0; i < 6; i++ ) {
						Piezo::chirp( 1E6/2100, 1E6/2400, 4 );
					}
					Piezo::chirp( 1E6/2000, 1E6/3200, 4 );
					Piezo::chirp( 1E6/3200, 1E6/2000, 4 );
					Piezo::chirp( 1E6/2000, 1E6/3000, 4 );
					Piezo::chirp( 1E6/3000, 1E6/2000, 6 );
					Piezo::chirp( 1E6/2000, 1E6/3200, 2 );
					break;

				case 1:
					Piezo::chirp( 1E6/1600, 1E6/1800, 2 );
					Piezo::chirp( 1E6/1700, 1E6/1500, 2 );
					for ( int i = 0; i < 2; i++ ) {
						Piezo::chirp( 1E6/1400, 1E6/1800, 4 );
					}
					for ( int i = 0; i < 3; i++ ) {
						Piezo::chirp( 1E6/1600, 1E6/2100, 6 );
						Piezo::chirp( 1E6/2000, 1E6/1500, 6 );
					}
					Piezo::chirp( 1E6/1700, 1E6/2200, 4 );
					Piezo::chirp( 1E6/2200, 1E6/1700, 6 );
					break;

				case 2:
					Piezo::chirp( 1E6/2200, 1E6/2800, 4 );
					Piezo::chirp( 1E6/2800, 1E6/2200, 2 );
					for ( int i = 0; i < 2; i++ ) {
						Piezo::chirp( 1E6/2300, 1E6/2900, 4 );
						Piezo::chirp( 1E6/2900, 1E6/2300, 3 );
					}
					for ( int i = 0; i < 3; i++ ) {
						Piezo::chirp( 1E6/2400, 1E6/3000, 3 );
						Piezo::chirp( 1E6/3000, 1E6/2400, 3 );
					}
					for ( int i = 0; i < 6; i++ ) {
						Piezo::chirp( 1E6/2500, 1E6/2900, 4 );
						Piezo::chirp( 1E6/2900, 1E6/2500, 6 );
					}
					break;

				case 3:
					for ( int i = 0; i < 2; i++ ) {
						Piezo::chirp( 1E6/3500, 1E6/3800, 4 );
					}
					for ( int i = 0; i < 3; i++ ) {
						Piezo::chirp( 1E6/3300, 1E6/3700, 4 );
					}
					for ( int i = 0; i < 4; i++ ) {
						Piezo::chirp( 1E6/3100, 1E6/3600, 4 );
					}
					for ( int i = 0; i < 3; i++ ) {
						Piezo::chirp( 1E6/3000, 1E6/3600, 1 );
						Piezo::chirp( 1E6/3600, 1E6/3000, 2 );
					}
					Piezo::chirp( 1E6/2800, 1E6/3600, 1 );
					break;

				case 4:
					Piezo::chirp( 1E6/1400, 1E6/2400, 2 );
					for ( int i = 0; i < 3; i++ ) {
						Piezo::chirp( 1E6/2400, 1E6/2000, 2 );
						Piezo::chirp( 1E6/2000, 1E6/2400, 3 );
					}
					Piezo::chirp( 1E6/2400, 1E6/2000, 2 );
					Piezo::chirp( 1E6/2000, 1E6/2400, 2 );
					for ( int i = 0; i < 5; i++ ) {
						Piezo::chirp( 1E6/2100, 1E6/2400, 4 );
					}
					break;

				case 5:
					for ( int i = 0; i < 3; i++ ) {
						Piezo::chirp( 1E6/1600, 1E6/2200, 8 );
					}
					Piezo::chirp( 1E6/2300, 1E6/3100, 2 );
					Piezo::tone( 1E6/3100, 1E6*0.1 );
					Piezo::chirp( 1E6/3100, 1E6/2600, 1 );
					break;
			}

			Piezo::off();
			if ( lightLEDs ) {
				LEDs::off();
			}
		}

		void static play( bool lightLEDs=false )
		{
			// initialize with an index that does not exist, see following if
			static int melodyStartIndex = -1;

			// get new start index that is different from last one
			int newIndex = random( 0, numMelodies );
			if ( newIndex == melodyStartIndex ) {
				melodyStartIndex = newIndex + 2;
			}
			else {
				melodyStartIndex = newIndex;
			}

			// play 2-4 consecutive melodies
			int count = random( 2, 4+1 );
			for ( int i = 0; i < count; i++ ) {
				playSingleMelody( (melodyStartIndex+i) % numMelodies, lightLEDs );
				delay( 20 );
			}
		}
};
