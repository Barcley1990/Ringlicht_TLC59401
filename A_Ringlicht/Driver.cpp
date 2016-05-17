/*
 * Driver.cpp
 *
 * Created: 16.04.2015 11:38:27
 *  Author: Tobias Nuss
 *
 * PRINCIPLES OF OPERATION:
 * The TLC59401 has a flexible serial interface, which can be connected to micro controllers or digital signal
 * processors in various ways. Only three pins are needed to input data into the device. The rising edge of SCLK
 * signal shifts the data from the SIN pin to the internal register. After all data are clocked in, a high-level pulse of
 * XLAT signal latches the serial data to the internal registers. The internal registers are level-triggered latches of
 * XLAT signal. All data are clocked in MSB first. The length of serial data is 96 bit or 192 bit, depending on the
 * programming mode. 
 *
 * Grayscale data and dot correction data can be entered during a grayscale cycle. Although
 * new grayscale data can be clocked in during a grayscale cycle, the XLAT signal should only latch the grayscale
 * data at the end of the grayscale cycle. Latching in new grayscale data immediately overwrites the existing
 * grayscale data.
 *
 * MODE:	When MODE=GND, the device is in GS mode. When MODE=Vcc, the device is in DC Mode	
 * XERR:	Reports both error Flags (TEF and LOD). Normal operation: HIGH (Data Sheet S.13)
 * SIN:		Serial Data In		
 * SCLK:	Serial Clock
 * XLAT:	Latch
 * BLANK:	Force all outputs off. Normal condition: LOW (In the layout Blank is an open drain output, therefore the pin must set HIGH for normal operation!)
 * GSCLK:	
 * PWM1:	
 * PWM2:	
 *
 * TEF: THERMAL ERROR FLAG
 * The TLC59401 provides a temperature error flag (TEF) circuit to indicate an over-temperature condition of the IC.
 * If the junction temperature exceeds the threshold temperature (+160°C typical), TEF goes high and the XERR
 * pin goes to a low level. When the junction temperature becomes lower than the threshold temperature, TEF goes
 * low and the XERR pin becomes high impedance. The TEF status can also be read out from the TLC59401
 * status register.
 *
 * LOD: LED OPEN DETECTION
 * The TLC59401 has an LED-open detection circuit that detects broken or disconnected LEDs. The LED open
 * detector pulls the XERR pin to GND when an open LED is detected. XERR and the corresponding error bit in the
 * Status Information Data is only active under the following open LED conditions:
 * 1. OUTn is on and the time tpd2 (1 ?s typical) has passed.
 * 2. The voltage of OUTn is < 0.3V (typical)
 * The LOD status of each output can be also read out from the SOUT pin. See the Status Information Output
 * section for details. The LOD error bits are latched into the Status Information Data when XLAT returns to a low
 * state after a high state. Therefore, the XLAT pin must be pulsed high, then low while XERR is active in order to
 * latch the LOD error into the Status Information Data for subsequent reading via the serial shift register.
 *
 * OPERATING MODES
 * The TLC59401 has two operating modes defined by MODE. The GS (Grayscale) and DC (Dot Correction) registers are
 * set to random values that are not known immediately after power on. The GS and DC values must be
 * programmed before turning on the outputs. Please note that when initially setting GS and DC data after power
 * on, the GS data must be set before the DC data is set. Failure to set GS data before DC data may result in
 * losing the first bit of GS data. XLAT must be low when the MODE pin goes high-to-low or low-to-high to change
 * back and forth between GS mode and DC mode.
 * Vcc: GS mode, 192 bit ; GND: DC mode 96 bit.
 */ 
#include "Driver.h"

// Constructor
Driver::Driver(uint8_t n, uint8_t c, uint8_t d, uint8_t l, uint8_t m) 
{
  numdrivers = n;
  _clk = c;	// SCLK
  _dat = d;	// SIN
  _lat = l;	// XLAT
  _mod = m; // MODE

  pwmbuffer = (uint16_t *)calloc(2, 16*n);
}

/*
The TLC59401 can adjust the brightness of each channel OUTn using a PWM control scheme. The use of 12
bits per channel results in 4096 different brightness steps, from 0% to 100% brightness.
Brightness in % = (GSn/4095) * 100
Where: GSn = the programmed grayscale value for output n (GSn = 0 to 4095)
	     n = 0 to 15
		 Grayscale data for all OUTn 
The input shift register enters grayscale data into the grayscale register for all channels simultaneously. 
The complete grayscale data format consists of 16x12 bit words, which forms a 192-bit wide data packet. 
The data packet must be clocked in MSB first.
*/

#define MODE	2	// GS or DC mode
#define XERR	3	// Reports the error flags
#define DATA    4	// Serial Data In (SIN)
#define SCLK	5	// Serial Clock (SCLK)
#define LATCH   6	// Latch (XLAT)
#define BLANK	7	// set to -1 to not use the enable pin (its optional).
#define GCLK	8

// The TLC59401 compares the grayscale
// value of each output OUTn with the grayscale counter value.

void Driver::write(void) 
{
	// Disable outputs
	digitalWrite(BLANK, LOW);
	
	// Clock in data
	digitalWrite(_lat, LOW);
	// 16 channels per TLC59401
	for (int i=16*numdrivers-1; i>=0 ; i--) {
		// 12 bits per channel, send MSB first
		for (int j=11; j>=0; j--) {
			digitalWrite(_clk, LOW);					
			if (pwmbuffer[i] & (1 << j))
				digitalWrite(_dat, HIGH);
			else
				digitalWrite(_dat, LOW);
			digitalWrite(_clk, HIGH);			
		}
	}
	digitalWrite(_clk, LOW);
	// end of clocking in  

	// latch the serial data into the grayscale register. New grayscale data immediately become valid at the rising edge of the XLAT
	// signal; therefore, new grayscale data should be latched at the end of a grayscale cycle when BLANK is high.
	digitalWrite(_lat, HIGH); 
	digitalWrite(_lat, LOW);
	// end of latching in
	
	digitalWrite(BLANK, HIGH);
	for(int p=0;p<4096;p++){
		digitalWrite(GCLK, HIGH);
		digitalWrite(GCLK, LOW);
	}
}

void Driver::update()
{
	
}

void Driver::setDotCorrection()
{
	setMode(DC);
		
	digitalWrite(_lat, LOW);
	for (int i=0; i<96; i++)
	{
		digitalWrite(_clk, LOW);
		digitalWrite(_dat, HIGH);
		digitalWrite(_clk, HIGH);
	}
	digitalWrite(_lat, HIGH);
	digitalWrite(_lat, LOW);

	// The first GS data input cycle after dot correction requires an additional SCLK pulse after the XLAT signal to complete
	// the grayscale update cycle.
	digitalWrite(_clk, HIGH);
	digitalWrite(_clk, LOW);
	
}

void Driver::setPWM(uint8_t chan, uint16_t pwm) 
{
  //Serial.println(chan);Serial.println(pwm);
  if (pwm > 4095) pwm = 4095;
  if (chan > 16*numdrivers) return;	// 16 LEDs (channels) are connected. 1-8: bottom ring; 9-16 mid ring.
  uint8_t ch;
  switch(chan)
  {
	  // bottom ring
	  case 1: ch = 0; break;
	  case 2: ch = 4; break;
	  case 3: ch = 8; break;
	  case 4: ch = 12; break;
	  case 5: ch = 16; break;
	  case 6: ch = 20; break;
	  case 7: ch = 24; break;
	  case 8: ch = 28; break;
	  // mid ring
	  case 9: ch = 32; break;
	  case 10: ch = 36; break;
	  case 11: ch = 40; break;
	  case 12: ch = 44; break;
	  case 13: ch = 48; break;
	  case 14: ch = 52; break;
	  case 15: ch = 56; break;
	  case 16: ch = 60; break;
	  default: Serial.println("Channel not available!"); break;
  }
  //normalization: 1 channel -> 4 outputs
  pwmbuffer[ch] = pwm;
  pwmbuffer[ch+1] = pwm;
  pwmbuffer[ch+2] = pwm; 
  pwmbuffer[ch+3] = pwm;
}

void Driver::test()
{
	for (uint8_t i=1; i<=16; i++)
	{
		setPWM(i, 1000);
		write();
		delay(500);
		setPWM(i, 0);
	}
	
}

boolean Driver::begin() 
{
  if (!pwmbuffer){
	  Serial.println("pwmbuffer error");
	  return false;
  }

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  pinMode(_mod, OUTPUT); 
  digitalWrite(_lat, LOW);
  // setting  GS mode
  digitalWrite(_mod, LOW);

  return true;
}

void Driver::full_brightness()
{
	for (int i=1; i<=16; i++)
	{
		setPWM(i,4095);
	}
	write();
}

void Driver::reset_all()
{
	for (int i=1; i<=16; i++)
		setPWM(i,0);
	write();
}

// DC mode or GS mode
void Driver::setMode(uint8_t mode)
{
	digitalWrite(_lat, LOW);
	if (mode==1)
		digitalWrite(_mod, LOW);	// GS mode
	else
		digitalWrite(_mod, HIGH);	// DC mode	
}