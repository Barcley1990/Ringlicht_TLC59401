/*
 * Driver.cpp
 *
 * Created: 16.04.2015 11:38:27
 *  Author: Tobias Nuss
 */ 
#include "Driver.h"

// Constructor
Driver::Driver(uint8_t n, uint8_t c, uint8_t d, uint8_t l) 
{
  numdrivers = n;
  _clk = c;
  _dat = d;
  _lat = l;

  pwmbuffer = (uint16_t *)calloc(2, 24*n);
}

void Driver::write(void) 
{
digitalWrite(_lat, LOW);
	// 24 channels per TLC5974
	for (int i=24*numdrivers - 1 ; i>0 ; i--) 
	{
		// 12 bits per channel, send MSB first
		for (int j=11; j>=0; j--) 
		{
			digitalWrite(_clk, LOW);
			
			if (pwmbuffer[i] & (1 << j))
			{
				digitalWrite(_dat, HIGH);
			}
			else
			{
				digitalWrite(_dat, LOW);
			}
			digitalWrite(_clk, HIGH);
		}
	}
  digitalWrite(_clk, LOW);

  digitalWrite(_lat, HIGH); 
  digitalWrite(_lat, LOW);
}

void Driver::setPWM(uint8_t chan, uint16_t pwm) 
{
  if (pwm > 4095) pwm = 4095;
  if (chan > 8*numdrivers) return;
  uint8_t ch=0;
  switch(chan)
  {
	  case 1: ch = 1; break;
	  case 2: ch = 4; break;
	  case 3: ch = 7; break;
	  case 4: ch = 10; break;
	  case 5: ch = 13; break;
	  case 6: ch = 16; break;
	  case 7: ch = 19; break;
	  case 8: ch = 22; break;
	  default: Serial.print("Channel not available!\r"); break;
  }
  pwmbuffer[ch] = pwm;
  pwmbuffer[ch+1] = pwm;
  pwmbuffer[ch+2] = pwm; 
}

boolean Driver::begin() 
{
  if (!pwmbuffer) return false;

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);

  return true;
}

void Driver::reset_all()
{
	for (int i=0; i<24; i++)
	{
		setPWM(i,0);
	}
	write();
}
void Driver::full_brightness()
{
	digitalWrite(_lat, LOW);
	digitalWrite(_clk, LOW);
	// 24 channels per TLC5974
	for (int i=288; i>0 ; i--)
	{
			digitalWrite(_clk, LOW);
			delay(1);
			digitalWrite(_dat, HIGH);
			delay(1);
			digitalWrite(_clk, HIGH);	
	}
	digitalWrite(_clk, LOW);

	digitalWrite(_lat, HIGH);
	digitalWrite(_lat, LOW);
}