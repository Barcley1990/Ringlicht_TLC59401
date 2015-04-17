
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
	bool Check_Input();
	bool Check_Reset();
	bool Check_LedValue();
	
	// a string to hold incoming data
	String m_inputString = "";  
	// whether the string is complete
	boolean m_stringComplete = false;
		
	uint8_t m_led;
	uint16_t m_val;
		
private:
	uint32_t m_value;
	bool m_inputOk = false;
	char m_tmp_buffer[128];
	char *m_tmp_ptr = m_tmp_buffer;

};


#endif 