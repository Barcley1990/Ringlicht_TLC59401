/*
 * Functions.cpp
 *
 * Created: 16.04.2015 11:38:27
 *  Author: Tobias Nuss
 */ 
#include "Functions.h"

Functions::Functions()
{
	m_inputString.reserve(5000);
}

bool Functions::Check_Reset()
{
	const char *reset = "RESET";
	for (int i=0; i<5; ++i)
	{
		if (m_inputString[i] == *reset)
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

bool Functions::Check_Input()
{
	const char *led = "LED";
	const char *value = "VALUE";
		 
	// check for 'LED'
	for (int i=0; i<3; ++i)
	{
		if (m_inputString[i] == *led )
		{
			led++;
		}
		else
			return false;
	}
	// check for 'VALUE'
	for (int i=5; i<10; ++i)
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
	// get Channel and Brightness
	for(uint8_t i=0; i<=1; ++i)
	{
		*m_tmp_ptr = m_inputString[i+3]; // umkopieren von Zeichen 3 & 4  aus s_buffer in tmp_buffer
		m_tmp_ptr++;
	}
	for(uint8_t i=0; i<=3; ++i)
	{
		*m_tmp_ptr = m_inputString[i+10]; // umkopieren von Zeichen 10 - 13  aus s_buffer in tmp_buffer
		m_tmp_ptr++;
	}
		
	m_value = (uint32_t) atol(m_tmp_buffer);
	m_led = m_value / 10000;
	m_val = m_value - (m_led * 10000);

	Serial.println(m_value);
	//Serial.print("\r");	

	m_tmp_ptr = m_tmp_buffer;
	m_inputString = "";
	m_stringComplete = false;
	memset(m_tmp_buffer, 0, sizeof(m_tmp_buffer));
}

bool Functions::Check_Polarisation_1()
{
	const char *pol = "NPOLY";
	for (int i=0; i<5; ++i)
	{
		if (m_inputString[i] == *pol)
		{
			pol++;
		}
		else
			return false;		
	}
	return true;
}

bool Functions::Check_Polarisation_2()
{
	const char *pol = "YPOLY";
	for (int i=0; i<5; ++i)
	{
		if (m_inputString[i] == *pol)
		{
			pol++;
		}
		else
		return false;
	}
	return true;
}

bool Functions::Check_PolarisationValue()
{
	for (uint8_t i=0; i<3; ++i)
	{
		*m_tmp_ptr = m_inputString[i+5];
		m_tmp_ptr++;
	}
	m_pol_val = (uint16_t) atol(m_tmp_buffer);
	if (m_pol_val > 255)
	{
		m_pol_val = 255;
	}
		
	m_tmp_ptr = m_tmp_buffer;
	m_inputString = "";
	m_stringComplete = false;
	memset(m_tmp_buffer, 0, sizeof(m_tmp_buffer));
}

bool Functions::Toggle() {
	const char *ptr = "TOGGLE";
	for (int i=0; i<6; ++i)
	{
		if (m_inputString[i] == *ptr)
		{
			ptr++;
		}
		else
		return false;
	}
	
	// copy values
	*m_tmp_ptr = m_inputString[6]; 
	uint8_t i=(uint8_t)atoi(m_tmp_buffer);
	*m_tmp_ptr = m_inputString[7];
	uint8_t j=(uint8_t)atoi(m_tmp_buffer);
	
	// if i and j are between 0 and 10
	if (i>=0 && i<=10 && j>=0 && j<=10){
		TogglePin(i, j);
		
		m_tmp_ptr = m_tmp_buffer;
		m_inputString = "";
		m_stringComplete = false;
		memset(m_tmp_buffer, 0, sizeof(m_tmp_buffer));
		return true;		
	}
	else
	return false;	
}


void Functions::TogglePin(uint8_t pin, uint8_t state){
	switch (pin) {
		case 2: if (state==1)	// Mode
			PORTD |= (1<<PD2);
		else
			PORTD &= ~(1<<PD2);
		break;
		case 3: if (state==1)	// XERR
			PORTD |= (1<<PD3);
		else
			PORTD &= ~(1<<PD3);
		break;
		case 4: if (state==1)	// SIN
			PORTD |= (1<<PD4);
		else
			PORTD &= ~(1<<PD4);
		break;
		case 5: if (state==1)	// SCLK
			PORTD |= (1<<PD5);
		else
			PORTD &= ~(1<<PD5);
		break;
		case 6: if (state==1)	// XLAT
			PORTD|= (1<<PD6);
		else
			PORTD &= ~(1<<PD6);
		break;
		case 7: if (state==1)	// BLANK
			PORTD |= (1<<PD7);
		else
			PORTD &= ~(1<<PD7);
		break;
	}
}

bool Functions::Help(){
	const char *ptr = "HELP";
	for (int i=0; i<4; ++i)
	{
		if (m_inputString[i] == *ptr)
		{
			ptr++;
		}
		else
			return false;
	}
	Serial.println("");
	Serial.println("***** Commands *****");
	Serial.println("(1):RESET");
	Serial.println("(2):LEDxxVALUExxxx");
	Serial.println("(3):YPOLYxxx");
	Serial.println("(4):NPOLYxxx");
	Serial.println("(5):TOGGLExx");
	Serial.println("");
	Serial.println("(1):Reset all LEDs to 0");
	Serial.println("(2):Set LED 1-16 individually with values from 0-4095.");
	Serial.println("(3):Turn on 8 LEDs with polarization filter. Set Brightness from 0-255.");
	Serial.println("(4):Turn on 8 LEDs without polarization filter. Set Brightness from 0-255.");
	Serial.println("(5):Toggle a micro controller pin. The first value sets the number of the pin, the second  is used for HIGH (1) and LOW (0).");
	Serial.println("********************");
	
	m_tmp_ptr = m_tmp_buffer;
	m_inputString = "";
	m_stringComplete = false;
	memset(m_tmp_buffer, 0, sizeof(m_tmp_buffer));
	
	return true;
}