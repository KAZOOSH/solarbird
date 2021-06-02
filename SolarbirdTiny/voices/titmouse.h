// nick@bitfasching.de, Kazoosh, 2021
// Original bird voice: https://www.nabu.de/downloads/vogelportraets/Kohlmeise_Gesang_NABU_Lars_Lachmann.mp3

class Titmouse
{
	public:

		Titmouse() {}

		static const unsigned char numMelodies = 2;

		void static playSingleMelody( unsigned char melodySelector, bool lightLEDs=false )
		{
			if ( lightLEDs ) { LEDs::glow(); }
			Piezo::on();

			switch ( melodySelector )
			{
				case 0:
					Piezo::chirp( 1E6/4000, 1E6/4700, 2 );
					Piezo::chirp( 1E6/4700, 1E6/4600, 1 );
					Piezo::tone( 1E6/4600, 1E6*0.08 );
					break;

				case 1:
					Piezo::chirp( 1E6/3200, 1E6/3100, 1 );
					Piezo::tone( 1E6/3100, 1E6*0.08 );
					break;
			}

			Piezo::off();
			if ( lightLEDs ) { LEDs::off(); }
		}

		void static play( bool lightLEDs=false )
		{
			// melody pattern is always the same, only count and end is different
			int count = random( 4, 15+1 );
			for ( int i = 0; i < count; i++ ) {
				playSingleMelody( i % numMelodies, lightLEDs );
				delay( 130 );
			}
		}
};
