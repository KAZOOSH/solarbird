// nick@bitfasching.de, Kazoosh, 2021
// Original bird voice: https://www.nabu.de/downloads/vogelportraets/Zaunkoenig_Gesang_NABU_Lars_Lachmann.mp3

class Wren
{
	public:

		Wren() {}

		static const unsigned char numMelodies = 4;

		void static playSingleMelody( unsigned char melodySelector, bool lightLEDs=false )
		{
			if ( lightLEDs ) { LEDs::glow(); }

			switch ( melodySelector )
			{
				case 0:
					Piezo::on();
					Piezo::chirp( 1E6/6700, 1E6/7200, 1, 20 );
					Piezo::chirp( 1E6/7200, 1E6/6700, 1, 60 );
					Piezo::chirp( 1E6/6700, 1E6/6400, 1, 20 );
					Piezo::off();
					delay( 50 );
					Piezo::on();
					Piezo::chirp( 1E6/6400, 1E6/6900, 1, 20 );
					Piezo::chirp( 1E6/6900, 1E6/6400, 1, 60 );
					Piezo::chirp( 1E6/6400, 1E6/6100, 1, 20 );
					Piezo::off();
					delay( 65 );
					Piezo::on();
					Piezo::tone( 1E6/4500, 1E6*0.070 );
					Piezo::off();
					delay( 40 );
					Piezo::chirp( 1E6/5100, 1E6/5300, 1 );
					for ( int i = 0; i < 5; i++ ) {
						Piezo::on();
						Piezo::chirp( 1E6/5300, 1E6/4300, 1, 4 );
						Piezo::off();
						delay( 55 );
					}
					Piezo::on();
					Piezo::chirp( 1E6/7600, 1E6/5800, 1, 20 );
					Piezo::chirp( 1E6/5800, 1E6/7600, 1, 20 );
					Piezo::chirp( 1E6/7600, 1E6/6700, 1, 20 );
					Piezo::off();
					delay( 40 );
					Piezo::on();
					Piezo::chirp( 1E6/4600, 1E6/3300, 1, 4 );
					Piezo::off();
					for ( int i = 0; i < 8; i++ ) {
						Piezo::on();
						Piezo::tone( 1E6/10000, 1E6*0.005 );
						Piezo::off();
						delay( 30 );
					}
					Piezo::on();
					Piezo::chirp( 1E6/5700, 1E6/6700, 1, 6 );
					Piezo::chirp( 1E6/6700, 1E6/5700, 1, 6 );
					Piezo::off();
					delay( 40 );
					Piezo::on();
					Piezo::chirp( 1E6/3100, 1E6/3400, 1, 8 );
					Piezo::chirp( 1E6/3400, 1E6/3700, 1, 16 );
					Piezo::off();
					delay( 60 );
					break;

				case 1:
					Piezo::on();
					Piezo::chirp( 1E6/8800, 1E6/8400, 1, 100 );
					Piezo::tone( 1E6/8400, 1E6*0.065 );
					Piezo::tone( 1E6/8300, 1E6*0.040 );
					Piezo::chirp( 1E6/8300, 1E6/8000, 1, 200 );
					Piezo::off();
					delay( 55 );
					Piezo::on();
					Piezo::chirp( 1E6/6000, 1E6/3600, 1, 5 );
					Piezo::off();
					delay( 45 );
					Piezo::on();
					Piezo::chirp( 1E6/5800, 1E6/6400, 1, 7 );
					Piezo::chirp( 1E6/6400, 1E6/5700, 1, 10 );
					Piezo::off();
					delay( 45 );
					for ( int i = 0; i < 5; i++ ) {
						Piezo::on();
						Piezo::chirp( 1E6/4900, 1E6/4700, 1, 8 );
						Piezo::tone( 1E6/4700, 1E6*0.010 );
						Piezo::chirp( 1E6/4700, 1E6/5000, 1, 8 );
						Piezo::off();
						delay( 50 );
					}
					Piezo::on();
					Piezo::chirp( 1E6/3300, 1E6/2300, 1, 2 );
					Piezo::off();
					delay( 50 );
					Piezo::on();
					Piezo::chirp( 1E6/6700, 1E6/7300, 1, 8 );
					Piezo::chirp( 1E6/7400, 1E6/7000, 1, 80 );
					Piezo::off();
					delay( 100 );
					break;

				case 2:
					for ( int i = 0; i < 2; i++ ) {
						Piezo::on();
						Piezo::chirp( 1E6/4000, 1E6/5300, 2, 3 );
						Piezo::tone( 1E6/5300, 1E6*0.030 );
						Piezo::chirp( 1E6/5300, 1E6/4000, 2, 3 );
						Piezo::off();
						delay( 80 );
					}
					Piezo::on();
					Piezo::chirp( 1E6/3300, 1E6/5000, 2, 3 );
					Piezo::tone( 1E6/5000, 1E6*0.030 );
					Piezo::chirp( 1E6/5000, 1E6/3300, 2, 3 );
					Piezo::off();
					delay( 80 );
					for ( int i = 0; i < 2; i++ ) {
						Piezo::on();
						Piezo::chirp( 1E6/3000, 1E6/4500, 2, 2 );
						Piezo::tone( 1E6/4500, 1E6*0.030 );
						Piezo::chirp( 1E6/4500, 1E6/3000, 2, 2 );
						Piezo::off();
						delay( 80 );
					}
					Piezo::on();
					Piezo::chirp( 1E6/2900, 1E6/4300, 2, 2 );
					Piezo::tone( 1E6/4300, 1E6*0.025 );
					Piezo::chirp( 1E6/4300, 1E6/2900, 2, 2 );
					Piezo::off();
					delay( 40 );
					for ( int i = 0; i < 5; i++ ) {
						Piezo::on();
						Piezo::chirp( 1E6/3000, 1E6/3800, 2, 2 );
						Piezo::chirp( 1E6/3400, 1E6/2000, 3, 2 );
						Piezo::off();
						delay( 30 );
					}
					delay( 90-30 );
					Piezo::on();
					Piezo::chirp( 1E6/6600, 1E6/2200, 3, 3 );
					Piezo::chirp( 1E6/2200, 1E6/3400, 3, 3 );
					Piezo::chirp( 1E6/3400, 1E6/1900, 2, 3 );
					Piezo::off();
					delay( 100 );
					break;

				case 3:
					Piezo::on();
					Piezo::chirp( 1E6/4600, 1E6/3200, 1, 3 );
					Piezo::off();
					delay( 30 );
					Piezo::on();
					Piezo::tone( 1E6/5000, 1E6*0.060 );
					Piezo::off();
					delay( 15 );
					Piezo::on();
					Piezo::chirp( 1E6/3400, 1E6/2400, 2, 3 );
					Piezo::off();
					delay( 25 );
					Piezo::on();
					Piezo::chirp( 1E6/7000, 1E6/9000, 1, 6 );
					Piezo::tone( 1E6/8900, 1E6*0.035 );
					Piezo::chirp( 1E6/8900, 1E6/7100, 1, 7 );
					Piezo::off();
					for ( int i = 0; i < 3; i++ ) {
						Piezo::on();
						Piezo::chirp( 1E6/3500, 1E6/8100, 1, 8 );
						Piezo::chirp( 1E6/8100, 1E6/7000, 1, 9 );
						Piezo::off();
						delay( 60 );
					}
					Piezo::on();
					Piezo::chirp( 1E6/3400, 1E6/2400, 2, 3 );
					Piezo::off();
					delay( 30 );
					Piezo::on();
					Piezo::chirp( 1E6/5200, 1E6/5500, 1, 20 );
					Piezo::chirp( 1E6/5500, 1E6/3600, 1, 6 );
					Piezo::off();
					break;
			}

			if ( lightLEDs ) { LEDs::off(); }
		}

		void static play( bool lightLEDs=false )
		{
			// initialize with an index that does not exist
			static int melodyStartIndex = -1;

			// get new start index that is different from last one
			melodyStartIndex = ( melodyStartIndex + random( 1, numMelodies-1+1 ) ) % numMelodies;

			// play 1-2 consecutive melodies
			int count = random( 1, 2+1 );
			for ( int i = 0; i < count; i++ ) {
				playSingleMelody( (melodyStartIndex+i) % numMelodies, lightLEDs );
			}
		}
};
