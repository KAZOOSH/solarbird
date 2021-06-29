EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Solaranima210527_2049"
Date "2021-05-27"
Rev "1.1000"
Comp "KAZOOSH!"
Comment1 "V1.101(add R8 for saver startup, higher Vth of Q2 possible)"
Comment2 "open hardware: github.com/kazoosh"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Diode:BAT48RL D1
U 1 1 6060B775
P 5700 3150
F 0 "D1" H 5550 2950 50  0000 C CNN
F 1 "BAT48RL" H 5450 3050 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P10.16mm_Horizontal" H 5700 2975 50  0001 C CNN
F 3 "www.st.com/resource/en/datasheet/bat48.pdf" H 5700 3150 50  0001 C CNN
	1    5700 3150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 606143C5
P 7250 4800
F 0 "#PWR09" H 7250 4550 50  0001 C CNN
F 1 "GND" H 7255 4627 50  0000 C CNN
F 2 "" H 7250 4800 50  0001 C CNN
F 3 "" H 7250 4800 50  0001 C CNN
	1    7250 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 60615262
P 4850 4800
F 0 "#PWR06" H 4850 4550 50  0001 C CNN
F 1 "GND" H 4855 4627 50  0000 C CNN
F 2 "" H 4850 4800 50  0001 C CNN
F 3 "" H 4850 4800 50  0001 C CNN
	1    4850 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3500 4850 4800
$Comp
L power:GND #PWR04
U 1 1 60625045
P 3600 4800
F 0 "#PWR04" H 3600 4550 50  0001 C CNN
F 1 "GND" H 3605 4627 50  0000 C CNN
F 2 "" H 3600 4800 50  0001 C CNN
F 3 "" H 3600 4800 50  0001 C CNN
	1    3600 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4550 7250 4800
$Comp
L MCU_Microchip_ATtiny:ATtiny85V-10PU U2
U 1 1 606058EB
P 7250 3950
F 0 "U2" H 7400 3250 50  0000 R CNN
F 1 "ATtiny85V-10PU" H 7900 3150 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7250 3950 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 7250 3950 50  0001 C CNN
	1    7250 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6064EFB8
P 3000 4800
F 0 "#PWR03" H 3000 4550 50  0001 C CNN
F 1 "GND" H 3005 4627 50  0000 C CNN
F 2 "" H 3000 4800 50  0001 C CNN
F 3 "" H 3000 4800 50  0001 C CNN
	1    3000 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6064F3E5
P 2450 4800
F 0 "#PWR02" H 2450 4550 50  0001 C CNN
F 1 "GND" H 2455 4627 50  0000 C CNN
F 2 "" H 2450 4800 50  0001 C CNN
F 3 "" H 2450 4800 50  0001 C CNN
	1    2450 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4350 3000 4800
$Comp
L Device:R R4
U 1 1 606534F1
P 3000 2900
F 0 "R4" H 3070 2946 50  0000 L CNN
F 1 "220k" H 3070 2855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2930 2900 50  0001 C CNN
F 3 "~" H 3000 2900 50  0001 C CNN
	1    3000 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 606547AF
P 2450 2900
F 0 "R3" H 2520 2946 50  0000 L CNN
F 1 "510k" H 2520 2855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 2900 50  0001 C CNN
F 3 "~" H 2450 2900 50  0001 C CNN
	1    2450 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 4350 2450 4800
Wire Wire Line
	2450 3150 2700 3150
Wire Wire Line
	2700 3150 2700 4150
Connection ~ 2450 3150
Wire Wire Line
	2450 3150 2450 3050
$Comp
L Device:L_Core_Ferrite L1
U 1 1 60662572
P 5450 2850
F 0 "L1" H 5550 3050 50  0000 L CNN
F 1 "47...130uH" H 5550 2950 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 5450 2850 50  0001 C CNN
F 3 "~" H 5450 2850 50  0001 C CNN
	1    5450 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 6067FB7F
P 4250 4800
F 0 "#PWR05" H 4250 4550 50  0001 C CNN
F 1 "GND" H 4255 4627 50  0000 C CNN
F 2 "" H 4250 4800 50  0001 C CNN
F 3 "" H 4250 4800 50  0001 C CNN
	1    4250 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6068F1F4
P 6350 4800
F 0 "#PWR08" H 6350 4550 50  0001 C CNN
F 1 "GND" H 6355 4627 50  0000 C CNN
F 2 "" H 6350 4800 50  0001 C CNN
F 3 "" H 6350 4800 50  0001 C CNN
	1    6350 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 6068FD92
P 6000 4800
F 0 "#PWR07" H 6000 4550 50  0001 C CNN
F 1 "GND" H 6005 4627 50  0000 C CNN
F 2 "" H 6000 4800 50  0001 C CNN
F 3 "" H 6000 4800 50  0001 C CNN
	1    6000 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3150 7250 3350
Wire Wire Line
	2450 2400 2450 2750
Wire Wire Line
	3000 2400 3000 2750
Wire Wire Line
	7250 2400 7250 3150
Connection ~ 7250 3150
$Comp
L Device:C C2
U 1 1 6069694D
P 6350 3750
F 0 "C2" H 6465 3796 50  0000 L CNN
F 1 "100nF" H 6400 3600 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 6388 3600 50  0001 C CNN
F 3 "~" H 6350 3750 50  0001 C CNN
	1    6350 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 606989F5
P 6000 3750
F 0 "C1" H 6118 3796 50  0000 L CNN
F 1 "220uF" H 6050 3600 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 6038 3600 50  0001 C CNN
F 3 "~" H 6000 3750 50  0001 C CNN
	1    6000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3600 6000 3150
Wire Wire Line
	6000 3150 6350 3150
Wire Wire Line
	6350 3600 6350 3150
Connection ~ 6350 3150
Wire Wire Line
	6350 3150 6800 3150
Wire Wire Line
	6000 3900 6000 4800
Wire Wire Line
	6350 3900 6350 4800
Wire Wire Line
	3000 2400 2450 2400
$Comp
L Device:R R1
U 1 1 60654BA9
P 1800 2900
F 0 "R1" H 1850 2950 50  0000 L CNN
F 1 "1M" H 1850 2850 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 1870 2809 50  0001 L CNN
F 3 "~" H 1800 2900 50  0001 C CNN
	1    1800 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2400 2100 2750
Connection ~ 3000 2400
Wire Wire Line
	4850 2650 4850 2850
$Comp
L Device:Speaker_Crystal LS1
U 1 1 606D2991
P 9700 3950
F 0 "LS1" H 9600 3650 50  0000 L CNN
F 1 "PIEZO SIGNAL" H 9600 3550 50  0000 L CNN
F 2 "" H 9665 3900 50  0001 C CNN
F 3 "~" H 9665 3900 50  0001 C CNN
	1    9700 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:LED LED1
U 1 1 606DAB8A
P 9200 3250
F 0 "LED1" H 9350 3200 50  0000 C CNN
F 1 "LED_GN" H 9200 3400 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 9200 3250 50  0001 C CNN
F 3 "https://docs.rs-online.com/0622/0900766b81302e6b.pdf" H 9200 3250 50  0001 C CNN
	1    9200 3250
	-1   0    0    1   
$EndComp
$Comp
L Device:LED LED2
U 1 1 606DDA34
P 9200 3550
F 0 "LED2" H 9350 3500 50  0000 C CNN
F 1 "LED_GN" H 9200 3700 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 9200 3550 50  0001 C CNN
F 3 "~" H 9200 3550 50  0001 C CNN
	1    9200 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 606DE168
P 8750 3250
F 0 "R5" V 8650 3250 50  0000 C CNN
F 1 "120" V 8850 3250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8680 3250 50  0001 C CNN
F 3 "~" H 8750 3250 50  0001 C CNN
	1    8750 3250
	0    1    1    0   
$EndComp
Connection ~ 4850 2650
Wire Wire Line
	4250 2650 4850 2650
$Comp
L Switch:SW_SPDT SW1
U 1 1 606FCCBB
P 4050 4650
F 0 "SW1" H 4400 4750 50  0000 C CNN
F 1 "SW_SPDT" H 4400 4650 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Slide_1P2T_CK_OS102011MS2Q" H 4050 4650 50  0001 C CNN
F 3 "~" H 4050 4650 50  0001 C CNN
	1    4050 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4750 4250 4800
Wire Wire Line
	3850 4650 3750 4650
Wire Wire Line
	3600 4650 3600 4800
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 607253BC
P 9400 4050
F 0 "J4" H 9350 3950 50  0000 L CNN
F 1 "Conn_01x01" H 9480 4001 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 9400 4050 50  0001 C CNN
F 3 "~" H 9400 4050 50  0001 C CNN
	1    9400 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 60726281
P 9400 3950
F 0 "J3" H 9350 4050 50  0000 L CNN
F 1 "Conn_01x01" H 9480 3901 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 9400 3950 50  0001 C CNN
F 3 "~" H 9400 3950 50  0001 C CNN
	1    9400 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 3250 9450 3550
Wire Wire Line
	9350 3250 9450 3250
Wire Wire Line
	9350 3550 9450 3550
Connection ~ 9450 3550
Wire Wire Line
	9450 3550 9450 3750
Wire Wire Line
	8900 3250 9050 3250
Wire Wire Line
	8900 3550 9050 3550
Wire Wire Line
	7850 4150 7950 4150
Wire Wire Line
	5450 2650 5450 2700
Wire Wire Line
	5450 3000 5450 3150
Wire Wire Line
	4850 2650 5450 2650
Wire Wire Line
	5200 3150 5450 3150
Wire Wire Line
	5550 3150 5450 3150
Connection ~ 5450 3150
Wire Wire Line
	5850 3150 6000 3150
Connection ~ 6000 3150
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6076DD1A
P 4850 2650
F 0 "#FLG0101" H 4850 2725 50  0001 C CNN
F 1 "PWR_FLAG" H 4850 2823 50  0001 C CNN
F 2 "" H 4850 2650 50  0001 C CNN
F 3 "~" H 4850 2650 50  0001 C CNN
	1    4850 2650
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6076F71F
P 3750 4650
F 0 "#FLG0102" H 3750 4725 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 4550 50  0001 C CNN
F 2 "" H 3750 4650 50  0001 C CNN
F 3 "~" H 3750 4650 50  0001 C CNN
	1    3750 4650
	1    0    0    -1  
$EndComp
Connection ~ 3750 4650
Wire Wire Line
	3750 4650 3600 4650
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 607734E9
P 6800 3150
F 0 "#FLG0103" H 6800 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 6800 3323 50  0001 C CNN
F 2 "" H 6800 3150 50  0001 C CNN
F 3 "~" H 6800 3150 50  0001 C CNN
	1    6800 3150
	1    0    0    -1  
$EndComp
Connection ~ 6800 3150
Wire Wire Line
	6800 3150 7250 3150
Wire Wire Line
	8600 3250 8300 3250
Wire Wire Line
	8300 3250 8300 3650
Wire Wire Line
	8300 3650 7850 3650
$Comp
L Device:R R6
U 1 1 607F9A71
P 8750 3550
F 0 "R6" V 8650 3550 50  0000 C CNN
F 1 "120" V 8850 3550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8680 3550 50  0001 C CNN
F 3 "~" H 8750 3550 50  0001 C CNN
	1    8750 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 607F9D26
P 8750 3950
F 0 "R7" V 8650 3950 50  0000 C CNN
F 1 "330" V 8950 3950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8680 3950 50  0001 C CNN
F 3 "~" H 8750 3950 50  0001 C CNN
	1    8750 3950
	0    1    1    0   
$EndComp
$Comp
L Device:Solar_Cells SC1
U 1 1 6060DDD4
P 3600 4050
F 0 "SC1" H 3708 4096 50  0000 L CNN
F 1 "Solar Cell 2,4V 50mA" H 3708 4005 50  0000 L CNN
F 2 "" V 3600 4110 50  0001 C CNN
F 3 "~" V 3600 4110 50  0001 C CNN
	1    3600 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 60716B0F
P 3600 2650
F 0 "J1" V 3600 2750 50  0000 L CNN
F 1 "Conn_01x01" H 3680 2601 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 3600 2650 50  0001 C CNN
F 3 "~" H 3600 2650 50  0001 C CNN
	1    3600 2650
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 60720F2F
P 3700 2650
F 0 "J2" V 3700 2450 50  0000 L CNN
F 1 "Conn_01x01" H 3780 2601 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 3700 2650 50  0001 C CNN
F 3 "~" H 3700 2650 50  0001 C CNN
	1    3700 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9200 3950 9500 3950
Wire Wire Line
	9200 4050 9500 4050
Wire Wire Line
	7850 3750 8400 3750
Wire Wire Line
	8400 3750 8400 3550
Wire Wire Line
	8400 3550 8600 3550
Wire Wire Line
	8500 3850 8500 3750
Wire Wire Line
	8500 3750 9450 3750
Wire Wire Line
	7850 3850 8500 3850
$Comp
L power:GND #PWR010
U 1 1 6065D07E
P 9400 4800
F 0 "#PWR010" H 9400 4550 50  0001 C CNN
F 1 "GND" H 9405 4627 50  0000 C CNN
F 2 "" H 9400 4800 50  0001 C CNN
F 3 "" H 9400 4800 50  0001 C CNN
	1    9400 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 4550 8450 4550
Wire Wire Line
	9200 4750 9050 4750
Wire Wire Line
	9400 4800 9400 4650
Wire Wire Line
	9400 4650 9200 4650
Wire Wire Line
	9200 4650 9200 4750
Wire Wire Line
	7950 4650 8300 4650
Wire Wire Line
	7950 4150 7950 4650
Wire Wire Line
	8300 4650 8300 4550
Wire Wire Line
	4250 2650 4250 3400
$Comp
L Joe_Library:NiMH_1,25V_600mAh BT1
U 1 1 606BEBD1
P 4250 3900
F 0 "BT1" H 4400 4000 50  0000 L CNN
F 1 "NiMH 1,25V 600mAh" H 4400 3900 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_2466_1xAAA" V 4250 3960 50  0001 C CNN
F 3 "~" V 4250 3960 50  0001 C CNN
	1    4250 3900
	1    0    0    -1  
$EndComp
Connection ~ 9200 4050
Wire Wire Line
	7850 3950 8600 3950
Wire Wire Line
	8900 3950 9200 3950
Connection ~ 9200 3950
Wire Wire Line
	7850 4050 9200 4050
$Comp
L Joe_Library:QX5252F U1
U 1 1 60B0E9AA
P 4850 2900
F 0 "U1" H 5050 3050 50  0000 L CNN
F 1 "QX5252F" H 5050 2950 50  0000 L CNN
F 2 "" H 4850 2900 50  0001 C CNN
F 3 "https://skootsone.yolasite.com/resources/QX5252.pdf" H 4850 2900 50  0001 C CNN
	1    4850 2900
	1    0    0    -1  
$EndComp
$Comp
L Joe_Library:BS170 Q2
U 1 1 60B13145
P 2900 4150
F 0 "Q2" H 2800 4350 50  0000 L CNN
F 1 "BS170" H 2700 3800 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 3100 4075 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BS170-D.PDF" H 2900 4150 50  0001 L CNN
	1    2900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3050 3000 3150
Connection ~ 3000 3150
Wire Wire Line
	3000 3150 3000 3950
$Comp
L Device:C C3
U 1 1 60B4A25E
P 2100 2900
F 0 "C3" H 2215 2946 50  0000 L CNN
F 1 "1n" H 2200 2800 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 2138 2750 50  0001 C CNN
F 3 "~" H 2100 2900 50  0001 C CNN
	1    2100 2900
	1    0    0    -1  
$EndComp
Connection ~ 2450 2400
$Comp
L Diode:BAT48RL D2
U 1 1 60B1425F
P 3600 3650
F 0 "D2" V 3550 3800 50  0000 C CNN
F 1 "BAT48RL" V 3650 3900 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P10.16mm_Horizontal" H 3600 3475 50  0001 C CNN
F 3 "www.st.com/resource/en/datasheet/bat48.pdf" H 3600 3650 50  0001 C CNN
	1    3600 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 4000 4250 4350
Connection ~ 4250 4350
Wire Wire Line
	4250 4350 4250 4550
Connection ~ 4250 3400
Wire Wire Line
	4250 3400 4250 3700
Wire Wire Line
	3600 3800 3600 3850
Wire Wire Line
	3600 3500 3600 3400
Wire Wire Line
	3600 4250 3600 4350
Wire Wire Line
	3600 3400 4250 3400
Wire Wire Line
	3600 4350 4250 4350
Wire Wire Line
	2100 2400 1800 2400
Wire Wire Line
	1800 2400 1800 2750
Connection ~ 2100 2400
Wire Wire Line
	2450 3950 2450 3150
Wire Wire Line
	2100 3050 2100 4150
Wire Wire Line
	1800 4650 1800 4800
$Comp
L power:GND #PWR01
U 1 1 606572F7
P 1800 4800
F 0 "#PWR01" H 1800 4550 50  0001 C CNN
F 1 "GND" H 1805 4627 50  0000 C CNN
F 2 "" H 1800 4800 50  0001 C CNN
F 3 "" H 1800 4800 50  0001 C CNN
	1    1800 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6065521D
P 1800 4500
F 0 "R2" H 1870 4546 50  0000 L CNN
F 1 "1M" H 1870 4455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1730 4500 50  0001 C CNN
F 3 "~" H 1800 4500 50  0001 C CNN
	1    1800 4500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q1
U 1 1 6064ACD5
P 2350 4150
F 0 "Q1" H 2500 4350 50  0000 L CNN
F 1 "2N7000" H 2100 3800 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2550 4075 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2350 4150 50  0001 L CNN
	1    2350 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3050 1800 4150
Wire Wire Line
	2100 4150 1800 4150
Connection ~ 2100 4150
Connection ~ 1800 4150
Wire Wire Line
	1800 4150 1800 4350
Text Notes 1900 6300 0    50   ~ 0
2.)  Mosfets vor Einlöten auf Vgth @Id=4uA checken (Vgth=Vgs=Vds):\n      Q1 Vgth = 1,7V (Vcc=2Vgth)\n      Q2 Vgth < 1,8V (Startbedingung)\n      Bei unseren Kits haben wir das bereits getan.
Text Notes 1900 6600 0    50   ~ 0
3.)  L1 selbst wickeln:\n      7Windungen Schaltdraht 0,5mm auf blauen Ringkern TDK N87 10x6x4  (AL=900nH/N²)\n      L=N²*AL Schaltung getestet für N=7(stabilere Vcc unter Last) bis N=11(beste Energieeffizienz)
$Comp
L power:GND #PWR012
U 1 1 60B535A1
P 3900 2850
F 0 "#PWR012" H 3900 2600 50  0001 C CNN
F 1 "GND" H 3905 2677 50  0000 C CNN
F 2 "" H 3900 2850 50  0001 C CNN
F 3 "" H 3900 2850 50  0001 C CNN
	1    3900 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2850 3600 3150
Wire Wire Line
	3600 3150 4500 3150
Wire Wire Line
	3000 3150 3300 3150
Wire Wire Line
	3700 2850 3900 2850
Text Notes 1900 6900 0    50   ~ 0
5.)  J1 und J2 frei lassen.
Text Notes 6550 3000 0    50   ~ 0
Vcc=3,5...3,7V
Text Notes 1900 7050 0    50   ~ 0
6.)  D2 und SC1 an Batteriepins löten
$Comp
L Joe_Library:SW_Push_standard_6x6_four_pins SW2
U 1 1 606774BC
P 8750 4650
F 0 "SW2" H 8750 5000 50  0000 C CNN
F 1 "SW_Push_standard_6x6_four_pins" H 8750 4900 50  0000 C CNN
F 2 "Joe_footprint_Library:SW_PUSH_6mm_H5mm_4pin" H 8750 4850 50  0001 C CNN
F 3 "https://docs.rs-online.com/17fc/0900766b8160dc5b.pdf" H 8750 4850 50  0001 C CNN
	1    8750 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2400 2450 2400
Wire Wire Line
	2100 4150 2150 4150
Text Notes 1900 6750 0    50   ~ 0
4.)  SW2 nur 2 diagonale Pins verlöten (egal welche) die anderen beiden Pins entfernen.
Text Notes 1900 5250 0    100  ~ 20
AUFBAUHINWEISE
Text Notes 1900 7200 0    50   ~ 0
7.)  U1 Bezeichnung zeigt zur Batterie. U2 Nase wie Platinenaufdruck. Schrift lesbar wie "RESET"
Text Notes 1900 5900 0    50   ~ 0
1.)  Flache Bauteile zuerst löten. Batteriehalter zuletzt. Mosfets, LEDs und ICs sind empfindlich gegen elektrostatische Aufladung.
Text Notes 1900 7500 0    50   ~ 0
9.)  R8 wird durch J1 und J2 gesteckt und gelötet. 
Text Notes 1900 5750 0    50   ~ 0
Die Solaranimals sind eine androide energieautarke Lebensform. (Sie wissen es nur noch nicht!) Sie können je nach Firmware mehrere Tage oder Wochen mit einem sonnengeladenen 1,2V NiMH-Akku überleben.\n\nDie Sonne lädt den Akku ständig nach. Wenn er doch mal leer ist, einfach den Vogel für einen Tag oder mehrere in die Sonne legen. Dabei geht es etwas schneller, wenn der Schiebeschalter ausgeschaltet ist (in Richtung SOLAR).\n\nAm wohlsten fühlen sich die Solarvögel in der Gruppe. Sie mögen es warm, sonnig und trocken.....
Text Notes 2450 1850 0    276  ~ 55
DIE SOLARVÖGEL VON KAZOOSH!
Text Notes 600  900  0    100  ~ 20
Bitspecht   Krachstelze   C Adler   Soundkönig   Blitzhuhn   Bugfink   Atmsel   Whilewachtel   Microchirp   Solderling   Bootkehlchen
Text Notes 1900 7350 0    50   ~ 0
8.)  C3 wird über R1 gelötet.
$Comp
L Device:R R8
U 1 1 60DBB7AF
P 3300 4500
F 0 "R8" H 3370 4546 50  0000 L CNN
F 1 "33k" H 3370 4455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3230 4500 50  0001 C CNN
F 3 "~" H 3300 4500 50  0001 C CNN
	1    3300 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 60DBCF38
P 3300 4800
F 0 "#PWR011" H 3300 4550 50  0001 C CNN
F 1 "GND" H 3305 4627 50  0000 C CNN
F 2 "" H 3300 4800 50  0001 C CNN
F 3 "" H 3300 4800 50  0001 C CNN
	1    3300 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3150 3300 4350
Wire Wire Line
	3300 4650 3300 4800
Connection ~ 3300 3150
Wire Wire Line
	3300 3150 3600 3150
Connection ~ 3600 3150
Wire Wire Line
	3000 2400 7250 2400
Text Notes 1850 7650 0    50   ~ 0
10.)  Zum Start Batterieschalter in Richtung PIEZO schieben und RESET drücken.
$EndSCHEMATC
