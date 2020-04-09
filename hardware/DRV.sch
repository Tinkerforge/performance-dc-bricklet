EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "DC V2 Bricklet"
Date "2020-01-09"
Rev "2.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2020, T.Schneidermann <tim@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L tinkerforge:DRV8701 U?
U 1 1 5EB1D0C4
P 3800 4300
AR Path="/5EB1D0C4" Ref="U?"  Part="1" 
AR Path="/5EAFEC80/5EB1D0C4" Ref="U?"  Part="1" 
F 0 "U?" H 3250 5150 50  0000 C CNN
F 1 "DRV8701" H 3800 4300 50  0000 C CNN
F 2 "kicad-libraries:VQFN_4x4mm" H 3800 4300 50  0001 C CNN
F 3 "" H 3800 4300 50  0001 C CNN
	1    3800 4300
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CONN_2 P?
U 1 1 5EB38AC7
P 10450 4250
AR Path="/5EB38AC7" Ref="P?"  Part="1" 
AR Path="/5EAFEC80/5EB38AC7" Ref="P?"  Part="1" 
F 0 "P?" H 10578 4278 40  0000 L CNN
F 1 "OUT" H 10578 4202 40  0000 L CNN
F 2 "kicad-libraries:OQ_2P_5mm_Vertical" H 10450 4250 60  0001 C CNN
F 3 "" H 10450 4250 60  0000 C CNN
	1    10450 4250
	1    0    0    1   
$EndComp
Wire Wire Line
	8800 4050 8800 4350
Wire Wire Line
	9150 4050 9150 4150
Connection ~ 9150 4150
Wire Wire Line
	9150 4150 9150 4450
Connection ~ 8800 4350
Wire Wire Line
	8800 4350 8800 4450
$Comp
L tinkerforge:GND #PWR?
U 1 1 5EB38AEE
P 8950 5000
AR Path="/5EB38AEE" Ref="#PWR?"  Part="1" 
AR Path="/5EAFEC80/5EB38AEE" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8950 4750 50  0001 C CNN
F 1 "GND" H 8955 4827 50  0000 C CNN
F 2 "" H 8950 5000 50  0000 C CNN
F 3 "" H 8950 5000 50  0000 C CNN
	1    8950 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 5000 8950 5000
Connection ~ 8950 5000
Wire Wire Line
	8950 5000 9150 5000
$Comp
L tinkerforge:Cs C?
U 1 1 5EB38AF7
P 9450 4550
AR Path="/5EB38AF7" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5EB38AF7" Ref="C?"  Part="1" 
F 0 "C?" H 9300 4600 31  0000 L CNN
F 1 "1nF/100V" H 9500 4500 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 9450 4550 60  0001 C CNN
F 3 "" H 9450 4550 60  0000 C CNN
	1    9450 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 4350 10100 4350
$Comp
L tinkerforge:Cs C?
U 1 1 5EB38AFE
P 9900 4550
AR Path="/5EB38AFE" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5EB38AFE" Ref="C?"  Part="1" 
F 0 "C?" H 9750 4600 31  0000 L CNN
F 1 "1nF/100V" H 9950 4500 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 9900 4550 60  0001 C CNN
F 3 "" H 9900 4550 60  0000 C CNN
	1    9900 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 4350 9450 4450
Wire Wire Line
	9900 4450 9900 4150
Wire Wire Line
	9900 4150 10100 4150
Wire Wire Line
	9450 4650 9450 5000
Wire Wire Line
	9450 5000 9700 5000
Wire Wire Line
	9900 5000 9900 4650
$Comp
L tinkerforge:GND #PWR?
U 1 1 5EB38B0A
P 9700 5000
AR Path="/5EB38B0A" Ref="#PWR?"  Part="1" 
AR Path="/5EAFEC80/5EB38B0A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9700 4750 50  0001 C CNN
F 1 "GND" H 9705 4827 50  0000 C CNN
F 2 "" H 9700 5000 50  0000 C CNN
F 3 "" H 9700 5000 50  0000 C CNN
	1    9700 5000
	1    0    0    -1  
$EndComp
Connection ~ 9700 5000
Wire Wire Line
	9700 5000 9900 5000
Wire Wire Line
	9150 4150 9900 4150
Connection ~ 9900 4150
Wire Wire Line
	9450 4350 8800 4350
Connection ~ 9450 4350
$Comp
L tinkerforge:CONN_2 P?
U 1 1 5EB544F4
P 10650 1350
AR Path="/5EB544F4" Ref="P?"  Part="1" 
AR Path="/5EAFEC80/5EB544F4" Ref="P?"  Part="1" 
F 0 "P?" H 10778 1378 40  0000 L CNN
F 1 "IN" H 10778 1302 40  0000 L CNN
F 2 "kicad-libraries:OQ_2P_5mm_Vertical_Black" H 10650 1350 60  0001 C CNN
F 3 "" H 10650 1350 60  0000 C CNN
	1    10650 1350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR?
U 1 1 5EB54501
P 8650 2300
AR Path="/5EB54501" Ref="#PWR?"  Part="1" 
AR Path="/5EAFEC80/5EB54501" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8650 2050 50  0001 C CNN
F 1 "GND" H 8655 2127 50  0000 C CNN
F 2 "" H 8650 2300 50  0000 C CNN
F 3 "" H 8650 2300 50  0000 C CNN
	1    8650 2300
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:TVS D?
U 1 1 5EB54507
P 9550 1500
AR Path="/5EB54507" Ref="D?"  Part="1" 
AR Path="/5EAFEC80/5EB54507" Ref="D?"  Part="1" 
F 0 "D?" V 9350 1550 50  0000 L CNN
F 1 "SMBJ36CA" V 9200 1350 31  0000 L CNN
F 2 "kicad-libraries:SMB" H 9550 1500 50  0001 C CNN
F 3 "" H 9550 1500 50  0000 C CNN
	1    9550 1500
	0    1    1    0   
$EndComp
Text GLabel 10100 1000 0    50   Output ~ 0
V_GPIO
Wire Wire Line
	10100 1000 10250 1000
Wire Wire Line
	10250 1000 10250 1250
Connection ~ 10250 1250
Wire Wire Line
	10250 1250 10300 1250
Wire Wire Line
	10300 1450 10250 1450
Wire Wire Line
	10250 1450 10250 1800
Wire Wire Line
	10250 1800 9900 1800
Connection ~ 9900 1800
Wire Wire Line
	9550 1800 9900 1800
Wire Wire Line
	9900 1750 9900 1800
Wire Wire Line
	9550 1750 9550 1800
Text GLabel 2650 4350 0    50   Input ~ 0
IN1
Text GLabel 2650 4450 0    50   Input ~ 0
IN2
Wire Wire Line
	2650 4450 3100 4450
Wire Wire Line
	3100 4350 2650 4350
Wire Wire Line
	2650 4550 3100 4550
Text GLabel 2650 4550 0    50   Input ~ 0
nSLEEP
$Comp
L tinkerforge:Rs R?
U 1 1 5E8FA9AB
P 1450 5050
F 0 "R?" H 1503 5081 31  0000 L CNN
F 1 "1k" H 1503 5019 31  0000 L CNN
F 2 "kicad-libraries:R0603F" H 1450 5050 60  0001 C CNN
F 3 "" H 1450 5050 60  0000 C CNN
	1    1450 5050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:Rs R?
U 1 1 5E8FB676
P 1750 5050
F 0 "R?" H 1803 5081 31  0000 L CNN
F 1 "1k" H 1803 5019 31  0000 L CNN
F 2 "kicad-libraries:R0603F" H 1750 5050 60  0001 C CNN
F 3 "" H 1750 5050 60  0000 C CNN
	1    1750 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 5150 1750 5350
Wire Wire Line
	1750 5350 1050 5350
Connection ~ 1750 5350
Text GLabel 1050 5250 0    50   Output ~ 0
SNSOUT
Text GLabel 1050 5350 0    50   Output ~ 0
nFAULT
Wire Wire Line
	1750 4800 1750 4950
$Comp
L tinkerforge:+3.3VP #PWR?
U 1 1 5E903516
P 1600 4800
F 0 "#PWR?" H 1750 4750 50  0001 C CNN
F 1 "+3.3VP" H 1620 4943 50  0000 C CNN
F 2 "" H 1600 4800 50  0001 C CNN
F 3 "" H 1600 4800 50  0001 C CNN
	1    1600 4800
	1    0    0    -1  
$EndComp
Connection ~ 1600 4800
Wire Wire Line
	1600 4800 1750 4800
Wire Wire Line
	1050 5250 1450 5250
Wire Wire Line
	1450 4800 1450 4950
Wire Wire Line
	1450 4800 1600 4800
Wire Wire Line
	1450 5150 1450 5250
Connection ~ 1450 5250
Wire Wire Line
	1450 5250 2850 5250
Text GLabel 4700 4850 2    50   Output ~ 0
SO
Wire Wire Line
	4700 4850 4500 4850
Wire Wire Line
	3700 5300 3700 5450
Wire Wire Line
	3700 5450 3800 5450
Wire Wire Line
	3800 5450 3800 5300
Wire Wire Line
	3900 5300 3900 5450
Wire Wire Line
	3900 5450 3800 5450
Connection ~ 3800 5450
$Comp
L tinkerforge:GND #PWR?
U 1 1 5E908F92
P 3800 5550
F 0 "#PWR?" H 3800 5300 50  0001 C CNN
F 1 "GND" H 3805 5377 50  0000 C CNN
F 2 "" H 3800 5550 50  0000 C CNN
F 3 "" H 3800 5550 50  0000 C CNN
	1    3800 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5450 3800 5550
$Comp
L tinkerforge:Rs R?
U 1 1 5E90AA24
P 2500 4750
F 0 "R?" H 2553 4781 31  0000 L CNN
F 1 "200k" H 2553 4719 31  0000 L CNN
F 2 "kicad-libraries:R0603F" H 2500 4750 60  0001 C CNN
F 3 "" H 2500 4750 60  0000 C CNN
	1    2500 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 4650 3100 4650
Wire Wire Line
	2850 5250 2850 4850
Wire Wire Line
	2850 4850 3100 4850
Wire Wire Line
	3100 4950 2950 4950
Wire Wire Line
	2950 4950 2950 5350
Wire Wire Line
	1750 5350 2950 5350
$Comp
L tinkerforge:GND #PWR?
U 1 1 5E9156B2
P 2500 4850
F 0 "#PWR?" H 2500 4600 50  0001 C CNN
F 1 "GND" H 2505 4677 50  0000 C CNN
F 2 "" H 2500 4850 50  0000 C CNN
F 3 "" H 2500 4850 50  0000 C CNN
	1    2500 4850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:Cs C?
U 1 1 5E9161B4
P 2350 3850
AR Path="/5E9161B4" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5E9161B4" Ref="C?"  Part="1" 
F 0 "C?" H 2200 3900 31  0000 L CNN
F 1 "100nF/100V" H 2400 3800 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2350 3850 60  0001 C CNN
F 3 "" H 2350 3850 60  0000 C CNN
	1    2350 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3750 2750 3750
Wire Wire Line
	2750 3750 2750 3800
Wire Wire Line
	2750 3800 3100 3800
Wire Wire Line
	3100 3900 2750 3900
Wire Wire Line
	2750 3900 2750 3950
Wire Wire Line
	2750 3950 2350 3950
$Comp
L tinkerforge:Cs C?
U 1 1 5E91AAD7
P 2350 3550
AR Path="/5E91AAD7" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5E91AAD7" Ref="C?"  Part="1" 
F 0 "C?" H 2200 3600 31  0000 L CNN
F 1 "1uF/16V" H 2400 3500 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2350 3550 60  0001 C CNN
F 3 "" H 2350 3550 60  0000 C CNN
	1    2350 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3650 2850 3650
Wire Wire Line
	2850 3650 2850 3700
Wire Wire Line
	2850 3700 3100 3700
Wire Wire Line
	2350 3450 2350 3250
Wire Wire Line
	2350 3250 3800 3250
Wire Wire Line
	3800 3250 3800 3400
$Comp
L tinkerforge:Cs C?
U 1 1 5E91EBE9
P 2100 4250
AR Path="/5E91EBE9" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5E91EBE9" Ref="C?"  Part="1" 
F 0 "C?" H 1950 4300 31  0000 L CNN
F 1 "1uF/16V" H 2150 4200 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2100 4250 60  0001 C CNN
F 3 "" H 2100 4250 60  0000 C CNN
	1    2100 4250
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:Cs C?
U 1 1 5E91FFF7
P 1700 4250
AR Path="/5E91FFF7" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5E91FFF7" Ref="C?"  Part="1" 
F 0 "C?" H 1550 4300 31  0000 L CNN
F 1 "1uF/16V" H 1750 4200 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1700 4250 60  0001 C CNN
F 3 "" H 1700 4250 60  0000 C CNN
	1    1700 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 4000 3100 4000
Wire Wire Line
	2100 4400 1900 4400
Wire Wire Line
	1700 4400 1700 4350
$Comp
L tinkerforge:GND #PWR?
U 1 1 5E92B517
P 1900 4400
F 0 "#PWR?" H 1900 4150 50  0001 C CNN
F 1 "GND" H 1905 4227 50  0000 C CNN
F 2 "" H 1900 4400 50  0000 C CNN
F 3 "" H 1900 4400 50  0000 C CNN
	1    1900 4400
	1    0    0    -1  
$EndComp
Connection ~ 1900 4400
Wire Wire Line
	1900 4400 1700 4400
$Comp
L tinkerforge:Rs R?
U 1 1 5E92C795
P 5050 5200
F 0 "R?" H 5100 5250 31  0000 L CNN
F 1 "TBD" H 5100 5150 31  0000 L CNN
F 2 "kicad-libraries:R0603F" H 5050 5200 60  0001 C CNN
F 3 "" H 5050 5200 60  0000 C CNN
	1    5050 5200
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:Rs R?
U 1 1 5E92E39E
P 5050 5500
F 0 "R?" H 5103 5531 31  0000 L CNN
F 1 "TBD" H 5103 5469 31  0000 L CNN
F 2 "kicad-libraries:R0603F" H 5050 5500 60  0001 C CNN
F 3 "" H 5050 5500 60  0000 C CNN
	1    5050 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 5400 5050 5350
Text GLabel 2050 4100 0    50   Output ~ 0
AVDD
Wire Wire Line
	2100 4350 2100 4400
Wire Wire Line
	2050 4100 2100 4100
Wire Wire Line
	2100 4100 2100 4150
Connection ~ 2100 4100
Wire Wire Line
	2100 4100 3100 4100
Text GLabel 5100 5000 2    50   Input ~ 0
AVDD
Wire Wire Line
	5100 5000 5050 5000
Wire Wire Line
	5050 5000 5050 5100
Wire Wire Line
	5050 5350 4650 5350
Wire Wire Line
	4650 5350 4650 4950
Wire Wire Line
	4650 4950 4500 4950
Connection ~ 5050 5350
Wire Wire Line
	5050 5350 5050 5300
$Comp
L tinkerforge:GND #PWR?
U 1 1 5E93F4A5
P 5050 5600
F 0 "#PWR?" H 5050 5350 50  0001 C CNN
F 1 "GND" H 5055 5427 50  0000 C CNN
F 2 "" H 5050 5600 50  0000 C CNN
F 3 "" H 5050 5600 50  0000 C CNN
	1    5050 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 4000 1700 4150
$Comp
L tinkerforge:MOSFET_N_CH Q?
U 1 1 5E950B5D
P 7050 3400
F 0 "Q?" H 7241 3431 50  0000 L CNN
F 1 "CSD19533Q5A" H 7241 3354 31  0000 L CNN
F 2 "kicad-libraries:SON_5x6mm" H 7250 3500 50  0001 C CNN
F 3 "" H 7050 3400 50  0000 C CNN
	1    7050 3400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:MOSFET_N_CH Q?
U 1 1 5E9518BF
P 9050 2000
F 0 "Q?" H 9241 2031 50  0000 L CNN
F 1 "CSD19533Q5A" H 9241 1954 31  0000 L CNN
F 2 "kicad-libraries:SON_5x6mm" H 9250 2100 50  0001 C CNN
F 3 "" H 9050 2000 50  0000 C CNN
	1    9050 2000
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:MOSFET_N_CH Q?
U 1 1 5E957ED9
P 7050 3900
F 0 "Q?" H 7241 3931 50  0000 L CNN
F 1 "CSD19533Q5A" H 7241 3854 31  0000 L CNN
F 2 "kicad-libraries:SON_5x6mm" H 7250 4000 50  0001 C CNN
F 3 "" H 7050 3900 50  0000 C CNN
	1    7050 3900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:MOSFET_N_CH Q?
U 1 1 5E96C160
P 6200 4500
F 0 "Q?" H 6391 4531 50  0000 L CNN
F 1 "CSD19533Q5A" H 6391 4454 31  0000 L CNN
F 2 "kicad-libraries:SON_5x6mm" H 6400 4600 50  0001 C CNN
F 3 "" H 6200 4500 50  0000 C CNN
	1    6200 4500
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:MOSFET_N_CH Q?
U 1 1 5E96C63B
P 6200 5050
F 0 "Q?" H 6391 5081 50  0000 L CNN
F 1 "CSD19533Q5A" H 6391 5004 31  0000 L CNN
F 2 "kicad-libraries:SON_5x6mm" H 6400 5150 50  0001 C CNN
F 3 "" H 6200 5050 50  0000 C CNN
	1    6200 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4700 6300 4750
Wire Wire Line
	6300 4750 5900 4750
Connection ~ 6300 4750
Wire Wire Line
	6300 4750 6300 4850
Wire Wire Line
	6000 4500 6000 4200
Wire Wire Line
	4500 4200 6000 4200
Wire Wire Line
	5900 4300 5900 4750
Wire Wire Line
	4500 4300 5900 4300
Wire Wire Line
	4500 4400 5800 4400
$Comp
L tinkerforge:Rs R?
U 1 1 5E9A2113
P 6300 5450
F 0 "R?" H 6350 5500 31  0000 L CNN
F 1 "0,01/WSHM2818R0100FEA" H 6350 5400 31  0000 L CNN
F 2 "kicad-libraries:R2818" H 6300 5450 60  0001 C CNN
F 3 "" H 6300 5450 60  0000 C CNN
	1    6300 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 5350 6300 5300
Wire Wire Line
	6300 5300 5700 5300
Wire Wire Line
	5700 5300 5700 4650
Wire Wire Line
	5700 4650 4500 4650
Connection ~ 6300 5300
Wire Wire Line
	6300 5300 6300 5250
Wire Wire Line
	4500 4750 5600 4750
Wire Wire Line
	5600 4750 5600 5600
Wire Wire Line
	5600 5600 6300 5600
Wire Wire Line
	6300 5600 6300 5550
Wire Wire Line
	6300 5300 7150 5300
Wire Wire Line
	6300 5600 6300 5700
Connection ~ 6300 5600
$Comp
L tinkerforge:GND #PWR?
U 1 1 5E9B4A80
P 6300 5700
F 0 "#PWR?" H 6300 5450 50  0001 C CNN
F 1 "GND" H 6305 5527 50  0000 C CNN
F 2 "" H 6300 5700 50  0000 C CNN
F 3 "" H 6300 5700 50  0000 C CNN
	1    6300 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3900 4500 3900
Wire Wire Line
	4500 3800 6800 3800
Wire Wire Line
	6800 3800 6800 3650
Wire Wire Line
	6800 3650 7150 3650
Wire Wire Line
	7150 3650 7150 3600
Wire Wire Line
	7150 3650 7150 3700
Connection ~ 7150 3650
Wire Wire Line
	6850 3400 6700 3400
Wire Wire Line
	6700 3400 6700 3700
Wire Wire Line
	6700 3700 4500 3700
Wire Wire Line
	6300 4300 6300 3000
Wire Wire Line
	6300 3000 6750 3000
Wire Wire Line
	7150 3000 7150 3200
Wire Wire Line
	7150 4100 7150 5300
Connection ~ 9550 1250
Wire Wire Line
	8650 2300 9150 2300
Wire Wire Line
	9150 2300 9150 2200
Wire Wire Line
	9150 1800 9550 1800
Connection ~ 9550 1800
$Comp
L tinkerforge:Rs R?
U 1 1 5EA0B9B9
P 8650 1500
F 0 "R?" H 8550 1550 31  0000 L CNN
F 1 "100k" H 8500 1450 31  0000 L CNN
F 2 "kicad-libraries:R0603F" H 8650 1500 60  0001 C CNN
F 3 "" H 8650 1500 60  0000 C CNN
	1    8650 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1400 8650 1250
Connection ~ 8650 1250
Wire Wire Line
	8650 1250 9550 1250
Wire Wire Line
	8650 1800 8650 1600
$Comp
L tinkerforge:ZENER D?
U 1 1 5EA1BB65
P 8650 2000
F 0 "D?" V 8600 1850 50  0000 L CNN
F 1 "Z12V" V 8750 1800 39  0000 L CNN
F 2 "" H 8650 2000 50  0000 C CNN
F 3 "" H 8650 2000 50  0000 C CNN
	1    8650 2000
	0    1    1    0   
$EndComp
Connection ~ 8650 1800
Wire Wire Line
	8650 2200 8650 2300
Connection ~ 8650 2300
Wire Wire Line
	9550 1250 9900 1250
$Comp
L tinkerforge:Varistor R?
U 1 1 5EA23D9F
P 9900 1500
F 0 "R?" H 10000 1700 50  0000 L CNN
F 1 "B72530T6250K062" H 9700 1850 31  0000 L CNN
F 2 "kicad-libraries:1210" H 9900 1500 60  0001 C CNN
F 3 "" H 9900 1500 60  0000 C CNN
	1    9900 1500
	1    0    0    -1  
$EndComp
Connection ~ 9900 1250
Wire Wire Line
	9900 1250 10250 1250
Wire Wire Line
	8850 1800 8850 2000
Wire Wire Line
	8650 1800 8850 1800
$Comp
L tinkerforge:CP1 C?
U 1 1 5EA2CBD6
P 7950 1500
F 0 "C?" H 8080 1546 50  0000 L CNN
F 1 "220uF/100V/UVY2A221MHD1TO" V 8250 1150 24  0000 L CNN
F 2 "kicad-libraries:ELKO_RAD_12" H 7950 1500 60  0001 C CNN
F 3 "" H 7950 1500 60  0000 C CNN
	1    7950 1500
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CP1 C?
U 1 1 5EA2F6BC
P 7450 1500
F 0 "C?" H 7580 1546 50  0000 L CNN
F 1 "220uF/100V/UVY2A221MHD1TO" V 7750 1150 24  0000 L CNN
F 2 "kicad-libraries:ELKO_RAD_12" H 7450 1500 60  0001 C CNN
F 3 "" H 7450 1500 60  0000 C CNN
	1    7450 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1300 7450 1250
Wire Wire Line
	7950 1300 7950 1250
Connection ~ 7950 1250
Wire Wire Line
	7950 1250 8650 1250
Wire Wire Line
	7450 1700 7450 2300
Wire Wire Line
	7450 2300 7950 2300
Wire Wire Line
	7950 1700 7950 2300
Connection ~ 7950 2300
Wire Wire Line
	7950 2300 8650 2300
Connection ~ 6750 3000
Wire Wire Line
	6750 3000 7150 3000
Connection ~ 7450 1250
Wire Wire Line
	7450 1250 7950 1250
Connection ~ 3800 3250
Text Notes 10550 1600 0    50   ~ 0
6-36V\n
$Comp
L tinkerforge:TVS D?
U 1 1 5EA57577
P 8800 3800
AR Path="/5EA57577" Ref="D?"  Part="1" 
AR Path="/5EAFEC80/5EA57577" Ref="D?"  Part="1" 
F 0 "D?" V 8600 3700 50  0000 L CNN
F 1 "SMBJ36CA" H 8700 3700 31  0000 L CNN
F 2 "kicad-libraries:SMB" H 8800 3800 50  0001 C CNN
F 3 "" H 8800 3800 50  0000 C CNN
	1    8800 3800
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:TVS D?
U 1 1 5EA5C412
P 9150 3800
AR Path="/5EA5C412" Ref="D?"  Part="1" 
AR Path="/5EAFEC80/5EA5C412" Ref="D?"  Part="1" 
F 0 "D?" V 8950 3700 50  0000 L CNN
F 1 "SMBJ36CA" H 9050 3700 31  0000 L CNN
F 2 "kicad-libraries:SMB" H 9150 3800 50  0001 C CNN
F 3 "" H 9150 3800 50  0000 C CNN
	1    9150 3800
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:TVS D?
U 1 1 5EA5C6B3
P 8800 4700
AR Path="/5EA5C6B3" Ref="D?"  Part="1" 
AR Path="/5EAFEC80/5EA5C6B3" Ref="D?"  Part="1" 
F 0 "D?" V 8600 4600 50  0000 L CNN
F 1 "SMBJ36CA" H 8700 4600 31  0000 L CNN
F 2 "kicad-libraries:SMB" H 8800 4700 50  0001 C CNN
F 3 "" H 8800 4700 50  0000 C CNN
	1    8800 4700
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:TVS D?
U 1 1 5EA5CD9F
P 9150 4700
AR Path="/5EA5CD9F" Ref="D?"  Part="1" 
AR Path="/5EAFEC80/5EA5CD9F" Ref="D?"  Part="1" 
F 0 "D?" V 8950 4600 50  0000 L CNN
F 1 "SMBJ36CA" H 9050 4600 31  0000 L CNN
F 2 "kicad-libraries:SMB" H 9150 4700 50  0001 C CNN
F 3 "" H 9150 4700 50  0000 C CNN
	1    9150 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 4950 8800 5000
Wire Wire Line
	9150 4950 9150 5000
Wire Wire Line
	3800 1250 4200 1250
Connection ~ 6750 1250
Wire Wire Line
	6750 1250 7450 1250
Wire Wire Line
	3800 1250 3800 3250
Wire Wire Line
	8000 4150 8000 3650
Wire Wire Line
	8000 3650 7150 3650
Wire Wire Line
	8000 4150 9150 4150
Wire Wire Line
	8800 3550 8800 3400
Wire Wire Line
	8800 3400 8950 3400
Wire Wire Line
	9150 3400 9150 3550
Wire Wire Line
	8950 3400 8950 3000
Connection ~ 8950 3400
Wire Wire Line
	8950 3400 9150 3400
Wire Wire Line
	6750 1250 6750 3000
Wire Wire Line
	7150 3000 8950 3000
Connection ~ 7150 3000
Wire Wire Line
	5800 5050 6000 5050
Wire Wire Line
	5800 4400 5800 5050
Wire Wire Line
	8000 4750 8000 4350
Wire Wire Line
	8000 4750 6300 4750
Wire Wire Line
	8000 4350 8800 4350
$Comp
L tinkerforge:Cs C?
U 1 1 5E8FB7B3
P 4200 1350
AR Path="/5E8FB7B3" Ref="C?"  Part="1" 
AR Path="/5EAFEC80/5E8FB7B3" Ref="C?"  Part="1" 
F 0 "C?" H 4050 1400 31  0000 L CNN
F 1 "100nF/100V" H 4200 1250 31  0000 L CNN
F 2 "kicad-libraries:C0603F" H 4200 1350 60  0001 C CNN
F 3 "" H 4200 1350 60  0000 C CNN
	1    4200 1350
	1    0    0    -1  
$EndComp
Connection ~ 4200 1250
Wire Wire Line
	4200 1250 4800 1250
$Comp
L tinkerforge:CP1 C?
U 1 1 5E8FD966
P 4800 1450
F 0 "C?" H 4600 1600 50  0000 L CNN
F 1 "10uF/100V" V 4950 1350 24  0000 L CNN
F 2 "kicad-libraries:ELKO_83" H 4800 1450 60  0001 C CNN
F 3 "" H 4800 1450 60  0000 C CNN
	1    4800 1450
	1    0    0    -1  
$EndComp
Connection ~ 4800 1250
Wire Wire Line
	4800 1250 6750 1250
Wire Wire Line
	4200 1450 4200 1800
Wire Wire Line
	4200 1800 4500 1800
Wire Wire Line
	4800 1800 4800 1650
$Comp
L tinkerforge:GND #PWR?
U 1 1 5E904C40
P 4500 1800
AR Path="/5E904C40" Ref="#PWR?"  Part="1" 
AR Path="/5EAFEC80/5E904C40" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4500 1550 50  0001 C CNN
F 1 "GND" H 4505 1627 50  0000 C CNN
F 2 "" H 4500 1800 50  0000 C CNN
F 3 "" H 4500 1800 50  0000 C CNN
	1    4500 1800
	1    0    0    -1  
$EndComp
Connection ~ 4500 1800
Wire Wire Line
	4500 1800 4800 1800
$EndSCHEMATC
