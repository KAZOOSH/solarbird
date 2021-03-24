/*
 * T45PiezoTest.c
 * Created: 23.03.2021 20:25:44
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
 *    .---------' | |  BAT43                       |
 *    |    ___    | |                              |
 *    o----UUU----)-o--->|--o------o-------o-------)---------------o-----o--------------o--------.
 *    |           |         |      |       |       |               |     |              |        |
 *    |    47u    |        .-.    .-.     .-.      |               |     |      PIEZO   |        |
 *    |           |        | |    | |     | |      |               |     |        _     |        |
 *    |           |        | |    | |     | |      |               |     |       | |    |        |    100   GN
 *    |           |      3M'-'  1M'-' 220k'-'      |          100u | +   |    .-|| ||-. |ATtiny85|    ___   LED
 *    |           |         |      |       o-------o              ###   ---   |  |_|  | | 1 __ 8 | .-|___|-->|-----.
 *    |           |         |   ||-o--. ||-+       |              ---   ---   |       | '-o|  |o-' |               |
 *    |   |       |         |   ||<-  | ||<-       V               | 100n|    |       '---o|  |o---'               |
 *    '---| |-----o         o---||-+  '-||-+       -               |     |    |       .---o|  |o-------------------o
 *     +  |   -   |         |2N7000| BS170 |       |               |     |    |       | .-o|__|o---.               |
 *                |        .-.     |       |       V SOLARZELLE    |     |    |  ___  | |          |  ___          |
 *       Ni-MH    |        | |     |       |       -               |     |    '-|___|-' |          '-|___|-->|-----'
 *       1,25V    |        | |     |       |       |               |     |              |                   GN
 *                |      1M'-'     |       |       V               |     |       100    |             100   LED
 *                |         |      |       |       -               |     |              |
 *                |         |      |       |       |               |     |              |
 *               ---       ---    ---     ---     ---             ---   ---            ---
 *
 * (created by AACircuit v1.28.7 beta 10/23/16 www.tech-chat.de)
 *
 */ 

#define F_CPU 8000000UL

#define PIEPA PB3
#define PIEPB PB4
#define PIEPDDR DDRB
#define PIEPPORT PORTB
#define PIEPPIN PINB

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t wdtcnt = 0;

//Variable delay
void var_delay_10us(uint8_t ten_us)
{
	for (uint8_t i=0; i<ten_us; i++) _delay_us(10);
}

//Pieps
void piepsen(uint16_t n, uint16_t t)
{
	PIEPPORT |= 1<<PIEPA;
	PIEPPORT &= ~(1<<PIEPB);
	while(n)
	{
		n--;
		PIEPPIN = (1<<PIEPB | 1<<PIEPA);
		var_delay_10us(t);
	}
}


//WDT-Interrupt-init
//START 8s TIMER, CURRENT DRAW 6uA
void init_wdt()
{
	cli();
	MCUSR &= ~(1<<WDRF);
	WDTCR |= (1<<WDIE) | (1<<WDP3) | (1<<WDP0) ;
	wdt_reset();
	sei();
}


//WDT-Interrupt
//WAKEUP
ISR(WDT_vect)
{
	wdtcnt++;
}

int main(void)
{
    //init
	PIEPDDR |= 1<<PIEPA;
	PIEPDDR |= 1<<PIEPB;
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	init_wdt();
		
	//Job
	sei();
	while (1) 
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
		// SLEEP CURRENT DRAW 6uA
		sleep_mode();
    }
}