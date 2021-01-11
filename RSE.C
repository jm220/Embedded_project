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
	unsigned char VehicleID;
	unsigned char Speed;
	unsigned char Heading1;
	unsigned char Heading2;

	unsigned char Timestamp1;
	unsigned char Timestamp2;
	unsigned char Timestamp3;
	unsigned char Timestamp4;
	unsigned char Timestamp5;
	unsigned char Timestamp6;
	unsigned char Timestamp7;
	unsigned char Timestamp8;
	unsigned char Timestamp9;
	unsigned char ID;

	unsigned int A1, A2, A3;
	unsigned int B1, B2, B3;
	unsigned int C1, C2, C3;
	unsigned int D1, D2, D3;

	unsigned char Lat1, Lat2;
	unsigned char Long1, Long2;

	unsigned char X, Y, X1, X2, Y1, Y2;

	unsigned char init;
   	unsigned int n;

// ----------RX and TX Functions----------------

	void RX_byte1 (unsigned char *ID);
	void RX_byte2 (unsigned char *Long1);
	void RX_byte3 (unsigned char *Long2);
	void RX_byte4 (unsigned char *Lat1);
	void RX_byte5 (unsigned char *Lat2);
	void RX_byte6 (void);
	void RX_byte7 (void);
	void RX_byte8 (void);
	void RX_byte9 (unsigned char *Timestamp1);
	void RX_byte10 (unsigned char *Timestamp2);
	void RX_byte11 (unsigned char *Timestamp3);
	void RX_byte12 (unsigned char *Timestamp4);
	void RX_byte13 (unsigned char *Timestamp5);
	void RX_byte14 (unsigned char *Timestamp6);
	void RX_byte15 (unsigned char *Timestamp7);
	void RX_byte16 (unsigned char *Timestamp8);
	void RX_byte17 (unsigned char *Timestamp9);
	void RX_X (unsigned char *X);
	void RX_Y (unsigned char *Y);
	void RX ();
	void TX (void);
	void VictimWarning ();
	void RX_GEN (unsigned char *init);
	//void Initialization (unsigned char *Init);

//----------------------------------------------

	int i, index;
	sbit LED1 = P2^2;
	unsigned char GPS_data [9][6];
	sbit compare_points = P1^1;
	sbit compare_time = P1^2;

//----------------------------------------------

void main (void)
{

	UART0_Init ();                  	// initialize UART0
	PORT_Init ();                   	// Initialize crossbar and GPIO
	OSCILLATOR_Init ();
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
	EA=1;
	PCA0MD&= ~0x40;
	
//--------------Fixed Reference Points------------------
	// point 1
	A1 = 0x01;
	B1 = 0x02;
	C1 = 0x03;
	D1 = 0x04;

	// point 2
	A2 = 0x05;
	B2 = 0x06;
	C2 = 0x07;
	D2 = 0x08;

	// point 3
	A3 = 0xA1;
	B3 = 0xB1;
	C3 = 0xC1;
	D3 = 0xD1;
	
//----------Initialization----------	
	//RX_byte2 (&Long1);
    //----------car1----------
do
{
	RX();
	GPS_data [0][0] = ID;
	GPS_data [0][1] = Lat1;
	GPS_data [0][2] = Lat2;
	GPS_data [0][3] = Long1;
	GPS_data [0][4] = Long2;
	GPS_data [0][5] = Timestamp1;

	RX();
	GPS_data [1][0] = ID;
	GPS_data [1][1] = Lat1;
	GPS_data [1][2] = Lat2;
	GPS_data [1][3] = Long1;
	GPS_data [1][4] = Long2;
	GPS_data [1][5] = Timestamp1;

	RX();
	GPS_data [2][0] = ID;
	GPS_data [2][1] = Lat1;
	GPS_data [2][2] = Lat2;
	GPS_data [2][3] = Long1;
	GPS_data [2][4] = Long2;
	GPS_data [2][5] = Timestamp1;

	//---------------car2---------------

	RX();
	GPS_data [3][0] = ID;
	GPS_data [3][1] = Lat1;
	GPS_data [3][2] = Lat2;
	GPS_data [3][3] = Long1;
	GPS_data [3][4] = Long2;
	GPS_data [3][5] = Timestamp1;

	RX();
	GPS_data [4][0] = ID;
	GPS_data [4][1] = Lat1;
	GPS_data [4][2] = Lat2;
	GPS_data [4][3] = Long1;
	GPS_data [4][4] = Long2;
	GPS_data [4][5] = Timestamp1;

	RX();
	GPS_data [5][0] = ID;
	GPS_data [5][1] = Lat1;
	GPS_data [5][2] = Lat2;
	GPS_data [5][3] = Long1;
	GPS_data [5][4] = Long2;
	GPS_data [5][5] = Timestamp1;

	//----------------car3-------------

	RX();
	GPS_data [6][0] = ID;
	GPS_data [6][1] = Lat1;
	GPS_data [6][2] = Lat2;
	GPS_data [6][3] = Long1;
	GPS_data [6][4] = Long2;
	GPS_data [6][5] = Timestamp1;

	RX();
	GPS_data [7][0] = ID;
	GPS_data [7][1] = Lat1;
	GPS_data [7][2] = Lat2;
	GPS_data [7][3] = Long1;
	GPS_data [7][4] = Long2;
	GPS_data [7][5] = Timestamp1;

	RX();
	GPS_data [8][0] = ID;
	GPS_data [8][1] = Lat1;
	GPS_data [8][2] = Lat2;
	GPS_data [8][3] = Long1;
	GPS_data [8][4] = Long2;
	GPS_data [8][5] = Timestamp1;


	//RX_X(&X);
	//RX_Y(&Y);
	{
		index = 0;   
		while (index <=2)
		{
			compare_time = ((GPS_data[3*index][5] < GPS_data[(3*index)+1][5]) && (GPS_data[(3*index)+1][5] < GPS_data[(3*index)+2][5]));
					
			compare_points = ((A1 == GPS_data[(3*index)][1])&&(B1 == GPS_data[(3*index)][2])&&(C1 == GPS_data[(3*index)][3])&&(D1 == GPS_data[(3*index)][4])
       		&&(A2 == GPS_data[(3*index)+1][1])&&(B2 == GPS_data[(3*index)+1][2])&&(C2 == GPS_data[(3*index)+1][3])&&(D2 == GPS_data[(3*index)+1][4])
   	     	&&(A3 == GPS_data[(3*index)+2][1])&&(B3 == GPS_data[(3*index)+2][2])&&(C3 == GPS_data[(3*index)+2][3])&&(D3 == GPS_data[(3*index)+2][4]));
			
			index++;					
			if (compare_time && compare_points)

			{	
				Assign = 0xAB;
				TX();
			
				Assign = GPS_data[3*(index-1)][0];
				TX();

				Assign = 0x57; // W
				TX();

				Assign = 0x57; // W
				TX();

				Assign = 0x44; // D
				TX();
  	 
   		 		//for (i = 0; i<= 10000; i++);
       				//LED1 = ~LED1;
				//VictimWarning ();
			}
				
		}
//----------------------next group initilization----------------------
	Assign = 0x47;
	TX();	

	Assign = 0x89;
	TX();

	RX_GEN (&init);

	Assign = 0x48;
	TX();

     }
 
  }

} 
// end main

//------------------Victim Warning----------------

void VictimWarning ()
{
	X1 = 0x50;
	X2 = 0x70;
	Y1 = 0x50;
	Y2 = 0x60;

	if((X1 <= X)&&(X2 >= X)&&(Y1 <= Y)&&(Y2 >= Y));
	{
		Assign = 0x66; // f
		TX();
	}
}

//----------------- Initialization --------------


/*void Initialization ()
{

	RX_Initialization (&Init);

}*/

/*void RX_Initialization (unsigned char *Init)

{
	SCON0=0x50;

	RI0=0;

	while (RI0==0); //Reception

	*Init = SBUF0;

    RI0=0;


}*/

//----------------- RX Definitons --------------

void RX (void)
{
	RX_GEN (&init);
	Assign = 0xA4;	
	
	TX();
    	RX_GEN (&init);

	//Assign = 0xD3;
	//TX();    
//----------------- Data transfer --------------

	RX_byte1 (&ID);
	RX_byte2 (&Long1);
	RX_byte3 (&Long2);
	RX_byte4 (&Lat1);
	RX_byte5 (&Lat2);

	RX_byte6 ();
	RX_byte7 ();
	RX_byte8 ();

	RX_byte9 (&Timestamp1);
	RX_byte10 (&Timestamp2);
	RX_byte11 (&Timestamp3);
	RX_byte12 (&Timestamp4);
	RX_byte13 (&Timestamp5);
	RX_byte14 (&Timestamp6);
	RX_byte15 (&Timestamp7);
	RX_byte16 (&Timestamp8);
	RX_byte17 (&Timestamp9);
}

void RX_GEN (unsigned char *init)
{
	SCON0=0x50;
	RI0=0;
    	
	while (RI0==0); //Reception
	*init = SBUF0;
	
        RI0=0;
}

void RX_X (unsigned char *X)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*X = SBUF0; 
	
    	RI0=0;
}

void RX_Y (unsigned char *Y)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Y = SBUF0;
	
    	RI0=0;
}

void RX_byte1 (unsigned char *ID)
{
	SCON0=0x50;
	RI0=0;
	
	while (RI0==0); //Reception
	*ID = SBUF0;
	
    	RI0=0;
}

void RX_byte2 (unsigned char *Long1)
{
	SCON0=0x50;
	RI0=0;
	
	while (RI0==0); //Reception
	*Long1 = SBUF0;
	
    	RI0=0;
}

void RX_byte3 (unsigned char *Long2)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Long2 = SBUF0;
	 
    	RI0=0;
}

void RX_byte4 (unsigned char *Lat1)
{

	SCON0=0x50;
	RI0=0;
	
	while (RI0==0); //Reception
	*Lat1= SBUF0;
	
    	RI0=0;
}

void RX_byte5 (unsigned char *Lat2)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Lat2 = SBUF0;
	
    	RI0=0;
}

void RX_byte6 (void)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	Speed = SBUF0;
	
    	RI0=0;
}

void RX_byte7 (void)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	Heading1 = SBUF0;
	
    	RI0=0;
}

void RX_byte8 (void)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	Heading2 = SBUF0;
	
    	RI0=0;
}

void RX_byte9 (unsigned char *Timestamp1)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp1 = SBUF0;
    	
	RI0=0;
}

void RX_byte10 (unsigned char *Timestamp2)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp2 = SBUF0;

    	RI0=0;
}

void RX_byte11 (unsigned char *Timestamp3)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp3 = SBUF0;
	
    	RI0=0;
}

void RX_byte12 (unsigned char *Timestamp4)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp4 = SBUF0;
	
    	RI0=0;
}

void RX_byte13 (unsigned char *Timestamp5)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp5 = SBUF0;

    	RI0=0;
}

void RX_byte14 (unsigned char *Timestamp6)
{
	SCON0=0x50;
	RI0=0;
	while (RI0==0); //Reception
	*Timestamp6 = SBUF0;

    	RI0=0;
}

void RX_byte15 (unsigned char *Timestamp7)
{
	SCON0=0x50;
	RI0=0;
	
	while (RI0==0); //Reception
	*Timestamp7 = SBUF0;

    	RI0=0;
}

void RX_byte16 (unsigned char *Timestamp8)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp8 = SBUF0;

    	RI0=0;
}

void RX_byte17 (unsigned char *Timestamp9)
{
	SCON0=0x50;
	RI0=0;

	while (RI0==0); //Reception
	*Timestamp9 = SBUF0;

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
