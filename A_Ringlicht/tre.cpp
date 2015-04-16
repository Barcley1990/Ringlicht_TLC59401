/*
 * CPPFile1.cpp
 *
 * Created: 16.04.2015 11:38:27
 *  Author: Tobias Nuss
 */ 

#include "tre.h"

Adafruit_TLC5947::Adafruit_TLC5947(uint8_t n, uint8_t c, uint8_t d, uint8_t l) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  _lat = l;

  pwmbuffer = (uint16_t *)calloc(2, 24*n);
}

void Adafruit_TLC5947::write(void) 
{
digitalWrite(_lat, LOW);
	// 24 channels per TLC5974
	for (int8_t c=24*numdrivers - 1; c>0 ; c--) 
	{
		// 12 bits per channel, send MSB first
		for (int8_t b=12; b>0; b--) 
		{
			digitalWrite(_clk, LOW);
			
			if (pwmbuffer[c] & (1 << b))
				digitalWrite(_dat, HIGH);
			else
				digitalWrite(_dat, LOW);

			digitalWrite(_clk, HIGH);
		}
	}
  digitalWrite(_clk, LOW);
  
  digitalWrite(_lat, HIGH);  
  digitalWrite(_lat, LOW);
}

void Adafruit_TLC5947::setPWM(uint8_t chan, uint16_t pwm) 
{
  if (pwm > 4095) pwm = 4095;
  if (chan > 24*numdrivers) return;
  pwmbuffer[chan] = pwm;  
}

boolean Adafruit_TLC5947::begin() {
  if (!pwmbuffer) return false;

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);

  return true;
}
