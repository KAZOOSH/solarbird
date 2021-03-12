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
 * Bevor Du das liest musst Du den Stecker Deines Computers ziehen* denn dieses hier
 * geht sonst mit an (Du kannst es Deinem Laptop auch zu fressen geben).
 *
 * (*ach isser jetzt aus? War nur Spaß!)
 * L#### ######, ein schönes Weihnachtsfest wünsch ich Dir und dass Du mit lieben 
 * Leuten um Dich rum eine schöne Zeit verbringst. Und ein wenig Festtagsruhe 
 * sollst Du Dir auch gönnen. Hier guck:
 *
 *  :100000000EC03AC127C026C025C024C023C022C0CC
 *  :1000100021C020C01FC01EC0B5C01CC01BC0112401
 *  :100020001FBECFE5D1E0DEBFCDBF10E0A0E6B0E05F
 *  :10003000ECE2F3E002C005900D92A436B107D9F7C7
 *  :1000400020E0A4E6B0E001C01D92A736B207E1F7B8
 *  :100050003FD16AC1D5CF86B1856086B90895F8943D
 *  :10006000BC98C49A8FE39FE10197F1F700C00000AC
 *  :1000700078940895F894BC9AC49837987894089521
 *  :100080001F93CF93DF93182FF894E9DF379A86E018
 *  :1000900087B9369A3699FECF24B135B1912FC0E099
 *  :1000A000D0E008C09150369A3699FECF24B135B1D0
 *  :1000B000C20FD31F9111F6CFDDDF7894612FCE01EF
 *  :1000C00070E01ED1CB01DF91CF911F910895F8947C
 *  :1000D00085B7877E806185BF789485B7806285BF4C
 *  :1000E000889585B78F7D85BF089587B38B6187BB62
 *  :1000F00088B3847E88BBC29A08958BB780648BBF17
 *  :1001000008958BB78F7B8BBF0895F89494B7977F32
 *  :1001100094BF886481BDA89578940895A89584B704
 *  :10012000877F84BF81B5886181BD11BC0895F89433
 *  :1001300080916600882321F188B38B6188BB80E4BD
 *  :100140008A95F1F7809166008F3FB9F48091640041
 *  :10015000882399F0809165008E3129F48FEB92E12C
 *  :100160000197F1F708C0809165008F3131F48FE776
 *  :100170009EE30197F1F700C0000088B3847E88BB3E
 *  :10018000789408951F920F920FB60F9211242F9317
 *  :100190003F934F935F936F937F938F939F93AF930F
 *  :1001A000BF93EF93FF93F894B9DFB29B3DC0A5DFF7
 *  :1001B00080916600882349F18091600090916100F0
 *  :1001C000A0916200B0916300892B8A2B8B2BE9F000
 *  :1001D0008FEF8093660083E098DF809165008F3118
 *  :1001E00071F58091600090916100A0916200B091E2
 *  :1001F00063000197A109B1098093600090936100A9
 *  :10020000A0936200B09363001AC082EF9BE2A0E06B
 *  :10021000B0E08093600090936100A0936200B0937F
 *  :100220006300109266000BC080916600882329F05D
 *  :100230008091660081508093660080E066DF809147
 *  :1002400065008F5F8093650080916500803210F0BB
 *  :10025000109265007894FF91EF91BF91AF919F91BB
 *  :100260008F917F916F915F914F913F912F910F905F
 *  :100270000FBE0F901F9018951F920F920FB60F92FE
 *  :1002800011242F933F934F935F936F937F938F939B
 *  :100290009F93AF93BF93EF93FF93F89432DF80E087
 *  :1002A00034DF809166008150809366007894FF91DE
 *  :1002B000EF91BF91AF919F918F917F916F915F91DE
 *  :1002C0004F913F912F910F900FBE0F901F90189557
 *  :1002D000F89424DF0ADFBFDE10DF78948091650098
 *  :1002E0008D3159F4B29B09C088E0CADE21E089351E
 *  :1002F000924008F420E02093640019DFE8DEEECF9E
 *  :10030000AA1BBB1B51E107C0AA1FBB1FA617B7073B
 *  :1003100010F0A61BB70B881F991F5A95A9F7809557
 *  :0C0320009095BC01CD010895F894FFCF2A
 *  :04032C00F22B0000B0
 *  :00000001FF
 *
 *
 *
 *       _   _  _   _  _      _   
 *      ( ) ( )(_) (_)( )   /'_`\ 
 *      | |_| |   _ _ | |__(_) ) |
 *      |  _  | /'_` )|  _ `\ /'/'
 *      | | | |( (_| || | | ||_|  
 *      (_) (_)`\__,_)(_) (_)(_)  
 *                         
 *
 *
 *                   
 * Na gut, so siehts eben ganz tief drinnen aus. Dann geb ich Dir noch die 
 *
 * SCHALTUNG                                          
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
 *
 * Sieht aus wie ne Spinne auf Rollschuhen.
 *
 * Naja nicht ganz, das ist ja auch ein Weihnachtsgeschenk. Deins. Genaugenommen der Teil davon,
 * den ich erstmal denken musste und Dir auch aufschreiben kann. Also lass uns auspacken.
 *
 * Ist aber doch garnicht weihnachtlich! Stimmt. Hier das 
 * 
 * GESCHENKPAPIER
 *
  *                                                  ___-
   *                                      ___---'''              ____--
                                ___---'''           ____----''''
             |        ___---'''        ___-----''''             _____---
            )o(   -'''   ____----''''         _____------'''''     |
           \ # /   -''''    ______-----''''''
          \ +#+ /   --'''''                                        |
      -)oo## + ##oo(-                                         \    o    /
          / +#+ \     -___                                     \#\ |  #/
           / # \           '''---___                           \\-|||-//
            )o(                      '''           +     -  --o----o----o-  -
             |                                     +             -|||- \
                                                o +|+ o       //#  | \\#
                   |                             +|||+         //  o   \
                   +                 ö       +++-------+++         |
                  +|+                \           +|||+
                 +|||+              /           o +|+ o            |
            +----|+#+|----+         # \ \          +
         -+-----#|###|#-----+-     / #  o          +
            +----|###|----+       /  o# #
                 +|#|+            /    #   \            Da fehlten noch die Sterne.
                  +|+              /o #  o  \
                   +             /o   #    #  
                   |           /  # # #   # #   \
                                /    ## ##o   \      Der Baum ist bischen krumm aber 
                               / /#o  ##      #  \                    schööön nicht?
                              //   ####  o   #  \
       Und unten               # o   ## ### o #   \
                            / ## #  o## #       \                       ++
       echter Schnee!     /   // ### ###  o\ o \                  ++++ +  ++
                            /   / o ###                    +++++ +           ++++
                   ++                ##            ++++++ +     +               +++
        ++++    ++++++ ++++ ++++ ++  ##    ++++ +++             ++                 +
     ++++  ++ ++ +                 ++##+ ++                   +   ++
   *                                                      +  +
  *
 * 
 * Jetzt ist es schon besser. Und was soll das nun sein? Hm sagen wir mal,es fängt mit "H" an und
 * endet mit "and". Kann aber auch anders was sein. Das hängt noch davon ab, wie mans baut.
 * 
 *                ### #### ####### ####### ####### ## ### #### #### #####.
 *
 * Aber das Jessy so selten zu sehen war ist mir auch nicht entgangen. Da hab ich so bei mir
 * gedacht, so ein Hundehalsband was leuchtet wäre toll und das kann ich doch auch bauen. 
 * Also hab ich mich Dir mit meinem neusten Laptop gegenübergesetzt und Dich gefragt, welche Farben
 * Du magst, damit ich die richtigen LEDS dranlöten kann. Du hast Dich gegen rot entschieden. Und
 * grünblau find ich auch viel viel besser. Und dann hab ich noch mit meinem Handy ganz viel Kaffee
 * getrunken (das Handy hat nichts abbekommen) und bissel gelesen und getippt und jetzt isses
 * fertig.
 * 
 * Und was kann das nun? Das Hundehalsband? Sieht ja komisch aus dieser Quellcode da unten.
 * (falls Du soweit unten noch Lesen kannst) 
 * Also eigentlich kanns garnicht so sehr viel. Aber es ist:
 * 
 *                               VOLL ÖKO
 *
 *                  !!!!!!!!!!! TATATADAAA  !!!!!!!!!!!!
 *  
 * Also find ich, das ist ein schlaues, ultramodernes, politisch äußerst korrektes Teil.
 * 
 *                            Und so gehts:
 *
 * Du drückst kurz die TASTE des Hundehalsbands und..............................................
 * schon fängts an zu blinkern. Ja echt! Aber das was es so irre schlau macht ist die Möglichkeit,
 * es ohne Netzstecker zu betreiben. Ich hätte Dir sonst noch eine Verlängerungsschnur
 * mit reinpacken müssen. Ja die ganze Zeit einfach die Batterie angeschlossen zu lassen und eine
 * TASTE statt eines EINSCHALTERS zu verwenden. Du musst zugeben das ist schon genial! 
 *
 *                           Genau wie am Fahrrad.
 *
 * Das liegt daran, dass es die Fähigkeit hat zu schlafen (nicht nur ein bischen sondern eher
 * schon wie nach 10 Flaschen Wein) und dabei den Energieverbrauch 100000 fach zu senken 
 *
 *                            ohne zu pullern.
 *
 * So ist es auch leichter wasserdicht zu bekommen, falls Du es nachts an einem Amphibienfahrzeug
 * betreiben willst oder Jessy grad Fische fängt.Das Geblinker dient ebenfalls dazu Batteriestrom
 * zu sparen, denn eigentlich Blitzen die LEDS ja nur ganz kurz auf. Sogar in der Zwischenzeit
 * schläft es und verbraucht so gut wie garkeine Energie. Und wenns 12Stunden an war gehts von ganz
 * alleine wieder aus, falls Dus mal vergisst. In dem Zustand hält die Batterie dann Jahre. 
 * Wenn Du das Halsband vorher selber ausschalten willst geht das natürlich auch.
 * Du drückst so lange auf die TASTE bis es aus ist. Das ist alles. Du musst nichtmaldolle drücken.
 * (da würde es aber auch aus gehen...ist aber eine andere Erfindung) Und wenn Jessy selber mal
 * kurz an die TASTE kommt gehts nicht gleich aus und Jessy wird für lange unsichtbar.
 * Dann bleibt es einfach an!
 *                              Unfassbar!
 *
 * Man könnte noch einbauen, dass es wirklich nur leuchtet, wenns auch dunkel ist, so wie bei den
 * Flimmerfeen. (edit: Das ist ja schon V1.1adc da ist das schon eingebaut!)
 * Oder dass Du es per USB aufladen kannst und garkeine Batterien kaufen musst. Aber braucht man
 * das wirklich? 
 *
 *                                  Nö 
 *
 * denk ich und finds so wies jetzt ist fertig. Mir ist wichtiger dass es jetzt fertig ist. Dann
 * gibts später vielleicht eine V2.0. die ins Stromnetz einspeisen kann. Aber da wäre wieder dieses
 * Problem mit dem 
 *                             langen Kabel.
 * 
 * Und ist das jetzt schön? So schön wie Deine Bommeln V1.0 für den Weihnachtsbaum (ohne LEDS)?
 * Das kann ich Dir nicht beantworten. 
 * Also ich find ja die Syntax von C schön...die ganzen geschweiften Bordüren bzw. Klammern. 
 * Ich möchte Dir aber sagen, dass ich sowas vorher auch noch nicht hinbekommen habe und jedesmal
 * beim Nachdenken über das Energiesparen durch Schlaf selbst eingeschlafen bin. Doch dieses
 * Halsband ist der Grund dass ichs jetzt kann: 
 * Dieses gleichzeitig schlafen können und dabei einen Knopf permanent zu überwachen, 
 * ob da jemand gerade drückt...absolut schwierig. Wenn ichs an mir selbst probierte bin ich 
 * immer sofort aufgewacht, wenn jemand mich gedrückt hat. Aber dieses schwarze Ding da...
 * Und was ich vorher auch noch nicht konnte war, zu machen, dass es immer ÖKO ist weil es auch 
 * von selber nach ner Weile schlafen geht. (Wie die Kinder) Also hat es mich auch selber was ge-
 * lehrt. Und darum ging es mir auch. Und dass wirs zusammen ausprobiern. Würd gern wissen wie weit
 * es reicht.
 */
 
// JETZT GEHTS LOS, DAS GROSSE KOPFLEUCHTEN

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