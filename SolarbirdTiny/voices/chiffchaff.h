// nick@bitfasching.de, Kazoosh, 2021
// Original bird voice: https://www.nabu.de/downloads/vogelportraets/Zilpzalp_Gesang_NABU_Lars_Lachmann.mp3

class Chiffchaff
{
	public:

		Chiffchaff() {}

		static const unsigned char numMelodies = 2;

		void static playSingleMelody( unsigned char melodySelector, bool lightLEDs=false )
		{
			switch ( melodySelector )
			{
				case 0:
					for ( int i = 0; i < 2; i++ ) {
						if ( lightLEDs ) { LEDs::glow(); }
						Piezo::on();
						Piezo::chirp( 1E6/6500, 1E6/3500, 1 );
						Piezo::chirp( 1E6/3500, 1E6/3900, 1 );
						Piezo::chirp( 1E6/3900, 1E6/3700, 1 );
						Piezo::off();
						if ( lightLEDs ) { LEDs::off(); }
						delay( i == 0 ? 200 : 170 );
					}
					if ( lightLEDs ) { LEDs::glow(); }
					Piezo::on();
					Piezo::chirp( 1E6/6500, 1E6/5000, 1 );
					Piezo::chirp( 1E6/5000, 1E6/5300, 1 );
					Piezo::chirp( 1E6/5300, 1E6/3000, 2 );
					Piezo::chirp( 1E6/3000, 1E6/3400, 2 );
					Piezo::chirp( 1E6/3400, 1E6/3300, 1 );
					Piezo::chirp( 1E6/3300, 1E6/4400, 1 );
					Piezo::chirp( 1E6/4400, 1E6/4000, 1 );
					Piezo::off();
					if ( lightLEDs ) { LEDs::off(); }
					delay( 160 );
					for ( int i = 0; i < 2; i++ ) {
						if ( lightLEDs ) { LEDs::glow(); }
						Piezo::on();
						Piezo::chirp( 1E6/6400, 1E6/3500, 1 );
						Piezo::chirp( 1E6/3500, 1E6/3700, 2 );
						Piezo::chirp( 1E6/3700, 1E6/2900, 3 );
						Piezo::chirp( 1E6/2900, 1E6/3900, 3 );
						Piezo::tone( 1E6/3900, 1E6*0.02 );
						Piezo::off();
						if ( lightLEDs ) { LEDs::off(); }
						delay( i == 0 ? 200 : 150 );
					}
					if ( lightLEDs ) { LEDs::glow(); }
					Piezo::on();
					Piezo::chirp( 1E6/6200, 1E6/5200, 1 );
					Piezo::tone( 1E6/5250, 1E6*0.015 );
					Piezo::chirp( 1E6/5300, 1E6/3000, 2 );
					Piezo::chirp( 1E6/3000, 1E6/3300, 3 );
					Piezo::tone( 1E6/3300, 1E6*0.015 );
					Piezo::chirp( 1E6/3400, 1E6/4600, 3 );
					Piezo::chirp( 1E6/4600, 1E6/4000, 1 );
					Piezo::off();
					if ( lightLEDs ) { LEDs::off(); }
					delay( 190 );
					if ( lightLEDs ) { LEDs::glow(); }
					Piezo::on();
					Piezo::chirp( 1E6/6200, 1E6/5000, 1 );
					Piezo::chirp( 1E6/5000, 1E6/5300, 1 );
					Piezo::chirp( 1E6/5300, 1E6/3100, 2 );
					Piezo::chirp( 1E6/3100, 1E6/3400, 2 );
					Piezo::tone( 1E6/3400, 1E6*0.02 );
					Piezo::chirp( 1E6/3400, 1E6/4400, 2 );
					Piezo::chirp( 1E6/4400, 1E6/3800, 1 );
					Piezo::off();
					if ( lightLEDs ) { LEDs::off(); }
					delay( 200 );
					if ( lightLEDs ) { LEDs::glow(); }
					Piezo::on();
					Piezo::chirp( 1E6/6000, 1E6/4500, 1 );
					Piezo::chirp( 1E6/4500, 1E6/4700, 1 );
					Piezo::chirp( 1E6/4800, 1E6/3700, 1 );
					Piezo::off();
					if ( lightLEDs ) { LEDs::off(); }
					delay( 270 );
					for ( int i = 0; i < 2; i++ ) {
						if ( lightLEDs ) { LEDs::glow(); }
						Piezo::on();
						Piezo::chirp( 1E6/6100, 1E6/4300, 1 );
						Piezo::chirp( 1E6/4300, 1E6/4900, 1 );
						Piezo::tone( 1E6/4900, 1E6*0.015 );
						Piezo::chirp( 1E6/4900, 1E6/3700, 1 );
						Piezo::off();
						if ( lightLEDs ) { LEDs::off(); }
						delay( i == 0 ? 220 : 200 );
					}
					if ( lightLEDs ) { LEDs::glow(); }
					Piezo::on();
					Piezo::chirp( 1E6/6000, 1E6/5200, 1 );
					Piezo::chirp( 1E6/5200, 1E6/5300, 1 );
					Piezo::chirp( 1E6/5300, 1E6/3100, 2 );
					Piezo::chirp( 1E6/3100, 1E6/3300, 2 );
					Piezo::tone( 1E6/3350, 1E6*0.02 );
					Piezo::chirp( 1E6/3400, 1E6/4700, 2 );
					Piezo::chirp( 1E6/4700, 1E6/4100, 1 );
					Piezo::off();
					if ( lightLEDs ) { LEDs::off(); }
					break;

				case 1:
					for ( int i = 0; i < 2; i++ ) {
						if ( lightLEDs ) { LEDs::glow(); }
						Piezo::on();
						Piezo::chirp( 1E6/6200, 1E6/3500, 1 );
						Piezo::chirp( 1E6/3500, 1E6/3800, 1 );
						Piezo::chirp( 1E6/3800, 1E6/3700, 1 );
						Piezo::off();
						if ( lightLEDs ) { LEDs::off(); }
						delay( 200 );
					}
					for ( int i = 0; i < 4; i++ ) {
						if ( lightLEDs ) { LEDs::glow(); }
						Piezo::on();
						Piezo::chirp( 1E6/6200, 1E6/3400, 2 );
						Piezo::chirp( 1E6/3400, 1E6/3700, 1 );
						Piezo::tone( 1E6/3700, 1E6*0.015 );
						Piezo::chirp( 1E6/3700, 1E6/2800, 3 );
						Piezo::chirp( 1E6/2800, 1E6/3900, 4 );
						Piezo::tone( 1E6/3900, 1E6*0.01 );
						Piezo::off();
						if ( lightLEDs ) { LEDs::off(); }
						delay( 220 );
					}
					for ( int i = 0; i < 3; i++ ) {
						if ( lightLEDs ) { LEDs::glow(); }
						Piezo::on();
						Piezo::chirp( 1E6/6200, 1E6/5000, 1 );
						Piezo::tone( 1E6/5000, 1E6*0.01 );
						Piezo::chirp( 1E6/5000, 1E6/5200, 1 );
						Piezo::chirp( 1E6/5200, 1E6/3100, 2 );
						Piezo::chirp( 1E6/3100, 1E6/3400, 1 );
						Piezo::tone( 1E6/3400, 1E6*0.015 );
						Piezo::chirp( 1E6/3400, 1E6/4600, 3 );
						Piezo::chirp( 1E6/4600, 1E6/4100, 1 );
						Piezo::off();
						if ( lightLEDs ) { LEDs::off(); }
						delay( i < 2 ? 240 : 0 );
					}
			}
		}

		void static play( bool lightLEDs=false )
		{
			// initialize with an index that does not exist, see following if
			static int melodyStartIndex = -1;

			// get new start index that is different from last one
			melodyStartIndex = ( melodyStartIndex + random( 1, numMelodies-1+1 ) ) % numMelodies;

			// play a single long melody
			playSingleMelody( melodyStartIndex, lightLEDs );
		}
};
