// nick@bitfasching.de, Kazoosh, 2021

class LEDs
{
	public:

		LEDs() {}

		void static initOutput()
		{
			// make pins outputs
			bitWrite( DDRB, PIN_LED_1_ANODE, 1 );
			bitWrite( DDRB, PIN_LED_2_ANODE, 1 );
			bitWrite( DDRB, PIN_LED_CATHODES, 1 );
		}

		void static off()
		{
			// drive all pins low = LEDs off
			digitalWrite( PIN_LED_1_ANODE, LOW );
			digitalWrite( PIN_LED_2_ANODE, LOW );
			digitalWrite( PIN_LED_CATHODES, LOW );
		}
};
