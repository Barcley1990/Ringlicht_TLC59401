/*
 * PWM.cpp
 *
 * Created: 13.05.2015 13:15:39
 * Author: Tobias Nuss
 */ 

#include "PWM.h"


PWM::PWM(int pwm1Pin, int pwm2Pin)
{
	m_pwm_Channel_nonPol = pwm1Pin;
	m_pwmChannel_Pol = pwm2Pin;	
	
	pinMode(m_pwmChannel_Pol, OUTPUT);
	pinMode(m_pwm_Channel_nonPol, OUTPUT);
	analogWrite(m_pwm_Channel_nonPol, 0);
	analogWrite(m_pwmChannel_Pol, 0);
}

void PWM::setPWM_1(uint8_t value)
{		
	Serial.println(value);
	Serial.print("\r");
	analogWrite(m_pwm_Channel_nonPol, value);
}

void PWM::setPWM_2(uint8_t value)
{	
	Serial.println(value);
	Serial.print("\r");
	analogWrite(m_pwmChannel_Pol, value);
}

void PWM::Reset(void)
{
	analogWrite(m_pwmChannel_Pol, 0);
	analogWrite(m_pwm_Channel_nonPol, 0);
}

void PWM::Init(void);
{
	pinMode(3, OUTPUT);			// ( TIMER0B )
	pinMode(5, OUTPUT);			// ( TIMER3A )
	
	TCCR0A |= (1<<COM0B1);		// These bits control the Output Compare pin (OC0A) behavior.
	
}

