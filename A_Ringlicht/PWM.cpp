/*
 * PWM.cpp
 *
 * Created: 13.05.2015 13:15:39
 * Author: Tobias Nuss
 */ 
#ifndef cbi	/* clear Bit in Register */
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~(1<<bit))
#endif
#ifndef sbi	/* set Bit in Register */
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= (1<<bit))
#endif

#include "PWM.h"


PWM::PWM(int pwm1Pin, int pwm2Pin)
{
	m_pwm_Channel_nonPol = pwm1Pin;
	m_pwmChannel_Pol = pwm2Pin;	
}

void PWM::setPWM_1(uint8_t value) // NonPol
{		
	Serial.println(value);
	Serial.print("\r");
	if (value == 0)
	{
		digitalWrite(9, 0);
	}
	if (value >= 255)
	{
		digitalWrite(9, 1);
	}
	else
	{
		OCR1AL = value; // set pwm duty
	}	
}

void PWM::setPWM_2(uint8_t value)	// Pol
{	
	Serial.println(value);
	Serial.print("\r");
	if (value == 0)
	{
		digitalWrite(5, 0);
	}
	if (value >= 255)
	{
		digitalWrite(5, 1);
	}
	else
	{
		OCR3AL = value; // set pwm duty
	}
}

void PWM::Reset(void)
{
	digitalWrite(5,0);
	digitalWrite(9,0);
}

void PWM::Init(void)
{
	pinMode(5, OUTPUT);			// ( TIMER3A )
	pinMode(9, OUTPUT);			// ( TIMER1A )
	
	TCCR1B = TCCR1B & 0b11111000 | 0x01;				// No Prescaling
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0) | (1<<WGM10);	// 8 Bit FastPWM		
		
	TCCR3B = TCCR3B & 0b11111000 | 0x01;					// No Prescaling	
	TCCR3A |= (1<<COM3A1) | (1<<COM1A0) | (1<<WGM30);		// 8 Bit FastPWM
}

