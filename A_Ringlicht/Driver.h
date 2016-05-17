/*
 * Driver.h
 *
 * Created: 16.04.2015 11:38:39
 *  Author: Tobias Nuss
 */ 
#ifndef _ADAFRUIT_TLC59401_H
#define _ADAFRUIT_TLC59401_H

#include <Arduino.h>

#define GS 1
#define DC 0

class Driver
{
 public:
	Driver(uint8_t n, uint8_t c, uint8_t d, uint8_t l, uint8_t m);

	boolean begin(void);

	void setPWM(uint8_t chan, uint16_t pwm);
	void write(void);
	void reset_all();
	void full_brightness();
	void update();
	void setMode(uint8_t mode);
	void setDotCorrection();
	void test();

private:
	uint16_t *pwmbuffer;
	uint8_t numdrivers, _clk, _dat, _lat, _mod;
	uint16_t value;

};


#endif /* _ADAFRUIT_TLC59401_H */