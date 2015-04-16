/*
 * IncFile1.h
 *
 * Created: 16.04.2015 11:38:39
 *  Author: Tobias Nuss
 */ 


#ifndef _ADAFRUIT_TLC5947_H
#define _ADAFRUIT_TLC5947_H

#include <Arduino.h>


class Driver
{
 public:
	Driver(uint8_t n, uint8_t c, uint8_t d, uint8_t l);

	boolean begin(void);

	void setPWM(uint8_t chan, uint16_t pwm);
	void write(void);
	void reset_all();


private:
	uint16_t *pwmbuffer;
	uint8_t numdrivers, _clk, _dat, _lat;

};


#endif /* INCFILE1_H_ */