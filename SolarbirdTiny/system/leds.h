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

		unsigned long static senseBrightness( const unsigned long dischargeTimeWindowMillis=300UL )
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

			// change anodes to inputs (start discharging towards potential of cathodes)
			bitWrite( DDRB, PIN_LED_1_ANODE, 0 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 0 );

			// count time until potential of anodes is high
			unsigned long dischargeStartMillis = millis();
			unsigned long dischargeMillis = 0;
			bool dischargedInTime = false;
			while ( dischargeMillis <= dischargeTimeWindowMillis ) {
				dischargeMillis = millis()-dischargeStartMillis;
				if ( bitRead( PINB, PIN_LED_1_ANODE ) || bitRead( PINB, PIN_LED_2_ANODE ) ) {
					dischargedInTime = true;
					break;
				}
			}
			if ( !dischargedInTime ) {
				dischargeMillis = dischargeTimeWindowMillis;
			}

			// restore LED state
			off();

			// discharge time is inverse proportional to brightness
			return dischargeTimeWindowMillis - dischargeMillis;
		}
};
