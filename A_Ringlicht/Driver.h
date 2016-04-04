/*
 * Driver.h
 *
 * Created: 16.04.2015 11:38:39
 *  Author: Tobias Nuss
 */ 
#ifndef _ADAFRUIT_TLC59401_H
#define _ADAFRUIT_TLC59401_H

#include <Arduino.h>


class Driver
{
 public:
	Driver(uint8_t n, uint8_t c, uint8_t d, uint8_t l);

	boolean begin(void);

	void setPWM(uint8_t chan, uint16_t pwm);
	void write(void);
	void reset_all();
	void full_brightness();


private:
	uint16_t *pwmbuffer;
	uint8_t numdrivers, _clk, _dat, _lat;

};


#endif /* _ADAFRUIT_TLC59401_H */