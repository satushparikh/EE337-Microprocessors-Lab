#include <at89c5131.h>

/*

Two frequency simultaneously with timers in interrupts mode.

First LED1 time period is 2ms.
Second LED2 time period is 3ms.

*/


sbit LED1=P3^6;
sbit LED2=P3^7;


void timer0_isr () interrupt 1
{ //this interrupt if for timer 0
   LED1 = ~LED1;
   //Reload values for TH0 and TL0. Start timer 0.
   //since time period is 2ms
   //it should toggle every 1ms
   //for 1ms count = 2000
   //-2000 = f830
   	TH0 =  0xF8;  //Values for Timer 0 TH0
	TL0 =  0x30; //Values for Timer 0 TL0
}

void timer1_isr () interrupt 3
{ //THIS IS INTERRUPT FOR TIMER 1
   LED2 = ~LED2;
   //Reload values for TH1 and TL1. Start timer 1.
   //TOGGLE EVERY 1.5 ms
   //3000 COUNT 
   //-3000 F448
   	TH1 =  0xF4;   //Values for Timer 1 TH1
	TL1 =  0x48; //Values for Timer 1 TL1
}

//Main function
void main(void)
{
	TMOD = 0x11; //mode 1 timer 0 and timer 1
	
	TH0 =  0xF8;  //Values for Timer 0 TH0
	TL0 =  0x30; //Values for Timer 0 TL0
	TH1 =  0xF4;   //Values for Timer 1 TH1
	TL1 =  0x48; //Values for Timer 1 TL1
	
	EA = 1;  //activate global interrupts
	ET0 = 1; //activate interrupts for both timers
	ET1 = 1;
	TR0 = 1; //start timer 0
	TR1 = 1; //start timer 1
	LED1 = 0;
	LED2 = 0;
	while(1);
}

/* 
    Timer delay calculation in mode 1
	(65536-n)*T; T is time after which count increases by 1
	T=12/f ; 
	8051 timers use 1/12 of XTAL frequency(f) , regardless of machine cycle time 
*/
/* For pt-51 f = 24 MHz
   to create square wave of time period 2 ms 
   square wave is high for 1ms and low for 1ms
   T=0.5 micro second
   65536-n * 0.5e-6=e-3 
   n = 0x F830 
   so TH0 = F8
  and TL0 = 30
*/