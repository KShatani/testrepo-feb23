#include <stdlib.h>
#include <stdio.h>
#include <p89lpc9351.h>
#include <time.h>

#define XTAL 7373000L
#define BAUD 9600L
//kshen whattup homies. 
// Make sure these definitions match your wiring
#define LCD_RS P2_7 //pin 4
#define LCD_RW P2_6 //pin 5
#define LCD_E  P2_5 //pin 6
#define LCD_D7 P1_4 //pin 14
#define LCD_D6 P1_6 //pin 13
#define LCD_D5 P1_7 //pin 12
#define LCD_D4 P2_0 //pin 11
#define LCD_D3 P2_1 //pin 10
#define LCD_D2 P2_2 //pin 9
#define LCD_D1 P2_3 //pin 8
#define LCD_D0 P2_4 //pin 7
#define CHARS_PER_LINE 16

// InitPorts: initializes ports 
void InitPorts(void)
{
	P0M1=0;
	P0M2=0;
	P1M1=0;
	P1M2=0;
	P2M1=0;
	P2M2=0;
	P3M1=0;
	P3M2=0;
}

//Wait50us: 
void Wait50us (void)
{
	_asm
    mov R0, #82
L0: djnz R0, L0 ; 2 machine cycles-> 2*0.27126us*92=50us
    _endasm;
}

//waitms: the wait function
void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<20; k++) Wait50us();
}

//
void LCD_pulse (void)
{
	LCD_E=1;
	Wait50us();
	LCD_E=0;
}

//
void LCD_byte (unsigned char x)
{
	// The accumulator in the C8051Fxxx is bit addressable!
	ACC=x;
	LCD_D7=ACC_7;
	LCD_D6=ACC_6;
	LCD_D5=ACC_5;
	LCD_D4=ACC_4;
	LCD_D3=ACC_3;
	LCD_D2=ACC_2;
	LCD_D1=ACC_1;
	LCD_D0=ACC_0;
	LCD_pulse();
}

//WriteData: 
void WriteData (unsigned char x)
{
	LCD_RS=1;
	LCD_byte(x);
	waitms(2);
}
//WriteCommand: 
void WriteCommand (unsigned char x)
{
	LCD_RS=0;
	LCD_byte(x);
	waitms(5);
}

//LCD_8BIT
void LCD_8BIT (void)
{
	LCD_E=0;  // Resting state of LCD's enable is zero
	LCD_RW=0; // We are only writing to the LCD in this program
	waitms(20);
	// First make sure the LCD is in 8-bit mode
	WriteCommand(0x33);
	WriteCommand(0x33);
	WriteCommand(0x33); // Stay in 8-bit mode

	// Configure the LCD
	WriteCommand(0x38);
	WriteCommand(0x0c);
	WriteCommand(0x01); // Clear screen command (takes some time)
	waitms(20); // Wait for clear screen command to finsih.
}

//LCDprint: prints the charater to print on the screen. indicates line & bit clears
void LCDprint(char * string, unsigned char line, bit clear)
{
	unsigned char j;

	WriteCommand(line==2?0xc0:0x80);
	waitms(5);
	for(j=0; string[j]!=0; j++)	WriteData(string[j]);// Write the message
	if(clear) for(; j<CHARS_PER_LINE; j++) WriteData(' '); // Clear the rest of the line
}
////////////////////////////////////////////////////////////////////////////////////
// display_reading: displays the battery voltage and run time
void display_reading()
{
	double start_t = clock();
	
	//code goes here
	
	double end_t = clock();
	double program_time = double
	// Display something in the LCD
	LCDprint("Voltage:", 1, 1);
	LCDprint("Run time: %f", 2, 1, );
}
	
// turn_r: makes a right turn
void turn_right(void)
{
	
}

// turn_l: makes a left turn
void turn_left(void)
{
	
}
// drive_s: drive straight
void drive_straight(int r_m_speed, int l_m_speed)
{
	r_motor = r_m_speed;
	l_motor = l_m_speed;
}
//detect: detects the number of peaks
int detect(void)
{
	if(sensor == BUMP_THRESH)
	{bump_count++;}

}
void main(void)
{
	InitPorts();
	LCD_8BIT();
	
	//This is the "main loop" - it will run forever. 
	while(start_status == 1)
	{
		display_reading(); //displaying voltage and time values
		drive_s();
		
		int position = detect();
		
		if( position < ){
		//we are far to the righ of the line: right leftwards
		drive_left();
		}
		
		else if (position < ){
		//we are somewhat close to being centere on the line: drive straight
		drive_straight();
		}
		
		else{ 
		// we are far to the left of the line: drive rightwards
		drive_right();
		}
		
}