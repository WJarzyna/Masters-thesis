EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
L Driver_FET:IRS2186 U3
U 1 1 6287A5ED
P 8550 6200
F 0 "U3" H 8550 6881 50  0000 C CNN
F 1 "IRS2186" H 8550 6790 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket" H 8550 6200 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/irs2186pbf.pdf?fileId=5546d462533600a40153567716c427ed" H 8550 6200 50  0001 C CNN
	1    8550 6200
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF540N Q2
U 1 1 6287BD23
P 9750 6500
F 0 "Q2" H 9954 6546 50  0000 L CNN
F 1 "IRF540N" H 9954 6455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 10000 6425 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 9750 6500 50  0001 L CNN
	1    9750 6500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BUZ11 Q4
U 1 1 6287E48C
P 10550 6500
F 0 "Q4" H 10755 6546 50  0000 L CNN
F 1 "IRFP3077" H 10755 6455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-247-3_Vertical" H 10750 6425 50  0001 L CIN
F 3 "" H 10550 6500 50  0001 L CNN
	1    10550 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 6300 10650 6300
Wire Wire Line
	10350 6500 10150 6500
Wire Wire Line
	10150 6500 10150 6250
Wire Wire Line
	10150 6250 9550 6250
Wire Wire Line
	9550 6250 9550 6500
Wire Wire Line
	9850 6700 10650 6700
$Comp
L Transistor_FET:IRF540N Q1
U 1 1 6289D9CF
P 9750 5800
F 0 "Q1" H 9954 5846 50  0000 L CNN
F 1 "IRF540N" H 9954 5755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 10000 5725 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 9750 5800 50  0001 L CNN
	1    9750 5800
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BUZ11 Q3
U 1 1 6289D9D5
P 10550 5800
F 0 "Q3" H 10755 5846 50  0000 L CNN
F 1 "IRFP3077" H 10755 5755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-247-3_Vertical" H 10750 5725 50  0001 L CIN
F 3 "" H 10550 5800 50  0001 L CNN
	1    10550 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5600 10650 5600
Wire Wire Line
	10350 5800 10150 5800
Wire Wire Line
	10150 5800 10150 5550
Wire Wire Line
	10150 5550 9550 5550
Wire Wire Line
	9550 5550 9550 5800
Wire Wire Line
	9850 6000 10650 6000
Wire Wire Line
	10650 6000 10650 6150
Connection ~ 10650 6000
Connection ~ 10650 6300
Connection ~ 10650 6150
Wire Wire Line
	10650 6150 10650 6300
Wire Wire Line
	9550 5800 9500 5800
Connection ~ 9550 5800
Wire Wire Line
	9550 6500 9500 6500
Connection ~ 9550 6500
$Comp
L Device:D D1
U 1 1 628F57A1
P 8550 5400
F 0 "D1" H 8550 5183 50  0000 C CNN
F 1 "1N4007" H 8550 5274 50  0000 C CNN
F 2 "Diode_THT:D_DO-15_P12.70mm_Horizontal" H 8550 5400 50  0001 C CNN
F 3 "~" H 8550 5400 50  0001 C CNN
	1    8550 5400
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C2
U 1 1 628F65C7
P 9000 6250
F 0 "C2" H 9118 6296 50  0000 L CNN
F 1 "470u" H 9118 6205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 9038 6100 50  0001 C CNN
F 3 "~" H 9000 6250 50  0001 C CNN
	1    9000 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 628F74AA
P 7950 5850
F 0 "C1" H 8068 5896 50  0000 L CNN
F 1 "470u" H 8068 5805 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 7988 5700 50  0001 C CNN
F 3 "~" H 7950 5850 50  0001 C CNN
	1    7950 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6290FB22
P 9350 6500
F 0 "R2" V 9143 6500 50  0000 C CNN
F 1 "22" V 9234 6500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 9280 6500 50  0001 C CNN
F 3 "~" H 9350 6500 50  0001 C CNN
	1    9350 6500
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 5400 9000 5400
Wire Wire Line
	9000 5400 9000 5900
Wire Wire Line
	8850 5900 9000 5900
Connection ~ 9000 5900
Wire Wire Line
	9000 5900 9000 6100
Wire Wire Line
	8850 6400 9000 6400
Wire Wire Line
	9000 6400 9250 6400
Wire Wire Line
	9250 6400 9250 6150
Wire Wire Line
	9250 6150 10650 6150
Connection ~ 9000 6400
Wire Wire Line
	8850 6500 9200 6500
$Comp
L Device:R R1
U 1 1 629320EA
P 9350 5800
F 0 "R1" V 9143 5800 50  0000 C CNN
F 1 "22" V 9234 5800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 9280 5800 50  0001 C CNN
F 3 "~" H 9350 5800 50  0001 C CNN
	1    9350 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 6000 9100 6000
Wire Wire Line
	9100 6000 9100 5800
Wire Wire Line
	9100 5800 9200 5800
Wire Wire Line
	8550 5700 7950 5700
Wire Wire Line
	8400 5400 7950 5400
Wire Wire Line
	7950 5400 7950 5700
Connection ~ 7950 5700
$Comp
L power:GND #PWR0101
U 1 1 6293B9DB
P 8550 6700
F 0 "#PWR0101" H 8550 6450 50  0001 C CNN
F 1 "GND" H 8555 6527 50  0000 C CNN
F 2 "" H 8550 6700 50  0001 C CNN
F 3 "" H 8550 6700 50  0001 C CNN
	1    8550 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6293C52A
P 7950 6000
F 0 "#PWR0102" H 7950 5750 50  0001 C CNN
F 1 "GND" H 7955 5827 50  0000 C CNN
F 2 "" H 7950 6000 50  0001 C CNN
F 3 "" H 7950 6000 50  0001 C CNN
	1    7950 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6294AD62
P 10650 6700
F 0 "#PWR0103" H 10650 6450 50  0001 C CNN
F 1 "GND" H 10655 6527 50  0000 C CNN
F 2 "" H 10650 6700 50  0001 C CNN
F 3 "" H 10650 6700 50  0001 C CNN
	1    10650 6700
	1    0    0    -1  
$EndComp
Connection ~ 10650 6700
$Comp
L power:+48V #PWR0104
U 1 1 6294CEF1
P 10650 5400
F 0 "#PWR0104" H 10650 5250 50  0001 C CNN
F 1 "+48V" H 10665 5573 50  0000 C CNN
F 2 "" H 10650 5400 50  0001 C CNN
F 3 "" H 10650 5400 50  0001 C CNN
	1    10650 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0105
U 1 1 6294DE56
P 7950 5400
F 0 "#PWR0105" H 7950 5250 50  0001 C CNN
F 1 "+12V" H 7965 5573 50  0000 C CNN
F 2 "" H 7950 5400 50  0001 C CNN
F 3 "" H 7950 5400 50  0001 C CNN
	1    7950 5400
	1    0    0    -1  
$EndComp
Connection ~ 7950 5400
Wire Wire Line
	10650 5400 10650 5600
Connection ~ 10650 5600
$Comp
L Device:CP C4
U 1 1 62953F0D
P 11300 5750
F 0 "C4" H 11418 5796 50  0000 L CNN
F 1 "2200u" H 11418 5705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D18.0mm_P7.50mm" H 11338 5600 50  0001 C CNN
F 3 "~" H 11300 5750 50  0001 C CNN
	1    11300 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 6295482D
P 11650 5750
F 0 "C5" H 11765 5796 50  0000 L CNN
F 1 "100n" H 11765 5705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D9.0mm_W2.5mm_P5.00mm" H 11688 5600 50  0001 C CNN
F 3 "~" H 11650 5750 50  0001 C CNN
	1    11650 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11650 5600 11300 5600
Connection ~ 11300 5600
Wire Wire Line
	11300 5600 10650 5600
$Comp
L power:GND #PWR0106
U 1 1 62956001
P 11300 5900
F 0 "#PWR0106" H 11300 5650 50  0001 C CNN
F 1 "GND" H 11305 5727 50  0000 C CNN
F 2 "" H 11300 5900 50  0001 C CNN
F 3 "" H 11300 5900 50  0001 C CNN
	1    11300 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 629565E8
P 11650 5900
F 0 "#PWR0107" H 11650 5650 50  0001 C CNN
F 1 "GND" H 11655 5727 50  0000 C CNN
F 2 "" H 11650 5900 50  0001 C CNN
F 3 "" H 11650 5900 50  0001 C CNN
	1    11650 5900
	1    0    0    -1  
$EndComp
Text GLabel 12200 6150 1    50   Input ~ 0
A
Wire Wire Line
	10650 6150 12000 6150
$Comp
L Isolator:TLP2748 U1
U 1 1 62B61615
P 7100 5650
F 0 "U1" H 7544 5696 50  0000 L CNN
F 1 "TLP2748" H 7544 5605 50  0000 L CNN
F 2 "Package_SO:SO-6L_10x3.84mm_P1.27mm" H 6400 5150 50  0001 L CIN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=29407&prodName=TLP2748" H 6992 5675 50  0001 L CNN
	1    7100 5650
	1    0    0    -1  
$EndComp
$Comp
L Isolator:TLP2748 U2
U 1 1 62B737D7
P 7100 6900
F 0 "U2" H 7544 6946 50  0000 L CNN
F 1 "TLP2748" H 7544 6855 50  0000 L CNN
F 2 "Package_SO:SO-6L_10x3.84mm_P1.27mm" H 6400 6400 50  0001 L CIN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=29407&prodName=TLP2748" H 6992 6925 50  0001 L CNN
	1    7100 6900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 62B93B44
P 7100 5250
F 0 "#PWR0112" H 7100 5100 50  0001 C CNN
F 1 "+5V" H 7115 5423 50  0000 C CNN
F 2 "" H 7100 5250 50  0001 C CNN
F 3 "" H 7100 5250 50  0001 C CNN
	1    7100 5250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 62B9A25D
P 7100 6500
F 0 "#PWR0113" H 7100 6350 50  0001 C CNN
F 1 "+5V" H 7115 6673 50  0000 C CNN
F 2 "" H 7100 6500 50  0001 C CNN
F 3 "" H 7100 6500 50  0001 C CNN
	1    7100 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 62B9ACA7
P 7100 7300
F 0 "#PWR0114" H 7100 7050 50  0001 C CNN
F 1 "GND" H 7105 7127 50  0000 C CNN
F 2 "" H 7100 7300 50  0001 C CNN
F 3 "" H 7100 7300 50  0001 C CNN
	1    7100 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 62B9B651
P 7100 6050
F 0 "#PWR0115" H 7100 5800 50  0001 C CNN
F 1 "GND" H 7105 5877 50  0000 C CNN
F 2 "" H 7100 6050 50  0001 C CNN
F 3 "" H 7100 6050 50  0001 C CNN
	1    7100 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 6300 7500 6900
Wire Wire Line
	7500 6200 7500 5650
Wire Wire Line
	8250 6200 7500 6200
Wire Wire Line
	7500 6300 8250 6300
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 62C53433
P 5350 4900
F 0 "J1" H 5268 4575 50  0000 C CNN
F 1 "Conn_01x02" H 5268 4666 50  0000 C CNN
F 2 "Connector_AMASS:AMASS_XT60-M_1x02_P7.20mm_Vertical" H 5350 4900 50  0001 C CNN
F 3 "~" H 5350 4900 50  0001 C CNN
	1    5350 4900
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 62C54950
P 5350 5900
F 0 "J2" H 5268 5275 50  0000 C CNN
F 1 "Conn_01x08" H 5268 5366 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Horizontal" H 5350 5900 50  0001 C CNN
F 3 "~" H 5350 5900 50  0001 C CNN
	1    5350 5900
	-1   0    0    1   
$EndComp
Text GLabel 5550 5500 2    50   Input ~ 0
A
$Comp
L power:+12V #PWR0116
U 1 1 62C65950
P 5850 5600
F 0 "#PWR0116" H 5850 5450 50  0001 C CNN
F 1 "+12V" H 5865 5773 50  0000 C CNN
F 2 "" H 5850 5600 50  0001 C CNN
F 3 "" H 5850 5600 50  0001 C CNN
	1    5850 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0117
U 1 1 62C6897A
P 6700 7100
F 0 "#PWR0117" H 6700 6850 50  0001 C CNN
F 1 "GNDD" H 6704 6945 50  0000 C CNN
F 2 "" H 6700 7100 50  0001 C CNN
F 3 "" H 6700 7100 50  0001 C CNN
	1    6700 7100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0118
U 1 1 62C68EAC
P 6700 5850
F 0 "#PWR0118" H 6700 5600 50  0001 C CNN
F 1 "GNDD" H 6704 5695 50  0000 C CNN
F 2 "" H 6700 5850 50  0001 C CNN
F 3 "" H 6700 5850 50  0001 C CNN
	1    6700 5850
	1    0    0    -1  
$EndComp
Text GLabel 5550 6200 2    50   Input ~ 0
I_A
$Comp
L power:GNDD #PWR0119
U 1 1 62C79E35
P 5850 6100
F 0 "#PWR0119" H 5850 5850 50  0001 C CNN
F 1 "GNDD" H 5854 5945 50  0000 C CNN
F 2 "" H 5850 6100 50  0001 C CNN
F 3 "" H 5850 6100 50  0001 C CNN
	1    5850 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 6100 5850 6100
Wire Wire Line
	5550 5600 5850 5600
Wire Wire Line
	6050 6000 5550 6000
$Comp
L power:+5V #PWR0121
U 1 1 62CA59F4
P 6050 5700
F 0 "#PWR0121" H 6050 5550 50  0001 C CNN
F 1 "+5V" H 6065 5873 50  0000 C CNN
F 2 "" H 6050 5700 50  0001 C CNN
F 3 "" H 6050 5700 50  0001 C CNN
	1    6050 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5700 5550 5700
Wire Wire Line
	5550 5800 6400 5800
Wire Wire Line
	6400 5800 6400 5450
Wire Wire Line
	6400 5450 6700 5450
Wire Wire Line
	5550 5900 6400 5900
Wire Wire Line
	6400 5900 6400 6700
Wire Wire Line
	6400 6700 6700 6700
$Comp
L power:+48V #PWR0122
U 1 1 62CBF8BF
P 5750 4800
F 0 "#PWR0122" H 5750 4650 50  0001 C CNN
F 1 "+48V" H 5765 4973 50  0000 C CNN
F 2 "" H 5750 4800 50  0001 C CNN
F 3 "" H 5750 4800 50  0001 C CNN
	1    5750 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4800 5550 4800
$Comp
L power:GND #PWR0123
U 1 1 62CC7737
P 5750 4900
F 0 "#PWR0123" H 5750 4650 50  0001 C CNN
F 1 "GND" H 5755 4727 50  0000 C CNN
F 2 "" H 5750 4900 50  0001 C CNN
F 3 "" H 5750 4900 50  0001 C CNN
	1    5750 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4900 5550 4900
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 62ACB93F
P 13250 6150
F 0 "J3" H 13330 6192 50  0000 L CNN
F 1 "Conn_01x01" H 13330 6101 50  0000 L CNN
F 2 "Connector:Banana_Jack_1Pin" H 13250 6150 50  0001 C CNN
F 3 "~" H 13250 6150 50  0001 C CNN
	1    13250 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	12200 6150 13050 6150
$Comp
L power:GNDD #PWR0110
U 1 1 629D2174
P 11250 7250
F 0 "#PWR0110" H 11250 7000 50  0001 C CNN
F 1 "GNDD" H 11254 7095 50  0000 C CNN
F 2 "" H 11250 7250 50  0001 C CNN
F 3 "" H 11250 7250 50  0001 C CNN
	1    11250 7250
	1    0    0    -1  
$EndComp
Text GLabel 11250 6950 0    50   Input ~ 0
I_A
$Comp
L Device:C C3
U 1 1 6299EA46
P 11250 7100
F 0 "C3" H 11365 7146 50  0000 L CNN
F 1 "100n" H 11365 7055 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D9.0mm_W2.5mm_P5.00mm" H 11288 6950 50  0001 C CNN
F 3 "~" H 11250 7100 50  0001 C CNN
	1    11250 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	11450 6950 11250 6950
Wire Wire Line
	12100 6950 11750 6950
Wire Wire Line
	12400 6950 12400 6550
$Comp
L power:GNDD #PWR0111
U 1 1 629D283A
P 12400 7250
F 0 "#PWR0111" H 12400 7000 50  0001 C CNN
F 1 "GNDD" H 12404 7095 50  0000 C CNN
F 2 "" H 12400 7250 50  0001 C CNN
F 3 "" H 12400 7250 50  0001 C CNN
	1    12400 7250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0109
U 1 1 629D177D
P 11800 6550
F 0 "#PWR0109" H 11800 6300 50  0001 C CNN
F 1 "GNDD" H 11804 6395 50  0000 C CNN
F 2 "" H 11800 6550 50  0001 C CNN
F 3 "" H 11800 6550 50  0001 C CNN
	1    11800 6550
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0108
U 1 1 629D0BCA
P 12400 6550
F 0 "#PWR0108" H 12400 6400 50  0001 C CNN
F 1 "+3V3" H 12415 6723 50  0000 C CNN
F 2 "" H 12400 6550 50  0001 C CNN
F 3 "" H 12400 6550 50  0001 C CNN
	1    12400 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6299FBA0
P 11600 6950
F 0 "R3" H 11670 6996 50  0000 L CNN
F 1 "1k" H 11670 6905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 11530 6950 50  0001 C CNN
F 3 "~" H 11600 6950 50  0001 C CNN
	1    11600 6950
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C6
U 1 1 6299F35F
P 12400 7100
F 0 "C6" H 12518 7146 50  0000 L CNN
F 1 "100u" H 12518 7055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 12438 6950 50  0001 C CNN
F 3 "~" H 12400 7100 50  0001 C CNN
	1    12400 7100
	1    0    0    -1  
$EndComp
Connection ~ 12400 6550
$Comp
L Sensor_Current:ACS758xCB-100B-PFF U4
U 1 1 6299838C
P 12100 6550
F 0 "U4" V 12054 6894 50  0000 L CNN
F 1 "ACS758xCB-100B-PFF" V 12145 6894 50  0000 L CNN
F 2 "Sensor_Current:Allegro_CB_PFF" H 12100 6550 50  0001 C CNN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS758-Datasheet.ashx?la=en" H 12100 6550 50  0001 C CNN
	1    12100 6550
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0120
U 1 1 62C96938
P 6050 6000
F 0 "#PWR0120" H 6050 5850 50  0001 C CNN
F 1 "+3.3V" H 6065 6173 50  0000 C CNN
F 2 "" H 6050 6000 50  0001 C CNN
F 3 "" H 6050 6000 50  0001 C CNN
	1    6050 6000
	-1   0    0    1   
$EndComp
$EndSCHEMATC