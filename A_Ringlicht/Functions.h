
/*
 * IncFile1.h
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
	
	bool m_inputOk = false;
	
	String m_inputString = "";  
	
	 // a string to hold incoming data
	boolean m_stringComplete = false;  // whether the string is complete
	
private:
	

};


#endif 