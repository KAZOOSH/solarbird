/*
 * T45PiezoTest.c
 * Created: 23.03.2021 20:25:44
 * Author : 25mmHg
 * Fuses: lfuse=c2, hfuse=DF, efuse=FF
 *
 *    .--------------------------------------------.
 *    |       _______                              |
 *    |      | YX8051| Q1                          |
 *    |      | _ _ _ |                             |
 *    |     1 o o o o 4                            |
 *    |       | | | |                              |
 *    '-------' | | |  D1                          |
 *    .---------' | |  BAT43                       |
 *    |    ___    | |                              |
 *    o----UUU----)-o--->|--o------o-------o-------)---------------o-----o--------------o--------.
 *    |           |         |R1    |R2     |R3     |               |     |              |        |
 *    |    L1     |        .-.    .-.     .-.      |               |     |      PIEZO   |        |
 *    |    47uH   |        | |    | |     | |      |               |     |        _     |        |    R5
 *    |           |        | |    | |     | |      |          C1   |     |       | |    |   Q2   |    120   GN
 *    |           |      3M'-'  1M'-' 220k'-'      |          220u | +   |    .-|| ||-. |ATtiny85|    ___   LED
 *    |           |         |      |       o-------o              ###   ---   |  |_|  | | 1 __ 8 | .-|___|-->|-----.
 *    |           |         |   ||-o--. ||-+       |              ---   ---   |       | '-o|  |o-' |               |
 *    |   |       |         |   ||<-  | ||<-       V               | 100n|    |       '---o|  |o---'               |
 *    '---| |-----o         o---||-+  '-||-+       -               | C2  |    |       .---o|  |o-------------------o
 *     +  |   -   |         |2N7000| BS170 |       |               |     |    |       | .-o|__|o---.               |
 *                |      R4.-.  T1 |   T2  |       V SOLARZELLE    |     |    |  ___  | |          |  ___          |
 *       Ni-MH    |        | |     |       |       -               |     |    '-|___|-' |          '-|___|-->|-----'
 *       1,25V    |        | |     |       |       |               |     |              |                   GN
 *                |      1M'-'     |       |       V               |     |       R7     |             R6    LED
 *                |         |      |       |       -               |     |       120    |             120
 *                |         |      |       |       |               |     |              |
 *               ---       ---    ---     ---     ---             ---   ---            ---
 *
 * (created by AACircuit v1.28.7 beta 10/23/16 www.tech-chat.de)
 *
 * Mit dem Spannungsteiler R1/R4 wird die Betriebsspannung des ATtiny85 abgegriffen und geviertelt dem Gate von T1 zugeführt.
 * T1 öffnet bei ca. 1V Gatespannung. Dadurch sperrt T2 und via R3 fließt auch bei abgedunkelter Solarzelle ein Strom in Pin 1 von Q1.
 * Dies hat ein Abschalten des Aufwärtswandlers Q1 zur Folge. Die Betriebsspannung des ATtiny85 kann nicht weiter als bis auf 4V
 * ansteigen. Sinkt die Betriebsspannung sperrt T1, damit leitet T2 und dieser verbindet Pin 1 von Q1 mit GND. Dadurch startet der
 * Aufwärtswandler und die Betriebsspannung von Q2 wird somit auf ca. 4V konstant gehalten. Dies erfolgt weitgehend unabhämgig vom Strom-
 * bedarf des  Mikrocontrollers. (6uA bis 40mA). 
 * Aufgrund der sparsamen Reglung ist ein mehrtägiger Betrieb mit einer Akkuladung möglich.
 * C1 und C2 Puffern die Betriebsspannung. R5 bis R7 dienen der Strombegrenzung der Ports.
 * Der Piezosignalgeber wird von einer H-Schaltung mit Vpp=8V angetrieben und ist deshalb recht laut.
 * Ladebetrieb ist jeder Zeit möglich (wenn T2 leitet, wird das Laden vorübergehend ausgesetzt).
 * Der Mikrocontroller wird sowohl im Hellen als auch im Dunkeln mit der Energie des Akkus betrieben.
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

//Variable delay in 10us steps
void var_delay_10us(uint8_t ten_us)
{
	for (uint8_t i=0; i<ten_us; i++) _delay_us(10);
}

//Pieps
void piepsen(uint16_t n, uint16_t t)
{
	PIEPPORT |= 1<<PIEPA; //HIGH
	PIEPPORT &= ~(1<<PIEPB); //LOW
	while(n)
	{
		n--;
		PIEPPIN = (1<<PIEPB | 1<<PIEPA);//TOGGELN
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
	PIEPDDR |= 1<<PIEPA;//OUTPUT
	PIEPDDR |= 1<<PIEPB;//OUTPUT
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	init_wdt();//WECKEN DUCH WATCHDOGTIMER VORBEREITET
		
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