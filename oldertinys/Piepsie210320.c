/*
 * Piepsie210320.c
 *
 * Created: 20.03.2021 10:58:47
 * Author : 25mmHg
 * Device : ATtiny13 / ATtiny2313A
 *
 *                                             _    
 *                              ||            | |   
 *     o---------o-----.  .-----||-----.  .--|| ||--.
 *               |     |  |     ||     |  |   |_|   |
 *               |     |  |100n        |  |         |
 *               |     |  |   1 __ 8   |  |  Piezo  |
 *               |     |  |  -o|  |o---o  |         |
 *              ---    '--)---o|  |o---)--'         |
 *              ---    .--)---o|  |o---)--.         |
 *         100n  |     |  o---o|__|o-  |  |         |
 *               |     |  |            |  |         |
 *               |     |  | ATttiny13  |  |         |
 *               |     |  |            |  |   100   |
 *               |     |  |      |     |  |   ___   |
 *     o---------o-----'  '-----||-----'  '--|___|--'
 *                           0V  |  3V               
 *                                                   
 *                            CR2032                 
 *
 *
 * (created by AACircuit v1.28.7 beta 10/23/16 www.tech-chat.de)
 *
 */ 

#define F_CPU 4800000UL

#define PIEPA PB1
#define PIEPB PB2
#define PIEPDDR DDRB
#define PIEPPORT PORTB
#define PIEPPIN PINB

#define DET5 PB3
#define DET0 PB4
#define DETDDR DDRB
#define DETPORT PORTB
#define DETPIN PINB

#define GLITCH 2
#define LOOPS 10
#define ERRORS 2

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Variable delay
void var_delay_10us(uint8_t ten_us)
{
	for (uint8_t i=0; i<ten_us; i++) _delay_us(10);
}

//Pieps
void piepsen(uint16_t n, uint8_t t)
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

//Pin-Change-Interrupt-Routine
ISR(PCINT0_vect)
{	
}

int main(void)
{
    //init
	PIEPDDR |= 1<<PIEPA;
	PIEPDDR |= 1<<PIEPB;
	
	DETDDR &= ~(1<<DET5);
	DETDDR |= 1<<DET0;
	DETPORT |= 1<<DET5;
	DETPORT &= ~(1<<DET0);
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	PCMSK |= 1<<PCINT3;
		
	//Job
	sei();
	while (1) 
    {
		GIMSK |= 1<<PCIE;				
		sleep_mode();		
		GIMSK &= ~(1<<PCIE);		
		uint8_t contact = 0;
		for (uint8_t i=0; i < LOOPS; i++)
		{
			_delay_us(GLITCH);
			contact += (DETPIN & (1<<DET5));
		}
		if(contact <= ERRORS) piepsen(500, 10);
		if(contact >= (LOOPS - ERRORS)) piepsen(250, 20); 
    }
}

