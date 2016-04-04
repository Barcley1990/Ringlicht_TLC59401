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
 * MODE:		
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
Driver::Driver(uint8_t n, uint8_t c, uint8_t d, uint8_t l) 
{
  numdrivers = n;
  _clk = c;	// SCLK
  _dat = d;	// SIN
  _lat = l;	// XLAT

  pwmbuffer = (uint16_t *)calloc(2, 16*n);
}

/*
The TLC59401 can adjust the brightness of each channel OUTn using a PWM control scheme. The use of 12
bits per channel results in 4096 different brightness steps, from 0% to 100% brightness.
Brightness in % = (GSn/4095) * 100
*/
void Driver::write(void) 
{
digitalWrite(_lat, LOW);
	// 16 channels per TLC59401
	for (int i=16*numdrivers-1; i>=0 ; i--) 
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
	  default: Serial.print("Channel not available!\r"); break;
  }
  //normalization: 1 channel -> 4 outputs
  pwmbuffer[ch] = pwm;
  pwmbuffer[ch+1] = pwm;
  pwmbuffer[ch+2] = pwm; 
  pwmbuffer[ch+3] = pwm;
}

boolean Driver::begin() 
{
  if (!pwmbuffer) return false;

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);
  for (int i=0; i<288; ++i)
  {
	digitalWrite(_clk,LOW);
	digitalWrite(_dat,HIGH);
	digitalWrite(_clk,LOW);
  }
	digitalWrite(_lat, HIGH);
	digitalWrite(_lat, LOW);

  return true;
}

void Driver::full_brightness()
{
	for (int i=1; i<=8; i++)
	{
		setPWM(i,4095);
	}
	write();
}

void Driver::reset_all()
{
	for (int i=1; i<=8; i++)
	{
		setPWM(i,0);
	}
	write();
}