/*
 * A_Ringlicht.ino
 *
 * Created: 4/16/2015 11:33:02 AM
 * Author: Tobias Nuss
 */ 

#include "Driver.h"
#include "Functions.h"

// How many boards do you have chained?
#define NUM_TLC5974 1

#define data     4//13
#define clock    5//12
#define latch    7//10
#define oe  -1  // set to -1 to not use the enable pin (its optional)

Driver tlc = Driver(NUM_TLC5974, clock, data, latch);
Functions ser = Functions();

void setup()
{
	Serial.begin(19200);
	
	Serial.println("Ringlicht bereit!");
	tlc.begin();
	if (oe >= 0)
	{
		pinMode(oe, OUTPUT);
		digitalWrite(oe, LOW);
	}
	Serial.println("Eingabe Erwartet:");
	
	pinMode(3, OUTPUT);
	pinMode(2,OUTPUT);
	digitalWrite(2,HIGH);
	digitalWrite(3,LOW);
	tlc.reset_all();
}
	
void loop()
{
	if (ser.m_stringComplete)
	{
		Serial.print(ser.m_inputString);
		
		// check if RESET was insert	
		if (ser.Check_Reset())
		{				
			tlc.reset_all();		
		}		
		else 
		{	
			ser.Check_LedValue();
			// set LED
			tlc.setPWM(ser.m_led,ser.m_val);
			tlc.write();						
		}
	}	
}

void serialEvent()
{
	while(Serial.available())
	{
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		ser.m_inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n' || inChar == '\r') 
			ser.m_stringComplete = true;
	}
}


