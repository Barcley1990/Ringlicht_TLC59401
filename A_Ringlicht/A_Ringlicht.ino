/*
 * A_Ringlicht.ino
 *
 * Created: 4/16/2015 11:33:02 AM
 * Author: Tobias Nuss
 */ 

#include "Driver.h"
#include "Functions.h"
#include "PWM.h"

#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/io.h>

// ARDUINO MEGA! 

// How many boards do you have chained?
#define NUM_TLC5974 1
#define timeout 1000	// set uart timeout in ms

#define data    5
#define clock   4
#define latch   2
#define oe		-1	// set to -1 to not use the enable pin (its optional)
#define pwm_non_polarisation	7	// PWM Channel for overview LEDs without pol-filter
#define pwm_polarisation		8	// PWM Channel for overview LEDs with pol-filter

Driver tlc = Driver(NUM_TLC5974, clock, data, latch);
Functions ser = Functions();
PWM pwm = PWM(pwm_non_polarisation, pwm_polarisation);

volatile uint8_t transmit_started = 0;
volatile uint8_t uart_timeout = 0;

void setup()
{
	Serial.begin(14400);
	Timer_init();
	Serial.println("Ringlicht bereit!");
	tlc.begin();
	if (oe >= 0){pinMode(oe, OUTPUT);digitalWrite(oe, LOW);}
	Serial.println("Eingabe Erwartet:");

	tlc.reset_all();
	pwm.Reset();
}
	
void loop()
{
	cli();
	if (ser.m_stringComplete)
	{
		Serial.print("completed string arrived: ");
		// check if RESET was insert	
		if (ser.Check_Reset())
		{	
			tlc.reset_all();
			pwm.Reset();	
			Serial.print("+Reset\r");	
		}
		// Set LEDs for shadow detection (Driver)		
		else if(ser.Check_Input()) 
		{	
			ser.Check_LedValue();
			// set LED
			tlc.setPWM(ser.m_led, ser.m_val);
			tlc.write();						
		}
		// set LEDs for Polarization effect (MosFet)
		else if (ser.Check_Polarisation_1())
		{
			Serial.print("NPOLY ");
			ser.Check_PolarisationValue();
			pwm.setPWM_1(ser.m_pol_val);
		}
		// set LEDs for Polarization effect (MosFet)
		else if (ser.Check_Polarisation_2())
		{
			Serial.print("YPOLY ");
			ser.Check_PolarisationValue();
			pwm.setPWM_2(ser.m_pol_val);
		}
		// String does not match anything
		else
		{
			Serial.print("Ups.. String doesn't match!\r");
			ser.m_inputString = "";
			ser.m_stringComplete = false;
		}					
	}
	sei();
}

void serialEvent()
{
	while(Serial.available())
	{
		transmit_started = true;
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		ser.m_inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n' || inChar == '\r') 
		{
			ser.m_stringComplete = true;
			uart_timeout = 0;	
			transmit_started = false;
		}
	}
}

// Initialize Timer 1 for Interrupt Service Routine
// Interrupt every 16ms
void Timer_init()
{
	TCCR2B |= (1<<CS22) | (1<<CS21) |(1<<CS20);	// prescaler = 1024 -> 16Mhz/1024 = 15625Hz
	TIMSK2 |= (1<<TOIE2);
	sei();
}

ISR (TIMER2_OVF_vect)
{
	if (transmit_started == true)
		uart_timeout++;
	if (uart_timeout > 60)
	{
		transmit_started = false;
		uart_timeout = 0;
		Serial.print("UART Timeout\r");
	}	
}
