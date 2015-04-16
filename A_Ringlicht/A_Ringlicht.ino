
/*
 * A_Ringlicht.ino
 *
 * Created: 4/16/2015 11:33:02 AM
 * Author: Tobias Nuss
 */ 

#include "tre.h"

// How many boards do you have chained?
#define NUM_TLC5974 1

#define data     4//13
#define clock    5//12
#define latch    7//10
#define oe  -1  // set to -1 to not use the enable pin (its optional)

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch);


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
	Serial.begin(9600);
	inputString.reserve(200);
	
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
	reset_all();
}

void loop()
{
	serial_call();
}




bool check_input()
{	
	const char *led = "LED";
	const char *value = "VALUE";
		
	// check for 'LED'
	for (int i=0; i<3; i++)
	{
		if (inputString[i] == *led )
		{
			led++;
		}
		else
			return false;
	}	
	// check for 'VALUE'
	for (int i=5; i<10; i++)
	{
		if (inputString[i] == *value )
		{
			value++;
		}
		else
			return false;
	}	
	return true;
}

bool check_Reset()
{
	const char *reset = "RESET";
	for (int i=0; i<5; i++)
	{
		if (inputString[i] == *reset )
		{
			reset++;
		}
		else
			return false;
	}
	return true;
}


	
char tmp_buffer[128];
char *tmp_ptr = tmp_buffer;
bool inputOk = false;
	
void serial_call()
{
	if (stringComplete)
	{
		Serial.print(inputString);
		
		if (check_Reset())
		{
			reset_all();
			inputString = "";
			stringComplete = false;
			
		}
		
		
		// check if inputString == LEDxxVALUExxxx
		if (check_input())
		{
			Serial.print("+");
			inputOk = true;
		}
		else
			Serial.print("-");
		
		if (inputOk)
		{
			// get Channel and Brightness
			for(uint8_t i=0; i<=1; i++)
			{
				*tmp_ptr = inputString[i+3]; // umkopieren von Zeichen 3 & 4  aus s_buffer in tmp_buffer
				tmp_ptr++;
			}
			for(uint8_t i=0; i<=3; i++)
			{
				*tmp_ptr = inputString[i+10]; // umkopieren von Zeichen 10 - 13  aus s_buffer in tmp_buffer
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
		else
			Serial.print("error\r");
			
		tmp_ptr = tmp_buffer;		
		inputString = "";
		stringComplete = false;
	}	
}

void serialEvent()
{
	while(Serial.available())
	{
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n' || inChar == '\r') 
			stringComplete = true;
	}
}


void reset_all()
{
	for (int i=0; i<24; i++)
	{
		tlc.setPWM(i,0);
	}
	tlc.write();
}