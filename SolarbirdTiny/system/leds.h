// nick@bitfasching.de, Kazoosh, 2021

class LEDs
{
	public:

		LEDs() {}

		void static on()
		{
			// make pins outputs
			bitWrite( DDRB, PIN_LED_1_ANODE, 1 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 1 );
			bitWrite( DDRB, PIN_LED_CATHODES, 1 );

			// drive cathodes low and anodes high
			bitWrite( PORTB, PIN_LED_CATHODES, 0 );
			bitWrite( PORTB, PIN_LED_1_ANODE, 1 );
			bitWrite( PORTB, PIN_LED_2_ANODE, 1 );
		}

		// low current, use pullup as additional LED series resistor
		void static glow()
		{
			// make anodes pins inputs (writing to PORTB will only enable internal pullup)
			bitWrite( DDRB, PIN_LED_1_ANODE, 0 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 0 );

			// make cathodes pin output
			bitWrite( DDRB, PIN_LED_CATHODES, 1 );

			// drive cathodes low and anodes high
			bitWrite( PORTB, PIN_LED_CATHODES, 0 );
			bitWrite( PORTB, PIN_LED_1_ANODE, 1 );
			bitWrite( PORTB, PIN_LED_2_ANODE, 1 );
		}

		void static off()
		{
			// drive all pins low = LEDs off
			bitWrite( PORTB, PIN_LED_CATHODES, 0 );
			bitWrite( PORTB, PIN_LED_1_ANODE, 0 );
			bitWrite( PORTB, PIN_LED_2_ANODE, 0 );

			// make pins inputs (disconnect)
			bitWrite( DDRB, PIN_LED_1_ANODE, 0 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 0 );
			bitWrite( DDRB, PIN_LED_CATHODES, 0 );
		}

		unsigned int static senseBrightness( const unsigned int dischargeTimeWindowCycles=65535U )
		{
			// make pins outputs
			bitWrite( DDRB, PIN_LED_1_ANODE, 1 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 1 );
			bitWrite( DDRB, PIN_LED_CATHODES, 1 );

			// drive cathodes high and anodes low (inverse charging)
			bitWrite( PORTB, PIN_LED_CATHODES, 1 );
			bitWrite( PORTB, PIN_LED_1_ANODE, 0 );
			bitWrite( PORTB, PIN_LED_2_ANODE, 0 );

			// wait to charge
			delay( 1 );

			// disable interrupts during measurement
			noInterrupts();

			// initialize counter to maximum
			unsigned int dischargeCycles = dischargeTimeWindowCycles;

			// change anodes to inputs (start discharging towards potential of cathodes)
			bitWrite( DDRB, PIN_LED_1_ANODE, 0 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 0 );

			// count cycles until potential of either of the anodes goes high
			// returns maximum brightness of the two LEDs
			while ( dischargeCycles > 0 ) {
				if ( bitRead( PINB, PIN_LED_1_ANODE ) || bitRead( PINB, PIN_LED_2_ANODE ) ) {
					break;
				}
				dischargeCycles--;
			}

			// re-enable interrupts
			interrupts();

			// restore LED state
			off();

			return dischargeCycles;
		}
};
