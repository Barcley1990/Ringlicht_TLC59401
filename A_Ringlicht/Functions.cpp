/*
 * CPPFile1.cpp
 *
 * Created: 16.04.2015 11:38:27
 *  Author: Tobias Nuss
 */ 

#include "Functions.h"

Functions::Functions()
{
	
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
	return true;
}