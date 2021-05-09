// nick@bitfasching.de, Kazoosh, 2021

class Piezo
{
	public:

		Piezo() {}

		void static on()
		{
			// make pins outputs
			bitWrite( DDRB, PIN_PIEZO_A, 1 );
			bitWrite( DDRB, PIN_PIEZO_B, 1 );

			// drive A low and B high (for later toggling with differential output)
			bitWrite( PORTB, PIN_PIEZO_A, 0 );
			bitWrite( PORTB, PIN_PIEZO_B, 1 );
		}

		void static off()
		{
			// drive A and B low (same potential yields zero differential output)
			bitWrite( PORTB, PIN_PIEZO_A, 0 );
			bitWrite( PORTB, PIN_PIEZO_B, 0 );
		}

		void static inline toggle()
		{
			// invert A and B
			bitWrite( PORTB, PIN_PIEZO_A, !bitRead( PORTB, PIN_PIEZO_A ) );
			bitWrite( PORTB, PIN_PIEZO_B, !bitRead( PORTB, PIN_PIEZO_B ) );
		}

		void static tone( unsigned long tonePeriod, unsigned long durationMicros )
		{
			unsigned long startMicros = micros();

			while ( micros()-startMicros < durationMicros )
			{
				Piezo::toggle();
				delayMicroseconds( tonePeriod/2 );
			}
		}

		void static chirp( unsigned long tonePeriodStart, unsigned long tonePeriodEnd, unsigned long tonePeriodQuarterStep )
		{
			unsigned long tonePeriod = tonePeriodStart;
			unsigned char halfCycle = 0;

			// up
			if ( tonePeriodStart > tonePeriodEnd )
			{
				while ( tonePeriod > tonePeriodEnd )
				{
					halfCycle++;
					Piezo::toggle();
					delayMicroseconds( tonePeriod/2 );
					if ( halfCycle % 4 == 0 ) {
						tonePeriod -= tonePeriodQuarterStep;
					}
				}
			}
			// down
			else
			{
				while ( tonePeriod < tonePeriodEnd )
				{
					halfCycle++;
					Piezo::toggle();
					delayMicroseconds( tonePeriod/2 );
					if ( halfCycle % 4 == 0 ) {
						tonePeriod += tonePeriodQuarterStep;
					}
				}
			}
		}
};
