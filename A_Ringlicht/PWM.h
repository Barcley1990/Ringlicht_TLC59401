/*
 * PWM.h
 *
 * Created: 13.05.2015 13:15:39
 * Author: Tobias Nuss
 */ 
#ifndef PWM_H
#define PWM_H

#include <Arduino.h>


class PWM
{
public:
	// Constructor
	PWM(int pwm1Pin, int pwm2Pin);
	
	void setPWM_1(uint8_t value);
	void setPWM_2(uint8_t value);
	void Reset(void);
	void Init(void);


private:
	int m_pwm_Channel_nonPol;
	int m_pwmChannel_Pol;

};


#endif /* PWM_H */