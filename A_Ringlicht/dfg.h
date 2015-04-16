// dfg.h

#ifndef _DFG_h
#define _DFG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DfgClass
{
 protected:


 public:
	void init();
};

extern DfgClass Dfg;

#endif

