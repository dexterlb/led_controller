EESchema Schematic File Version 5
EELAYER 29 0
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
L Transistor_FET:IRF540N Q?
U 1 1 5D80940A
P 6600 2050
F 0 "Q?" H 6806 2096 50  0000 L CNN
F 1 "IRF540N" H 6806 2005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6850 1975 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 6600 2050 50  0001 L CNN
	1    6600 2050
	1    0    0    -1  
$EndComp
$Comp
L drivers_and_mosfets:TC4427A U?
U 1 1 5D809F3E
P 5850 2050
F 0 "U?" H 5925 2413 60  0000 C CNN
F 1 "TC4427A" H 5925 2307 60  0000 C CNN
F 2 "" H 5800 2050 60  0001 C CNN
F 3 "" H 5800 2050 60  0001 C CNN
	1    5850 2050
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F0:STM32F030F4Px U?
U 1 1 5D80BF07
P 5450 4100
F 0 "U?" H 5450 3211 50  0000 C CNN
F 1 "STM32F030F4Px" H 5450 3120 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 5050 3400 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 5450 4100 50  0001 C CNN
	1    5450 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4600 6150 4600
Text Label 6150 4600 0    50   ~ 0
SWDIO
Wire Wire Line
	5950 4700 6150 4700
Text Label 6150 4700 0    50   ~ 0
SWCLK
Text Label 6150 4200 0    50   ~ 0
TIM3_CH1
Text Label 6150 4300 0    50   ~ 0
TIM3_CH2
Text Label 6150 4000 0    50   ~ 0
TIM14_CH1
Text Label 6150 3800 0    50   ~ 0
TIM15_CH1
Text Label 6150 3900 0    50   ~ 0
TIM15_CH2
Text Label 4500 4700 0    50   ~ 0
TIM3_CH4
Wire Wire Line
	5950 4400 6150 4400
Wire Wire Line
	5950 4500 6150 4500
Text Label 6150 4400 0    50   ~ 0
TX_SCL
Text Label 6150 4500 0    50   ~ 0
RX_SDA
Wire Wire Line
	6150 4300 5950 4300
Wire Wire Line
	5950 4200 6150 4200
Wire Wire Line
	6150 4000 5950 4000
Wire Wire Line
	5950 3900 6150 3900
Wire Wire Line
	6150 3800 5950 3800
$EndSCHEMATC
