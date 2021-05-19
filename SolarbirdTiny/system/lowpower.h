// nick@bitfasching.de, Kazoosh, 2021

#include <avr/sleep.h> // low power sleep

class LowPower
{
	public:

		void static sleepSecond()
		{
			// initialize watchdog timer to wake up after one second
			// 8.5.2 (page 45) in datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
			WDTCR |= ( (1<<WDIE) | (1<<WDP2) | (1<<WDP1) );
			WDTCR &= ~(1<<WDE);
			interrupts();

			// set and enter deep sleep mode
			set_sleep_mode( SLEEP_MODE_PWR_DOWN );
			sleep_mode();

			// (watchdog timer wakes up controller)

			// disable watchdog timer
			noInterrupts();
			WDTCR |= ( (1<<WDCE) | (1<<WDE) );
			WDTCR = 0x00;
			interrupts();
		}

		void static sleepSeconds( int seconds )
		{
			while( seconds > 0 )
			{
				sleepSecond();
				seconds--;
			}
		}

		void static powerDown()
		{
			// set and enter deep sleep mode, will only wake up on external reset
			noInterrupts();
			set_sleep_mode( SLEEP_MODE_PWR_DOWN );
			sleep_mode();
		}
};

// dummy interrupt service routine for watchdog timer
// (would reset otherwise)
ISR( WDT_vect )
{
	// do literally nothing
	_NOP();
}
