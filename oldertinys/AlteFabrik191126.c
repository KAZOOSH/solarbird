/*
 * AlteFabrik191126
 * Version: 1.0
 * License: BSD 3-clause "New" or "Revised" license
 * Created: 26.11.2019 23:14:14
 * Author : 25mmHg
 * LFUSE : 0x75
 * HFUSE : 0xFF
 *
 *        .-- Vcc = 3V
 *        |
 *   .----o---------------------o--------------------.                     
 *   |    |                     |                    |                     
 *   |470u|100n                 |  .------##------.  |                     
 *   | +  |                     |  |      ##      |  |                     
 *  ###  ---                    '--o RST      VCC o--'                     
 *  ---  ---                       |              |     ___    LED_RED     
 *   |    |   serOut115200kBaud----o PB3   PB2SCK o----|___|---|>|-----.   
 *   |    |           ___          |              |    330uH + 6R      |   
 *   |    |       .--|___|---------o PB4  PB1MISO o--------------------'  
 *   |    |       |  330uH + 6R    |              |                        
 *   |    |       |             .--o GND  PB0MOSI o--.                   
 *   |    |       |             |  |              |  |                     
 *   |    |       |             |  '--------------'  |                     
 *  ===  ===      |            ===                   |                     
 *  GND  GND      |  LED_RED   GND    ATtiny13A      |                    
 *                '--|>|-----------------------------'                      
 *                                                                         
 */ 
 

#define F_CPU 4800000UL
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "BasicSerial3.h"

#define LEFT__A 4
#define LEFT__K 0
#define RIGHT_A 2
#define RIGHT_K 1

#define THRESHOLD 0x3E8 //1000
#define MAXXON_us 10
#define MINOFF_us 10
#define LOOPS_PER_MS 40
#define LOADTIME_us 60
#define FILTERSTART 0x3E8 //1000

volatile uint16_t wdtcnt = 0;
volatile uint16_t darkness = 0;
volatile uint16_t lefttime = 0;
volatile uint16_t righttime = 0;

void serOut(const char* str)
{
	while (*str) TxTimedByte(*str++ , TXDELAY);
}

void serOutHex(uint16_t data2hex)
{
	/*    CONVERT UNSIGNED INTEGER 2 HEX NUMBERS  AND SHOW  IT    */
	const uint16_t mask = 0xF;
	for(uint8_t i=0; i<4; i++)
	{
		uint8_t temp = (uint8_t)((data2hex >> (4*(3-i))) & mask);
		temp = (temp < 0xA ? temp+'0' : temp-0xA+'A');
		TxTimedByte(temp , TXDELAY);
	}
}

void flashLeft(uint8_t on_ms)
{
	DDRB  |=  (1<<LEFT__K)|(1<<LEFT__A); // Output
	int8_t temp = LOOPS_PER_MS;
	while(on_ms)
	{
		PORTB &= ~(1<<LEFT__K);
		PORTB |=  (1<<LEFT__A);          // LED on
		_delay_us(MAXXON_us);
		PORTB |=  (1<<LEFT__K);          // LED off
		_delay_us(MINOFF_us);
		if(temp > 0) temp--;
		else
		{
			temp = LOOPS_PER_MS;
			on_ms--;
		}
	}
	DDRB &= ~((1<<LEFT__K)|(1<<LEFT__A)); // InPU
}

void flashRight(uint8_t on_ms)
{
	DDRB  |=  (1<<RIGHT_K)|(1<<RIGHT_A); // Output
	int8_t temp = LOOPS_PER_MS;
	while(on_ms)
	{
		PORTB &= ~(1<<RIGHT_K);
		PORTB |=  (1<<RIGHT_A);          // LED on
		_delay_us(MAXXON_us);
		PORTB |=  (1<<RIGHT_K);          // LED off
		_delay_us(MINOFF_us);
		if(temp > 0) temp--;
		else
		{
			temp = LOOPS_PER_MS;
			on_ms--;
		}
	}
	DDRB &= ~((1<<RIGHT_K)|(1<<RIGHT_A)); // InPU
}

uint16_t disCharge()
{
	lefttime  = 0;
	righttime = 0;
	DDRB  |=  (1<<LEFT__K)|(1<<LEFT__A); // Output
	DDRB  |=  (1<<RIGHT_K)|(1<<RIGHT_A); // Output
	PORTB &= ~(1<<LEFT__A);              // A gnd
	PORTB &= ~(1<<RIGHT_A);              // A gnd
	PORTB |=  (1<<LEFT__K);              // K Vcc
	PORTB |=  (1<<RIGHT_K);              // K Vcc
	_delay_us(LOADTIME_us);              // load
	DDRB  &=  ~((1<<LEFT__K)|(1<<RIGHT_K)); // InPU
	PORTB &=  ~((1<<LEFT__K)|(1<<RIGHT_K)); // Input	
	while(PINB & ((1<<LEFT__K)|(1<<RIGHT_K)))
	{
		lefttime +=  (PINB & (1<<LEFT__K));
		righttime += (PINB & (1<<RIGHT_K));
		_delay_us(2);
	}
	return(lefttime > righttime ? righttime : lefttime);
}

void goes_power_down_now()
{
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	//cli();
	sleep_enable();                     // macro sets the SE-bit
	sei();
	sleep_cpu();                        // timed: sleep within 3 clock cycles
	sleep_disable();
}

uint16_t IIRfilter(uint8_t shiftsize, uint16_t data)
{
	static uint32_t filter;
	filter = filter ? ((filter << shiftsize) - filter + data) >> shiftsize : FILTERSTART; // simple hotstart
	return (uint16_t)filter;	
}

static inline void Initialize_WakeUpInterrupt()
{
	cli();
	wdt_reset();
	wdt_enable(WDTO_4S);
	MCUSR &= ~(1 << WDRF);								// make sure that i will be able to remove the system reset mode
	WDTCR |=  (1 << WDTIF)|(1 << WDTIE)|(1 << WDCE);	// set watchdog interrupt mode
	WDTCR &= ~(1 << WDE);								// clear watchdog system reset mode
}

ISR(WDT_vect)  // wakeup from sleeping
{
	wdtcnt++;
}

int main(void)
{
	serOut("\ninit\n");	
	while(1)
	{
		Initialize_WakeUpInterrupt();
		sei();
		goes_power_down_now();                   // powerdown 5...7uA, no clocks, we are sleeping not long (we have interrupts)
		cli();
		darkness = IIRfilter(3, disCharge());
		serOut("wdt=");
		serOutHex(wdtcnt);
		serOut("\tdarkness=");
		serOutHex(darkness);
		serOut("\tL=");
		serOutHex(lefttime);
		serOut("\tR=");
		serOutHex(righttime);
		serOut("\n");
		if(darkness > THRESHOLD)
		{			
			flashLeft(200);
			_delay_ms(64);
			flashRight(80);
		}
	}
}
