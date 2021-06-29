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
P 5900 3050
F 0 "D1" H 5750 2850 50  0000 C CNN
F 1 "BAT48RL" H 5650 2950 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P10.16mm_Horizontal" H 5900 2875 50  0001 C CNN
F 3 "www.st.com/resource/en/datasheet/bat48.pdf" H 5900 3050 50  0001 C CNN
	1    5900 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 606143C5
P 7450 4700
F 0 "#PWR09" H 7450 4450 50  0001 C CNN
F 1 "GND" H 7455 4527 50  0000 C CNN
F 2 "" H 7450 4700 50  0001 C CNN
F 3 "" H 7450 4700 50  0001 C CNN
	1    7450 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 60615262
P 5050 4700
F 0 "#PWR06" H 5050 4450 50  0001 C CNN
F 1 "GND" H 5055 4527 50  0000 C CNN
F 2 "" H 5050 4700 50  0001 C CNN
F 3 "" H 5050 4700 50  0001 C CNN
	1    5050 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3400 5050 4700
$Comp
L power:GND #PWR04
U 1 1 60625045
P 3800 4700
F 0 "#PWR04" H 3800 4450 50  0001 C CNN
F 1 "GND" H 3805 4527 50  0000 C CNN
F 2 "" H 3800 4700 50  0001 C CNN
F 3 "" H 3800 4700 50  0001 C CNN
	1    3800 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4450 7450 4700
$Comp
L MCU_Microchip_ATtiny:ATtiny85V-10PU U2
U 1 1 606058EB
P 7450 3850
F 0 "U2" H 7600 3150 50  0000 R CNN
F 1 "ATtiny85V-10PU" H 8100 3050 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7450 3850 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 7450 3850 50  0001 C CNN
	1    7450 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6064EFB8
P 3200 4700
F 0 "#PWR03" H 3200 4450 50  0001 C CNN
F 1 "GND" H 3205 4527 50  0000 C CNN
F 2 "" H 3200 4700 50  0001 C CNN
F 3 "" H 3200 4700 50  0001 C CNN
	1    3200 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6064F3E5
P 2650 4700
F 0 "#PWR02" H 2650 4450 50  0001 C CNN
F 1 "GND" H 2655 4527 50  0000 C CNN
F 2 "" H 2650 4700 50  0001 C CNN
F 3 "" H 2650 4700 50  0001 C CNN
	1    2650 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 4250 3200 4700
$Comp
L Device:R R4
U 1 1 606534F1
P 3200 2800
F 0 "R4" H 3270 2846 50  0000 L CNN
F 1 "220k" H 3270 2755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3130 2800 50  0001 C CNN
F 3 "~" H 3200 2800 50  0001 C CNN
	1    3200 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 606547AF
P 2650 2800
F 0 "R3" H 2720 2846 50  0000 L CNN
F 1 "510k" H 2720 2755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2580 2800 50  0001 C CNN
F 3 "~" H 2650 2800 50  0001 C CNN
	1    2650 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4250 2650 4700
Wire Wire Line
	2650 3050 2900 3050
Wire Wire Line
	2900 3050 2900 4050
Connection ~ 2650 3050
Wire Wire Line
	2650 3050 2650 2950
$Comp
L Device:L_Core_Ferrite L1
U 1 1 60662572
P 5650 2750
F 0 "L1" H 5750 2950 50  0000 L CNN
F 1 "47...130uH" H 5750 2850 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 5650 2750 50  0001 C CNN
F 3 "~" H 5650 2750 50  0001 C CNN
	1    5650 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 6067FB7F
P 4450 4700
F 0 "#PWR05" H 4450 4450 50  0001 C CNN
F 1 "GND" H 4455 4527 50  0000 C CNN
F 2 "" H 4450 4700 50  0001 C CNN
F 3 "" H 4450 4700 50  0001 C CNN
	1    4450 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6068F1F4
P 6550 4700
F 0 "#PWR08" H 6550 4450 50  0001 C CNN
F 1 "GND" H 6555 4527 50  0000 C CNN
F 2 "" H 6550 4700 50  0001 C CNN
F 3 "" H 6550 4700 50  0001 C CNN
	1    6550 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 6068FD92
P 6200 4700
F 0 "#PWR07" H 6200 4450 50  0001 C CNN
F 1 "GND" H 6205 4527 50  0000 C CNN
F 2 "" H 6200 4700 50  0001 C CNN
F 3 "" H 6200 4700 50  0001 C CNN
	1    6200 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3050 7450 3250
Wire Wire Line
	2650 2300 2650 2650
Wire Wire Line
	3200 2300 3200 2650
Wire Wire Line
	7450 2300 7450 3050
Connection ~ 7450 3050
$Comp
L Device:C C2
U 1 1 6069694D
P 6550 3650
F 0 "C2" H 6665 3696 50  0000 L CNN
F 1 "100nF" H 6600 3500 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 6588 3500 50  0001 C CNN
F 3 "~" H 6550 3650 50  0001 C CNN
	1    6550 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 606989F5
P 6200 3650
F 0 "C1" H 6318 3696 50  0000 L CNN
F 1 "220uF" H 6250 3500 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 6238 3500 50  0001 C CNN
F 3 "~" H 6200 3650 50  0001 C CNN
	1    6200 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3500 6200 3050
Wire Wire Line
	6200 3050 6550 3050
Wire Wire Line
	6550 3500 6550 3050
Connection ~ 6550 3050
Wire Wire Line
	6550 3050 7000 3050
Wire Wire Line
	6200 3800 6200 4700
Wire Wire Line
	6550 3800 6550 4700
Wire Wire Line
	3200 2300 2650 2300
$Comp
L Device:R R1
U 1 1 60654BA9
P 2000 2800
F 0 "R1" H 2050 2850 50  0000 L CNN
F 1 "1M" H 2050 2750 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2070 2709 50  0001 L CNN
F 3 "~" H 2000 2800 50  0001 C CNN
	1    2000 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2300 2300 2650
Connection ~ 3200 2300
Wire Wire Line
	5050 2550 5050 2750
$Comp
L Device:Speaker_Crystal LS1
U 1 1 606D2991
P 9900 3850
F 0 "LS1" H 9800 3550 50  0000 L CNN
F 1 "PIEZO SIGNAL" H 9800 3450 50  0000 L CNN
F 2 "" H 9865 3800 50  0001 C CNN
F 3 "~" H 9865 3800 50  0001 C CNN
	1    9900 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:LED LED1
U 1 1 606DAB8A
P 9400 3150
F 0 "LED1" H 9550 3100 50  0000 C CNN
F 1 "LED_GN" H 9400 3300 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 9400 3150 50  0001 C CNN
F 3 "https://docs.rs-online.com/0622/0900766b81302e6b.pdf" H 9400 3150 50  0001 C CNN
	1    9400 3150
	-1   0    0    1   
$EndComp
$Comp
L Device:LED LED2
U 1 1 606DDA34
P 9400 3450
F 0 "LED2" H 9550 3400 50  0000 C CNN
F 1 "LED_GN" H 9400 3600 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 9400 3450 50  0001 C CNN
F 3 "~" H 9400 3450 50  0001 C CNN
	1    9400 3450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 606DE168
P 8950 3150
F 0 "R5" V 8850 3150 50  0000 C CNN
F 1 "120" V 9050 3150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8880 3150 50  0001 C CNN
F 3 "~" H 8950 3150 50  0001 C CNN
	1    8950 3150
	0    1    1    0   
$EndComp
Connection ~ 5050 2550
Wire Wire Line
	4450 2550 5050 2550
$Comp
L Switch:SW_SPDT SW1
U 1 1 606FCCBB
P 4250 4550
F 0 "SW1" H 4600 4650 50  0000 C CNN
F 1 "SW_SPDT" H 4600 4550 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Slide_1P2T_CK_OS102011MS2Q" H 4250 4550 50  0001 C CNN
F 3 "~" H 4250 4550 50  0001 C CNN
	1    4250 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4650 4450 4700
Wire Wire Line
	4050 4550 3950 4550
Wire Wire Line
	3800 4550 3800 4700
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 607253BC
P 9600 3950
F 0 "J4" H 9550 3850 50  0000 L CNN
F 1 "Conn_01x01" H 9680 3901 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 9600 3950 50  0001 C CNN
F 3 "~" H 9600 3950 50  0001 C CNN
	1    9600 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 60726281
P 9600 3850
F 0 "J3" H 9550 3950 50  0000 L CNN
F 1 "Conn_01x01" H 9680 3801 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 9600 3850 50  0001 C CNN
F 3 "~" H 9600 3850 50  0001 C CNN
	1    9600 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 3150 9650 3450
Wire Wire Line
	9550 3150 9650 3150
Wire Wire Line
	9550 3450 9650 3450
Connection ~ 9650 3450
Wire Wire Line
	9650 3450 9650 3650
Wire Wire Line
	9100 3150 9250 3150
Wire Wire Line
	9100 3450 9250 3450
Wire Wire Line
	8050 4050 8150 4050
Wire Wire Line
	5650 2550 5650 2600
Wire Wire Line
	5650 2900 5650 3050
Wire Wire Line
	5050 2550 5650 2550
Wire Wire Line
	5400 3050 5650 3050
Wire Wire Line
	5750 3050 5650 3050
Connection ~ 5650 3050
Wire Wire Line
	6050 3050 6200 3050
Connection ~ 6200 3050
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6076DD1A
P 5050 2550
F 0 "#FLG0101" H 5050 2625 50  0001 C CNN
F 1 "PWR_FLAG" H 5050 2723 50  0001 C CNN
F 2 "" H 5050 2550 50  0001 C CNN
F 3 "~" H 5050 2550 50  0001 C CNN
	1    5050 2550
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6076F71F
P 3950 4550
F 0 "#FLG0102" H 3950 4625 50  0001 C CNN
F 1 "PWR_FLAG" H 4000 4450 50  0001 C CNN
F 2 "" H 3950 4550 50  0001 C CNN
F 3 "~" H 3950 4550 50  0001 C CNN
	1    3950 4550
	1    0    0    -1  
$EndComp
Connection ~ 3950 4550
Wire Wire Line
	3950 4550 3800 4550
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 607734E9
P 7000 3050
F 0 "#FLG0103" H 7000 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 7000 3223 50  0001 C CNN
F 2 "" H 7000 3050 50  0001 C CNN
F 3 "~" H 7000 3050 50  0001 C CNN
	1    7000 3050
	1    0    0    -1  
$EndComp
Connection ~ 7000 3050
Wire Wire Line
	7000 3050 7450 3050
Wire Wire Line
	8800 3150 8500 3150
Wire Wire Line
	8500 3150 8500 3550
Wire Wire Line
	8500 3550 8050 3550
$Comp
L Device:R R6
U 1 1 607F9A71
P 8950 3450
F 0 "R6" V 8850 3450 50  0000 C CNN
F 1 "120" V 9050 3450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8880 3450 50  0001 C CNN
F 3 "~" H 8950 3450 50  0001 C CNN
	1    8950 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 607F9D26
P 8950 3850
F 0 "R7" V 8850 3850 50  0000 C CNN
F 1 "330" V 9150 3850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8880 3850 50  0001 C CNN
F 3 "~" H 8950 3850 50  0001 C CNN
	1    8950 3850
	0    1    1    0   
$EndComp
$Comp
L Device:Solar_Cells SC1
U 1 1 6060DDD4
P 3800 3950
F 0 "SC1" H 3908 3996 50  0000 L CNN
F 1 "Solar Cell 2,4V 50mA" H 3908 3905 50  0000 L CNN
F 2 "" V 3800 4010 50  0001 C CNN
F 3 "~" V 3800 4010 50  0001 C CNN
	1    3800 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 60716B0F
P 3800 2550
F 0 "J1" V 3800 2650 50  0000 L CNN
F 1 "Conn_01x01" H 3880 2501 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 3800 2550 50  0001 C CNN
F 3 "~" H 3800 2550 50  0001 C CNN
	1    3800 2550
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 60720F2F
P 3900 2550
F 0 "J2" V 3900 2350 50  0000 L CNN
F 1 "Conn_01x01" H 3980 2501 50  0001 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x01_D0.9mm_OD2.1mm_Relief" H 3900 2550 50  0001 C CNN
F 3 "~" H 3900 2550 50  0001 C CNN
	1    3900 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 3850 9700 3850
Wire Wire Line
	9400 3950 9700 3950
Wire Wire Line
	8050 3650 8600 3650
Wire Wire Line
	8600 3650 8600 3450
Wire Wire Line
	8600 3450 8800 3450
Wire Wire Line
	8700 3750 8700 3650
Wire Wire Line
	8700 3650 9650 3650
Wire Wire Line
	8050 3750 8700 3750
$Comp
L power:GND #PWR010
U 1 1 6065D07E
P 9600 4700
F 0 "#PWR010" H 9600 4450 50  0001 C CNN
F 1 "GND" H 9605 4527 50  0000 C CNN
F 2 "" H 9600 4700 50  0001 C CNN
F 3 "" H 9600 4700 50  0001 C CNN
	1    9600 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4450 8650 4450
Wire Wire Line
	9400 4650 9250 4650
Wire Wire Line
	9600 4700 9600 4550
Wire Wire Line
	9600 4550 9400 4550
Wire Wire Line
	9400 4550 9400 4650
Wire Wire Line
	8150 4550 8500 4550
Wire Wire Line
	8150 4050 8150 4550
Wire Wire Line
	8500 4550 8500 4450
Wire Wire Line
	4450 2550 4450 3300
$Comp
L Joe_Library:NiMH_1,25V_600mAh BT1
U 1 1 606BEBD1
P 4450 3800
F 0 "BT1" H 4600 3900 50  0000 L CNN
F 1 "NiMH 1,25V 600mAh" H 4600 3800 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_2466_1xAAA" V 4450 3860 50  0001 C CNN
F 3 "~" V 4450 3860 50  0001 C CNN
	1    4450 3800
	1    0    0    -1  
$EndComp
Connection ~ 9400 3950
Wire Wire Line
	8050 3850 8800 3850
Wire Wire Line
	9100 3850 9400 3850
Connection ~ 9400 3850
Wire Wire Line
	8050 3950 9400 3950
$Comp
L Joe_Library:QX5252F U1
U 1 1 60B0E9AA
P 5050 2800
F 0 "U1" H 5250 2950 50  0000 L CNN
F 1 "QX5252F" H 5250 2850 50  0000 L CNN
F 2 "" H 5050 2800 50  0001 C CNN
F 3 "https://skootsone.yolasite.com/resources/QX5252.pdf" H 5050 2800 50  0001 C CNN
	1    5050 2800
	1    0    0    -1  
$EndComp
$Comp
L Joe_Library:BS170 Q2
U 1 1 60B13145
P 3100 4050
F 0 "Q2" H 3000 4250 50  0000 L CNN
F 1 "BS170" H 2900 3700 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 3300 3975 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BS170-D.PDF" H 3100 4050 50  0001 L CNN
	1    3100 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2950 3200 3050
Connection ~ 3200 3050
Wire Wire Line
	3200 3050 3200 3850
$Comp
L Device:C C3
U 1 1 60B4A25E
P 2300 2800
F 0 "C3" H 2415 2846 50  0000 L CNN
F 1 "1n" H 2400 2700 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 2338 2650 50  0001 C CNN
F 3 "~" H 2300 2800 50  0001 C CNN
	1    2300 2800
	1    0    0    -1  
$EndComp
Connection ~ 2650 2300
$Comp
L Diode:BAT48RL D2
U 1 1 60B1425F
P 3800 3550
F 0 "D2" V 3750 3700 50  0000 C CNN
F 1 "BAT48RL" V 3850 3800 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P10.16mm_Horizontal" H 3800 3375 50  0001 C CNN
F 3 "www.st.com/resource/en/datasheet/bat48.pdf" H 3800 3550 50  0001 C CNN
	1    3800 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 3900 4450 4250
Connection ~ 4450 4250
Wire Wire Line
	4450 4250 4450 4450
Connection ~ 4450 3300
Wire Wire Line
	4450 3300 4450 3600
Wire Wire Line
	3800 3700 3800 3750
Wire Wire Line
	3800 3400 3800 3300
Wire Wire Line
	3800 4150 3800 4250
Wire Wire Line
	3800 3300 4450 3300
Wire Wire Line
	3800 4250 4450 4250
Wire Wire Line
	2300 2300 2000 2300
Wire Wire Line
	2000 2300 2000 2650
Connection ~ 2300 2300
Wire Wire Line
	2650 3850 2650 3050
Wire Wire Line
	2300 2950 2300 4050
Wire Wire Line
	2000 4550 2000 4700
$Comp
L power:GND #PWR01
U 1 1 606572F7
P 2000 4700
F 0 "#PWR01" H 2000 4450 50  0001 C CNN
F 1 "GND" H 2005 4527 50  0000 C CNN
F 2 "" H 2000 4700 50  0001 C CNN
F 3 "" H 2000 4700 50  0001 C CNN
	1    2000 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6065521D
P 2000 4400
F 0 "R2" H 2070 4446 50  0000 L CNN
F 1 "1M" H 2070 4355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1930 4400 50  0001 C CNN
F 3 "~" H 2000 4400 50  0001 C CNN
	1    2000 4400
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q1
U 1 1 6064ACD5
P 2550 4050
F 0 "Q1" H 2700 4250 50  0000 L CNN
F 1 "2N7000" H 2300 3700 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2750 3975 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2550 4050 50  0001 L CNN
	1    2550 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2950 2000 4050
Wire Wire Line
	2300 4050 2000 4050
Connection ~ 2300 4050
Connection ~ 2000 4050
Wire Wire Line
	2000 4050 2000 4250
Text Notes 1900 6300 0    50   ~ 0
2.)  Mosfets vor Einlöten auf Vgth @Id=4uA checken (Vgth=Vgs=Vds):\n      Q1 Vgth = 1,7V (Vcc=2Vgth)\n      Q2 Vgth < 1,8V (Startbedingung)\n      Bei unseren Kits haben wir das bereits getan.
Text Notes 1900 6600 0    50   ~ 0
3.)  L1 selbst wickeln:\n      7Windungen Schaltdraht 0,5mm auf blauen Ringkern TDK N87 10x6x4  (AL=900nH/N²)\n      L=N²*AL Schaltung getestet für N=7(stabilere Vcc unter Last) bis N=11(beste Energieeffizienz)
$Comp
L power:GND #PWR012
U 1 1 60B535A1
P 4100 2750
F 0 "#PWR012" H 4100 2500 50  0001 C CNN
F 1 "GND" H 4105 2577 50  0000 C CNN
F 2 "" H 4100 2750 50  0001 C CNN
F 3 "" H 4100 2750 50  0001 C CNN
	1    4100 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2750 3800 3050
Wire Wire Line
	3800 3050 4700 3050
Wire Wire Line
	3200 3050 3500 3050
Wire Wire Line
	3900 2750 4100 2750
Text Notes 1900 6900 0    50   ~ 0
5.)  J1 und J2 frei lassen.
Text Notes 6750 2900 0    50   ~ 0
Vcc=3,5...3,7V
Text Notes 1900 7050 0    50   ~ 0
6.)  D2 und SC1 an Batteriepins löten
$Comp
L Joe_Library:SW_Push_standard_6x6_four_pins SW2
U 1 1 606774BC
P 8950 4550
F 0 "SW2" H 8950 4900 50  0000 C CNN
F 1 "SW_Push_standard_6x6_four_pins" H 8950 4800 50  0000 C CNN
F 2 "Joe_footprint_Library:SW_PUSH_6mm_H5mm_4pin" H 8950 4750 50  0001 C CNN
F 3 "https://docs.rs-online.com/17fc/0900766b8160dc5b.pdf" H 8950 4750 50  0001 C CNN
	1    8950 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2300 2650 2300
Wire Wire Line
	2300 4050 2350 4050
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
P 3500 4400
F 0 "R8" H 3570 4446 50  0000 L CNN
F 1 "33k" H 3570 4355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3430 4400 50  0001 C CNN
F 3 "~" H 3500 4400 50  0001 C CNN
	1    3500 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 60DBCF38
P 3500 4700
F 0 "#PWR011" H 3500 4450 50  0001 C CNN
F 1 "GND" H 3505 4527 50  0000 C CNN
F 2 "" H 3500 4700 50  0001 C CNN
F 3 "" H 3500 4700 50  0001 C CNN
	1    3500 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3050 3500 4250
Wire Wire Line
	3500 4550 3500 4700
Connection ~ 3500 3050
Wire Wire Line
	3500 3050 3800 3050
Connection ~ 3800 3050
Wire Wire Line
	3200 2300 7450 2300
Text Notes 1850 7650 0    50   ~ 0
10.)  Zum Start Batterieschalter in Richtung PIEZO schieben und RESET drücken.
$EndSCHEMATC
