/*
 * IncFile1.h
 *
 * Created: 16.04.2015 11:38:39
 *  Author: tobnu
 */ 


#ifndef _ADAFRUIT_TLC5947_H
#define _ADAFRUIT_TLC5947_H

#include <Arduino.h>


class Adafruit_TLC5947 {
 public:
  Adafruit_TLC5947(uint8_t n, uint8_t c, uint8_t d, uint8_t l);

  boolean begin(void);

  void setPWM(uint8_t chan, uint16_t pwm);
  void write(void);


 private:
  uint16_t *pwmbuffer;

  uint8_t numdrivers, _clk, _dat, _lat;

};


#endif /* INCFILE1_H_ */