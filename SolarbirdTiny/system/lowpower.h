// nick@bitfasching.de, Kazoosh, 2021

#include <avr/sleep.h> // low power sleep

class LowPower
{
	public:

		void static sleepOneSecond()
		{
			// initialize watchdog timer to wake up after one second
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
};

// dummy interrupt service routine for watchdog timer
// (would reset otherwise)
ISR( WDT_vect )
{
	// do literally nothing
	_NOP();
}
