
/*
 * A_Ringlicht.ino
 *
 * Created: 4/16/2015 11:33:02 AM
 * Author: Tobias Nuss
 * New Version for new layout. Used Microcontroller: Atmega 328P with ext. Quartz: 18.432 MHz
 * Used LED driver: TLC59401 (4x)
 *
 *	  Atmega328 -> digital pins (Arduino Uno)
 * MODE:	PD2 -> Pin 2
 * XERR:	PD3 -> Pin 3
 * SIN:		PD4 -> Pin 4
 * SCLK:	PD5 -> Pin 5
 * XLAT:	PD6 -> Pin 6
 * BLANK:	PD7 -> Pin 7
 * GSCLK:	PB0 -> Pin 8
 * PWM1:	PB1 -> Pin 9 (PWM)( TIMER1A)(OC1A)
 * PWM2:	PB2 -> Pin 10 (PWM)( TIMER1B)(OC1B)
 */ 

#define F_CPU 18432000UL

#include "Driver.h"
#include "Functions.h"
#include "PWM.h"

#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define BaudRate 115200
#define HIGH	1
#define LOW		0

// How many boards do you have chained?
#define NUM_TLC59401 1
#define timeout 1000	// set UART timeout in ms



/* N.B. The PWM is just working with this PIN configuration! */
#define pwm_non_polarisation	9	// PWM Channel for LEDs without pol-filter 
#define pwm_polarisation		10	// PWM Channel for LEDs with pol-filter	   

// create objects
Driver tlc = Driver(NUM_TLC59401, SCLK, DATA, LATCH, MODE);
Functions ser = Functions();
PWM pwm = PWM(pwm_non_polarisation, pwm_polarisation);

// globals for UART com.
volatile uint8_t transmit_started = 0;
volatile uint8_t uart_timeout = 0;



int cnt=0;
ISR(TIMER2_COMPB_vect)
{
	if(cnt>=4095){
		cnt=0;
		BLANK_LOW;
		_delay_us(2);
		BLANK_HIGH;
	}
	GCLK_HIGH;
	GCLK_LOW;
	cnt++;
}

void setup()
{
	// force off outputs
	pinMode(BLANK,OUTPUT); digitalWrite(BLANK, LOW);
	
	// Init UART
	Serial.begin(BaudRate);
	while(!Serial);
	
	// Init Driver
	if(tlc.begin());
	tlc.reset_all();
	
	// Init PWM
	//pwm.Init();
	//pwm.Reset();	

	Serial.println("---------------------------------");
	Serial.println("Ring light ready!");	
	Serial.println("Type 'HELP' for more information.");
	Serial.println("Input expected:");
	Serial.println("---------------------------------");
	
	delay(500);
}
	
// is called every main loop
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

void loop()
{
	cli();
	
	// Check Error Flag (toDo)

	if(Serial.available()>0)
		serialEvent();
	if (ser.m_stringComplete)
	{
		Serial.print("got something: ");
		
		// check if RESET was insert	
		if (ser.Check_Reset()){				
			tlc.reset_all();
			tlc.write();
			pwm.Reset();	
			Serial.println("+Reset");	
		}		
		// Print information
		
		else if (ser.Help());
		// Set LEDs for shadow detection (Driver)		
		else if(ser.Check_Input()) {	
			ser.Check_LedValue();
			// set LED
			tlc.setPWM(ser.m_led, ser.m_val);
			tlc.write();					
		}
		// set LEDs for Polarization effect (MosFet)
		else if (ser.Check_Polarisation_1()){
			Serial.print("NPOLY ");
			ser.Check_PolarisationValue();
			pwm.setPWM_1(ser.m_pol_val);
		}
		// set LEDs for Polarization effect (MosFet)
		else if (ser.Check_Polarisation_2()){
			Serial.print("YPOLY ");
			ser.Check_PolarisationValue();
			pwm.setPWM_2(ser.m_pol_val);
		}
		// toggle Pin (ex.: toggle01 -> pin 0 to HIGH)
		else if (ser.Toggle()){
			Serial.println("Toggle pin");
		}
		
		// String does not match anything
		else if(ser.Check_Input()) {
			ser.Check_LedValue();
			// set LED
			tlc.setPWM(ser.m_led, ser.m_val);
			tlc.write();
			ser.m_inputString = "";
			ser.m_stringComplete = false;
		}
		else {	
			Serial.println("String doesn't match!");
			ser.m_inputString = "";
			ser.m_stringComplete = false;
		}	
	}
	
	
	sei();
}



// ToDo: Neuen Timer für Timeout festlegen. Timer/Counter 3 ist für PWM an Pin 5 reserviert.
/*

// Initialize Timer 1 for Interrupt Service Routine
// Interrupt every 16ms
void Timer_init()
{
	TCCR3B |= (1<<CS32) | (1<<CS31) |(1<<CS30);	// prescaler = 1024 -> 16Mhz/1024 = 15625Hz
	TIMSK3 |= (1<<TOIE3);
}

ISR (TIMER3_OVF_vect)
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
*/