EESchema Schematic File Version 4
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
P 5300 1400
F 0 "U3" H 5400 1650 50  0000 L CNN
F 1 "LM386" H 5350 1550 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5400 1500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm386.pdf" H 5500 1600 50  0001 C CNN
	1    5300 1400
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U1
U 1 1 5BB68376
P 1900 1050
F 0 "U1" H 1900 1292 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 1900 1201 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1900 1250 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 2000 800 50  0001 C CNN
	1    1900 1050
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU U2
U 1 1 5BB68499
P 2050 3350
F 0 "U2" H 1409 3396 50  0000 R CNN
F 1 "ATmega328P-PU" H 1409 3305 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 2050 3350 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 2050 3350 50  0001 C CNN
	1    2050 3350
	1    0    0    -1  
$EndComp
Entry Wire Line
	-3300 -1150 -3200 -1050
$Comp
L custom:BOB-00544 U4
U 1 1 5BB68AD9
P 4950 3150
F 0 "U4" H 4981 3675 50  0000 C CNN
F 1 "BOB-00544" H 4981 3584 50  0000 C CNN
F 2 "custom:bob-00544" H 4900 4150 50  0001 C CNN
F 3 "" H 4900 4150 50  0001 C CNN
	1    4950 3150
	-1   0    0    1   
$EndComp
$Comp
L power:+9V #PWR01
U 1 1 5BB68BC8
P 1350 1000
F 0 "#PWR01" H 1350 850 50  0001 C CNN
F 1 "+9V" H 1365 1173 50  0000 C CNN
F 2 "" H 1350 1000 50  0001 C CNN
F 3 "" H 1350 1000 50  0001 C CNN
	1    1350 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5BB68C10
P 1350 1550
F 0 "#PWR02" H 1350 1300 50  0001 C CNN
F 1 "GND" H 1355 1377 50  0000 C CNN
F 2 "" H 1350 1550 50  0001 C CNN
F 3 "" H 1350 1550 50  0001 C CNN
	1    1350 1550
	1    0    0    -1  
$EndComp
Text GLabel 1400 1150 2    50   Input ~ 0
+9V
Wire Wire Line
	1350 1000 1350 1050
Wire Wire Line
	1350 1150 1400 1150
Text GLabel 1400 1500 2    50   Input ~ 0
GND
Wire Wire Line
	1350 1550 1350 1500
Wire Wire Line
	1350 1500 1400 1500
Wire Wire Line
	1600 1050 1350 1050
Connection ~ 1350 1050
Wire Wire Line
	1350 1050 1350 1150
Wire Wire Line
	1900 1350 1900 1400
Wire Wire Line
	1900 1400 1350 1400
Wire Wire Line
	1350 1400 1350 1500
Connection ~ 1350 1500
Text GLabel 2250 1050 2    50   Input ~ 0
+3V3
Wire Wire Line
	2200 1050 2250 1050
Wire Wire Line
	5200 1700 5200 1750
Text GLabel 5150 1850 0    50   Input ~ 0
GND
Text GLabel 5150 1050 0    50   Input ~ 0
+9V
Wire Wire Line
	5150 1050 5200 1050
Wire Wire Line
	5200 1050 5200 1100
Wire Wire Line
	5000 1500 4950 1500
Wire Wire Line
	4950 1500 4950 1750
Wire Wire Line
	4950 1750 5200 1750
$Comp
L Device:CP C5
U 1 1 5BB76434
P 5800 1400
F 0 "C5" V 6055 1400 50  0000 C CNN
F 1 "250uF" V 5964 1400 50  0000 C CNN
F 2 "Capacitor_THT:CP_Axial_L20.0mm_D10.0mm_P26.00mm_Horizontal" H 5838 1250 50  0001 C CNN
F 3 "~" H 5800 1400 50  0001 C CNN
	1    5800 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5950 1400 6000 1400
Wire Wire Line
	6000 1500 5950 1500
Wire Wire Line
	5950 1500 5950 1750
Connection ~ 5200 1750
Text GLabel 2000 1800 0    50   Input ~ 0
+3V3
Wire Wire Line
	2000 1800 2050 1800
Wire Wire Line
	2050 1800 2050 1850
Text GLabel 2000 4900 0    50   Input ~ 0
GND
Wire Wire Line
	2050 4850 2050 4900
Wire Wire Line
	2050 4900 2000 4900
Wire Wire Line
	2650 2650 4250 2650
Wire Wire Line
	4250 2650 4250 3150
Wire Wire Line
	4250 3150 4700 3150
Wire Wire Line
	4700 3350 4150 3350
Wire Wire Line
	4150 3350 4150 2550
Wire Wire Line
	4150 2550 2650 2550
Wire Wire Line
	4700 2950 4350 2950
Wire Wire Line
	4350 2950 4350 2450
Wire Wire Line
	4350 2450 2650 2450
Wire Wire Line
	4150 3450 4700 3450
Text GLabel 4650 3250 0    50   Input ~ 0
GND
Wire Wire Line
	4650 3250 4700 3250
Text GLabel 4650 3050 0    50   Input ~ 0
+3V3
Wire Wire Line
	4650 3050 4700 3050
Wire Wire Line
	5200 1750 5200 1850
Wire Wire Line
	5200 1850 5150 1850
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5BBBC1CA
P 6200 1400
F 0 "J2" H 6280 1392 50  0000 L CNN
F 1 "speaker_out" H 6280 1301 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 6200 1400 50  0001 C CNN
F 3 "~" H 6200 1400 50  0001 C CNN
	1    6200 1400
	1    0    0    -1  
$EndComp
Text GLabel 3000 3750 0    50   Input ~ 0
GND
Text GLabel 3000 3850 0    50   Input ~ 0
GND
Text Notes 3250 3100 0    50   ~ 0
blaster0 (bl0)
Text Notes 3250 3200 0    50   ~ 0
blaster1 (bl1)
Text Notes 3250 3400 0    50   ~ 0
blaster2 (bl2)
Text Notes 3250 3500 0    50   ~ 0
blaster3 (bl3)
Text Notes 3250 3300 0    50   ~ 0
booster0 (bs0)
Text Notes 3250 3600 0    50   ~ 0
booster1 (bs1)
$Comp
L Device:CP C1
U 1 1 5BBE6099
P 4700 1500
F 0 "C1" H 4800 1400 50  0000 C CNN
F 1 "10uF" H 4850 1600 50  0000 C CNN
F 2 "Capacitor_THT:CP_Axial_L10.0mm_D6.0mm_P15.00mm_Horizontal" H 4738 1350 50  0001 C CNN
F 3 "~" H 4700 1500 50  0001 C CNN
	1    4700 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5BBECF45
P 2850 2250
F 0 "R1" V 3200 2250 50  0001 R CNN
F 1 "3.9k" V 2850 2250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2780 2250 50  0001 C CNN
F 3 "~" H 2850 2250 50  0001 C CNN
	1    2850 2250
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5BC32DBF
P 3200 3150
F 0 "J1" H 3850 3250 50  0000 L CNN
F 1 "led_a" H 3850 3150 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 3200 3150 50  0001 C CNN
F 3 "~" H 3200 3150 50  0001 C CNN
	1    3200 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J3
U 1 1 5BC32E07
P 3200 3450
F 0 "J3" H 3850 3500 50  0000 L CNN
F 1 "led_b" H 3850 3400 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 3200 3450 50  0001 C CNN
F 3 "~" H 3200 3450 50  0001 C CNN
	1    3200 3450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 5BC339F5
P 950 1250
F 0 "J5" H 870 1467 50  0000 C CNN
F 1 "pwr_in" H 870 1376 50  0000 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 950 1250 50  0001 C CNN
F 3 "~" H 950 1250 50  0001 C CNN
	1    950  1250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1350 1050 1250 1050
Wire Wire Line
	1250 1050 1250 1250
Wire Wire Line
	1250 1250 1150 1250
Wire Wire Line
	1350 1500 1250 1500
Wire Wire Line
	1250 1500 1250 1350
Wire Wire Line
	1250 1350 1150 1350
Wire Wire Line
	2650 3050 3000 3050
Wire Wire Line
	2650 3150 3000 3150
Wire Wire Line
	2650 3250 3000 3250
Wire Wire Line
	2650 3350 3000 3350
Wire Wire Line
	2650 3450 3000 3450
Wire Wire Line
	2650 3550 3000 3550
Wire Wire Line
	4150 3450 4150 4150
Wire Wire Line
	2650 4150 4150 4150
Text HLabel 4650 2850 0    50   Input ~ 0
sd_cs
Wire Wire Line
	4650 2850 4700 2850
Text HLabel 2700 4250 2    50   Input ~ 0
sd_cs
Wire Wire Line
	2650 4250 2700 4250
Text Label 3800 2450 0    50   ~ 0
sd_di
Text Label 4150 3550 0    50   ~ 0
sd_cd
Text Label 3800 2650 0    50   ~ 0
sd_sck
Text Label 3800 2550 0    50   ~ 0
sd_do
Text Label 2750 3050 0    50   ~ 0
led_bl0
Text Label 2750 3150 0    50   ~ 0
led_bl1
Text Label 2750 3250 0    50   ~ 0
led_bs0
Text Label 2750 3350 0    50   ~ 0
led_bl2
Text Label 2750 3450 0    50   ~ 0
led_bl3
Text Label 2750 3550 0    50   ~ 0
led_bs1
Wire Wire Line
	2650 3850 2700 3850
$Comp
L Connector:Screw_Terminal_01x03 J4
U 1 1 5BC32E3D
P 3200 3750
F 0 "J4" H 3850 3800 50  0000 L CNN
F 1 "led_c" H 3850 3700 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 3200 3750 50  0001 C CNN
F 3 "~" H 3200 3750 50  0001 C CNN
	1    3200 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3850 2700 3650
Wire Wire Line
	2700 3650 3000 3650
$Comp
L Device:R_POT RV1
U 1 1 5C58E151
P 3600 2250
F 0 "RV1" V 3486 2250 50  0001 C CNN
F 1 "1k" V 3600 2250 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Vishay_T7-YA_Single_Vertical" H 3600 2250 50  0001 C CNN
F 3 "~" H 3600 2250 50  0001 C CNN
	1    3600 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 2250 2700 2250
Wire Wire Line
	5000 1300 4700 1300
Wire Wire Line
	4700 1300 4700 1350
Wire Wire Line
	4700 1650 4700 2250
Wire Wire Line
	4700 2250 3800 2250
Wire Wire Line
	3600 2100 3600 2050
Wire Wire Line
	3600 2050 3800 2050
Wire Wire Line
	3800 2050 3800 2250
Connection ~ 3800 2250
Wire Wire Line
	3800 2250 3750 2250
Text GLabel 3150 2150 2    50   Input ~ 0
GND
Wire Wire Line
	3150 2150 3050 2150
Wire Wire Line
	3050 2150 3050 2250
Connection ~ 3050 2250
Wire Wire Line
	3050 2250 3000 2250
Wire Wire Line
	3050 2250 3450 2250
Text Notes 2800 1850 0    50   ~ 0
With 3.3v max out of the m328, \nthis guarantees a maximum of \n2.62v into the amp. This would \nclip on full strength signals, but \nit allows us to take advantage of \nthe fact that audio is very rarely \nfull strength.
Wire Wire Line
	5600 1400 5650 1400
Wire Wire Line
	5200 1750 5950 1750
$EndSCHEMATC
