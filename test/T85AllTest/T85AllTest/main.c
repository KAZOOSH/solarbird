/*
 * T85AllTest.c
 *
 * Created: 21.04.2021 18:31:46
 * Author : 25mmHg
 * Fuses: lfuse=c2, hfuse=DF, efuse=FF
 *
 *    .--------------------------------------------.
 *    |       _______                              |
 *    |      | YX8051|                             |
 *    |      | _ _ _ |                             |
 *    |     1 o o o o 4                            |
 *    |       | | | |                              |
 *    '-------' | | |                              |
 *    .---------' | |  BAT48                       |
 *    |    ___    | |                              |
 *    o----UUU----)-o--->|--o------o-------o-------)---------------o-----o--------------o--------.
 *    |           |         |      |       |       |               |     |              |        |
 *    |    47u    |        .-.    .-.     .-.      |               |     |      PIEZO   |        |
 *    |           |        | |    | |     | |      |               |     |        _     |        |
 *    |           |        | |    | |     | |      |               |     |       | |    |        |  2x 200  2x GN LED
 *    |           |      1M'-'470k'-' 220k'-'      |          100u | +   |    .-|| ||-. |ATtiny85|
 *    |           |         |      |       o-------o              ###   ---   |  |_|  | | 1 __ 8 | .---------------.
 *    |           |         |   ||-o--. ||-+       |              ---   ---   |       | '-o|  |o-' |               |
 *    |   |       |         |   ||<-  | ||<-       V               | 100n|    |       '---o|  |o---'  ___          |
 *    '---| |-----o         o---||-+  '-||-+       -               |     |    |       .---o|  |o-----|___|-->|-----o
 *     +  |   -   |         |2N7000|ZVN4206|       |               |     |    |       | .-o|__|o---.               |
 *                |        .-.     |       |       V SOLARZELLE    |     |    |  ___  | |          |  ___          |
 *       Ni-MH    |        | |     |       |       -               |     |    '-|___|-' |          '-|___|-->|-----'
 *       1,25V    |        | |     |       |       |               |     |              |
 *                |    650k'-'     |       |       V               |     |       200    |
 *                |         |      |       |       -               |     |              |
 *                |         |      |       |       |               |     |              |
 *               ---       ---    ---     ---     ---             ---   ---            ---
 *
 * (created by AACircuit v1.28.7 beta 10/23/16 www.tech-chat.de)
 *
 */ 

#define F_CPU 8000000UL
#define MAXDARKNESS 20000UL

#define PIEPA PB3
#define PIEPB PB4
#define LEDANODE1 PB0
#define LEDANODE2 PB1
#define LEDKATHODES PB2
#define MYDDR DDRB
#define MYPORT PORTB
#define MYPIN PINB

//#define SET(x) |=  (x)
//#define CLR(x) &= ~(x)

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t wdtcnt = 0;

//Variable delay
void var_delay_10us(uint16_t ten_us)
{
	for (uint16_t i=0; i<ten_us; i++) _delay_us(10);
}

//Pieps
void piepsen(uint16_t n, uint16_t t)
{
	MYDDR  |=  ((1<<PIEPA) | (1<<PIEPB));
	MYPORT |=  (1<<PIEPA);
	MYPORT &= ~(1<<PIEPB);
	while(n)
	{
		n--;
		MYPIN |= ((1<<PIEPB) | (1<<PIEPA));
		var_delay_10us(t);
	}
	MYPORT &= ~((1<<PIEPA) | (1<<PIEPB));
	_delay_us(10);
	// PINSTATE: booth piezopins are GND
}

 //How dark is it
uint16_t get_darkness()
{
	uint16_t darkness = 0;
	//booth junctions invers charging
	MYDDR  |=  ((1<<LEDANODE1) | (1<<LEDANODE2) | (1<<LEDKATHODES));
	MYPORT &= ~((1<<LEDANODE1) | (1<<LEDANODE2));
	MYPORT |=  (1<<LEDKATHODES);
	_delay_us(10);
	//discharge junctions to HIGH
	MYDDR &= ~((1<<LEDANODE1 | 1<<LEDANODE2));
	while(!(MYPIN & ((1<<LEDANODE1) | (1<<LEDANODE2))) && (darkness < MAXDARKNESS))
	{
		darkness++;
		_delay_us(10);
	}
	MYPORT &= ~(1<<LEDKATHODES);
	MYPORT &= ~((1<<LEDANODE1) | (1<<LEDANODE2));
	MYDDR  |=  ((1<<LEDANODE1) | (1<<LEDANODE2) | (1<<LEDKATHODES));
	return(darkness);
	// PINSTATE: anodes are GND, kathodes are GND
}

 //Flash the LEDs
 void flash_leds(uint16_t ontime)
 {
	 MYDDR  |= ((1<<LEDANODE1) | (1<<LEDANODE2) | (1<<LEDKATHODES));
	 MYPORT &= ~(1<<LEDKATHODES);
	 MYPORT |= ((1<<LEDANODE1) | (1<<LEDANODE2));
	 var_delay_10us(ontime);
	 MYPORT &= ~((1<<LEDANODE1) | (1<<LEDANODE2));
	 // PINSTATE: anodes are GND, kathodes are GND
 }


// WDT-Interrupt-init
// START 8s TIMER, current is 6uA
void init_wdt()
{
	cli();
	MCUSR &= ~(1<<WDRF);
	WDTCR |= ((1<<WDIE) | (1<<WDP3) | (1<<WDP0)) ;
	wdt_reset();
	sei();
}


// WDT-Interrupt, w<keup from sleeping without RESET
ISR(WDT_vect)
{
	wdtcnt++;
}

int main(void)
{
    // init
	MYDDR |= ((1<<PIEPA) | (1<<PIEPB));
	MYDDR |= (1<<LEDKATHODES);
	
	// LOWLIGHT LEDs VIA PULLUP
	MYPORT |= (1<<LEDANODE1);
	MYPORT |= (1<<LEDANODE2);
	_delay_ms(1000);
	MYPORT &= ~(1<<LEDANODE1);
	MYPORT &= ~(1<<LEDANODE2);
	// PINSTATE: anodes are HiZ, kathodes and piezopins are GND
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	init_wdt();
		
	// Job	
	while(1) 
    {
		// Test Light Sensors
		if (wdtcnt == 1)
		{
			for (uint16_t i=0; i<1000; i++)
			{
				piepsen(10, (5+(get_darkness()>>3)));
			}			
		}
		
		// MAGIC!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		else if (wdtcnt & 2U)
		{
			// make 1s noise with LFSR
			MYDDR  |=  ((1<<PIEPA) | (1<<PIEPB));
			MYPORT |=  (1<<PIEPA);
			MYPORT &= ~(1<<PIEPB);
			uint16_t lfsr_state = 1;
			for (uint16_t i=0; i<44100; i++)
			{
				_delay_us(23);
				lfsr_state=(lfsr_state >> 1)^(-(lfsr_state & 1) & 0xB400u); // nach E.Galois
				if (lfsr_state & 1) MYPIN |= (1 << PIEPA) | (1 << PIEPB);
			}
			
			piepsen(250, 20);
			
			// make noise filtered with 2 LFSR (flanger)
			MYDDR  |=  ((1<<PIEPA) | (1<<PIEPB));
			MYPORT |=  (1<<PIEPA);
			MYPORT |=  (1<<PIEPB); // Differenz AB
			//MYPORT &= ~(1<<PIEPB); // Summe AB alternativ
			for (uint8_t i=0; i<4; i++)
			{
				uint16_t lfsr_stateA = 44257; // Startwert für A
				uint16_t lfsr_stateB = 38051; // Wert 100 Schritte vor A (B hat  hier 2,3ms Vorsprung vor A)
				for (uint16_t j=0; j<200; j++)
				{
					for (uint16_t k=0; k<1000; k++)
					{
						_delay_us(23);
						// nach E.Galois
						lfsr_stateA=(lfsr_stateA >> 1)^(-(lfsr_stateA & 1) & 0xB400U);
						// jedes 1000te Sample verpennen (Abstand A B variiert 2,3ms....0....2,3ms)
						if (k != 1) lfsr_stateB=(lfsr_stateB >> 1)^(-(lfsr_stateB & 1) & 0xB400U);
						// PowerMixer
						MYPIN |= ((lfsr_stateA & 1) << PIEPA) | ((lfsr_stateB & 1) << PIEPB);
					}
				}
			}
			MYPORT &= ~((1<<PIEPA) | (1<<PIEPB));
			// PINSTATE: booth piezopins are GND
		}
		// MAGIC END!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		else if(wdtcnt & 4U)
		{
			piepsen(1000, 5);
			piepsen(25, 200);
			piepsen(50, 100);
			piepsen(100, 50);
			piepsen(200, 25);
			piepsen(500, 10);
			piepsen(600, 8);
			piepsen(700, 7);
			piepsen(800, 6);
			piepsen(1000, 5);
		}
		
		else if (wdtcnt & 8U)
		{
			piepsen(600, 40);
			piepsen(800, 30);
			piepsen(600, 40);
			_delay_ms(240);
			piepsen(600, 40);
			piepsen(800, 30);
			
		}
		
		else if (wdtcnt & 16U)
		{
			piepsen(300, 40);
			flash_leds(get_darkness());
			piepsen(400, 30);
		}
		else;
		sei();
		sleep_mode();
		cli();
	}
}