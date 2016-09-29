EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:drivers_and_mosfets
LIBS:crystal_s
LIBS:ldo
LIBS:esp8266
LIBS:led_controller-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L MC34063 U6
U 1 1 57EA48FC
P 4100 4100
F 0 "U6" H 4400 4500 60  0000 C CNN
F 1 "MC34063" H 4450 3700 60  0000 C CNN
F 2 "Sockets_DIP:DIP-8__300" H 4100 4100 60  0001 C CNN
F 3 "" H 4100 4100 60  0000 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P15
U 1 1 57EA49AC
P 1700 2650
F 0 "P15" H 1700 2550 50  0000 C CNN
F 1 "+12v IN" H 1950 2650 50  0000 C CNN
F 2 "connectors:1PIN_DG306" H 1700 2650 60  0001 C CNN
F 3 "" H 1700 2650 60  0000 C CNN
	1    1700 2650
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X01 P16
U 1 1 57EA4A80
P 1700 2950
F 0 "P16" H 1700 2850 50  0000 C CNN
F 1 "GND IN" H 1950 2950 50  0000 C CNN
F 2 "connectors:1PIN_DG306" H 1700 2950 60  0001 C CNN
F 3 "" H 1700 2950 60  0000 C CNN
	1    1700 2950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR039
U 1 1 57EA4AB8
P 1950 3000
F 0 "#PWR039" H 1950 2750 60  0001 C CNN
F 1 "GND" H 1955 2819 60  0000 C CNN
F 2 "" H 1950 3000 60  0000 C CNN
F 3 "" H 1950 3000 60  0000 C CNN
	1    1950 3000
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR040
U 1 1 57EA4AD7
P 2200 2550
F 0 "#PWR040" H 2200 2400 60  0001 C CNN
F 1 "VDD" H 2217 2731 60  0000 C CNN
F 2 "" H 2200 2550 60  0000 C CNN
F 3 "" H 2200 2550 60  0000 C CNN
	1    2200 2550
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG041
U 1 1 57EA4B0E
P 1950 2550
F 0 "#FLG041" H 1950 2645 30  0001 C CNN
F 1 "PWR_FLAG" H 1950 2758 30  0001 C CNN
F 2 "" H 1950 2550 60  0000 C CNN
F 3 "" H 1950 2550 60  0000 C CNN
	1    1950 2550
	1    0    0    -1  
$EndComp
$Comp
L CP1 C5
U 1 1 57EA4B43
P 2500 2950
F 0 "C5" H 2633 2996 50  0000 L CNN
F 1 "1000μ" H 2633 2905 50  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor10x16RM5" H 2500 2950 60  0001 C CNN
F 3 "" H 2500 2950 60  0000 C CNN
	1    2500 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR042
U 1 1 57EA4BAE
P 2500 3250
F 0 "#PWR042" H 2500 3000 60  0001 C CNN
F 1 "GND" H 2505 3069 60  0000 C CNN
F 2 "" H 2500 3250 60  0000 C CNN
F 3 "" H 2500 3250 60  0000 C CNN
	1    2500 3250
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 57EA4C14
P 3050 2950
F 0 "C6" H 3165 2988 40  0000 L CNN
F 1 "100n" H 3165 2912 40  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor6MMDiscRM5" H 3088 2800 30  0001 C CNN
F 3 "" H 3050 2950 60  0000 C CNN
	1    3050 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR043
U 1 1 57EA4C84
P 3050 3200
F 0 "#PWR043" H 3050 2950 60  0001 C CNN
F 1 "GND" H 3055 3019 60  0000 C CNN
F 2 "" H 3050 3200 60  0000 C CNN
F 3 "" H 3050 3200 60  0000 C CNN
	1    3050 3200
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 57EA4E2B
P 5100 3600
F 0 "R18" H 5171 3638 40  0000 L CNN
F 1 "180Ω" H 5171 3562 40  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5030 3600 30  0001 C CNN
F 3 "" H 5100 3600 30  0000 C CNN
	1    5100 3600
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 57EA5192
P 3150 4550
F 0 "C11" H 3265 4588 40  0000 L CNN
F 1 "470p" H 3265 4512 40  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor6MMDiscRM5" H 3188 4400 30  0001 C CNN
F 3 "" H 3150 4550 60  0000 C CNN
	1    3150 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR044
U 1 1 57EA520D
P 3150 4850
F 0 "#PWR044" H 3150 4600 60  0001 C CNN
F 1 "GND" H 3155 4669 60  0000 C CNN
F 2 "" H 3150 4850 60  0000 C CNN
F 3 "" H 3150 4850 60  0000 C CNN
	1    3150 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR045
U 1 1 57EA52B2
P 4100 4850
F 0 "#PWR045" H 4100 4600 60  0001 C CNN
F 1 "GND" H 4105 4669 60  0000 C CNN
F 2 "" H 4100 4850 60  0000 C CNN
F 3 "" H 4100 4850 60  0000 C CNN
	1    4100 4850
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 57EA52FD
P 6250 3700
F 0 "L1" V 6443 3700 40  0000 C CNN
F 1 "220μH" V 6367 3700 40  0000 C CNN
F 2 "Inductors:INDUCTOR_V" H 6250 3700 60  0001 C CNN
F 3 "" H 6250 3700 60  0000 C CNN
	1    6250 3700
	0    -1   -1   0   
$EndComp
$Comp
L R R19
U 1 1 57EA53CD
P 6650 4000
F 0 "R19" H 6721 4038 40  0000 L CNN
F 1 "3.6k" H 6721 3962 40  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6580 4000 30  0001 C CNN
F 3 "" H 6650 4000 30  0000 C CNN
	1    6650 4000
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 57EA5435
P 6650 4600
F 0 "R20" H 6721 4638 40  0000 L CNN
F 1 "1.2k" H 6721 4562 40  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6580 4600 30  0001 C CNN
F 3 "" H 6650 4600 30  0000 C CNN
	1    6650 4600
	1    0    0    -1  
$EndComp
$Comp
L ZENER D3
U 1 1 57EA5616
P 5900 4600
F 0 "D3" V 5938 4521 50  0000 R CNN
F 1 "BYV10-40" V 5854 4521 40  0000 R CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" H 5900 4600 60  0001 C CNN
F 3 "" H 5900 4600 60  0000 C CNN
	1    5900 4600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR046
U 1 1 57EA572C
P 5900 4900
F 0 "#PWR046" H 5900 4650 60  0001 C CNN
F 1 "GND" H 5905 4719 60  0000 C CNN
F 2 "" H 5900 4900 60  0000 C CNN
F 3 "" H 5900 4900 60  0000 C CNN
	1    5900 4900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR047
U 1 1 57EA578F
P 6650 4900
F 0 "#PWR047" H 6650 4650 60  0001 C CNN
F 1 "GND" H 6655 4719 60  0000 C CNN
F 2 "" H 6650 4900 60  0000 C CNN
F 3 "" H 6650 4900 60  0000 C CNN
	1    6650 4900
	1    0    0    -1  
$EndComp
$Comp
L CP1 C7
U 1 1 57EA5BC4
P 7150 3950
F 0 "C7" H 7283 3996 50  0000 L CNN
F 1 "1000μ" H 7283 3905 50  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor10x16RM5" H 7150 3950 60  0001 C CNN
F 3 "" H 7150 3950 60  0000 C CNN
	1    7150 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 57EA5BCA
P 7150 4250
F 0 "#PWR048" H 7150 4000 60  0001 C CNN
F 1 "GND" H 7155 4069 60  0000 C CNN
F 2 "" H 7150 4250 60  0000 C CNN
F 3 "" H 7150 4250 60  0000 C CNN
	1    7150 4250
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 57EA5BD1
P 7700 3950
F 0 "C8" H 7815 3988 40  0000 L CNN
F 1 "100n" H 7815 3912 40  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor6MMDiscRM5" H 7738 3800 30  0001 C CNN
F 3 "" H 7700 3950 60  0000 C CNN
	1    7700 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 57EA5BD7
P 7700 4250
F 0 "#PWR049" H 7700 4000 60  0001 C CNN
F 1 "GND" H 7705 4069 60  0000 C CNN
F 2 "" H 7700 4250 60  0000 C CNN
F 3 "" H 7700 4250 60  0000 C CNN
	1    7700 4250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR050
U 1 1 57EA5CFB
P 7700 3600
F 0 "#PWR050" H 7700 3450 60  0001 C CNN
F 1 "+5V" H 7715 3781 60  0000 C CNN
F 2 "" H 7700 3600 60  0000 C CNN
F 3 "" H 7700 3600 60  0000 C CNN
	1    7700 3600
	1    0    0    -1  
$EndComp
$Comp
L MCP1700 U5
U 1 1 57EA613C
P 8700 3750
F 0 "U5" H 8700 4104 40  0000 C CNN
F 1 "MCP1700" H 8700 4028 40  0000 C CNN
F 2 "Housings_TO-92:TO-92-Free-molded-wide" H 8700 3960 30  0001 C CIN
F 3 "" H 8700 3750 60  0000 C CNN
	1    8700 3750
	1    0    0    -1  
$EndComp
$Comp
L CP1 C9
U 1 1 57EA6212
P 8150 3950
F 0 "C9" H 8283 3996 50  0000 L CNN
F 1 "1μ" H 8283 3905 50  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor5x6RM2.5" H 8150 3950 60  0001 C CNN
F 3 "" H 8150 3950 60  0000 C CNN
	1    8150 3950
	1    0    0    -1  
$EndComp
$Comp
L CP1 C10
U 1 1 57EA6344
P 9250 3950
F 0 "C10" H 9383 3996 50  0000 L CNN
F 1 "1μ" H 9383 3905 50  0000 L CNN
F 2 "Capacitors_ThroughHole:Capacitor5x6RM2.5" H 9250 3950 60  0001 C CNN
F 3 "" H 9250 3950 60  0000 C CNN
	1    9250 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR051
U 1 1 57EA649E
P 8150 4250
F 0 "#PWR051" H 8150 4000 60  0001 C CNN
F 1 "GND" H 8155 4069 60  0000 C CNN
F 2 "" H 8150 4250 60  0000 C CNN
F 3 "" H 8150 4250 60  0000 C CNN
	1    8150 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR052
U 1 1 57EA64DC
P 9250 4250
F 0 "#PWR052" H 9250 4000 60  0001 C CNN
F 1 "GND" H 9255 4069 60  0000 C CNN
F 2 "" H 9250 4250 60  0000 C CNN
F 3 "" H 9250 4250 60  0000 C CNN
	1    9250 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR053
U 1 1 57EA65AB
P 8700 4250
F 0 "#PWR053" H 8700 4000 60  0001 C CNN
F 1 "GND" H 8705 4069 60  0000 C CNN
F 2 "" H 8700 4250 60  0000 C CNN
F 3 "" H 8700 4250 60  0000 C CNN
	1    8700 4250
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR054
U 1 1 57EA6756
P 9250 3600
F 0 "#PWR054" H 9250 3450 60  0001 C CNN
F 1 "+3V3" H 9265 3781 60  0000 C CNN
F 2 "" H 9250 3600 60  0000 C CNN
F 3 "" H 9250 3600 60  0000 C CNN
	1    9250 3600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG055
U 1 1 57EAC700
P 6650 3600
F 0 "#FLG055" H 6650 3695 30  0001 C CNN
F 1 "PWR_FLAG" H 6650 3808 30  0001 C CNN
F 2 "" H 6650 3600 60  0000 C CNN
F 3 "" H 6650 3600 60  0000 C CNN
	1    6650 3600
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 57EA4CFB
P 5450 3000
F 0 "R17" H 5521 3038 40  0000 L CNN
F 1 "1Ω" H 5521 2962 40  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 5380 3000 30  0001 C CNN
F 3 "" H 5450 3000 30  0000 C CNN
	1    5450 3000
	1    0    0    -1  
$EndComp
$Comp
L R R22
U 1 1 57EAE8CB
P 5100 3000
F 0 "R22" H 5171 3038 40  0000 L CNN
F 1 "1Ω" H 5171 2962 40  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 5030 3000 30  0001 C CNN
F 3 "" H 5100 3000 30  0000 C CNN
	1    5100 3000
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 57EAE91F
P 4750 3000
F 0 "R21" H 4821 3038 40  0000 L CNN
F 1 "1Ω" H 4821 2962 40  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 4680 3000 30  0001 C CNN
F 3 "" H 4750 3000 30  0000 C CNN
	1    4750 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3000 1950 2950
Wire Wire Line
	1950 2950 1900 2950
Wire Wire Line
	1950 2550 1950 2650
Wire Wire Line
	1900 2650 5900 2650
Wire Wire Line
	2200 2650 2200 2550
Connection ~ 1950 2650
Wire Wire Line
	2500 2650 2500 2750
Connection ~ 2200 2650
Wire Wire Line
	2500 3250 2500 3150
Wire Wire Line
	3050 2650 3050 2750
Connection ~ 2500 2650
Wire Wire Line
	3050 3200 3050 3150
Wire Wire Line
	5100 2650 5100 2750
Connection ~ 3050 2650
Wire Wire Line
	5100 3250 5100 3350
Wire Wire Line
	5100 3850 5100 3900
Wire Wire Line
	5100 3900 4950 3900
Wire Wire Line
	5450 4000 4950 4000
Wire Wire Line
	5450 3250 5450 4000
Wire Wire Line
	5450 3300 3200 3300
Connection ~ 5100 3300
Wire Wire Line
	3200 3300 3200 3950
Wire Wire Line
	3200 3950 3250 3950
Wire Wire Line
	3250 4250 3150 4250
Wire Wire Line
	3150 4250 3150 4350
Wire Wire Line
	3150 4850 3150 4750
Wire Wire Line
	4100 3600 4100 2650
Connection ~ 4100 2650
Wire Wire Line
	4100 4850 4100 4600
Wire Wire Line
	6650 4250 6650 4350
Connection ~ 6650 4300
Wire Wire Line
	4950 4300 6650 4300
Wire Wire Line
	5900 3700 5900 4400
Wire Wire Line
	5900 3700 5950 3700
Wire Wire Line
	4950 4150 5900 4150
Connection ~ 5900 4150
Wire Wire Line
	6550 3700 8300 3700
Wire Wire Line
	6650 3600 6650 3750
Wire Wire Line
	5900 4900 5900 4800
Wire Wire Line
	6650 4900 6650 4850
Wire Wire Line
	7150 4250 7150 4150
Wire Wire Line
	7700 4250 7700 4150
Wire Wire Line
	7150 3700 7150 3750
Connection ~ 6650 3700
Wire Wire Line
	7700 3600 7700 3750
Connection ~ 7150 3700
Connection ~ 7700 3700
Wire Wire Line
	9250 4250 9250 4150
Wire Wire Line
	8150 4250 8150 4150
Wire Wire Line
	8700 4250 8700 4000
Wire Wire Line
	8150 3750 8150 3700
Connection ~ 8150 3700
Wire Wire Line
	9250 3600 9250 3750
Wire Wire Line
	9250 3700 9100 3700
Connection ~ 9250 3700
Wire Wire Line
	4750 3250 4750 3300
Connection ~ 4750 3300
Connection ~ 5450 3300
Wire Wire Line
	5450 2650 5450 2750
Connection ~ 5100 2650
Wire Wire Line
	4750 2750 4750 2650
Connection ~ 4750 2650
$Comp
L CONN_01X01 P?
U 1 1 57ED4108
P 6100 2650
F 0 "P?" H 6100 2550 50  0000 C CNN
F 1 "+12v OUT" H 6350 2650 50  0000 C CNN
F 2 "connectors:1PIN_DG306" H 6100 2650 60  0001 C CNN
F 3 "" H 6100 2650 60  0000 C CNN
	1    6100 2650
	1    0    0    1   
$EndComp
$Comp
L CONN_01X01 P?
U 1 1 57ED423E
P 6100 2950
F 0 "P?" H 6100 2850 50  0000 C CNN
F 1 "GND OUT" H 6350 2950 50  0000 C CNN
F 2 "connectors:1PIN_DG306" H 6100 2950 60  0001 C CNN
F 3 "" H 6100 2950 60  0000 C CNN
	1    6100 2950
	1    0    0    1   
$EndComp
Wire Wire Line
	5900 2950 5800 2950
Wire Wire Line
	5800 2950 5800 3050
Connection ~ 5450 2650
$Comp
L GND #PWR?
U 1 1 57ED44B5
P 5800 3050
F 0 "#PWR?" H 5800 2800 60  0001 C CNN
F 1 "GND" H 5805 2869 60  0000 C CNN
F 2 "" H 5800 3050 60  0000 C CNN
F 3 "" H 5800 3050 60  0000 C CNN
	1    5800 3050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
