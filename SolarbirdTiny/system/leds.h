// nick@bitfasching.de, Kazoosh, 2021

class LEDs
{
	public:

		LEDs() {}
		
		void static glow() // low current
		{
			// use pullup as additional LED series resistor
			bitWrite( DDRB, PIN_LED_1_ANODE, 0 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 0 );
			
			// make pin output
			bitWrite( DDRB, PIN_LED_CATHODES, 1 );

			// drive cathodes low and anodes high
			bitWrite( PORTB, PIN_LED_CATHODES, 0 );
			bitWrite( PORTB, PIN_LED_1_ANODE, 1 );
			bitWrite( PORTB, PIN_LED_2_ANODE, 1 );
		}
		

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
};
