EESchema Schematic File Version 4
LIBS:galaga-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Amplifier_Audio:LM386 U3
U 1 1 5BB681DC
P 7500 1200
F 0 "U3" H 7600 1450 50  0000 L CNN
F 1 "LM386" H 7550 1350 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7600 1300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm386.pdf" H 7700 1400 50  0001 C CNN
	1    7500 1200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U1
U 1 1 5BB68376
P 1900 1200
F 0 "U1" H 1900 1442 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 1900 1351 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1900 1400 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 2000 950 50  0001 C CNN
	1    1900 1200
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU U2
U 1 1 5BB68499
P 5450 3100
F 0 "U2" H 4809 3146 50  0000 R CNN
F 1 "ATmega328P-PU" H 4809 3055 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 5450 3100 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 5450 3100 50  0001 C CNN
	1    5450 3100
	1    0    0    -1  
$EndComp
Entry Wire Line
	-3300 -1150 -3200 -1050
$Comp
L custom:BOB-00544 U4
U 1 1 5BB68AD9
P 8350 2900
F 0 "U4" H 8381 3425 50  0000 C CNN
F 1 "BOB-00544" H 8381 3334 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 8300 3900 50  0001 C CNN
F 3 "" H 8300 3900 50  0001 C CNN
	1    8350 2900
	-1   0    0    1   
$EndComp
$Comp
L power:+9V #PWR01
U 1 1 5BB68BC8
P 1200 800
F 0 "#PWR01" H 1200 650 50  0001 C CNN
F 1 "+9V" H 1215 973 50  0000 C CNN
F 2 "" H 1200 800 50  0001 C CNN
F 3 "" H 1200 800 50  0001 C CNN
	1    1200 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5BB68C10
P 1200 2750
F 0 "#PWR02" H 1200 2500 50  0001 C CNN
F 1 "GND" H 1205 2577 50  0000 C CNN
F 2 "" H 1200 2750 50  0001 C CNN
F 3 "" H 1200 2750 50  0001 C CNN
	1    1200 2750
	1    0    0    -1  
$EndComp
Text GLabel 1400 750  2    50   Input ~ 0
+9V
Wire Wire Line
	1200 800  1200 850 
Text GLabel 1950 1550 2    50   Input ~ 0
DGND
Text GLabel 2250 1200 2    50   Input ~ 0
+3V3
Wire Wire Line
	7400 1500 7400 1550
Text GLabel 7200 1650 2    50   Input ~ 0
DGND
Text GLabel 7350 850  0    50   Input ~ 0
+9V
Wire Wire Line
	7350 850  7400 850 
Wire Wire Line
	7400 850  7400 900 
Wire Wire Line
	7200 1300 7150 1300
Wire Wire Line
	9000 1200 9050 1200
Wire Wire Line
	9050 1300 9000 1300
Wire Wire Line
	9000 1300 9000 1550
Text GLabel 5400 1550 0    50   Input ~ 0
+3V3
Wire Wire Line
	5400 1550 5450 1550
Wire Wire Line
	5450 1550 5450 1600
Text GLabel 5400 4650 0    50   Input ~ 0
DGND
Wire Wire Line
	5450 4600 5450 4650
Wire Wire Line
	5450 4650 5400 4650
Wire Wire Line
	7650 2400 7650 2900
Wire Wire Line
	7650 2900 8100 2900
Wire Wire Line
	8100 3100 7550 3100
Wire Wire Line
	7550 3100 7550 2300
Wire Wire Line
	7550 2300 6050 2300
Wire Wire Line
	8100 2700 7750 2700
Wire Wire Line
	7750 2700 7750 2200
Wire Wire Line
	7750 2200 6050 2200
Text GLabel 8050 3000 0    50   Input ~ 0
DGND
Wire Wire Line
	8050 3000 8100 3000
Text GLabel 8050 2800 0    50   Input ~ 0
+3V3
Wire Wire Line
	8050 2800 8100 2800
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5BBBC1CA
P 9250 1200
F 0 "J2" H 9330 1192 50  0000 L CNN
F 1 "speaker_out" H 9330 1101 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 9250 1200 50  0001 C CNN
F 3 "~" H 9250 1200 50  0001 C CNN
	1    9250 1200
	1    0    0    -1  
$EndComp
Text GLabel 6400 3500 0    50   Input ~ 0
DGND
Text GLabel 6400 3600 0    50   Input ~ 0
DGND
Text Notes 6650 2850 0    50   ~ 0
blaster0 (bl0)
Text Notes 6650 2950 0    50   ~ 0
blaster1 (bl1)
Text Notes 6650 3150 0    50   ~ 0
blaster2 (bl2)
Text Notes 6650 3250 0    50   ~ 0
blaster3 (bl3)
Text Notes 6650 3050 0    50   ~ 0
booster0 (bs0)
Text Notes 6650 3350 0    50   ~ 0
booster1 (bs1)
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5BC32DBF
P 6600 2900
F 0 "J1" H 7250 3000 50  0000 L CNN
F 1 "led_a" H 7250 2900 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 6600 2900 50  0001 C CNN
F 3 "~" H 6600 2900 50  0001 C CNN
	1    6600 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J3
U 1 1 5BC32E07
P 6600 3200
F 0 "J3" H 7250 3250 50  0000 L CNN
F 1 "led_b" H 7250 3150 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 6600 3200 50  0001 C CNN
F 3 "~" H 6600 3200 50  0001 C CNN
	1    6600 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 5BC339F5
P 900 850
F 0 "J5" H 820 1067 50  0000 C CNN
F 1 "pwr_in" H 820 976 50  0000 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 900 850 50  0001 C CNN
F 3 "~" H 900 850 50  0001 C CNN
	1    900  850 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1200 850  1100 850 
Wire Wire Line
	6050 2800 6400 2800
Wire Wire Line
	6050 2900 6400 2900
Wire Wire Line
	6050 3000 6400 3000
Wire Wire Line
	6050 3100 6400 3100
Wire Wire Line
	6050 3200 6400 3200
Wire Wire Line
	6050 3300 6400 3300
Text HLabel 8050 2600 0    50   Input ~ 0
sd_cs
Wire Wire Line
	8050 2600 8100 2600
Text HLabel 6100 2600 2    50   Input ~ 0
sd_cs
Text Label 7200 2200 0    50   ~ 0
sd_di
Text Label 7200 2400 0    50   ~ 0
sd_sck
Text Label 7200 2300 0    50   ~ 0
sd_do
Text Label 6150 2800 0    50   ~ 0
led_bl0
Text Label 6150 2900 0    50   ~ 0
led_bl1
Text Label 6150 3000 0    50   ~ 0
led_bs0
Text Label 6150 3100 0    50   ~ 0
led_bl2
Text Label 6150 3200 0    50   ~ 0
led_bl3
Text Label 6150 3300 0    50   ~ 0
led_bs1
$Comp
L Connector:Screw_Terminal_01x03 J4
U 1 1 5BC32E3D
P 6600 3500
F 0 "J4" H 7250 3550 50  0000 L CNN
F 1 "led_c" H 7250 3450 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 6600 3500 50  0001 C CNN
F 3 "~" H 6600 3500 50  0001 C CNN
	1    6600 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1100 6200 1100
$Comp
L Isolator:LTV-817M U5
U 1 1 5D708174
P 2750 2300
F 0 "U5" H 2750 2625 50  0001 C CNN
F 1 "LTV-817M" H 2750 2534 50  0001 C CNN
F 2 "Package_DIP:DIP-4_W10.16mm" H 2750 2000 50  0001 C CNN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 2350 2600 50  0001 C CNN
	1    2750 2300
	0    1    -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5D7084DD
P 1350 1500
F 0 "R2" H 1420 1546 50  0000 L CNN
F 1 "10k" H 1420 1455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1280 1500 50  0001 C CNN
F 3 "~" H 1350 1500 50  0001 C CNN
	1    1350 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D70854B
P 1700 2250
F 0 "R3" H 1770 2296 50  0000 L CNN
F 1 "10K" H 1770 2205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1630 2250 50  0001 C CNN
F 3 "~" H 1700 2250 50  0001 C CNN
	1    1700 2250
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5D7085A6
P 2650 1100
F 0 "SW1" V 2604 1248 50  0001 L CNN
F 1 "SW_Push" V 2695 1248 50  0001 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 2650 1300 50  0001 C CNN
F 3 "" H 2650 1300 50  0001 C CNN
	1    2650 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 2400 7650 2400
Wire Wire Line
	7200 1650 7150 1650
Wire Wire Line
	7150 1300 7150 1550
Text GLabel 6400 3400 0    50   Input ~ 0
DGND
Wire Wire Line
	1100 950  1200 950 
Wire Wire Line
	1200 950  1200 2500
Connection ~ 1200 850 
Wire Wire Line
	1350 2150 1350 2500
Connection ~ 1200 2500
Wire Wire Line
	1400 750  1350 750 
Wire Wire Line
	1350 750  1350 850 
Connection ~ 1350 850 
Wire Wire Line
	2650 900  2650 850 
Wire Wire Line
	1200 850  1350 850 
Connection ~ 1350 2500
Text GLabel 2650 2650 3    50   Input ~ 0
DGND
Text GLabel 2850 3000 3    50   Input ~ 0
PWR_OFF
$Comp
L Device:R R4
U 1 1 5D77529A
P 2850 2800
F 0 "R4" V 2643 2800 50  0000 C CNN
F 1 "180R" V 2734 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2780 2800 50  0001 C CNN
F 3 "~" H 2850 2800 50  0001 C CNN
	1    2850 2800
	-1   0    0    1   
$EndComp
Text GLabel 6100 2500 2    50   Input ~ 0
PWR_OFF
Wire Wire Line
	6100 2500 6050 2500
Wire Wire Line
	1350 850  1350 1200
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J6
U 1 1 5D757B8F
P 9400 2400
F 0 "J6" H 9450 2717 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 9450 2626 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 9400 2400 50  0001 C CNN
F 3 "~" H 9400 2400 50  0001 C CNN
	1    9400 2400
	1    0    0    -1  
$EndComp
Connection ~ 7550 2300
Connection ~ 7650 2400
Wire Wire Line
	6050 3400 6100 3400
Wire Wire Line
	6100 3400 6100 3700
Wire Wire Line
	6100 3700 8950 3700
Wire Wire Line
	8950 3700 8950 2500
Wire Wire Line
	8950 2500 9200 2500
Text GLabel 9800 2300 2    50   Input ~ 0
+3V3
Wire Wire Line
	9800 2300 9700 2300
Text GLabel 9800 2500 2    50   Input ~ 0
DGND
Wire Wire Line
	9800 2500 9700 2500
Wire Wire Line
	7650 2400 9200 2400
Wire Wire Line
	7550 2300 9200 2300
Wire Wire Line
	7750 2200 8900 2200
Wire Wire Line
	8900 2200 8900 1950
Wire Wire Line
	8900 1950 10150 1950
Wire Wire Line
	10150 1950 10150 2400
Wire Wire Line
	10150 2400 9700 2400
Connection ~ 7750 2200
Wire Wire Line
	6050 2000 6200 2000
Wire Wire Line
	6100 2600 6050 2600
$Comp
L Device:C C3
U 1 1 5E13D4E4
P 8100 1050
F 0 "C3" V 7848 1050 50  0000 C CNN
F 1 "0.05uF" V 7939 1050 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D12.0mm_W4.4mm_P7.75mm" H 8138 900 50  0001 C CNN
F 3 "~" H 8100 1050 50  0001 C CNN
	1    8100 1050
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5E13D5AB
P 8450 1050
F 0 "R1" V 8243 1050 50  0000 C CNN
F 1 "10R" V 8334 1050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 8380 1050 50  0001 C CNN
F 3 "~" H 8450 1050 50  0001 C CNN
	1    8450 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 1050 8300 1050
Wire Wire Line
	7950 1050 7900 1050
Wire Wire Line
	7900 1050 7900 1200
Connection ~ 7900 1200
Wire Wire Line
	7900 1200 8700 1200
Wire Wire Line
	7800 1200 7900 1200
Wire Wire Line
	8600 1050 8650 1050
Wire Wire Line
	8650 1050 8650 1550
Connection ~ 8650 1550
Wire Wire Line
	8650 1550 9000 1550
$Comp
L Device:CP C2
U 1 1 5E1771D5
P 6750 1350
F 0 "C2" V 7005 1350 50  0000 C CNN
F 1 "330uF" V 6914 1350 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 6788 1200 50  0001 C CNN
F 3 "~" H 6750 1350 50  0001 C CNN
	1    6750 1350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6750 1200 6750 750 
Wire Wire Line
	6750 750  7400 750 
Wire Wire Line
	7400 750  7400 850 
Connection ~ 7400 850 
$Comp
L Device:CP C4
U 1 1 5E17DFAC
P 8850 1200
F 0 "C4" V 9105 1200 50  0000 C CNN
F 1 "330uF" V 9014 1200 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 8888 1050 50  0001 C CNN
F 3 "~" H 8850 1200 50  0001 C CNN
	1    8850 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6200 1100 6200 2000
$Comp
L Transistor_FET:IRF540N Q1
U 1 1 5E19A72B
P 1450 1950
F 0 "Q1" H 1656 1996 50  0000 L CNN
F 1 "IRF540N" H 1656 1905 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1700 1875 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 1450 1950 50  0001 L CNN
	1    1450 1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2250 1200 2200 1200
Wire Wire Line
	1350 1650 1350 1700
Wire Wire Line
	1950 1550 1900 1550
Wire Wire Line
	1900 1550 1900 1500
Wire Wire Line
	2850 2950 2850 3000
Wire Wire Line
	2850 2600 2850 2650
Wire Wire Line
	2650 2650 2650 2600
Wire Wire Line
	1250 2500 1350 2500
Wire Wire Line
	1200 2500 1350 2500
Wire Wire Line
	1700 2100 1700 1950
Wire Wire Line
	1700 1950 1650 1950
Wire Wire Line
	1700 2400 1700 2500
Wire Wire Line
	1700 2500 1350 2500
Wire Wire Line
	1900 1550 1900 1700
Wire Wire Line
	1900 1700 1350 1700
Connection ~ 1900 1550
Connection ~ 1350 1700
Wire Wire Line
	1350 1700 1350 1750
Wire Wire Line
	1600 1200 1350 1200
Connection ~ 1350 1200
Wire Wire Line
	1350 1200 1350 1350
Connection ~ 1700 1950
Wire Wire Line
	1350 850  2650 850 
Text Notes 2650 3600 0    50   ~ 0
HIGH = ON\nLOW = OFF
Connection ~ 2650 850 
Wire Wire Line
	2650 1300 2650 1950
Wire Wire Line
	2650 1950 1700 1950
Wire Wire Line
	2650 2000 2650 1950
Connection ~ 2650 1950
Wire Wire Line
	2850 2000 2850 850 
Wire Wire Line
	2650 850  2850 850 
Text Notes 6550 2600 0    50   ~ 0
HIGH = ON\nLOW = OFF
Wire Wire Line
	7400 1550 7150 1550
Connection ~ 7150 1550
Wire Wire Line
	7150 1550 7150 1650
Wire Wire Line
	7150 1550 6750 1550
Wire Wire Line
	6750 1550 6750 1500
Connection ~ 7400 1550
Wire Wire Line
	7400 1550 8650 1550
Wire Wire Line
	1200 2500 1200 2750
Wire Wire Line
	5450 1550 5550 1550
Wire Wire Line
	5550 1550 5550 1600
Connection ~ 5450 1550
$EndSCHEMATC
