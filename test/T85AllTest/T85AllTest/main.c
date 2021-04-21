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
#define MAXDARKNESS 10000UL

#define PIEPA PB3
#define PIEPB PB4
#define LEDANODE1 PB0
#define LEDANODE2 PB1
#define LEDKATHODES PB2
#define MYDDR DDRB
#define MYPORT PORTB
#define MYPIN PINB

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
	MYPIN |= 1<<PIEPA;
	MYPORT &= ~(1<<PIEPB);
	while(n)
	{
		n--;
		MYPIN = (1<<PIEPB | 1<<PIEPA);
		var_delay_10us(t);
	}
}

 //Lichtmessen
uint16_t get_darkness()
{
	uint16_t darkness = 0;	
	//booth junctions invers charging
	MYPORT &= ~(1<<LEDANODE1 | 1<<LEDANODE2);
	MYPORT |= 1<<LEDKATHODES;
	_delay_us(10);
	//discharge junctions to HIGH
	MYDDR &= ~(1<<LEDANODE1 | 1<<LEDANODE2);
	while(!(MYPIN & (1<<LEDANODE1 | 1<<LEDANODE2)) && (darkness < MAXDARKNESS))
	{
		darkness++;
		_delay_us(10);
	}
	MYPORT &= ~(1<<LEDKATHODES);
	MYDDR |= (1<<LEDANODE1 | 1<<LEDANODE2);
	return(darkness);
}

 //Flash
 void flash_leds(uint16_t ontime)
 {
	 MYPORT |= (1<<LEDANODE1 | 1<<LEDANODE2);
	 var_delay_10us(ontime);
	 MYPORT &= ~(1<<LEDANODE1 | 1<<LEDANODE2);
 }


//WDT-Interrupt-init
// START 8s TIMER, STROMVERBRAUCH 6 MIKROAMPRE
void init_wdt()
{
	cli();
	MCUSR &= ~(1<<WDRF);
	WDTCR |= (1<<WDIE) | (1<<WDP3) | (1<<WDP0) ;
	wdt_reset();
	sei();
}


//WDT-Interrupt
ISR(WDT_vect)  // wakeup from sleeping
{
	wdtcnt++;
}

int main(void)
{
    //init
	MYDDR |= 1<<PIEPA;
	MYDDR |= 1<<PIEPB;
	MYDDR |= 1<<LEDANODE1;
	MYDDR |= 1<<LEDANODE2;
	MYDDR |= 1<<LEDKATHODES;
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	init_wdt();
		
	//Job
	sei();
	while(1) 
    {
		if(wdtcnt & 1)
		{
			piepsen(1000, 5);
			piepsen(25, 200);
			piepsen(50, 500);
			piepsen(100, 50);
			piepsen(200, 25);
			piepsen(500, 10);
			piepsen(600, 8);
			piepsen(700, 7);
			piepsen(800, 6);
			piepsen(1000, 5);
		}
		
		else
		{
			piepsen(1000, 5);
			flash_leds(get_darkness());
			piepsen(500, 10);
		}
		sleep_mode();
	}
}