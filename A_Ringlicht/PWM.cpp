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
	
	OCR1AL = value; // set pwm duty
		
}

void PWM::setPWM_2(uint8_t value)	// Pol
{	
	Serial.println(value);
	Serial.print("\r");
	
	OCR1BL = value; // set pwm duty
	
}

void PWM::Reset(void)
{
	OCR1AL = 0x0;
	OCR1BL = 0x0;
}

void PWM::Init(void)
{
	pinMode(m_pwm_Channel_nonPol, OUTPUT);	// ( TIMER3A )
	pinMode(m_pwmChannel_Pol, OUTPUT);		// ( TIMER1A )
	
	TCCR1B = TCCR1B & 0b11111000 | 0x01;	// No Prescaling
	TCCR1A |= (1<<COM1A1) | (1<<WGM10);		// 8 Bit FastPWM		
		
	//TCCR3B = TCCR3B & 0b11111000 | 0x01;	// No Prescaling	
	//TCCR3A |= (1<<COM3A1) | (1<<WGM30);		// 8 Bit FastPWM
}

