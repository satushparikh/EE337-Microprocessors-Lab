#include <at89c5131.h>

bit tx_complete = 0,rx_complete = 0; //Bit flags for interrupts

/**********************************************************
   uart_init(): 
	Initialization function to be completed
	Initializes UART peripheral for 8-bit transfer, 
	1 start and 1 stop bits. 
	
	Please write TH1 value for required baud rate
***********************************************************/	
void uart_init(void)
{
	//TMOD=0x__;			//Configure Timer 1 in Mode 2
	//TH1=__;					//Load TH1 to obtain require Baudrate (Refer Serial.pdf for calculations)
	//SCON=0x__;			//Configure UART peripheral for 8-bit data transfer 
	//								//Start Timer 1
										//Enable Serial Interrupt
										//Enable Global Interrupt
	TMOD = 0x20;//use of timer 1 in mode 2 : 8 bit auto reload
	TH1  = 0xF3;//sets baud rate to 4800 bps
	SCON = 0x50 ;
	TR1 = 1;//start timer 1
	ES = 1;//enables serial interrupt
	EA = 1;//enables all interrupts
	/*
	SCON register
	to usonly serial mode 1,8 bit data , 1 stop bit,1 start bit is of interest to us for which sm0=0 sm1=1
	RSM0 SM1 SM2 REN TB8 RB8 TI RI 
	SM0,SM1 are used to program start bit,stop bit and data bits
	EN if we want 8051 to both transfer and receive data REN must be set to 1,by making ren=0 receiver is disabled
	TB8=RB8=TM2=0 DON'T THINK MAKE 0
	TI AND RI ARE  transmitter and receiver interrupt flag 
	 */
}


/**********************************************************
   transmit_char(<unsigned char ch>): 
	Transmits a character using UART
***********************************************************/	
void transmit_char(unsigned char ch)
{
	SBUF=ch;				//Load data in SBUF
	while(!tx_complete); 			//Wait for tx_complete flag (interrupt to complete)
	tx_complete = 0;		//Clear tx_complete flag 
}


/**********************************************************
   transmit_string(<String pointer>): 
	Transmit a string using UART
***********************************************************/	
void transmit_string(unsigned char *s)
{
	while(*s != 0)
	{
			transmit_char(*s++);
	}
}


/**********************************************************
   receive_char(): 
	Receives a character through UART. Returns a 
	character.
***********************************************************/		
unsigned char receive_char(void)
{
	unsigned char ch = 0;
	while(!rx_complete);				//Wait for rx_complete(interrupt to complete)
	rx_complete = 0;
	ch = SBUF;					//Read data from SBUF
	return ch;					//Return read character
}


/**********************************************************
   Serial_ISR(): 
	Interrupt service routine for UART interrupt.
	Determines whether it is a transmit or receive
	interrupt and raise corresponding flag.
	Transmit or receive functions (defined above) monitor
	for these flags to check if data transfer is done.
***********************************************************/	
void serial_ISR(void) interrupt 4
{
		if(TI==1)			//check whether TI is set
		{
			TI = 0;			//Clear TI flag
			tx_complete = 1;	//Set tx_complete flag indicating interrupt completion
		}
		else if(RI==1)			//check whether RI is set
		{
			RI = 0;			//Clear RI flag
			rx_complete = 1;	//Set rx_complete flag indicating interrupt completion
		}
}
