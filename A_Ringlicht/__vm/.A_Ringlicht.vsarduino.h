/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: LED_Ringlicht, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 161
#define ARDUINO_MAIN
#define F_CPU 18432000L
#define __AVR__
#define F_CPU 18432000L
#define ARDUINO 161
#define ARDUINO_AVR_UNO
#define ARDUINO_ARCH_AVR
extern "C" void __cxa_pure_virtual() {;}

//
void serialEvent();
//

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\standard\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <..\A_Ringlicht\A_Ringlicht.ino>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Arduino.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\CDC.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Client.h>
#include <..\A_Ringlicht\Driver.cpp>
#include <..\A_Ringlicht\Driver.h>
#include <..\A_Ringlicht\Functions.cpp>
#include <..\A_Ringlicht\Functions.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HID.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial0.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial1.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial2.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial3.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\HardwareSerial_private.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\IPAddress.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\IPAddress.h>
#include <..\A_Ringlicht\PWM.cpp>
#include <..\A_Ringlicht\PWM.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Print.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Print.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Printable.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Server.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Stream.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Stream.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Tone.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\USBAPI.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\USBCore.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\USBCore.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\USBDesc.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Udp.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\WCharacter.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\WInterrupts.c>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\WMath.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\WString.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\WString.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\abi.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\binary.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\hooks.c>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\main.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\new.cpp>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\new.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\variants\standard\pins_arduino.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\wiring.c>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\wiring_analog.c>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\wiring_digital.c>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\wiring_private.h>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\wiring_pulse.c>
#include <..\..\..\..\..\..\..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\wiring_shift.c>
