EESchema Schematic File Version 4
LIBS:agc-dsky-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title "AGC DSKY Emulator: Indicator Lamps"
Date "2018-11-10"
Rev "v0.1"
Comp ""
Comment1 "Gregory Brooks"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CAF38ED
P 2250 2000
AR Path="/5CAF38ED" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CAF38ED" Ref="IC31"  Part="1" 
F 0 "IC31" H 2250 2325 50  0000 C CNN
F 1 "WS2812B" H 2250 2234 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 1950 1700 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 1950 1600 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 1950 1500 50  0001 L CNN "Aliexpress"
	1    2250 2000
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CAF38F4
P 2700 3000
AR Path="/5CAF38F4" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CAF38F4" Ref="#PWR0157"  Part="1" 
F 0 "#PWR0157" H 2700 3110 50  0001 L CNN
F 1 "5v" H 2700 3124 50  0000 C CNN
F 2 "" H 2700 3000 50  0001 C CNN
F 3 "" H 2700 3000 50  0001 C CNN
	1    2700 3000
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CAF38FB
P 2250 3150
AR Path="/5CAF38FB" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CAF38FB" Ref="IC32"  Part="1" 
F 0 "IC32" H 2250 3475 50  0000 C CNN
F 1 "WS2812B" H 2250 3384 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 1950 2850 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 1950 2750 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 1950 2650 50  0001 L CNN "Aliexpress"
	1    2250 3150
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:D D?
U 1 1 5CAF3903
P 2850 1850
AR Path="/5CAF3903" Ref="D?"  Part="1" 
AR Path="/5CAD9882/5CAF3903" Ref="D1"  Part="1" 
F 0 "D1" V 2946 1792 50  0000 R CNN
F 1 "MMSD4148T1G" V 2855 1792 50  0000 R CNN
F 2 "agg:SOD-123" H 2850 1850 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2140498.pdf" H 2850 1850 50  0001 C CNN
F 4 "9556079" H 2850 1850 50  0001 C CNN "Farnell"
	1    2850 1850
	0    -1   -1   0   
$EndComp
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CAF390A
P 2850 1700
AR Path="/5CAF390A" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CAF390A" Ref="#PWR0158"  Part="1" 
F 0 "#PWR0158" H 2850 1810 50  0001 L CNN
F 1 "5v" H 2850 1824 50  0000 C CNN
F 2 "" H 2850 1700 50  0001 C CNN
F 3 "" H 2850 1700 50  0001 C CNN
	1    2850 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1900 2850 1850
Wire Wire Line
	2850 1700 2850 1750
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CAF3913
P 2850 2050
AR Path="/5CAF3913" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CAF3913" Ref="#PWR0159"  Part="1" 
F 0 "#PWR0159" H 2720 2090 50  0001 L CNN
F 1 "GND" H 2950 2000 50  0000 C CNN
F 2 "" H 2850 2050 50  0001 C CNN
F 3 "" H 2850 2050 50  0001 C CNN
	1    2850 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2000 2850 2050
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CAF391B
P 2700 3200
AR Path="/5CAF391B" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CAF391B" Ref="#PWR0160"  Part="1" 
F 0 "#PWR0160" H 2570 3240 50  0001 L CNN
F 1 "GND" H 2800 3150 50  0000 C CNN
F 2 "" H 2700 3200 50  0001 C CNN
F 3 "" H 2700 3200 50  0001 C CNN
	1    2700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3150 2700 3200
Wire Wire Line
	2650 3150 2700 3150
Wire Wire Line
	2650 3050 2700 3050
Wire Wire Line
	2700 3050 2700 3000
Wire Wire Line
	1850 2000 1800 2000
Wire Wire Line
	1800 3050 1850 3050
Text Notes 3050 1800 0    50   ~ 0
Hack to lower VDD to around 4.3V for first LED (replaces level shifter)\nSource: https://todbot.com/blog/2017/01/12/crashspace-bigbutton-w-esp8266/
Text HLabel 1750 1900 0    50   Input ~ 0
DIN
Wire Wire Line
	1750 1900 1850 1900
$Comp
L agg-kicad:C C?
U 1 1 5CB0E050
P 2850 1900
AR Path="/5CB0E050" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0E050" Ref="C19"  Part="1" 
F 0 "C19" V 2854 1958 50  0000 L CNN
F 1 "100nF" V 2945 1958 50  0000 L CNN
F 2 "agg:0402" H 2850 1900 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 2850 1900 50  0001 C CNN
F 4 "2810260" H 2850 1900 50  0001 C CNN "Farnell"
	1    2850 1900
	0    1    1    0   
$EndComp
$Comp
L agg-kicad:C C?
U 1 1 5CB0E14A
P 2700 3050
AR Path="/5CB0E14A" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0E14A" Ref="C20"  Part="1" 
F 0 "C20" V 2704 3108 50  0000 L CNN
F 1 "100nF" V 2795 3108 50  0000 L CNN
F 2 "agg:0402" H 2700 3050 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 2700 3050 50  0001 C CNN
F 4 "2810260" H 2700 3050 50  0001 C CNN "Farnell"
	1    2700 3050
	0    1    1    0   
$EndComp
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0E2E8
P 2700 3550
AR Path="/5CB0E2E8" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0E2E8" Ref="#PWR0161"  Part="1" 
F 0 "#PWR0161" H 2700 3660 50  0001 L CNN
F 1 "5v" H 2700 3674 50  0000 C CNN
F 2 "" H 2700 3550 50  0001 C CNN
F 3 "" H 2700 3550 50  0001 C CNN
	1    2700 3550
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0E2EF
P 2250 3700
AR Path="/5CB0E2EF" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0E2EF" Ref="IC33"  Part="1" 
F 0 "IC33" H 2250 4025 50  0000 C CNN
F 1 "WS2812B" H 2250 3934 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 1950 3400 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 1950 3300 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 1950 3200 50  0001 L CNN "Aliexpress"
	1    2250 3700
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0E2F6
P 2700 3750
AR Path="/5CB0E2F6" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0E2F6" Ref="#PWR0162"  Part="1" 
F 0 "#PWR0162" H 2570 3790 50  0001 L CNN
F 1 "GND" H 2800 3700 50  0000 C CNN
F 2 "" H 2700 3750 50  0001 C CNN
F 3 "" H 2700 3750 50  0001 C CNN
	1    2700 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3700 2700 3750
Wire Wire Line
	2650 3700 2700 3700
Wire Wire Line
	2650 3600 2700 3600
Wire Wire Line
	2700 3600 2700 3550
$Comp
L agg-kicad:C C?
U 1 1 5CB0E301
P 2700 3600
AR Path="/5CB0E301" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0E301" Ref="C21"  Part="1" 
F 0 "C21" V 2704 3658 50  0000 L CNN
F 1 "100nF" V 2795 3658 50  0000 L CNN
F 2 "agg:0402" H 2700 3600 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 2700 3600 50  0001 C CNN
F 4 "2810260" H 2700 3600 50  0001 C CNN "Farnell"
	1    2700 3600
	0    1    1    0   
$EndComp
Connection ~ 2700 3050
Connection ~ 2700 3150
Connection ~ 2700 3600
Connection ~ 2700 3700
Wire Wire Line
	1850 3150 1800 3150
Wire Wire Line
	1800 3150 1800 3600
Wire Wire Line
	1800 3600 1850 3600
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0EAAE
P 2700 4100
AR Path="/5CB0EAAE" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0EAAE" Ref="#PWR0163"  Part="1" 
F 0 "#PWR0163" H 2700 4210 50  0001 L CNN
F 1 "5v" H 2700 4224 50  0000 C CNN
F 2 "" H 2700 4100 50  0001 C CNN
F 3 "" H 2700 4100 50  0001 C CNN
	1    2700 4100
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0EAB5
P 2250 4250
AR Path="/5CB0EAB5" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0EAB5" Ref="IC34"  Part="1" 
F 0 "IC34" H 2250 4575 50  0000 C CNN
F 1 "WS2812B" H 2250 4484 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 1950 3950 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 1950 3850 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 1950 3750 50  0001 L CNN "Aliexpress"
	1    2250 4250
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0EABC
P 2700 4300
AR Path="/5CB0EABC" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0EABC" Ref="#PWR0164"  Part="1" 
F 0 "#PWR0164" H 2570 4340 50  0001 L CNN
F 1 "GND" H 2800 4250 50  0000 C CNN
F 2 "" H 2700 4300 50  0001 C CNN
F 3 "" H 2700 4300 50  0001 C CNN
	1    2700 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 4250 2700 4300
Wire Wire Line
	2650 4250 2700 4250
Wire Wire Line
	2650 4150 2700 4150
Wire Wire Line
	2700 4150 2700 4100
$Comp
L agg-kicad:C C?
U 1 1 5CB0EAC7
P 2700 4150
AR Path="/5CB0EAC7" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0EAC7" Ref="C22"  Part="1" 
F 0 "C22" V 2704 4208 50  0000 L CNN
F 1 "100nF" V 2795 4208 50  0000 L CNN
F 2 "agg:0402" H 2700 4150 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 2700 4150 50  0001 C CNN
F 4 "2810260" H 2700 4150 50  0001 C CNN "Farnell"
	1    2700 4150
	0    1    1    0   
$EndComp
Connection ~ 2700 4150
Connection ~ 2700 4250
Wire Wire Line
	1800 3700 1800 4150
Wire Wire Line
	1800 4150 1850 4150
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0EE11
P 2700 4650
AR Path="/5CB0EE11" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0EE11" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 2700 4760 50  0001 L CNN
F 1 "5v" H 2700 4774 50  0000 C CNN
F 2 "" H 2700 4650 50  0001 C CNN
F 3 "" H 2700 4650 50  0001 C CNN
	1    2700 4650
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0EE18
P 2250 4800
AR Path="/5CB0EE18" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0EE18" Ref="IC35"  Part="1" 
F 0 "IC35" H 2250 5125 50  0000 C CNN
F 1 "WS2812B" H 2250 5034 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 1950 4500 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 1950 4400 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 1950 4300 50  0001 L CNN "Aliexpress"
	1    2250 4800
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0EE1F
P 2700 4850
AR Path="/5CB0EE1F" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0EE1F" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 2570 4890 50  0001 L CNN
F 1 "GND" H 2800 4800 50  0000 C CNN
F 2 "" H 2700 4850 50  0001 C CNN
F 3 "" H 2700 4850 50  0001 C CNN
	1    2700 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 4800 2700 4850
Wire Wire Line
	2650 4800 2700 4800
Wire Wire Line
	2650 4700 2700 4700
Wire Wire Line
	2700 4700 2700 4650
$Comp
L agg-kicad:C C?
U 1 1 5CB0EE2A
P 2700 4700
AR Path="/5CB0EE2A" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0EE2A" Ref="C23"  Part="1" 
F 0 "C23" V 2704 4758 50  0000 L CNN
F 1 "100nF" V 2795 4758 50  0000 L CNN
F 2 "agg:0402" H 2700 4700 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 2700 4700 50  0001 C CNN
F 4 "2810260" H 2700 4700 50  0001 C CNN "Farnell"
	1    2700 4700
	0    1    1    0   
$EndComp
Connection ~ 2700 4700
Connection ~ 2700 4800
Wire Wire Line
	1800 4250 1800 4700
Wire Wire Line
	1800 4700 1850 4700
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0EE35
P 2700 5200
AR Path="/5CB0EE35" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0EE35" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 2700 5310 50  0001 L CNN
F 1 "5v" H 2700 5324 50  0000 C CNN
F 2 "" H 2700 5200 50  0001 C CNN
F 3 "" H 2700 5200 50  0001 C CNN
	1    2700 5200
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0EE3C
P 2250 5350
AR Path="/5CB0EE3C" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0EE3C" Ref="IC36"  Part="1" 
F 0 "IC36" H 2250 5675 50  0000 C CNN
F 1 "WS2812B" H 2250 5584 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 1950 5050 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 1950 4950 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 1950 4850 50  0001 L CNN "Aliexpress"
	1    2250 5350
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0EE43
P 2700 5400
AR Path="/5CB0EE43" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0EE43" Ref="#PWR0168"  Part="1" 
F 0 "#PWR0168" H 2570 5440 50  0001 L CNN
F 1 "GND" H 2800 5350 50  0000 C CNN
F 2 "" H 2700 5400 50  0001 C CNN
F 3 "" H 2700 5400 50  0001 C CNN
	1    2700 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5350 2700 5400
Wire Wire Line
	2650 5350 2700 5350
Wire Wire Line
	2650 5250 2700 5250
Wire Wire Line
	2700 5250 2700 5200
$Comp
L agg-kicad:C C?
U 1 1 5CB0EE4E
P 2700 5250
AR Path="/5CB0EE4E" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0EE4E" Ref="C24"  Part="1" 
F 0 "C24" V 2704 5308 50  0000 L CNN
F 1 "100nF" V 2795 5308 50  0000 L CNN
F 2 "agg:0402" H 2700 5250 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 2700 5250 50  0001 C CNN
F 4 "2810260" H 2700 5250 50  0001 C CNN "Farnell"
	1    2700 5250
	0    1    1    0   
$EndComp
Connection ~ 2700 5250
Connection ~ 2700 5350
Wire Wire Line
	1800 4800 1800 5250
Wire Wire Line
	1800 5250 1850 5250
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0F53D
P 3650 3150
AR Path="/5CB0F53D" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0F53D" Ref="IC37"  Part="1" 
F 0 "IC37" H 3650 3475 50  0000 C CNN
F 1 "WS2812B" H 3650 3384 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 2850 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 2750 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 2650 50  0001 L CNN "Aliexpress"
	1    3650 3150
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0F544
P 4100 3200
AR Path="/5CB0F544" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F544" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 3970 3240 50  0001 L CNN
F 1 "GND" H 4200 3150 50  0000 C CNN
F 2 "" H 4100 3200 50  0001 C CNN
F 3 "" H 4100 3200 50  0001 C CNN
	1    4100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3150 4100 3200
Wire Wire Line
	4050 3150 4100 3150
Wire Wire Line
	4050 3050 4100 3050
Wire Wire Line
	4100 3050 4100 3000
$Comp
L agg-kicad:C C?
U 1 1 5CB0F551
P 4100 3050
AR Path="/5CB0F551" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0F551" Ref="C25"  Part="1" 
F 0 "C25" V 4104 3108 50  0000 L CNN
F 1 "100nF" V 4195 3108 50  0000 L CNN
F 2 "agg:0402" H 4100 3050 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 3050 50  0001 C CNN
F 4 "2810260" H 4100 3050 50  0001 C CNN "Farnell"
	1    4100 3050
	0    1    1    0   
$EndComp
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0F558
P 4100 3550
AR Path="/5CB0F558" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F558" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 4100 3660 50  0001 L CNN
F 1 "5v" H 4100 3674 50  0000 C CNN
F 2 "" H 4100 3550 50  0001 C CNN
F 3 "" H 4100 3550 50  0001 C CNN
	1    4100 3550
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0F55F
P 3650 3700
AR Path="/5CB0F55F" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0F55F" Ref="IC38"  Part="1" 
F 0 "IC38" H 3650 4025 50  0000 C CNN
F 1 "WS2812B" H 3650 3934 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 3400 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 3300 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 3200 50  0001 L CNN "Aliexpress"
	1    3650 3700
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0F566
P 4100 3750
AR Path="/5CB0F566" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F566" Ref="#PWR0171"  Part="1" 
F 0 "#PWR0171" H 3970 3790 50  0001 L CNN
F 1 "GND" H 4200 3700 50  0000 C CNN
F 2 "" H 4100 3750 50  0001 C CNN
F 3 "" H 4100 3750 50  0001 C CNN
	1    4100 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3700 4100 3750
Wire Wire Line
	4050 3700 4100 3700
Wire Wire Line
	4050 3600 4100 3600
Wire Wire Line
	4100 3600 4100 3550
$Comp
L agg-kicad:C C?
U 1 1 5CB0F571
P 4100 3600
AR Path="/5CB0F571" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0F571" Ref="C26"  Part="1" 
F 0 "C26" V 4104 3658 50  0000 L CNN
F 1 "100nF" V 4195 3658 50  0000 L CNN
F 2 "agg:0402" H 4100 3600 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 3600 50  0001 C CNN
F 4 "2810260" H 4100 3600 50  0001 C CNN "Farnell"
	1    4100 3600
	0    1    1    0   
$EndComp
Connection ~ 4100 3050
Connection ~ 4100 3150
Connection ~ 4100 3600
Connection ~ 4100 3700
Wire Wire Line
	3250 3150 3200 3150
Wire Wire Line
	3200 3150 3200 3600
Wire Wire Line
	3200 3600 3250 3600
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0F57F
P 4100 4100
AR Path="/5CB0F57F" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F57F" Ref="#PWR0172"  Part="1" 
F 0 "#PWR0172" H 4100 4210 50  0001 L CNN
F 1 "5v" H 4100 4224 50  0000 C CNN
F 2 "" H 4100 4100 50  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0F586
P 3650 4250
AR Path="/5CB0F586" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0F586" Ref="IC39"  Part="1" 
F 0 "IC39" H 3650 4575 50  0000 C CNN
F 1 "WS2812B" H 3650 4484 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 3950 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 3850 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 3750 50  0001 L CNN "Aliexpress"
	1    3650 4250
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0F58D
P 4100 4300
AR Path="/5CB0F58D" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F58D" Ref="#PWR0173"  Part="1" 
F 0 "#PWR0173" H 3970 4340 50  0001 L CNN
F 1 "GND" H 4200 4250 50  0000 C CNN
F 2 "" H 4100 4300 50  0001 C CNN
F 3 "" H 4100 4300 50  0001 C CNN
	1    4100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4250 4100 4300
Wire Wire Line
	4050 4250 4100 4250
Wire Wire Line
	4050 4150 4100 4150
Wire Wire Line
	4100 4150 4100 4100
$Comp
L agg-kicad:C C?
U 1 1 5CB0F598
P 4100 4150
AR Path="/5CB0F598" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0F598" Ref="C27"  Part="1" 
F 0 "C27" V 4104 4208 50  0000 L CNN
F 1 "100nF" V 4195 4208 50  0000 L CNN
F 2 "agg:0402" H 4100 4150 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 4150 50  0001 C CNN
F 4 "2810260" H 4100 4150 50  0001 C CNN "Farnell"
	1    4100 4150
	0    1    1    0   
$EndComp
Connection ~ 4100 4150
Connection ~ 4100 4250
Wire Wire Line
	3200 3700 3200 4150
Wire Wire Line
	3200 4150 3250 4150
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0F5A3
P 4100 4650
AR Path="/5CB0F5A3" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F5A3" Ref="#PWR0174"  Part="1" 
F 0 "#PWR0174" H 4100 4760 50  0001 L CNN
F 1 "5v" H 4100 4774 50  0000 C CNN
F 2 "" H 4100 4650 50  0001 C CNN
F 3 "" H 4100 4650 50  0001 C CNN
	1    4100 4650
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0F5AA
P 3650 4800
AR Path="/5CB0F5AA" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0F5AA" Ref="IC40"  Part="1" 
F 0 "IC40" H 3650 5125 50  0000 C CNN
F 1 "WS2812B" H 3650 5034 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 4500 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 4400 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 4300 50  0001 L CNN "Aliexpress"
	1    3650 4800
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0F5B1
P 4100 4850
AR Path="/5CB0F5B1" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F5B1" Ref="#PWR0175"  Part="1" 
F 0 "#PWR0175" H 3970 4890 50  0001 L CNN
F 1 "GND" H 4200 4800 50  0000 C CNN
F 2 "" H 4100 4850 50  0001 C CNN
F 3 "" H 4100 4850 50  0001 C CNN
	1    4100 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4800 4100 4850
Wire Wire Line
	4050 4800 4100 4800
Wire Wire Line
	4050 4700 4100 4700
Wire Wire Line
	4100 4700 4100 4650
$Comp
L agg-kicad:C C?
U 1 1 5CB0F5BC
P 4100 4700
AR Path="/5CB0F5BC" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0F5BC" Ref="C28"  Part="1" 
F 0 "C28" V 4104 4758 50  0000 L CNN
F 1 "100nF" V 4195 4758 50  0000 L CNN
F 2 "agg:0402" H 4100 4700 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 4700 50  0001 C CNN
F 4 "2810260" H 4100 4700 50  0001 C CNN "Farnell"
	1    4100 4700
	0    1    1    0   
$EndComp
Connection ~ 4100 4700
Connection ~ 4100 4800
Wire Wire Line
	3200 4250 3200 4700
Wire Wire Line
	3200 4700 3250 4700
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB0F5C7
P 4100 5200
AR Path="/5CB0F5C7" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F5C7" Ref="#PWR0176"  Part="1" 
F 0 "#PWR0176" H 4100 5310 50  0001 L CNN
F 1 "5v" H 4100 5324 50  0000 C CNN
F 2 "" H 4100 5200 50  0001 C CNN
F 3 "" H 4100 5200 50  0001 C CNN
	1    4100 5200
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB0F5CE
P 3650 5350
AR Path="/5CB0F5CE" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB0F5CE" Ref="IC41"  Part="1" 
F 0 "IC41" H 3650 5675 50  0000 C CNN
F 1 "WS2812B" H 3650 5584 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 5050 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 4950 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 4850 50  0001 L CNN "Aliexpress"
	1    3650 5350
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB0F5D5
P 4100 5400
AR Path="/5CB0F5D5" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB0F5D5" Ref="#PWR0177"  Part="1" 
F 0 "#PWR0177" H 3970 5440 50  0001 L CNN
F 1 "GND" H 4200 5350 50  0000 C CNN
F 2 "" H 4100 5400 50  0001 C CNN
F 3 "" H 4100 5400 50  0001 C CNN
	1    4100 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5350 4100 5400
Wire Wire Line
	4050 5350 4100 5350
Wire Wire Line
	4050 5250 4100 5250
Wire Wire Line
	4100 5250 4100 5200
$Comp
L agg-kicad:C C?
U 1 1 5CB0F5E0
P 4100 5250
AR Path="/5CB0F5E0" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB0F5E0" Ref="C29"  Part="1" 
F 0 "C29" V 4104 5308 50  0000 L CNN
F 1 "100nF" V 4195 5308 50  0000 L CNN
F 2 "agg:0402" H 4100 5250 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 5250 50  0001 C CNN
F 4 "2810260" H 4100 5250 50  0001 C CNN "Farnell"
	1    4100 5250
	0    1    1    0   
$EndComp
Connection ~ 4100 5250
Connection ~ 4100 5350
Wire Wire Line
	3200 4800 3200 5250
Wire Wire Line
	3200 5250 3250 5250
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB1067D
P 4100 5750
AR Path="/5CB1067D" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB1067D" Ref="#PWR0178"  Part="1" 
F 0 "#PWR0178" H 4100 5860 50  0001 L CNN
F 1 "5v" H 4100 5874 50  0000 C CNN
F 2 "" H 4100 5750 50  0001 C CNN
F 3 "" H 4100 5750 50  0001 C CNN
	1    4100 5750
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB10684
P 3650 5900
AR Path="/5CB10684" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB10684" Ref="IC42"  Part="1" 
F 0 "IC42" H 3650 6225 50  0000 C CNN
F 1 "WS2812B" H 3650 6134 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 5600 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 5500 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 5400 50  0001 L CNN "Aliexpress"
	1    3650 5900
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB1068B
P 4100 5950
AR Path="/5CB1068B" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB1068B" Ref="#PWR0179"  Part="1" 
F 0 "#PWR0179" H 3970 5990 50  0001 L CNN
F 1 "GND" H 4200 5900 50  0000 C CNN
F 2 "" H 4100 5950 50  0001 C CNN
F 3 "" H 4100 5950 50  0001 C CNN
	1    4100 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5900 4100 5950
Wire Wire Line
	4050 5900 4100 5900
Wire Wire Line
	4050 5800 4100 5800
Wire Wire Line
	4100 5800 4100 5750
$Comp
L agg-kicad:C C?
U 1 1 5CB10696
P 4100 5800
AR Path="/5CB10696" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB10696" Ref="C30"  Part="1" 
F 0 "C30" V 4104 5858 50  0000 L CNN
F 1 "100nF" V 4195 5858 50  0000 L CNN
F 2 "agg:0402" H 4100 5800 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 5800 50  0001 C CNN
F 4 "2810260" H 4100 5800 50  0001 C CNN "Farnell"
	1    4100 5800
	0    1    1    0   
$EndComp
Connection ~ 4100 5800
Connection ~ 4100 5900
Wire Wire Line
	3200 5350 3200 5800
Wire Wire Line
	3200 5800 3250 5800
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB106A1
P 4100 6300
AR Path="/5CB106A1" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB106A1" Ref="#PWR0180"  Part="1" 
F 0 "#PWR0180" H 4100 6410 50  0001 L CNN
F 1 "5v" H 4100 6424 50  0000 C CNN
F 2 "" H 4100 6300 50  0001 C CNN
F 3 "" H 4100 6300 50  0001 C CNN
	1    4100 6300
	1    0    0    -1  
$EndComp
$Comp
L ws2812b:WS2812B IC?
U 1 1 5CB106A8
P 3650 6450
AR Path="/5CB106A8" Ref="IC?"  Part="1" 
AR Path="/5CAD9882/5CB106A8" Ref="IC43"  Part="1" 
F 0 "IC43" H 3650 6775 50  0000 C CNN
F 1 "WS2812B" H 3650 6684 50  0000 C CNN
F 2 "agc-dsky:WS2812B" H 3350 6150 50  0001 L CNN
F 3 "https://www.kitronik.co.uk/pdf/WS2812B-LED-datasheet.pdf" H 3350 6050 50  0001 L CNN
F 4 "https://www.aliexpress.com/item/10-1000pcs-WS2812B-4pins-5050-SMD-Black-White-version-WS2812-Individually-Addressable-Digital-RGB-LED-Chip/32810203444.html?spm=2114.search0604.3.54.65db7218Hnfvt0&ws_ab_test=searchweb0_0,searchweb201602_2_10065_10068_10130_10547_319_317_10548_10696_10192_5728811_10190_453_10084_454_10083_10618_10307_10820_10301_10821_10303_537_536_5733215_5733315_328_10059_10884_5731015_5733115_10887_100031_5733415_321_322_10103_5733515_5733615,searchweb201603_55,ppcSwitch_0&algo_expid=fa88f8e5-9015-4ff5-99be-874e1b964a2c-8&algo_pvid=fa88f8e5-9015-4ff5-99be-874e1b964a2c" H 3350 5950 50  0001 L CNN "Aliexpress"
	1    3650 6450
	1    0    0    -1  
$EndComp
$Comp
L agg-kicad:GND #PWR?
U 1 1 5CB106AF
P 4100 6500
AR Path="/5CB106AF" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB106AF" Ref="#PWR0181"  Part="1" 
F 0 "#PWR0181" H 3970 6540 50  0001 L CNN
F 1 "GND" H 4200 6450 50  0000 C CNN
F 2 "" H 4100 6500 50  0001 C CNN
F 3 "" H 4100 6500 50  0001 C CNN
	1    4100 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 6450 4100 6500
Wire Wire Line
	4050 6450 4100 6450
Wire Wire Line
	4050 6350 4100 6350
Wire Wire Line
	4100 6350 4100 6300
$Comp
L agg-kicad:C C?
U 1 1 5CB106BA
P 4100 6350
AR Path="/5CB106BA" Ref="C?"  Part="1" 
AR Path="/5CAD9882/5CB106BA" Ref="C31"  Part="1" 
F 0 "C31" V 4104 6408 50  0000 L CNN
F 1 "100nF" V 4195 6408 50  0000 L CNN
F 2 "agg:0402" H 4100 6350 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2373808.pdf" H 4100 6350 50  0001 C CNN
F 4 "2810260" H 4100 6350 50  0001 C CNN "Farnell"
	1    4100 6350
	0    1    1    0   
$EndComp
Connection ~ 4100 6350
Connection ~ 4100 6450
Wire Wire Line
	3200 5900 3200 6350
Wire Wire Line
	3200 6350 3250 6350
Connection ~ 2850 1900
Connection ~ 2850 2000
Text Notes 2150 2350 0    50   ~ 0
COMP\nACTY
Wire Wire Line
	1850 5350 1800 5350
Wire Wire Line
	1800 5350 1800 5550
Wire Wire Line
	1800 5550 3050 5550
Wire Wire Line
	3050 5550 3050 3050
Wire Wire Line
	3050 3050 3250 3050
Wire Wire Line
	3200 3700 3250 3700
Wire Wire Line
	3200 4250 3250 4250
Wire Wire Line
	3200 4800 3250 4800
Wire Wire Line
	3200 5350 3250 5350
Wire Wire Line
	3200 5900 3250 5900
NoConn ~ 3250 6450
Wire Wire Line
	1800 2000 1800 3050
$Comp
L agg-kicad:5v #PWR?
U 1 1 5CB25685
P 4100 3000
AR Path="/5CB25685" Ref="#PWR?"  Part="1" 
AR Path="/5CAD9882/5CB25685" Ref="#PWR0182"  Part="1" 
F 0 "#PWR0182" H 4100 3110 50  0001 L CNN
F 1 "5v" H 4100 3124 50  0000 C CNN
F 2 "" H 4100 3000 50  0001 C CNN
F 3 "" H 4100 3000 50  0001 C CNN
	1    4100 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3700 1850 3700
Wire Wire Line
	1800 4250 1850 4250
Wire Wire Line
	1800 4800 1850 4800
$Comp
L agg-kicad:PWR #FLG0103
U 1 1 5D765F83
P 2700 1900
F 0 "#FLG0103" H 2700 2060 50  0001 C CNN
F 1 "PWR" H 2700 2034 50  0000 C CNN
F 2 "" H 2700 1900 50  0001 C CNN
F 3 "" H 2700 1900 50  0001 C CNN
	1    2700 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 1900 2700 1900
Connection ~ 2700 1900
Wire Wire Line
	2700 1900 2850 1900
Wire Wire Line
	2650 2000 2850 2000
$EndSCHEMATC
