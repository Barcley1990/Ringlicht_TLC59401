
/*
 * Functions.h
 *
 * Created: 16.04.2015 11:38:39
 *  Author: Tobias Nuss
 */ 
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <Arduino.h>

class Functions
{
public:
	Functions();	
	bool Help();
	bool Check_Reset();
	bool Check_Input();
	bool Check_LedValue();
	bool Check_Polarisation_1();
	bool Check_Polarisation_2();
	bool Check_PolarisationValue();
	bool Toggle();
	void TogglePin(uint8_t pin, uint8_t state);
	
	
	// a string to hold incoming data
	String m_inputString = "";  
	// whether the string is complete
	boolean m_stringComplete = false;
		
	uint8_t m_led = 0;
	uint16_t m_val = 0;
	uint16_t m_pol_val = 0;
		
private:
	uint32_t m_value = 0;
	bool m_inputOk = false;
	char m_tmp_buffer[128];
	char *m_tmp_ptr = m_tmp_buffer;
};


#endif 