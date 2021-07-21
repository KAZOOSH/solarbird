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
			tonePeriod -= 24; // compensate for CPU cycles between toggles

			while ( micros()-startMicros < durationMicros )
			{
				Piezo::toggle();
				delayMicroseconds( tonePeriod/2 );
			}
		}

		void static chirp( unsigned long tonePeriodStart, unsigned long tonePeriodEnd, unsigned long tonePeriodStep, unsigned int tonePeriodStepInterval=4, bool disableInterrupts=true )
		{
			unsigned long tonePeriod = tonePeriodStart;
			unsigned int halfCycle = 0;

			if ( disableInterrupts ) { noInterrupts(); }

			// up
			if ( tonePeriodStart > tonePeriodEnd )
			{
				while ( tonePeriod > tonePeriodEnd )
				{
					halfCycle++;
					Piezo::toggle();
					delayMicroseconds( tonePeriod/2 );
					if ( halfCycle == tonePeriodStepInterval ) {
						tonePeriod -= tonePeriodStep;
						halfCycle = 0;
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
					if ( halfCycle == tonePeriodStepInterval ) {
						tonePeriod += tonePeriodStep;
						halfCycle = 0;
					}
				}
			}

			if ( disableInterrupts ) { interrupts(); }
		}
};
