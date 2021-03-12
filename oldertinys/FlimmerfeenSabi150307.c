/*
 * flimmerfeen_final140622.c
 * Powerconsumtion 5...7uA in powerdown, 20mA peak (lifespan more then 3 months with Coincell CR2032)
 * Created: 16.06.2014 00:03
 * state: working
 * Todo: make a debug interface for ADC in testLEDs
 * Todo: make a startup sequence with stabile voltages on LDRPWR_PIN and LDR_PIN ------------------- done
 * Author: 25mmHg, Mischbeck (compute the average values)
 * Circuit: 25mmHg
 * Population: 9+2(unborn)
 *
 *                                                68
 *       LED bl                                     ___    LED rt
 *   .----|<-------------------------------------o-|___|--->|-------.
 *   |                                           |                  |
 *   |   LED gn                                  |         LED gn   |
 *   o----|<-------------------------------------)-----o--->|-------o
 *   |           68                              |     |            |
 *   |   LED rt ___                              |     |   LED bl   |
 *   o----|<---|___|-----------------------------)-----)-o->|-------o
 *   |                                           |     | |          |
 *   |                                           '---. | |          |
 *  ===                  .-- Vcc = 3V                | | |          |
 *  GND                  |                           | | |          |
 *                       |                           | | |          |
 *   .----o--------------o------------------------.  | | |          |
 *   |    |              |                        |  | | |          |
 *   |    |              |                        |  | | |          |
 *   |    |              |   4k7   .-----------.  |  | | |          |
 *   |    |              |   ___   |           |  |  | | |          |
 *   |    |       .----. '--|___|--o RST   VCC o--'  | | |          |
 *   |    |       |    |           |           |     | | |          |
 *   |    |      .-.   '-----------o PB3   SCK o-----' | |          |
 *   |    |      | |LDR            |           |       | |          |
 *   |    |      | |   .-----------o PB4  MISO o-------' |          |
 *   |    |      '-'   |           |           |         |          |
 *   |    |       |    | .---------o GND  MOSI o---------'          |
 *   |    |       o----' |         |           |                    |
 *   |    |       |      |         '-----------'                    |
 *   |470u|100n  .-.     |           ATtiny13A                      |
 *   | +  |      | |LDR  |                                          |
 *  ###  ---     | |     |                                          |
 *  ---  ---     '-'     |                                          |
 *   |    |       |      |                                          |
 *  ===  ===     ===    ===                                        ===
 *  GND  GND     GND    GND                                        GND
 *
 *
 *(created by AACircuit v1.28.6 beta 04/19/05 www.tech-chat.de)
 *
 * Text:
 * Die Flimmerfeen
 * "Flimmerfeen sind eine erst kürzlich in der Dresdner Heide entdeckte frühe Form einer androiden Spezies.
 * Vorwiegend um die Zeit der Sommersonnenwende herum kann man sie in der Nähe des großen Sandbergs beobachten.
 * Am Tag verstecken sie sich oft in den Wipfeln der Bäume. Leichter aufzuspüren sind sie in der Nacht. Hier
 * verraten sie sich durch die schwachen Lichtblitze ihrer Kommunikationsorgane mit denen sie untereinander
 * Kontakt suchen. Manche behaupten, dass sie nur in der Lage sind, ihre Art zu erhalten, wenn es mehreren
 * von ihnen gelingt, einen synchronen Puls auszusenden. In den lauen Frühsommernächten ist das Klima dafür
 * am günstigsten. und die Flimmerfeen finden sich in größeren Gruppen zusammen" Installation 2014
 *
 *
 */ 
 

#define F_CPU 4800000UL
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define RB_PIN 2
#define GG_PIN 1
#define BR_PIN 0
#define LDRPWR_PIN 3
#define LDR_PIN 4

#define VALUESIZE 24 // not more then 29 is RAMsave
#define IGNOREBAND 2
#define DARKTHRESHOLD 850
#define CALIBRATIONTIME 30000
#define FOR_DARKNESS 0
#define FOR_DIFFERENCE 1
#define MAX_ADC 1023
#define ZERO_ADC 0

volatile uint8_t wdtcnt = 0;
volatile uint8_t dark = 0;
volatile uint8_t voltageDividerLastState =0;
volatile uint8_t voltageDividerChanging =0;

uint16_t lastValues[VALUESIZE];
uint8_t full = 0;

void blitz(uint8_t ontime, uint8_t ledled)
{
    PORTB &= ~(1<<ledled);      //LED on
    while(ontime)
    {
        _delay_ms(1);
        ontime--;
    }
    PORTB |=  (1<<ledled);      //LED off
}

void testLEDs()
{
    _delay_ms(500);
    for(uint8_t i = 0; i<3; i++)
    {
        for(uint8_t ii = i+2; ii > 0; ii--)
        {
            blitz(50, i);
            _delay_ms(250);
        } 
        _delay_ms(500);        
    }
}

void full_array()
{
	for(uint8_t i = 0; (i<12) && (full == 0); i++)
	{
		blitz(2, RB_PIN);
		_delay_ms(100);
		blitz(2, BR_PIN);
		_delay_ms(100);
	}
	full=1;
}


void disable_unused_modules() 
{
    cli();
	DDRB  |=  (1<<LDRPWR_PIN);          // LDRPWR output
	PORTB &= ~(1<<LDRPWR_PIN);          // LDRPWR off
    ADCSRA &= ~(1<<ADEN);				// disable ADC 
    DIDR0 = (1<<ADC2D) | (1<<ADC3D);	// turn off digital input buffer for analog used pins
    sei();
}

void goes_power_down_now()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();
    sleep_enable();                     // macro sets the SE-bit
    sei();
    sleep_cpu();                        // timed: sleep within 3 clock cycles
    sleep_disable();
}

void prepareLDR(uint8_t diff)           // prepare Photoresistors vor darkness or difference light
{
	// LDRPWR via pullup(40k) or direct on Vcc 
	cli();
	DDRB = diff ? (DDRB |(1<<LDRPWR_PIN)) : (DDRB & ~(1<<LDRPWR_PIN));
	PORTB |= (1<<LDRPWR_PIN);          // LDRPWR on
	_delay_ms(10);
	sei();	
}

uint16_t readADC(uint8_t smooth, uint8_t channel)
{
    cli();
    ADCSRA |= (1<<ADEN);				// ADC enable, need 200uA Power
    uint16_t temp = 0;
    uint8_t i = smooth;

    ADMUX  = (channel == 3) ? (1<<MUX1)|(1<<MUX0) : (1<<MUX1);  // PB3 or PB4 (tiny13A as input for ADC 
    ADCSRA |= (1<<ADSC);                // dummyconversion 25 ADC-clocks
    while(ADCSRA & (1<<ADSC));			// wait for finishing AD-conversion
   (void) ADCW;							// ADC-readout to void

    while(i)
    {
        i--;
        ADCSRA |= (1<<ADSC);			// start conversion
        while(ADCSRA&(1<<ADSC));		// waiting for end of conversion, duration 13ADC-clocks
        //low = ADCL;					// first reading (locking of ADCH)
        //high = ADCH;					// later get ADCH
        //temp += ((high<<8) | low); 
        temp += ADCW;					// summary 10bit ADC-readouts, ADCW is C-compiler 16-bit pseudo-register 
    }
    sei();    
    return temp / smooth;			    // return average ADC-readouts
}

uint16_t getArrAverage(uint8_t size)
{
	uint8_t i;
	uint16_t sum = 0;
	for (i=0 ;i < size; i++)
	{
		sum += lastValues[i];
	}
	return sum / size;
}
ISR(WDT_vect)                           // wakeup from sleeping
{
    cli();                              // no further interrupts
    if(wdtcnt < 0xFF) wdtcnt++; 
    else wdtcnt = 0;    
    WDTCR = (wdtcnt & 1) ? ((1<<WDP3)|(1<<WDE)|(1<<WDTIE)):((1<<WDP1)|(1<<WDP0)|(1<<WDE)|(1<<WDTIE)); // 4 or 0.015 seconds
    sei();							   // further interrupts possible
}

int main(void)
{   
    uint16_t actADC;
    uint8_t valueCounter = 0;
	
    ADCSRA |= (1<<ADPS0)|(1<<ADPS2);					// ADC prescaler = 32 (4M/32=125k), Voltage ref. Vcc 3V(is default)
    DDRB  |= ((1<<RB_PIN)|(1<<GG_PIN)|(1<<BR_PIN));		// All leds output
    DDRB  &= ~(1<<LDR_PIN);								// LDR voltage divider input
    PORTB |= ((1<<RB_PIN)|(1<<GG_PIN)|(1<<BR_PIN));		// All leds HIGH and off (MCU drives kathode)
	prepareLDR(FOR_DARKNESS);							// ready for calibration
	
	_delay_ms(CALIBRATIONTIME);							// for manual calibration of  DARKTRESHOLD value
    
    testLEDs();

    WDTCR = (1<<WDE)|(1<<WDTIE)|(1<<WDP3)| (1<<WDP0);	// Wdt enable, Wdt interrupt enable, 8s intro   
    sei();												// interrupts global enable


    while(1)
    {       
        if(!(wdtcnt & 1))                               // LDRs 4s darkness next interrupt in 15ms
    	{
    	    if(!(wdtcnt % 16) || (wdtcnt < 10))         // check darkness on the beginning and every 8 while-loops
    	    {
    	        prepareLDR(FOR_DARKNESS);
    	        dark = (readADC(8, LDRPWR_PIN) > DARKTHRESHOLD);
    	    }

    	    if(dark == 1)
    	    {
				prepareLDR(FOR_DIFFERENCE);
    	        actADC = readADC(8, LDR_PIN);
                uint16_t arrAvg = MAX_ADC >>1;
                
                if(valueCounter == VALUESIZE) full_array();
				valueCounter = valueCounter % VALUESIZE;    // loop inside array and override in the beginning again                

    	        if (!full)
                {
                    lastValues[valueCounter] = actADC;
                    valueCounter++;	                        // go to next place in array
                    arrAvg = getArrAverage(valueCounter);
                }    	        
  				
    	        // beware peaks from arrAvg! 
                // update arrAvg and lastValues[] only if actADC is inside passband
                // 3/4 (arrAvg to ZERO_ADC) to arrAvg + 1/4 (arrAvg to MAX_ADC)
                else if ((actADC <= arrAvg + ((MAX_ADC - arrAvg) >>2)) || (actADC >= arrAvg - ((arrAvg - ZERO_ADC) >>2)))
                {
                    lastValues[valueCounter] = actADC;
                    valueCounter++;
                    arrAvg = getArrAverage(VALUESIZE);
                }


                if(actADC > arrAvg + IGNOREBAND) 			// compare actADC with arrAvg
    	        {
    	            voltageDividerChanging = (voltageDividerLastState == 1) ? 0 : 1; 
    	            voltageDividerLastState =1;
    	        }
				
    	        else if (actADC < arrAvg - IGNOREBAND)		// compare actADC with arrAvg
    	        {
    	            voltageDividerChanging = (voltageDividerLastState == 0) ? 0 : 1; 
    	            voltageDividerLastState =0;
    	        }
				else voltageDividerChanging = 0;
    	    }
    	} 

        if((wdtcnt > 2 && wdtcnt < 20) || dark == 1)
        {
            if (voltageDividerChanging == 0)
            {
                blitz(2, GG_PIN);
            }
        
            else if (voltageDividerLastState == 1)
            {
                blitz(20, RB_PIN);
            }
        
            else
            {
                blitz(20, BR_PIN);
            }
        } 
        disable_unused_modules();        
        goes_power_down_now();                          // powerdown 5...7uA, no clocks, we are sleeping not long (we have interrupts)
    }
}
