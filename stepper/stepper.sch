EESchema Schematic File Version 5
EELAYER 33 0
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
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 4950 3325
Connection ~ 4625 3625
Connection ~ 4950 4225
Connection ~ 4625 4125
Connection ~ 4275 4025
Connection ~ 5675 4650
Connection ~ 3525 4125
Connection ~ 3525 4025
Connection ~ 1575 4625
Connection ~ 2225 4525
Wire Wire Line
	1575 4525 1575 4625
Wire Wire Line
	1575 4625 1575 4750
Wire Wire Line
	1575 4625 1625 4625
Wire Wire Line
	1625 4525 1575 4525
Wire Wire Line
	2125 4525 2225 4525
Wire Wire Line
	2225 4425 2225 4525
Wire Wire Line
	2225 4525 2225 4625
Wire Wire Line
	2225 4625 2125 4625
Wire Wire Line
	2575 4875 2575 4950
Wire Wire Line
	2575 5250 2575 5325
Wire Wire Line
	2575 5750 2575 5825
Wire Wire Line
	2575 6125 2575 6200
Wire Wire Line
	2800 3300 2925 3300
Wire Wire Line
	2800 3400 2925 3400
Wire Wire Line
	2800 3500 3225 3500
Wire Wire Line
	2800 3600 3225 3600
Wire Wire Line
	2800 3700 3225 3700
Wire Wire Line
	2800 3800 3225 3800
Wire Wire Line
	3000 4875 3000 4950
Wire Wire Line
	3000 5250 3000 5325
Wire Wire Line
	3000 5750 3000 5825
Wire Wire Line
	3000 6125 3000 6200
Wire Wire Line
	3525 3750 3525 4025
Wire Wire Line
	3525 4025 3525 4125
Wire Wire Line
	3525 4025 3600 4025
Wire Wire Line
	3525 4125 3525 4225
Wire Wire Line
	3525 4125 3600 4125
Wire Wire Line
	3600 4225 3525 4225
Wire Wire Line
	3700 2275 3800 2275
Wire Wire Line
	4000 2275 4325 2275
Wire Wire Line
	4100 4025 4275 4025
Wire Wire Line
	4100 4125 4625 4125
Wire Wire Line
	4100 4225 4950 4225
Wire Wire Line
	4275 4025 4275 4400
Wire Wire Line
	4275 4025 5175 4025
Wire Wire Line
	4275 4700 4275 4750
Wire Wire Line
	4475 3325 4950 3325
Wire Wire Line
	4475 3625 4625 3625
Wire Wire Line
	4475 3725 5175 3725
Wire Wire Line
	4475 3825 5175 3825
Wire Wire Line
	4625 2800 4625 2900
Wire Wire Line
	4625 3625 4625 3200
Wire Wire Line
	4625 4125 4625 4400
Wire Wire Line
	4625 4125 5175 4125
Wire Wire Line
	4625 4700 4625 4750
Wire Wire Line
	4950 2800 4950 2900
Wire Wire Line
	4950 3325 4950 3200
Wire Wire Line
	4950 3325 5175 3325
Wire Wire Line
	4950 3425 4950 3325
Wire Wire Line
	4950 4225 4950 4400
Wire Wire Line
	4950 4225 5175 4225
Wire Wire Line
	4950 4700 4950 4750
Wire Wire Line
	5175 3425 4950 3425
Wire Wire Line
	5175 3625 4625 3625
Wire Wire Line
	5575 2825 5575 3025
Wire Wire Line
	5575 4650 5575 4525
Wire Wire Line
	5575 4650 5675 4650
Wire Wire Line
	5675 4650 5675 4750
Wire Wire Line
	5675 4650 5775 4650
Wire Wire Line
	5775 2825 5775 3025
Wire Wire Line
	5775 4525 5775 4650
Wire Wire Line
	6075 3625 6150 3625
Wire Wire Line
	6075 3725 6150 3725
Wire Wire Line
	6075 3825 6150 3825
Wire Wire Line
	6075 3925 6150 3925
Text Label 3225 3500 2    50   ~ 0
SLEEP
Text Label 3225 3600 2    50   ~ 0
ENABLE
Text Label 3225 3700 2    50   ~ 0
DIR
Text Label 3225 3800 2    50   ~ 0
STEP
Text Label 4325 2275 2    50   ~ 0
ENABLE
Text Label 4475 3325 2    50   ~ 0
SLEEP
Text Label 4475 3625 2    50   ~ 0
ENABLE
Text Label 4475 3725 2    50   ~ 0
STEP
Text Label 4475 3825 2    50   ~ 0
DIR
$Comp
L power:VDD #PWR0111
U 1 1 5E9CDFB9
P 2225 4425
F 0 "#PWR0111" H 2225 4275 50  0001 C CNN
F 1 "VDD" H 2240 4598 50  0000 C CNN
F 2 "" H 2225 4425 50  0001 C CNN
F 3 "" H 2225 4425 50  0001 C CNN
	1    2225 4425
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0103
U 1 1 5E9D1D81
P 2575 4875
F 0 "#PWR0103" H 2575 4725 50  0001 C CNN
F 1 "VDD" H 2590 5048 50  0000 C CNN
F 2 "" H 2575 4875 50  0001 C CNN
F 3 "" H 2575 4875 50  0001 C CNN
	1    2575 4875
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0108
U 1 1 5E9D4232
P 2575 5750
F 0 "#PWR0108" H 2575 5600 50  0001 C CNN
F 1 "+3V3" H 2590 5923 50  0000 C CNN
F 2 "" H 2575 5750 50  0001 C CNN
F 3 "" H 2575 5750 50  0001 C CNN
	1    2575 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0118
U 1 1 5E9C2D8B
P 2925 3400
F 0 "#PWR0118" H 2925 3250 50  0001 C CNN
F 1 "+3V3" V 2925 3650 50  0000 C CNN
F 2 "" H 2925 3400 50  0001 C CNN
F 3 "" H 2925 3400 50  0001 C CNN
	1    2925 3400
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR0102
U 1 1 5E9DB7FC
P 3000 4875
F 0 "#PWR0102" H 3000 4725 50  0001 C CNN
F 1 "VDD" H 3015 5048 50  0000 C CNN
F 2 "" H 3000 4875 50  0001 C CNN
F 3 "" H 3000 4875 50  0001 C CNN
	1    3000 4875
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0109
U 1 1 5E9DCC10
P 3000 5750
F 0 "#PWR0109" H 3000 5600 50  0001 C CNN
F 1 "+3V3" H 3015 5923 50  0000 C CNN
F 2 "" H 3000 5750 50  0001 C CNN
F 3 "" H 3000 5750 50  0001 C CNN
	1    3000 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0121
U 1 1 5E92BAC0
P 3525 3750
F 0 "#PWR0121" H 3525 3600 50  0001 C CNN
F 1 "+3V3" H 3540 3923 50  0000 C CNN
F 2 "" H 3525 3750 50  0001 C CNN
F 3 "" H 3525 3750 50  0001 C CNN
	1    3525 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0117
U 1 1 5E928D43
P 4625 2800
F 0 "#PWR0117" H 4625 2650 50  0001 C CNN
F 1 "+3V3" H 4640 2973 50  0000 C CNN
F 2 "" H 4625 2800 50  0001 C CNN
F 3 "" H 4625 2800 50  0001 C CNN
	1    4625 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0120
U 1 1 5E927EB0
P 4950 2800
F 0 "#PWR0120" H 4950 2650 50  0001 C CNN
F 1 "+3V3" H 4965 2973 50  0000 C CNN
F 2 "" H 4950 2800 50  0001 C CNN
F 3 "" H 4950 2800 50  0001 C CNN
	1    4950 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0115
U 1 1 5E926AAB
P 5575 2825
F 0 "#PWR0115" H 5575 2675 50  0001 C CNN
F 1 "+3V3" H 5590 2998 50  0000 C CNN
F 2 "" H 5575 2825 50  0001 C CNN
F 3 "" H 5575 2825 50  0001 C CNN
	1    5575 2825
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0116
U 1 1 5E92CDA6
P 5775 2825
F 0 "#PWR0116" H 5775 2675 50  0001 C CNN
F 1 "VDD" H 5790 2998 50  0000 C CNN
F 2 "" H 5775 2825 50  0001 C CNN
F 3 "" H 5775 2825 50  0001 C CNN
	1    5775 2825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E9CFAE2
P 1575 4750
F 0 "#PWR0104" H 1575 4500 50  0001 C CNN
F 1 "GND" H 1579 4577 50  0001 C CNN
F 2 "" H 1575 4750 50  0001 C CNN
F 3 "" H 1575 4750 50  0001 C CNN
	1    1575 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5E9D13E5
P 2575 5325
F 0 "#PWR0107" H 2575 5075 50  0001 C CNN
F 1 "GND" H 2579 5152 50  0001 C CNN
F 2 "" H 2575 5325 50  0001 C CNN
F 3 "" H 2575 5325 50  0001 C CNN
	1    2575 5325
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5E9D2913
P 2575 6200
F 0 "#PWR0106" H 2575 5950 50  0001 C CNN
F 1 "GND" H 2579 6027 50  0001 C CNN
F 2 "" H 2575 6200 50  0001 C CNN
F 3 "" H 2575 6200 50  0001 C CNN
	1    2575 6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5E9C3FFA
P 2925 3300
F 0 "#PWR0122" H 2925 3050 50  0001 C CNN
F 1 "GND" H 2929 3127 50  0001 C CNN
F 2 "" H 2925 3300 50  0001 C CNN
F 3 "" H 2925 3300 50  0001 C CNN
	1    2925 3300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5E9DAD81
P 3000 5325
F 0 "#PWR0110" H 3000 5075 50  0001 C CNN
F 1 "GND" H 3004 5152 50  0001 C CNN
F 2 "" H 3000 5325 50  0001 C CNN
F 3 "" H 3000 5325 50  0001 C CNN
	1    3000 5325
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5E9DC048
P 3000 6200
F 0 "#PWR0105" H 3000 5950 50  0001 C CNN
F 1 "GND" H 3004 6027 50  0001 C CNN
F 2 "" H 3000 6200 50  0001 C CNN
F 3 "" H 3000 6200 50  0001 C CNN
	1    3000 6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5E9BA0E2
P 3700 2275
F 0 "#PWR0119" H 3700 2025 50  0001 C CNN
F 1 "GND" H 3704 2102 50  0001 C CNN
F 2 "" H 3700 2275 50  0001 C CNN
F 3 "" H 3700 2275 50  0001 C CNN
	1    3700 2275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E91E8FF
P 4275 4750
F 0 "#PWR0101" H 4275 4500 50  0001 C CNN
F 1 "GND" H 4279 4577 50  0001 C CNN
F 2 "" H 4275 4750 50  0001 C CNN
F 3 "" H 4275 4750 50  0001 C CNN
	1    4275 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5E91E1AB
P 4625 4750
F 0 "#PWR0114" H 4625 4500 50  0001 C CNN
F 1 "GND" H 4629 4577 50  0001 C CNN
F 2 "" H 4625 4750 50  0001 C CNN
F 3 "" H 4625 4750 50  0001 C CNN
	1    4625 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5E91D3AE
P 4950 4750
F 0 "#PWR0113" H 4950 4500 50  0001 C CNN
F 1 "GND" H 4954 4577 50  0001 C CNN
F 2 "" H 4950 4750 50  0001 C CNN
F 3 "" H 4950 4750 50  0001 C CNN
	1    4950 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E91F887
P 5675 4750
F 0 "#PWR0112" H 5675 4500 50  0001 C CNN
F 1 "GND" H 5679 4577 50  0001 C CNN
F 2 "" H 5675 4750 50  0001 C CNN
F 3 "" H 5675 4750 50  0001 C CNN
	1    5675 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NC_Small JP1
U 1 1 5E99BD02
P 3900 2275
F 0 "JP1" H 3975 2400 50  0000 R CNN
F 1 "EN_ALWAYS" H 4100 2175 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3900 2275 50  0001 C CNN
F 3 "~" H 3900 2275 50  0001 C CNN
	1    3900 2275
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E91BC08
P 4275 4550
F 0 "R1" H 4345 4595 50  0000 L CNN
F 1 "10k" H 4345 4505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4205 4550 50  0001 C CNN
F 3 "~" H 4275 4550 50  0001 C CNN
	1    4275 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5E91570F
P 4625 3050
F 0 "R2" H 4695 3095 50  0000 L CNN
F 1 "10k" H 4695 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4555 3050 50  0001 C CNN
F 3 "~" H 4625 3050 50  0001 C CNN
	1    4625 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5E91A9A0
P 4625 4550
F 0 "R3" H 4695 4595 50  0000 L CNN
F 1 "10k" H 4695 4505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4555 4550 50  0001 C CNN
F 3 "~" H 4625 4550 50  0001 C CNN
	1    4625 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5E914BD6
P 4950 3050
F 0 "R4" H 5020 3095 50  0000 L CNN
F 1 "10k" H 5020 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4880 3050 50  0001 C CNN
F 3 "~" H 4950 3050 50  0001 C CNN
	1    4950 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5E91A9AF
P 4950 4550
F 0 "R5" H 5020 4595 50  0000 L CNN
F 1 "10k" H 5020 4505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4880 4550 50  0001 C CNN
F 3 "~" H 4950 4550 50  0001 C CNN
	1    4950 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C1
U 1 1 5E9D0DCB
P 2575 5100
F 0 "C1" H 2690 5145 50  0000 L CNN
F 1 "CP1" H 2690 5055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 2575 5100 50  0001 C CNN
F 3 "~" H 2575 5100 50  0001 C CNN
	1    2575 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C2
U 1 1 5E9D2920
P 2575 5975
F 0 "C2" H 2690 6020 50  0000 L CNN
F 1 "CP1" H 2690 5930 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 2575 5975 50  0001 C CNN
F 3 "~" H 2575 5975 50  0001 C CNN
	1    2575 5975
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E9D6328
P 3000 5100
F 0 "C3" H 3115 5145 50  0000 L CNN
F 1 "C" H 3115 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3038 4950 50  0001 C CNN
F 3 "~" H 3000 5100 50  0001 C CNN
	1    3000 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E9DC038
P 3000 5975
F 0 "C4" H 3115 6020 50  0000 L CNN
F 1 "C" H 3115 5930 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3038 5825 50  0001 C CNN
F 3 "~" H 3000 5975 50  0001 C CNN
	1    3000 5975
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5E92D42D
P 6350 3725
F 0 "J4" H 6430 3717 50  0000 L CNN
F 1 "Stepper" H 6430 3626 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6350 3725 50  0001 C CNN
F 3 "~" H 6350 3725 50  0001 C CNN
	1    6350 3725
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x02_Odd_Even J1
U 1 1 5E9CC7B0
P 1825 4525
F 0 "J1" H 1875 4741 50  0000 C CNN
F 1 "VDD_IN" H 1875 4650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Vertical" H 1825 4525 50  0001 C CNN
F 3 "~" H 1825 4525 50  0001 C CNN
	1    1825 4525
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 5E9BD10B
P 2600 3500
F 0 "J2" H 2600 3900 50  0000 C CNN
F 1 "In" H 2600 3825 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2600 3500 50  0001 C CNN
F 3 "~" H 2600 3500 50  0001 C CNN
	1    2600 3500
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J3
U 1 1 5E9181EE
P 3800 4125
F 0 "J3" H 3850 4441 50  0000 C CNN
F 1 "Jumpers" H 3850 4350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 3800 4125 50  0001 C CNN
F 3 "~" H 3800 4125 50  0001 C CNN
	1    3800 4125
	1    0    0    1   
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A1
U 1 1 5E9136E1
P 5575 3725
F 0 "A1" H 5875 2975 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 6275 2875 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 5850 2975 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 5675 3425 50  0001 C CNN
	1    5575 3725
	1    0    0    -1  
$EndComp
$EndSCHEMATC