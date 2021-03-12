/*
 *   _               _       _           __ _  _  __ ___  ___   __  __           _      
 *  (_)             | |     | |         /_ | || |/_ |__ \|__ \ / / /_ |         | |     
 *   _ _ __ ___   __| |_   _| | ___ _   _| | || |_| |  ) |  ) / /_  | | __ _  __| | ___ 
 *  | | '_ ` _ \ / _` | | | | |/ _ \ | | | |__   _| | / /  / / '_ \ | |/ _` |/ _` |/ __|
 *  | | | | | | | (_| | |_| | |  __/ |_| | |  | | | |/ /_ / /| (_) || | (_| | (_| | (__ 
 *  |_|_| |_| |_|\__,_|\__,_|_|\___|\__,_|_|  |_| |_|____|____\___/ |_|\__,_|\__,_|\___|
 *                                                              ______                  
 *                                                             |______|      
 * imdueu141226_1adc.c
 * Created: 26.12.2014 17:21:15
 * Author: Johannes
 * Version: 1.1adc (status working, adc working)
 * Lizenz: one coffee two persons one dog
 * Hardware: ATtiny45
 * Fuses: lfuse=F3, hfuse=DF, efuse=FF
 *
 * EIN HUNDEHALSBAND    
 *                                                     |       ___
 *                      .--------------------------o---| |----|___|------.
 *                      |                          |   |                 |
 *                      |                          | 3.6V     3.6R       |
 *                      |    .----###----.         | LI-Cell  safety     |
 *      4*100R          '----o RST   VCC o---------o                     |
 *       ___   LED           |           |         |                     |
 *   .--|___|--|<--o------o--o ADC3  SCK o------.  |          4*100R     |
 *   |   ___   LED |      |  |           |      |  |     LED   ___       |
 *   o--|___|--|<--'   .--)--o ADC2 MISO o------)--)--o-->|---|___|------o
 *   |                 |  |  |           |      |  |  |  LED   ___       |
 *   o-----------------)--)--o GND  MOSI o -.   |  |  '-->|---|___|------o
 *   |                 |  |  '-----------'  |   |  |                     |
 *   |   ___   LED     |  |                 |   |  |     LED   ___       |
 *   o--|___|--|<------o  |    ATtiny45     |   |  |  .-->|---|___|------o
 *   |   ___   LED     |  |                 |   |  |  |  LED   ___       |
 *   o--|___|--|<------o  |                 '---)--)--o-->|---|___|------o
 *   |                 |  |                     |  |                     |
 *   |        ___      |  |                     |  |                     |
 *   |  .----|___|-----'  |         .-----------'  o-----.               |
 *   |  |     LDR         |         |              |     |               |
 *   |  '-----------------'       | o             ###   ###              |
 *   |                          |=|>              ---   ---   2*220uF    |
 *   |                            | o              |     |               |
 *   |                              |              |     |               |
 *   |                              |              |     |               |
 *   '------------------------------o--------------o-----o---------------'
 *
 */

#define F_CPU 6400000UL
//#define PICOPOWER uncomment if AVR can disable Brown-out by software during sleep 
// (else comment + disable BOD by fuse)

// Pins ATtiny 25,45,85 (13, 13A different INT0-Pin)
#define MOSI 0 //PB0                Pin5 ISP_input
#define MISO 1 //PB1 (t13 INT0)     Pin6 ISP_output
#define SCK 2  //PB2 INT0!          Pin7 ISP_input
#define ADC3 3 //PB3                Pin2 GPIO
#define ADC2 4 //PB4                Pin3 GPIO
//    !RESET   PB5(disabled)        Pin1 RESET
//    VCC                           Pin8
//    GND                           Pin4

//#define LEDS (1<<MISO)
#define LEDS ((1<<MOSI)|(1<<MISO)|(1<<ADC3)|(1<<ADC2))
#define TASTE (1<<SCK)
#define LEDS_ON   (PORTB |=  LEDS)
#define LEDS_OFF  (PORTB &= ~LEDS)
#define LEDS_TOGGLE (PINB |= LEDS)
#define TASTE_OFF   (PINB & TASTE)
#define TASTE_ON    (~TASTE_OFF)

// 12h EINSCHALTDAUER
#define ONCNTDOWN   (3600000UL*12)/(32*120)
// ALTERNATIV 1min EINSCHALTDAUER (TESTMODE)
//#define ONCNTDOWN (3600000UL/60)/(32*120) 

// Libs
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

// Global Variables
volatile uint8_t state=0;                           // STATUS HALSBAND: 0=OFF;1...0xFE=COUNTDOWN;0xFF=ON
volatile uint8_t wdtcnt=0;                          // ZÄHLER FÜR WECKZYKLEN
volatile uint32_t oncntdown = ONCNTDOWN;            // ZÄHLER FÜR EINSCHALTDAUER
uint8_t dark=0;                                     // WENNS DUNKEL IST, WIRDS 1

// Funktions
void init_adc()                         // VORBEREITUNG AD-WANDLUNG LICHTSENSOR
{
    ADCSRA |= (1<<ADPS0)|(1<<ADPS2);    // ADC prescaler = 32 (6,4M/32=200k), Voltage ref. Vcc 3V(is default)
}

void prepareLDR()                       // VORBEREITUNG LICHTMESSUNG
{
    // LDRPWR via pullup(40k) on Vcc 
    cli();
    DDRB  &= ~(1<<ADC2);                // LICHTSENSOR HOTPIN ALS EINGANG
    PORTB |=  (1<<ADC2);                // LICHTSENSOR MESSTROM AN
    //PORTB &= ~(1<<ADC3);              // LICHTSENSOR COLDPIN AN 0V SCHON ERLEDIGT
    _delay_ms(5);
    sei();  
}

void deactivateLDR()                    // ZUSTAND WIE VOR LICHTMESSUNG
{ 
    cli();
    DDRB  |=  (1<<ADC2);                // LICHTSENSORPIN WIEDER ALS AUSGANG
    PORTB &= ~(1<<ADC2);                // STROM AUS
    ADCSRA &= ~(1<<ADEN);               // AD-WANDLER AUS
    sei();  
}

uint16_t readADC(uint8_t smooth)
{
    cli();
    prepareLDR();
    ADCSRA |= (1<<ADEN);                // AD-WANDLER EINSCHALTEN STROMVERBRAUCH 200 MIKROAMPERE
    //ADMUX  = (1<<MUX1);               // ADC2 (PB4, Pin3) INPUT, Vcc as Reference
    ADMUX  = (1<<MUX2)|(1<<MUX1);       // ADC3 (PB3, Pin2) -EINGANG ADC2 (PB4, Pin3) +EINGANG Vcc IST REFERENZWERT
    ADCSRA |= (1<<ADSC);                // dummyconversion 25 ADC-clocks
    while(ADCSRA & (1<<ADSC));          // wait for finishing AD-conversion
   (void) ADCW;                         // ADC-readout to void

    uint16_t temp = 0;
    uint8_t i = smooth;
    while(i)
    {
        i--;
        ADCSRA |= (1<<ADSC);            // START AD-WANDLUNG
        while(ADCSRA&(1<<ADSC));        // waiting for end of conversion, duration 13ADC-clocks
        //low = ADCL;                   // first reading (locking of ADCH)
        //high = ADCH;                  // later get ADCH
        //temp += ((high<<8) | low); 
        temp += ADCW;                   // summary 10bit ADC-readouts, ADCW is C-compiler 16-bit pseudo-register 
    }
    deactivateLDR();
    sei();    
    return(temp / smooth);              // RÜCKGABE DES MITTELWERTS DER AD-WANDLUNGEN VON HELLIGKEITSMESSUNG
}

void goes_power_down_now()
{
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    #if defined (PICOPOWER)
    sleep_bod_disable(); // timed: disable brown-out during sleep (for ATtiny85 at Rev. C or newer) ***page35,149
    #endif
    sei();
    sleep_mode();
}

void init_ports()                               // TASTENSTROM AN, LEDPINS ALS AUSGANG
{
    DDRB  |=  LEDS;
    LEDS_OFF;
    PORTB |= TASTE;
}

void init_pininterrupts()                       // WECKEN DURCH TASTE MÖGLICH
{
    GIMSK  |=  (1<<INT0);
}

void no_pininterrupts()                         // WECKEN DURCH TASTE UNMÖGLICH
{
    GIMSK  &=  ~(1<<INT0);
}

void init_wdt(uint8_t wdtcrTimeBits) // START TIMER, STROMVERBRAUCH 6 MIKROAMPRE 
{
    cli();
    // clear WDT interrupt flag
    MCUSR &= ~(1<<WDRF);
    // allow changes, enable WDT not used on safety level1 (no WDTON-fuse programmed)
    // WDTCR = (1<<WDCE) | (1<<WDE);
    // WDT and WDT interrupt enable: set WDE, WDIE, delaytime to wakeup
    WDTCR = (1<<WDIE) | (1<<WDE) | wdtcrTimeBits;
    wdt_reset();
    sei();
}

void wdt_off()                       // STOP TIMER: WECKEN DURCH TIMER UNMÖGLICH STROMVERBRAUCH 0,1 MIKROAMPRE
{
    wdt_reset();
    // Clear WDR Flag in MCUSR
    MCUSR &= ~(1<<WDRF);
    // Write logical one to WDCE and WDE allow disable WDT in booth safety levels
    WDTCR |= (1<<WDCE) | (1<<WDE);
    // Turn off WDT
    WDTCR = 0;
}

void flashLEDS()                     // LEDS BLITZEN STROMVERBRAUCH MAXIMAL 80 MILLIAMPERE
{
    cli();
    if(state)
    {
        LEDS_ON;
        _delay_us(30);
        if((state == 0xFF) && dark)
        {
            if     (wdtcnt==30) _delay_ms(3);
            else if(wdtcnt==31) _delay_ms(10);
        }
        LEDS_OFF;
    }
    sei();
}

// Interupts
ISR(WDT_vect)                                   // DURCH TIMER GEWECKT
{
    cli();
    wdt_off();
    if(TASTE_OFF)
    {
        init_pininterrupts();
        if(state && oncntdown)                  // HALSBAND EIN
        {
            state=0xFF;
            init_wdt(WDTO_120MS);
            if(wdtcnt==31) oncntdown--; 
        }
        else                                    // HALSBAND AUS
        {
            oncntdown = ONCNTDOWN;
            state=0;
        }
    }
    else                                        // TASTE NOCH GEDRÜCKT, COUNTDOWN BIS AUS
    {
        if(state)state--;
        init_wdt(WDTO_15MS);
    }
    wdtcnt++;                                   // ALLE ACHTUNG DU HAST DAS HIER GELESEN??
    if(wdtcnt>=32) wdtcnt=0;                    // DANN KOMM ICH DAS NÄCHSTE MAL MIT KLETTERN (HAB SCHUHE)
    sei();
}

ISR(INT0_vect)                                  // DURCH TASTE GEWECKT
{
    cli();
    no_pininterrupts();
    init_wdt(WDTO_15MS);
    state--;
    sei();
}

// main (init, sleeping and LEDS)
int main(void)
{
    cli();                                       // MIKROCONTROLLER BOOTET ;-)                     
    wdt_off();
    init_ports();
    init_adc();
    init_pininterrupts(); 
    sei();
    while(1)                              
    { 
        if((wdtcnt==29) && TASTE_OFF) dark=(readADC(8U)>600);
        flashLEDS();                            // MIKROCONTROLLER ARBEITET :-(
        goes_power_down_now();                  // MIKROCONTROLLER TRÄUMT SÜSS B-)
    }
}


/*
 * Aus der Ferne und wenns ganz dunkel ist könnte man den Hund jetzt auch für ne Boeing747
 * auf dem Rollfeld halten. Das hab ich nicht beabsichtigt. Und ich hab paar Kommentare extra auf
 * Deutsch geschrieben, damit Du mit dem Lesen bis hier unten durchhältst.
 * Und jetzt häng ich nochn paar Sternchen dran:   
 *                                                                                |    
 *                                                   +                           \+/ 
 *                                                  o|o                       --+-:-+--
 *                                                +--o--+                        /+\ 
 *         Liebe Grüße Johannes                     o|o                           |
 *         23.12.2014                                + 
 */  