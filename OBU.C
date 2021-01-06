//#include <reg51.h>             	// SFR declarations
#include <c8051f340.h>
#include <stdio.h>




//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F34x
//-----------------------------------------------------------------------------

sfr16 SBRL1 = 0xB4;

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

//#define SYSCLK   	12000000 / 8

#define SYSCLK   	48000000      	// SYSCLK frequency in Hz
#define BAUDRATE0 	115200       	// Baud rate of UART0 in bps
#define BAUDRATE1 	115200       	// Baud rate of UART1 in bps

void SYSTEMCLOCK_Init (void);
void PORT_Init (void);
void UART0_Init (void);
void UART1_Init (void);
void OSCILLATOR_Init (void);

//----------------------------------------------

	unsigned char Assign;
	unsigned char ID_Received;
	unsigned char ID_Sent;
	unsigned char L1;
	unsigned char L2;
	unsigned char L3;
	unsigned char L4;
    	unsigned char init;
    	unsigned char Status;
    	long int n;

    
// ----------RX and TX Functions----------------

	void RX (void);
	void TX (void);
	void DataTransfer (unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	void RX_byte1 (unsigned int *ID_Received);
	void RX_byte3 (unsigned char *L1);
	void RX_byte4 (unsigned char *L2);
	void RX_byte5 (unsigned char *L3);
	void RWDRX_byte6 (unsigned char *L4);
    	void RX_byte7 (unsigned char *Status);
	void RWDTX (unsigned int x, unsigned int y);
    	void RXinit (unsigned char *init);
//----------------------------------------------

	int i;

	sbit LED1 = P2^2;

	unsigned int Vehid;

    

//----------------------------------------------

void main (void)
{

	UART0_Init ();                  	// initialize UART0
	PORT_Init ();                   	// Initialize crossbar and GPIO
	//UART1_Init ();
	OSCILLATOR_Init ();
	
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
	EA=1;
	PCA0MD&= ~0x40;

//----------------------Possible Wrong Way Drivers--------------------//   
//----------------------Set 1--------------------//    

	DataTransfer (0xBB, 0x01, 0x02, 0x03, 0x04, 0x01);
	DataTransfer (0xBB, 0x05, 0x06, 0x07, 0x08, 0x02);
	DataTransfer (0xBB, 0xA1, 0xB1, 0xC1, 0xD1, 0x03);

	DataTransfer (0x28, 0x1c, 0x6c, 0x93, 0x7f, 0x7e);
	DataTransfer (0x3c, 0x9b, 0x72, 0x55, 0x2a, 0x2b);
	DataTransfer (0x3a, 0xb8, 0x58, 0x66, 0x45, 0x78);

	DataTransfer (0x2b, 0xb2, 0xa3, 0xb4, 0x9f, 0x48);
	DataTransfer (0xae, 0x6e, 0x13, 0x7c, 0x79, 0x47);
	DataTransfer (0x61, 0x91, 0xc3, 0x40, 0x84, 0x1b);
	
	RX_byte7(&Status);
	
	if (Status == 0xAB)
	{
   		RX_byte1 (&ID_Received);
		RX_byte3 (&L1);
		RX_byte4 (&L2);
		RX_byte5 (&L3);
		//RWDRX_byte6 (&L4);
	}

	RXinit (&init);
  	// while (byte == 0xA4)
	
	Assign = 0xAB;
	TX ();
	RXinit (&init);

// Second group of data   			  
//----------------------Vehicle 4--------------------//    
	DataTransfer (0x7d, 0xb1, 0xb4, 0x74, 0x15, 0xc3);
	DataTransfer (0x84, 0x3b, 0x97, 0x49, 0x92, 0xb9);
	DataTransfer (0x49, 0x9a, 0x5f, 0x8e, 0x61, 0x5d);
//----------------------Vehicle 5--------------------//    
	DataTransfer (0x94, 0x2c, 0xaf, 0x52, 0x70, 0x87);
	DataTransfer (0x60, 0x3e, 0x6f, 0x94, 0x89, 0x4e);
	DataTransfer (0xb3, 0xbb, 0x9d, 0x8b, 0x80, 0x32);
//----------------------Vehicle 6--------------------//    
	DataTransfer (0x53, 0x8a, 0x42, 0x8f, 0x54, 0x82);
	DataTransfer (0x52, 0x33, 0x6b, 0xc0, 0x49, 0x7d);
	DataTransfer (0x4b, 0x87, 0x46, 0x7e, 0x49, 0x2e);
    
	RX_byte7(&Status);
	
	if (Status == 0xAB)	 
   	{ 
	RX_byte1 (&ID_Received);
	RX_byte3 (&L1);
	RX_byte4 (&L2);
	RX_byte5 (&L3);
	//RWDRX_byte6 (&L4);
    	}

   	RXinit (&init);
	// while (byte == 0xA4)
	Assign = 0xAB;
	TX ();
	RXinit (&init);

// Second group of data
   			 
   			 
//----------------------Vehicle 4--------------------//    
  	DataTransfer (0x7d, 0xb1, 0xb4, 0x74, 0x15, 0xc3);
	DataTransfer (0x84, 0x3b, 0x97, 0x49, 0x92, 0xb9);
	DataTransfer (0x49, 0x9a, 0x5f, 0x8e, 0x61, 0x5d);
//----------------------Vehicle 5--------------------//    
	DataTransfer (0x94, 0x2c, 0xaf, 0x52, 0x70, 0x87);
	DataTransfer (0x60, 0x3e, 0x6f, 0x94, 0x89, 0x4e);
    	DataTransfer (0xb3, 0xbb, 0x9d, 0x8b, 0x80, 0x32);

//----------------------Vehicle 6--------------------//    
	DataTransfer (0x53, 0x8a, 0x42, 0x8f, 0x54, 0x82);
    	DataTransfer (0x52, 0x33, 0x6b, 0xc0, 0x49, 0x7d);
    	DataTransfer (0x4b, 0x87, 0x46, 0x7e, 0x49, 0x2e);

	RX_byte7(&Status);
	if (Status == 0xAB)
	{
		RX_byte1 (&ID_Received);
		RX_byte3 (&L1);
		RX_byte4 (&L2);
		RX_byte5 (&L3);
		//RWDRX_byte6 (&L4);
	}
	
	RXinit (&init);
  	// while (byte == 0xA4)
   	Assign = 0xAB;
   	 
	TX ();
   	RXinit (&init);

// Second group of data		 
//----------------------Vehicle 4--------------------//    
  	DataTransfer (0x7d, 0xb1, 0xb4, 0x74, 0x15, 0xc3);
	DataTransfer (0x84, 0x3b, 0x97, 0x49, 0x92, 0xb9);
	DataTransfer (0x49, 0x9a, 0x5f, 0x8e, 0x61, 0x5d);
//----------------------Vehicle 5--------------------//    
	DataTransfer (0x94, 0x2c, 0xaf, 0x52, 0x70, 0x87);
    	DataTransfer (0x60, 0x3e, 0x6f, 0x94, 0x89, 0x4e);
    	DataTransfer (0xb3, 0xbb, 0x9d, 0x8b, 0x80, 0x32);

//----------------------Vehicle 6--------------------//    
	DataTransfer (0x53, 0x8a, 0x42, 0x8f, 0x54, 0x82);
   	DataTransfer (0x52, 0x33, 0x6b, 0xc0, 0x49, 0x7d);
    	DataTransfer (0x4b, 0x87, 0x46, 0x7e, 0x49, 0x2e);

    
    RX_byte7(&Status);

    if (Status == 0xAB)
   		 
   { 
	RX_byte1 (&ID_Received);
	RX_byte3 (&L1);
	RX_byte4 (&L2);
	RX_byte5 (&L3);

	//RWDRX_byte6 (&L4);
    }
// Second group of data initialization


   	RXinit (&init);
	// while (byte == 0xA4)
	Assign = 0xAB;
    
   	TX ();
   	RXinit (&init);

// Second group of data	 
//----------------------Vehicle 4--------------------//    
  	DataTransfer (0x32, 0xb8, 0x73, 0xb1, 0xae, 0x69);
	DataTransfer (0xb8, 0xaf, 0xbf, 0x4f, 0xaa, 0xb8);
	DataTransfer (0x99, 0x37, 0x34, 0xa9, 0x82, 0xc2);
//----------------------Vehicle 5--------------------//    
	DataTransfer (0x94, 0x2c, 0xaf, 0x52, 0x70, 0x87);
    	DataTransfer (0x60, 0x3e, 0x6f, 0x94, 0x89, 0x4e);
    	DataTransfer (0xb3, 0xbb, 0x9d, 0x8b, 0x80, 0x32);
//----------------------Vehicle 6--------------------//    
	DataTransfer (0x53, 0x8a, 0x42, 0x8f, 0x54, 0x82);
    	DataTransfer (0x52, 0x33, 0x6b, 0xc0, 0x49, 0x7d);
    	DataTransfer (0x4b, 0x87, 0x46, 0x7e, 0x49, 0x2e);
//RWDTX (0x60, 0x55);

    	RX_byte7(&Status);
    
	if (Status == 0xAB) // violation
  	 { 
		RX_byte1 (&ID_Received);
   		RX_byte3 (&L1);
   	 	RX_byte4 (&L2);
   	 	RX_byte5 (&L3);

   	 while (1)
   	 {    
		 for (i = 0; i<= 10000; i++);
		 LED1 = ~LED1;
   	 }

	//RWDRX_byte6 (&L4);
    }
     	/*while (1)

        	{    
            	//for (i = 0; i<= 10000; i++);
            	//LED1 = ~LED1;

   	 

           	 
            	if (ID_Received == 0x00AA)
            	for (i = 0; i<= 10000; i++);
            	LED1 = ~LED1;
       	 
           	 
            	if (ID_Received == 0x00BB)
            	for (i = 0; i<= 7500; i++);
            	LED1 = ~LED1;

  	 
            	if (ID_Received == 0x00CC)
            	for (i = 0; i<= 3000; i++);
            	LED1 = ~LED1;
        	}*/
//----------------- Display --------------//
	
	n = time();
} // end main



//----------------- RX Definitons --------------//


void RX_byte1 (unsigned char *ID_Received)
{

	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*ID_Received = SBUF0;

	 
    	RI0=0;

}


void RX_byte3 (unsigned char *L1)
{

	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*L1 = SBUF0;

	 
    	RI0=0;

}

void RX_byte4 (unsigned char *L2)
{

	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*L2 = SBUF0;

	 
    	RI0=0;

}

void RX_byte5 (unsigned char *L3)
{

	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*L3 = SBUF0;

	 
    	RI0=0;

}

void RWDRX_byte6 (unsigned char *L4)

{

SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*L4 = SBUF0;

	 
   	RI0=0;

}

void RX_byte7 (unsigned char *Status)
{

    SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*Status = SBUF0;

	 
   	RI0=0;


}

void RWDTX (unsigned int x, unsigned int y)

{
	Assign = x;
	TX();

	Assign = y;
	TX();

}




void RX (void)
{

	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

    	RI0=0;

}

void RXinit (unsigned char *init)
{

	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception
    
    *init = SBUF0;

    	RI0=0;

}

//----------------- TX Definitons --------------

void TX (void)
{
	SCON0=0x40;

	TI0 = 0;
    
	SBUF0 = Assign;

	while  (TI0 == 0);

	TI0 = 0;
   	 

}

//----------------- DataTranfer Definitons --------------
void DataTransfer (unsigned int ID_Sent, unsigned int Lat1, unsigned int Lat2,
unsigned int Long1, unsigned int Long2, unsigned int TS)
{

//----------------------System Initialization--------------------//  
    Assign = 0xAB;  
    TX ();

   // while (byte == 0xA4)
	RXinit (&init);
    	Assign = 0xCA;
    	TX ();

//----------Vehicle_ID-------//
      	Assign = ID_Sent;
      	TX();
//----------Longitude-------//
    	Assign = Long1;
    	TX();
	Assign = Long2;
	TX();

//----------Latitude-------//  

 
	Assign = Lat1;

	TX();

 
	Assign = Lat2;

	TX();

//----------Speed-------//  

 
	Assign = 0x79;

	TX();

//----------Heading-------//  

 
	Assign = 0xAE;

	TX();  

 
	Assign = 0xEB;

	TX();

//----------Timestamp-------//  

 
	Assign = TS;

	TX();

 
	Assign = 0x15;

	TX();

 
	Assign = 0xCA;

	TX();

 
	Assign = 0x57;

	TX();

 
	Assign = 0x10;

	TX();	 

 
	Assign = 0xFD;

	TX();  

 
	Assign = 0xBF;

	TX();

 
	Assign = 0x47;

	TX();  

 
	Assign = 0x65;

	TX();


}
    


void OSCILLATOR_Init (void)
{
   OSCICN = 0x80;                  	// Configure internal oscillator for
                                   	// its lowest frequency
}


void PORT_Init (void)
{
   XBR0 	= 0x01;                	// No digital peripherals selected
   XBR1 	= 0x40;                	// Enable crossbar and weak pull-ups
   XBR2 	= 0x01;                    	// route UART to crossbar
   P0MDOUT |= 0x11;                	// set P0.4 to push-pull output
   P2MDOUT |= 0x04;                	// Enable LED as a push-pull output
}

void SYSTEMCLOCK_Init (void)
{
   OSCICN |= 0x03;                 	// Configure internal oscillator for
                                   	// its maximum frequency and enable
                                   	// missing clock detector

   CLKMUL  = 0x00;                 	// Select internal oscillator as
                                   	// input to clock multiplier

   /*CLKMUL |= 0x80;                 	// Enable clock multiplier
   Delay();                        	// Delay for clock multiplier to begin
   CLKMUL |= 0xC0;                 	// Initialize the clock multiplier
   Delay();                        	// Delay for clock multiplier to begin

   while(!(CLKMUL & 0x20));        	// Wait for multiplier to lock
   CLKSEL  = 0x03;  */               	// Select system clock
}


void UART0_Init (void)
{
   
   SCON0 = 0x10;                   	// SCON0: 8-bit variable bit rate
                                   	//    	level of STOP bit is ignored
                                   	//    	RX enabled
                                   	//    	ninth bits are zeros
                                   	//    	clear RI0 and TI0 bits

   if (SYSCLK/BAUDRATE0/2/256 < 1) {
  	TH1 = -(SYSCLK/BAUDRATE0/2);
  	CKCON &= ~0x0B;              	// T1M = 1; SCA1:0 = xx
  	CKCON |=  0x08;
   } else if (SYSCLK/BAUDRATE0/2/256 < 4) {
  	TH1 = -(SYSCLK/BAUDRATE0/2/4);
  	CKCON &= ~0x0B;              	// T1M = 0; SCA1:0 = 01            	 
  	CKCON |=  0x09;
   } else if (SYSCLK/BAUDRATE0/2/256 < 12) {
  	TH1 = -(SYSCLK/BAUDRATE0/2/12);
  	CKCON &= ~0x0B;              	// T1M = 0; SCA1:0 = 00
   } else {
  	TH1 = -(SYSCLK/BAUDRATE0/2/48);
  	CKCON &= ~0x0B;              	// T1M = 0; SCA1:0 = 10
  	CKCON |=  0x02;
   }

   TL1 = TH1;                      	// init Timer1
   TMOD &= ~0xf0;                  	// TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                  	 
   TR1 = 1;                        	// START Timer1
   
   TI0 = 1;                        	// Indicate TX0 ready
   
}


//-----------------------------------------------------------------------------
// UART1_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure UART1 for baudrate1 and 8-N-1.
//
//-----------------------------------------------------------------------------

void UART1_Init (void)
{
   SMOD1 = 0x0C;                   	// set to disable parity, 8-data bit,
                                   	// disable extra bit,
                                   	// stop bit 1 bit wide

   SCON1 = 0x10;                   	// SCON1: 8-bit variable bit rate
                                   	//    	level of STOP bit is ignored
                                   	//    	RX enabled
                                   	//    	ninth bits are zeros
                                   	//    	clear RI0 and TI0 bits

   if (SYSCLK/BAUDRATE1/2/0xFFFF < 1) {
  	SBRL1 = -(SYSCLK/BAUDRATE1/2);
  	SBCON1 |= 0x03;              	// set prescaler to 1
   } else if (SYSCLK/BAUDRATE1/2/0xFFFF < 4) {
  	SBRL1 = -(SYSCLK/BAUDRATE1/2/4);
  	SBCON1 &= ~0x03;
  	SBCON1 |= 0x01;              	// set prescaler to 4

   } else if (SYSCLK/BAUDRATE1/2/0xFFFF < 12) {
  	SBRL1 = -(SYSCLK/BAUDRATE1/2/12);
  	SBCON1 &= ~0x03;             	// set prescaler to 12
   } else {
  	SBRL1 = -(SYSCLK/BAUDRATE1/2/48);
  	SBCON1 &= ~0x03;
  	SBCON1 |= 0x02;              	// set prescaler to 4
   }

   SCON1 |= 0x02;                  	// indicate ready for TX
   SBCON1 |= 0x40;                 	// enable baud rate generator
}
