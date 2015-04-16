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
	Serial.begin(9600);
	ser.m_inputString.reserve(200);

	Serial.println("TLC5974 test");
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

	
char tmp_buffer[128];
char *tmp_ptr = tmp_buffer;

	
void loop()
{
	if (ser.m_stringComplete)
	{
		Serial.print(ser.m_inputString);
		
		// check if RESET was insert
		if (!ser.Check_Reset())
		{	
			// check if inputString == LEDxxVALUExxxx
			if (ser.Check_Input())
			{
				Serial.print("+");
				ser.m_inputOk = true;
			}
			else
			{
				Serial.print("-");
				ser.m_inputOk = false;
			}
				
			if (ser.m_inputOk)
			{
				// get Channel and Brightness
				for(uint8_t i=0; i<=1; i++)
				{
					*tmp_ptr = ser.m_inputString[i+3]; // umkopieren von Zeichen 3 & 4  aus s_buffer in tmp_buffer
					tmp_ptr++;
				}
				for(uint8_t i=0; i<=3; i++)
				{
					*tmp_ptr = ser.m_inputString[i+10]; // umkopieren von Zeichen 10 - 13  aus s_buffer in tmp_buffer
					tmp_ptr++;
				}
			
				uint32_t value = (uint32_t) atol(tmp_buffer);
				uint8_t led = value / 10000;
				uint16_t val = value - (led * 10000);

				Serial.print(value);
				Serial.print("\r");
			
				// set LED
				tlc.setPWM(led,val);
				tlc.write();
			}
			else  // wrong input
				Serial.print("error\r");
			
			tmp_ptr = tmp_buffer;		
			ser.m_inputString = "";
			ser.m_stringComplete = false;
		}
		else // Reset
		{
			tlc.reset_all();
			ser.m_inputString = "";
			ser.m_stringComplete = false;			
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


