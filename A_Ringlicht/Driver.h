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

// Define data pins
#define MODE	2	// GS or DC mode
#define XERR	3	// Reports the error flags
#define DATA    4	// Serial Data In (SIN)
#define SCLK	5	// Serial Clock (SCLK)
#define LATCH   6	// Latch (XLAT)
#define BLANK	7	// set to -1 to not use the enable pin (its optional).
#define GCLK	8
// Define Ports
#define MODEPORT	PORTD
#define XERRPORT	PORTD
#define DATAPORT	PORTD
#define SCLKPORT	PORTD
#define LATCHPORT	PORTD
#define BLANKPORT	PORTD
#define GCLKPORT	PORTB
// Define pin functions
#define LATCH_HIGH	LATCHPORT |= (1<<PD6)
#define LATCH_LOW	LATCHPORT &= ~(1<<PD6)
#define DATA_HIGH	DATAPORT |= (1<<PD4)
#define DATA_LOW	DATAPORT &= ~(1<<PD4)
#define SCLK_HIGH	SCLKPORT |= (1<<PD5)
#define SCLK_LOW	SCLKPORT &= ~(1<<PD5)
#define GCLK_HIGH	GCLKPORT |= (1<<PB0)
#define GCLK_LOW	GCLKPORT &= ~(1<<PB0)
#define BLANK_HIGH	BLANKPORT |= (1<<PD7)
#define BLANK_LOW	BLANKPORT &= ~(1<<PD7)

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