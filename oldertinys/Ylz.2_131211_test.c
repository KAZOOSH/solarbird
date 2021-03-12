/*
 * Ylz.2_131211_test.c
 * MCU: ATtiny45
 * Fuses: (E:FF, H:DF, L:E2)
 * Erstellt: 30.11.2013 18:20:10
 * Letzte Bearbeitung: 12.12.2013 01:36:00
 * Autoren: Holger Freydank (MCU-init, AD-Wandlungen) und Johannes Fritzsche (Pseudorandom, Bitmuster, RF, Story)
 *
 *
 *
 *
 * Was ist passiert?
 *
 * Am 23.12.2019 fielen (was wegen des damals grassierenden 3D-printerhypes nicht weiter besonders ist) bei 
 * der 2. SolarWindExplorer-Mission die Kreiselstabilisatoren sowie 5 der 6 Lageregelungstriebwerke aus. 
 * Die SolarWind Explorer2 war eine unbemannte Sonde, die (nach dem "International Green Energy Propulsion Trust" 
 * von 2016) völlig ohne Haupttriebwerke auskommend die Eignung des Strahlungsdruckes der Sonne als low-G high-V 
 * Beschleunigungsantrieb für interstellare Missionen erörtern sollte. Bei dem Zwischenfall kam es zu während einer 
 * Zeit von 40 Tagen zu einer 180grad-Drehung der Sonde und der Kontakt zur Sonde musste aufgegeben werden. Aufgrund 
 * der Größe der Sonnensegel war die Sonde jedoch weiterhin für den Zeitraum von 5 Jahren mit optischen Instrumenten 
 * vom Erdorbit aus beobachtbar. Dabei wurde mit hochgenauen trigonometrischen Positionsbestimmungen eine 
 * Gewichtszunahme der Sonde um 25gramm festgestellt. Diese Gewichtszunahme ließ sich vorerst nicht erklären.....
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

uint8_t teiler[] = {13,7,5,2};

/*
 * Laufzeitfehler! Schnelles Blinken der LED. Das ist definitiv noch nie vorgekommen!
 */
void debug(void)
{
    for(uint8_t i=0; i<10; i++)
    {
        PORTB |=(1<<3);
        _delay_ms(50);
        PORTB &= ~(1<<3);
        _delay_ms(50);
    }
}

/*
 * AM 20.12.2028 also gut neun Jahre später erhielten J.P Rennert und A.Löwenhopf den Nobelpreis für Physik 
 * für ihren experimentellen Nachweis nichtmolekularer Materie, die schon einhundert Jahre vor ihnen von H.Lorentz 
 * vorausgesagt wurde. (erweiterte Äthertheorie). Dabei klassifizierten sie den Äther als eine energetisch 
 * hochpotente Substanz unendlich geringer Dichte, die besondere Eigenschaften besitzt.....
 */

/*
 * Erzeugung Zufallswert mit Hilfe LSB-Rauschen von Analog-Digital Wandlungen 
 */
uint16_t get_analog_random()
{
    uint8_t zahl=0, zahl2;
    uint16_t analog_random=0;
    for (uint8_t stelle=0; stelle < 16u; stelle++)
    {
        ADCSRA |= (1<<ADSC);        //Start der AD-Wandlung
        while(ADCSRA & (1<<ADSC));  //Warten auf Ende der Wandlung, dauert 13 Takte
        zahl =  ADCL;               //niederwertiges Byte der AD-Wandlung
        zahl2 = ADCH;               //höherwert. Byte ADCH muss auch gelesen werden, selbst wenn nicht verwendet
        zahl = zahl & 1;            //niederwertigstes Bit maskieren
        zahl = zahl << stelle;      //nach links schieben
        analog_random = analog_random + zahl;  //Zufallszahl zusammenbauen
    }
    return analog_random;
}






/*
 * Erzeugung 1MHz RF Träger
 *
 * Schaltung:
 *  
 *  
 *                               MOSI ----.                                      Wenn Reset auf LOW-Pegel gezogen
 *                               MISO --. |                                      wird, wird das ausgeführte Programm
 *                          VCC   SCK . | |       .-----------------------.      abgebrochen.
 *                           +        | | |       | .-------------------. |
 *              25k          |        | | |       | | .---------------. | |      Die Leitungen SCK, MISO, MOSI werden
 *              ___          |        | | |       | | |               | | |      nur für das Beschreiben des FLASH-
 *        .----|___|---------o------. | | |       | | |               | | |      Speichers mit einem Programmiergerät
 *        |      A                  | | | |       | | |     Loop      | | |      benötigt.
 *        |      |                  | | | |       | | |               | | |      Die LED bildet zusammen mit dem        
 *        |      |                  o_o_o_o       | | |               | | |      Vorwiderstand und der Loop-Antenne
 *        |      |                 |              | | '------------.  | | |      einen RF-Transmitter.
 *        |      |                 |ATtiny45      | '--------------)--' | |
 *        |      |                  o o o o       '----------------)----' |      Die vom RF-Transmitter ausgesandte
 *        |      |                  | | | |           ___     LED  |      |      Trägerwelle kann auf der Frequenz
 *        |      |                  | | '-)----------|___|-  ->|---'      |      von 1MHz mit einfachen Mittelwellen-
 *        |      |         ___      | |   |           220                 |      radios empfangen werden.
 *        |      '--------|___|-----)-'   '------o------------------------'
 *        |                2M       |            |
 *       ===                        |           ===
 *       GND               Reset ---'           GND
 *
 *
 *          (created by AACircuit v1.28.6 beta 04/19/05 www.tech-chat.de)
 */
void transmit_50us_1MHz(uint16_t dauer)
{
    for(uint16_t i=0; i<dauer; i++)
    {
        for(uint8_t j=0; j<100; j++)    //minimal werden 50 volle Trägerwellen erzeugt
        {
        PINB = 1<<PB3;                  //Trägererzeugung 1MHz (decrement + brne + Toggeln mit PINB = 4Takte?)
        //asm volatile ("nop");         //Trägerfrequenz verringern um 25%
        }
    }
}

void pause_1ms(uint16_t dauer) 
{ 
    for (uint16_t i=0; i<dauer; i++)   //Pause ohne Träger
    _delay_ms(1);
}

void pause_50us(uint16_t dauer)
{
    for (uint16_t i=0; i<dauer; i++)   //50us*dauer Pause ohne Träger
    _delay_us(50);
}


/*
 * Erzeugung Bitmuster für Knacklaut
 * Die Funktion burst3() generiert einen zeitsymmetrischen Burst der als Knacken gehört werden soll. Hierbei stellt 
 * sich das Problem, dass ein Knck ein sehr kurzer Laut ist. Eigentlich handelt es sich ja nur um einen Impuls.
 * Einen solchen Impuls als Rahmen für eine Trägerwelle zu verwenden ist eher ungünstig, da so nur wenig Energie
 * transportiert werden kann. Um eine oberwellenreiche percussive Schwingung zu generieren wird hierbei mit einer 
 * Frequenz von 10kHz beginnend die 1MHz Trägerwelle getastet. Je Durchlauf wird die Periodendauer der Frequenz
 * verdoppelt. Maximal 15x kann verdoppelt werden. Die längste modulierbare Periode beträgt mit step=15 1,6s. 
 * Sinnvoll sind Periodendauern bis ca. 40ms, die noch als einzelnes Knacken ohne Echo wahrgenommen werden können.
 * Step sollte also kleiner als 10 sein. Mit stretch kann die Anzahl der vollständigen Perioden je step erhöht werden. 
 * Sinnvoll sind hier Werte bis 4. Die längste Periode wird nur einmal mit dem Senden der Trägerwelle durchlaufen
 */
void burst3(uint8_t steps, uint8_t stretch)
{
    if ((steps>15) || (stretch>4))       //zu große Variablen! Verlassen ohne Trägergenerierung
    {
        debug();
        return;
    }

    uint8_t i=0;

    /*
     * sich verdoppelnde Periodendauer (steps=3, stretch=2):____-_-_--__--__----____----____
     */
    for (; i<steps; ++i)
    {
        for (uint8_t j=0; j<stretch; j++)
        {
            transmit_50us_1MHz(1<<i);
            pause_50us(1<<i);
        }
    }

    /*
     * Längste Periode       (steps=3, stretch=2): --------
     */
    transmit_50us_1MHz(1<<steps);

    /*
     * sich halbierende Periodendauer  (steps=3, stretch=2):____----____----__--__--_-_-_____
     */
    for (; i>0; --i)
    {
        for (uint8_t j=0; j<stretch; j++)
        {
            pause_50us(1<<i);
            transmit_50us_1MHz(1<<i);
        }
    }
}

/*
* 2089 starteten die ersten Harvestermissionen um größere Mengen dieser kostbaren Materie einzusammeln. 
 * Heute im 22.Jh ist ein Leben ohne die inzwischen "Ylz.2" genannte Substanz nicht mehr vorstellbar. 
 * Die durchschnittliche Lebenserwartung der Menschen hat sich mit ihrer Hilfe um 130Jahre verlängert. 
 * Da Ylz.2 selbst in geringsten Beimengungen den Zerfall radioaktiver Isotope vollständig stoppen kann 
 * und in höheren Konzentrationen für ionisierende Strahlungen eine Strahlungs-Suprabarriere darstellt 
 * wurde mit Ylz.2 eine interstellare Raumfahrt in der Post-Earth Periode überhaupt erst ermöglicht. 
 * Ylz.2 stellt wie viele Wissenschaftler heute sagen die bedeutendste Entdeckung des 21.Jh dar..........
 */ 

int main(void)
{
    DDRB |= (1<<3);                         //PB3 Output
    ADCSRA |= (1<<ADEN);                    //enable ADC
    ADMUX |= (1<<MUX1);       //PB4 als Input für ADC Enable 10Bit (rechtsbündige Werte in ADCH und ADCL)
    // Voltage reference selection auf Vcc nicht erforderlich, da Prozessor nach Reset so initialisiert
    ADCSRA |= (1<<ADPS1)|(1<<ADPS2);        //prescaler = 64 ADC-Takt = 125kHz (50kHz < Takt < 200kHz)
    
    _delay_ms(200); // Bootverzögerung nach Reset
	
	while(1)
    {        
        uint8_t n = 0;
        /*
         * 16Bit Linear Feedback Shift Register Code (LFSR)
         * Bildung einer Maximalfolge mit der vom AD-Wandler generierten Startfolge
         */
        uint16_t lfsr_in = get_analog_random();
        if(lfsr_in==0) lfsr_in=1;
        uint16_t lfsr_state=lfsr_in;
        uint16_t lfsr_out=0;
        do
        {
            for (uint8_t i=0; i<16; i++)
            {
                lfsr_state=(lfsr_state >> 1)^(-(lfsr_state & 1) & 0xB400u); // nach E.Galois
                /*
                 * 0xB400u ist ein uint hex Literal welches die taps: 16 14 13 11 nach der von E.Galois(*1811/†1832)
                 * inspirierten LFSR Topologie realisiert. Evariste Galois starb im Alter von 20Jahren an einem 
                 * Bauchschuss der ihm während eines Duells zugefügt wurde. Die oben aufgeführte Programmzeile 
                 * basiert auf seinen Erkenntnissen zur Lösung algebraischer Gleichungen mit mehreren Polynomen. 
                 * Hierbei handelt es sich um ein in Software realisiertes 16Bit breites linear rückgekoppeltes 
                 * Schieberegister (LFSR) mit intern realisierter XOR-Verknüpfung, die aufgrund von Galois 
                 * Erkenntnissen in einer einzigen Programmzeile realisiert werden kann.
                 */
                lfsr_out<<=1;
                lfsr_out|=lfsr_state & 1;
            }

            if (!(lfsr_out % teiler[n])) //zufallszahl ist durch teiler teilbar (%=0)
            {
                /*
                 * Auslesen Poti (64 unterschiedliche Stellungen werden erkannt und verändern das Knacken)
                 */
                uint8_t poti=0;             
                ADMUX |= 1<<ADLAR;          //enable 8Bit ADC. ADCH linksbündig gelesen (2LSB in ADCL verfallen)
                ADCSRA |= (1<<ADSC);        //Start der AD-Wandlung
                while(ADCSRA & (1<<ADSC));  //Warten auf Ende der Wandlung, dauert 13 Takte
                poti = ADCH;                //höherwertiges Byte ADCH
                /*
                 * Sounderzeugung und Trägerbildung
                 */
                burst3(poti>>4, (poti>>2)%5);
                ADMUX &= ~(1<<ADLAR);       //Enable 10Bit ADC. ADCH rechtsbündig gelesen (2MSB in ADCH zu lesen) 
                if(n<3) n++;                //simple Clusterbildung durch Verringern des teilers (%=0 wahrscheinlicher)
                if(n==3) n=1;
            }

            else
            {
                pause_1ms(lfsr_out>>10);     //zufallszahl ist nicht durch teiler teilbar
                if(n>0) n--;
                if(n==0) n=3;
            }                   
        /*
         * Verlasse do while Schleife zur Neubildung eines Startwertes, wenn sich die Maximalfolge wiederholt
         */
        } while (lfsr_state != lfsr_in);      
    }
}

/*
 * Das hier vorgestellte Programm soll das Experiment nachstellen, mit dem es gelang, die besonderen Eigenschaften 
 * von Ylz.2 in Bezug auf den radioaktiven Zerfall nachzuweisen:
 *
 * ein Geigerzähler hängt über einer Probe Uranerz und weist Heliumkerne sowie Elektronen und Positronen nach, die
 * beim radioaktivem Zerfall der Probe entstehen.
 * Beim Einbringen verschiedener Stoffe zwischen Probe und Geigerzähler zeigt sich kaum eine Abschwächung der 
 * Strahlung. Jedoch kommt der radioaktive Zerfall beim Einbringen einer Probe mit Ylz.2  sofort zum Erliegen.
 * Die Probe sendet keine Strahlung mehr aus.
 * 
 * Das Nachstellen des Experimentes mit radioaktivem Material war nach Studium der Hausordnung leider nicht möglich.
 * Deshalb wurde das Experiment hier simuliert.
 * Der oben aufgeführte Code realisiert die Nachbildung zufälliger Zerfallsereignisse und deren Strahlungseffekte 
 * durch Erzeugung einer Maximalfolge mit einem 16Bit Linear Feedback Shift Register (LFSR).
 * Der Startwert der in das LFSR geladen wird, wird aus den niederwertigsten Bits von 16 Analog-Digital Wandlungen
 * gebildet und ist damit ein Produkt des Zufalls.
 * Ein 16Bit breiter Abschnitt der vom LFSR gebildeten Folge wird anschließend auf Teilbarkeit überprüft.
 * Dazu werden in einem Array verschiedene Teiler vorgehalten, die mit steigendem Index kleiner werden.
 *
 * Wenn der 16Bit breite Abschnitt der Maximalfolge durch den gerade gültigen dieser Teiler ohne Rest teilbar ist, 
 * wird eine Pulsfolge ausgesandt, die einen Knacklaut erzeugt.
 * 
 * Damit dieser Knacklaut in einem externen Nachweisgerät (Mittelwellenempfänger) hörbar werden kann, muss er noch
 * mit einer 1MHz Trägerwelle moduliert und über eine magnetische Antenne abgestrahlt werden.
 * 
 * Außerdem wird nach erfolgter Abstrahlung eines Knacklautes der Index des Arrays um  eins erhöht, und damit der
 * nächste Teiler verkleinert (die Wahrscheinlichkeit einer erneuten Teilbarkeit steigt)
 * So wird eine Gruppenbildung begünstigt, die das Einschlagen mehrerer Partikel nachbildet.
 * 
 * Ist der 16Bit breite Abschnitt der Maximalfolge nicht durch den Teiler ohne Rest teilbar, passiert nichts.
 * Das Programm pausiert und der Index des Teilers wird um eins verringert. Damit wird die Wahrscheinlichkeit einer
 * erneuten Teilbarkeit verringert. Es entsteht eine längere Pause im Nachweisgerät.
 * Während der Pausen wird auch keine Trägerwelle ausgesandt, so das das Empfängerrauschen immer hörbar bleibt.
 *
 * Wenn eine Probe mit Ylz.2 in die Nähe der radioaktiven gebracht wird, verstummt das Knacken im Nachweisgerät.
 * Der Radioaktive Zerfall wurde gestoppt.
 * Um dies zu simulieren habe ich auf RFID-technik zurückgegriffen. Die Anwesenheit von Ylz.2 wird einfach dadurch
 * realisiert, dass die Data-LED des RFID-Lesegerätes mit der Resetleitung des Transmitters verbunden wird.
 * Johannes Fritzsche
 */ 

/*
------ Build started: Project: Ylz.2_131211_test, Configuration: Debug AVR ------
Build started.
Project "Ylz.2_131211_test.cproj" (default targets):
Target "PreBuildEvent" skipped, due to false condition; ('$(PreBuildEvent)'!='') was evaluated as (''!='').
Target "CoreBuild" in file "C:\Programme\Atmel\Atmel Studio 6.1\Vs\Compiler.targets" 
from project "C:\Dokumente und Einstellungen\CODE\Eigene Dateien\Atmel Studio
\6.1\Ylz.2_131211_test\Ylz.2_131211_test\Ylz.2_131211_test.cproj" (target "Build" depends on it):
Using "RunCompilerTask" task from assembly "C:\Programme\Atmel\Atmel Studio 6.1\Extensions\Application\AvrGCC.dll".
Task "RunCompilerTask"
C:\Programme\Atmel\Atmel Studio 6.1\shellUtils\make.exe all
.././Ylz.2_131211_test.c: In function 'get_analog_random':
Building file: .././Ylz.2_131211_test.c
Invoking: AVR/GNU C Compiler : 3.4.2
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe"  
-funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 
-Wall -mmcu=attiny45 -c -std=gnu99 -MD -MP -MF "Ylz.2_131211_test.d" -MT"Ylz.2_131211_test.d" -MT"Ylz.2_131211_test.o"   
-o "Ylz.2_131211_test.o" ".././Ylz.2_131211_test.c"
C:\Dokumente und Einstellungen\CODE\Eigene Dateien\Atmel Studio
\6.1\Ylz.2_131211_test\Ylz.2_131211_test\Ylz.2_131211_test.c(55,13): variable 'zahl2' set but not used 
[-Wunused-but-set-variable]
Finished building: .././Ylz.2_131211_test.c
Building target: Ylz.2_131211_test.elf
Invoking: AVR/GNU Linker : 3.4.2
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe" 
-o Ylz.2_131211_test.elf  Ylz.2_131211_test.o   -Wl,-Map="Ylz.2_131211_test.map" -Wl,--start-group -Wl,-lm  -Wl,
--end-group -Wl,--gc-sections -mmcu=attiny45
Finished building target: Ylz.2_131211_test.elf
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" 
-O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Ylz.2_131211_test.elf" "Ylz.2_131211_test.hex"
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" 
-j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings 
-O ihex "Ylz.2_131211_test.elf" "Ylz.2_131211_test.eep" || exit 0
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objdump.exe" 
-h -S "Ylz.2_131211_test.elf" > "Ylz.2_131211_test.lss"
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" 
-O srec -R .eeprom -R .fuse -R .lock -R .signature  "Ylz.2_131211_test.elf" "Ylz.2_131211_test.srec"
"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-size.exe" 
"Ylz.2_131211_test.elf"

text	   data	    bss	    dec	    hex	filename
784	      4	      0	    788	    314	Ylz.2_131211_test.elf

Done executing task "RunCompilerTask".
Using "RunOutputFileVerifyTask" task from assembly "C:\Programme\Atmel\Atmel Studio 6.1\Extensions\Application\AvrGCC.dll".
Task "RunOutputFileVerifyTask"

Program Memory Usage 	:	788 bytes   19,2 % Full
Data Memory Usage 		:	4 bytes   1,6 % Full

Done executing task "RunOutputFileVerifyTask".
Done building target "CoreBuild" in project "Ylz.2_131211_test.cproj".
Target "PostBuildEvent" skipped, due to false condition; ('$(PostBuildEvent)' != '') was evaluated as ('' != '').
Target "Build" in file "C:\Programme\Atmel\Atmel Studio 6.1\Vs\Avr.common.targets" 
from project "C:\Dokumente und Einstellungen\CODE\Eigene Dateien\Atmel Studio
\6.1\Ylz.2_131211_test\Ylz.2_131211_test\Ylz.2_131211_test.cproj" (entry point):
Done building target "Build" in project "Ylz.2_131211_test.cproj".
Done building project "Ylz.2_131211_test.cproj".

Build succeeded.
========== Build: 1 succeeded or up-to-date, 0 failed, 0 skipped ==========

*/