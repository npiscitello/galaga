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
P 8700 1150
F 0 "U3" H 8800 1400 50  0000 L CNN
F 1 "LM386" H 8750 1300 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 8800 1250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm386.pdf" H 8900 1350 50  0001 C CNN
	1    8700 1150
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U1
U 1 1 5BB68376
P 2050 1250
F 0 "U1" H 2050 1492 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 2050 1401 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2050 1450 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 2150 1000 50  0001 C CNN
	1    2050 1250
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
P 1200 2450
F 0 "#PWR02" H 1200 2200 50  0001 C CNN
F 1 "GND" H 1205 2277 50  0000 C CNN
F 2 "" H 1200 2450 50  0001 C CNN
F 3 "" H 1200 2450 50  0001 C CNN
	1    1200 2450
	1    0    0    -1  
$EndComp
Text GLabel 1400 750  2    50   Input ~ 0
+9V
Wire Wire Line
	1200 800  1200 850 
Text GLabel 2100 1700 2    50   Input ~ 0
DGND
Text GLabel 2400 1250 2    50   Input ~ 0
+3V3
Wire Wire Line
	8600 1450 8600 1500
Text GLabel 8400 1600 2    50   Input ~ 0
DGND
Text GLabel 8550 800  0    50   Input ~ 0
+9V
Wire Wire Line
	8550 800  8600 800 
Wire Wire Line
	8600 800  8600 850 
Wire Wire Line
	8400 1250 8350 1250
$Comp
L Device:CP C5
U 1 1 5BB76434
P 9200 1150
F 0 "C5" V 9455 1150 50  0000 C CNN
F 1 "250uF" V 9364 1150 50  0000 C CNN
F 2 "Capacitor_THT:CP_Axial_L20.0mm_D10.0mm_P26.00mm_Horizontal" H 9238 1000 50  0001 C CNN
F 3 "~" H 9200 1150 50  0001 C CNN
	1    9200 1150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9350 1150 9400 1150
Wire Wire Line
	9400 1250 9350 1250
Wire Wire Line
	9350 1250 9350 1500
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
P 9600 1150
F 0 "J2" H 9680 1142 50  0000 L CNN
F 1 "speaker_out" H 9680 1051 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 9600 1150 50  0001 C CNN
F 3 "~" H 9600 1150 50  0001 C CNN
	1    9600 1150
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
L Device:CP C1
U 1 1 5BBE6099
P 8100 1250
F 0 "C1" H 8200 1150 50  0000 C CNN
F 1 "10uF" H 8250 1350 50  0000 C CNN
F 2 "Capacitor_THT:CP_Axial_L10.0mm_D6.0mm_P15.00mm_Horizontal" H 8138 1100 50  0001 C CNN
F 3 "~" H 8100 1250 50  0001 C CNN
	1    8100 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5BBECF45
P 6250 2000
F 0 "R1" V 6600 2000 50  0001 R CNN
F 1 "3.9k" V 6250 2000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 6180 2000 50  0001 C CNN
F 3 "~" H 6250 2000 50  0001 C CNN
	1    6250 2000
	0    -1   -1   0   
$EndComp
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
Text HLabel 6100 2100 2    50   Input ~ 0
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
	6050 2000 6100 2000
Wire Wire Line
	8400 1050 8100 1050
Wire Wire Line
	8100 1050 8100 1100
Wire Wire Line
	8100 1400 8100 2000
Text Notes 6200 1600 0    50   ~ 0
With 3.3v max out of the m328, \nthis guarantees a maximum of \n2.62v into the amp. This would \nclip on full strength signals, but \nit allows us to take advantage of \nthe fact that audio is very rarely \nfull strength.
Wire Wire Line
	9000 1150 9050 1150
Wire Wire Line
	8600 1500 8750 1500
$Comp
L Isolator:LTV-817M U5
U 1 1 5D708174
P 2450 2150
F 0 "U5" H 2450 2475 50  0001 C CNN
F 1 "LTV-817M" H 2450 2384 50  0001 C CNN
F 2 "Package_DIP:DIP-4_W10.16mm" H 2450 1850 50  0001 C CNN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 2050 2450 50  0001 C CNN
	1    2450 2150
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q1
U 1 1 5D708462
P 1450 1950
F 0 "Q1" H 1655 1996 50  0001 L CNN
F 1 "2N7000" H 1655 1905 50  0001 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1650 1875 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 1450 1950 50  0001 L CNN
	1    1450 1950
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D7084DD
P 1350 1500
F 0 "R2" H 1420 1546 50  0000 L CNN
F 1 "10M" H 1420 1455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1280 1500 50  0001 C CNN
F 3 "~" H 1350 1500 50  0001 C CNN
	1    1350 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D70854B
P 2750 1650
F 0 "R3" H 2820 1696 50  0000 L CNN
F 1 "20K" H 2820 1605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2680 1650 50  0001 C CNN
F 3 "~" H 2750 1650 50  0001 C CNN
	1    2750 1650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5D7085A6
P 2750 1100
F 0 "SW1" V 2704 1248 50  0001 L CNN
F 1 "SW_Push" V 2795 1248 50  0001 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 2750 1300 50  0001 C CNN
F 3 "" H 2750 1300 50  0001 C CNN
	1    2750 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 2400 7650 2400
Connection ~ 8750 1500
Wire Wire Line
	8750 1500 9350 1500
Wire Wire Line
	8400 1600 8350 1600
Wire Wire Line
	8350 1250 8350 1600
Text GLabel 6400 3400 0    50   Input ~ 0
DGND
Wire Wire Line
	1100 950  1200 950 
Wire Wire Line
	1200 950  1200 2250
Wire Wire Line
	2400 1250 2350 1250
Connection ~ 1200 850 
Wire Wire Line
	2050 1700 2050 1550
Wire Wire Line
	2100 1700 2050 1700
Text GLabel 1250 2400 2    50   Input ~ 0
BGND
Wire Wire Line
	1250 2400 1200 2400
Connection ~ 1200 2400
Wire Wire Line
	1200 2400 1200 2450
Text GLabel 8800 1600 2    50   Input ~ 0
BGND
Wire Wire Line
	8800 1600 8750 1600
Wire Wire Line
	8750 1500 8750 1600
Wire Wire Line
	1350 2150 1350 2250
Connection ~ 1200 2250
Wire Wire Line
	1200 2250 1200 2400
Wire Wire Line
	1400 750  1350 750 
Wire Wire Line
	1350 750  1350 850 
Connection ~ 1350 850 
Wire Wire Line
	1750 1250 1600 1250
Wire Wire Line
	1600 1250 1600 850 
Wire Wire Line
	1600 850  1350 850 
Wire Wire Line
	2750 900  2750 850 
Wire Wire Line
	2750 850  1600 850 
Connection ~ 1600 850 
Wire Wire Line
	1200 850  1350 850 
Wire Wire Line
	2150 2050 2100 2050
Wire Wire Line
	2100 2050 2100 1950
Wire Wire Line
	2150 2250 1350 2250
Connection ~ 1350 2250
Text GLabel 2800 2250 2    50   Input ~ 0
DGND
Wire Wire Line
	2800 2250 2750 2250
Text GLabel 3150 2050 2    50   Input ~ 0
PWR_OFF
Wire Wire Line
	2750 2050 2800 2050
Connection ~ 2100 1950
Wire Wire Line
	2100 1950 1650 1950
Wire Wire Line
	2100 1950 2750 1950
Wire Wire Line
	1250 2250 1350 2250
Wire Wire Line
	1200 2250 1350 2250
$Comp
L Device:R R4
U 1 1 5D77529A
P 2950 2050
F 0 "R4" V 2743 2050 50  0000 C CNN
F 1 "180R" V 2834 2050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2880 2050 50  0001 C CNN
F 3 "~" H 2950 2050 50  0001 C CNN
	1    2950 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 2050 3150 2050
Text GLabel 6100 2500 2    50   Input ~ 0
PWR_OFF
Wire Wire Line
	6100 2500 6050 2500
Connection ~ 2050 1700
Wire Wire Line
	1350 1700 1350 1650
Wire Wire Line
	1350 1750 1350 1700
Connection ~ 1350 1700
Wire Wire Line
	1350 1700 2050 1700
Wire Wire Line
	2750 1800 2750 1950
Wire Wire Line
	1350 850  1350 1350
Wire Wire Line
	2750 1300 2750 1500
Wire Wire Line
	6400 2000 8100 2000
Wire Wire Line
	6100 2100 6050 2100
$EndSCHEMATC
