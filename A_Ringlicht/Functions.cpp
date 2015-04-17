/*
 * Functions.cpp
 *
 * Created: 16.04.2015 11:38:27
 *  Author: Tobias Nuss
 */ 
#include "Functions.h"

Functions::Functions()
{
	m_inputString.reserve(200);
}

bool Functions::Check_Input()
{
	const char *led = "LED";
	const char *value = "VALUE";
		 
	// check for 'LED'
	for (int i=0; i<3; i++)
	{
		if (m_inputString[i] == *led )
		{
			led++;
		}
		else
			return false;
	}
	// check for 'VALUE'
	for (int i=5; i<10; i++)
	{
		if (m_inputString[i] == *value )
		{
			value++;
		}
		else
			return false;
	}
	return true;	
}

bool Functions::Check_LedValue()
{
	// check if inputString == LEDxxVALUExxxx
	if (Check_Input())
	{
		Serial.print("+");
		m_inputOk = true;
	}
	else
	{
		Serial.print("-");
		m_inputOk = false;
	}
	
	if (m_inputOk)
	{
		// get Channel and Brightness
		for(uint8_t i=0; i<=1; i++)
		{
			*m_tmp_ptr = m_inputString[i+3]; // umkopieren von Zeichen 3 & 4  aus s_buffer in tmp_buffer
			m_tmp_ptr++;
		}
		for(uint8_t i=0; i<=3; i++)
		{
			*m_tmp_ptr = m_inputString[i+10]; // umkopieren von Zeichen 10 - 13  aus s_buffer in tmp_buffer
			m_tmp_ptr++;
		}
		
		m_value = (uint32_t) atol(m_tmp_buffer);
		m_led = m_value / 10000;
		m_val = m_value - (m_led * 10000);

		Serial.print(m_value);
		Serial.print("\r");	
	}
	else  // wrong input
	Serial.print("error\r");
	
	m_tmp_ptr = m_tmp_buffer;
	m_inputString = "";
	m_stringComplete = false;
}

bool Functions::Check_Reset()
{
	const char *reset = "RESET";
	for (int i=0; i<5; i++)
	{
		if (m_inputString[i] == *reset )
		{
			reset++;
		}
		else
			return false;
	}
	m_inputString = "";
	m_stringComplete = false;
	return true;
}