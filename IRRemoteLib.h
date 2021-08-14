/*
 Name:		IRRemoteLib.h
 Created:	8/13/2021 4:28:55 PM
 Author:	Carlos
 Editor:	http://www.visualmicro.com
*/

#ifndef _IRRemoteLib_h
#define _IRRemoteLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DATANBR 150.0
#define PERIOD 80 //miliseconds
#define PULSES 100

class IRRemote
{
public:
	IRRemote(int pin);
	unsigned long read();
private:
  unsigned long decodeNoArray();
  unsigned long binaryStr2DecNew(char* bin);
  uint8_t volatile* _pinIR;
	int _bitIR;
};

#endif

