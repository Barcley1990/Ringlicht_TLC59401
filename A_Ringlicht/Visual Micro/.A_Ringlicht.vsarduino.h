/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Micro, Platform=avr, Package=arduino
*/

#define __AVR_ATmega32u4__
#define __AVR_ATmega32U4__
#define ARDUINO 164
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 164
#define ARDUINO_AVR_MICRO
#define ARDUINO_ARCH_AVR
#define USB_VID 0x2341
#define USB_PID 0x8037
extern "C" void __cxa_pure_virtual() {;}

//
void serialEvent();
//

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\micro\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <A_Ringlicht.ino>
#include <Driver.cpp>
#include <Driver.h>
#include <Functions.cpp>
#include <Functions.h>
#include <PWM.cpp>
#include <PWM.h>
