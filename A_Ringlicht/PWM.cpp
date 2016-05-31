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

// PB1 (OC1B)
void PWM::setPWM_1(uint8_t value) // NonPol
{		
	Serial.println(value);
	Serial.print("\r");
	
	analogWrite(9, value);
	
	//OCR1AL = value; // set pwm duty
		
}
// PB2 (OC2A)
void PWM::setPWM_2(uint8_t value)	// Pol
{	
	Serial.println(value);
	Serial.print("\r");
	
	analogWrite(10, value);
	
	//OCR2A = value; // set pwm duty
	
}

void PWM::Reset(void)
{
	analogWrite(9, 0);
	analogWrite(10, 0);
	//OCR1AL = 0x0;
	//OCR2A = 0x0;
}

// Arduino UNO: 
// Timer0 8bit (__delay()__, __millis()__ and __micros()__)
// Timer1 16bit ( __Servo library__) --> used for PWM
// Timer2 8bit ( __tone()__)
void PWM::Init(void)
{
	pinMode(m_pwm_Channel_nonPol, OUTPUT);	// ( TIMER1A )
	pinMode(m_pwmChannel_Pol, OUTPUT);		// ( TIMER1B )
	
	/*
	TCCR1B = TCCR1B & 0b11111000 | 0x01;	// No Prescaling
	TCCR1A |= (1<<COM1A1) | (1<<WGM10);		// 8 Bit FastPWM		
		
	TCCR2B = TCCR2B & 0b11111000 | 0x01;	// No Prescaling	
	TCCR2A |= (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);		// 8 Bit FastPWM, Clear OC2A on Compare Match, set OC2A at BOTTOM,(non-inverting mode).
	*/
}

