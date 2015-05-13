/*
 * A_Ringlicht.ino
 *
 * Created: 4/16/2015 11:33:02 AM
 * Author: Tobias Nuss
 */ 

#include "Driver.h"
#include "Functions.h"
#include "PWM.h"

// ARDUINO MEGA! 

// How many boards do you have chained?
#define NUM_TLC5974 1

#define data    5
#define clock   4
#define latch   2
#define oe		-1	// set to -1 to not use the enable pin (its optional)
#define pwm_non_polarisation	7	// PWM for overview LEDs without pol-filter
#define pwm_polarisation		8

Driver tlc = Driver(NUM_TLC5974, clock, data, latch);
Functions ser = Functions();
PWM pwm = PWM();
void setup()
{
	Serial.begin(14400);
	
	Serial.println("Ringlicht bereit!");
	tlc.begin();
	if (oe >= 0)
	{
		pinMode(oe, OUTPUT);
		digitalWrite(oe, LOW);
	}
	Serial.println("Eingabe Erwartet:");
	
	tlc.reset_all();
}
	
void loop()
{
	if (ser.m_stringComplete)
	{
		Serial.print("completed string arrived ");
		// check if RESET was insert	
		if (ser.Check_Reset())
		{			
			Serial.print("+Reset\r");
			tlc.reset_all();		
		}		
		else 
		{	
			Serial.print("no Reset ");
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


// ToDo -> UART Timeout!