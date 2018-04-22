/*
 * GLOBALS.h
 *
 * Created: 15-04-2018 11:55:49
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

//COMPILER
#define OPTIMIZATION "O3"

//HARDWARE
// buttons
/*PL0 ( ICP4 ) Digital pin 49
36 PL1 ( ICP5 ) Digital pin 48
37 PL2 ( T5 ) Digital pin 47
38 PL3 ( OC5A ) Digital pin 46 (PWM)
39 PL4 ( OC5B ) Digital pin 45 (PWM)
40 PL5 ( OC5C ) Digital pin 44 (PWM)
41 PL6 Digital pin 43
42 PL7 Digital pin 42*/
#define PINBUT1 14
#define PINBUT2 15
#define PINBUT3 16
#define PINBUT4 17
#define PINBUT5 18
#define PINBUT6 19
#define PINBUT7 20
#define PINBUT8 21
// potentiometers
#define PINPOT1 A0
#define PINPOT1 A1
#define PINPOT1 A2
#define PINPOT1 A3
#define PINPOT1 A4 
#define PINPOT1 A5
#define PINPOT1 A6
// led's (to sequence)
/*PC0 ( A8 ) Digital pin 37
54 PC1 ( A9 ) Digital pin 36
55 PC2 ( A10 ) Digital pin 35
56 PC3 ( A11 ) Digital pin 34
57 PC4 ( A12 ) Digital pin 33
58 PC5 ( A13 ) Digital pin 32
59 PC6 ( A14 ) Digital pin 31
60 PC7 ( A15 ) Digital pin 30 */ 
#define PINLED1 10
#define PINLED2 9
#define PINLED3 8
#define PINLED4 7
#define PINLED5 6
#define PINLED6 5
#define PINLED7 13
/*43 PD0 ( SCL/INT0 ) Digital pin 21 (SCL)
44 PD1 ( SDA/INT1 ) Digital pin 20 (SDA)
45 PD2 ( RXDI/INT2 ) Digital pin 19 (RX1)
46 PD3 ( TXD1/INT3 ) Digital pin 18 (TX1)*/
#define PINRED 2
#define PINGREEN 3 
#define PINBLUE 4

#endif /* GLOBALS_H_ */