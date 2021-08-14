/*
 Name:		IRRemoteLib.cpp
 Created:	8/13/2021 4:28:55 PM
 Author:	Carlos
 Editor:	http://www.visualmicro.com
*/

#include "IRRemoteLib.h"


IRRemote::IRRemote(int pin) {
  // initialize digital pin IRPIN as input.
  pinMode(pin, INPUT);

  switch (pin) {
  case 0:
    _pinIR = &PIND;
    _bitIR = 0;
    break;
  case 1:
    _pinIR = &PIND;
    _bitIR = 1;
    break;
  case 2:
    _pinIR = &PIND;
    _bitIR = 2;
    break;
  case 3:
    _pinIR = &PIND;
    _bitIR = 3;
    break;
  case 4:
    _pinIR = &PIND;
    _bitIR = 4;
    break;
  case 5:
    _pinIR = &PIND;
    _bitIR = 5;
    break;
  case 6:
    _pinIR = &PIND;
    _bitIR = 6;
    break;
  case 7:
    _pinIR = &PIND;
    _bitIR = 7;
    break;
  case 8:
    _pinIR = &PINB;
    _bitIR = 0;
    break;
  case 9:
    _pinIR = &PINB;
    _bitIR = 1;
    break;
  case 10:
    _pinIR = &PINB;
    _bitIR = 2;
    break;
  case 11:
    _pinIR = &PINB;
    _bitIR = 3;
    break;
  case 12:
    _pinIR = &PINB;
    _bitIR = 4;
    break;
  case 13:
    _pinIR = &PINB;
    _bitIR = 5;
    break;

  }

}

unsigned long IRRemote::read() {
  unsigned long code = 0;
  int p;
  if ((p = *_pinIR & _BV(_bitIR)) == 0) {

    code = decodeNoArray();
    //Serial.print("Code (Hex): "); Serial.println(code, HEX);

    delay(250);
  }
  return code;
}

//Decode the signal from IR receiver
unsigned long IRRemote::decodeNoArray() {
  int i = 0, j = 0;
  double rate;
  char binary[PULSES] = { '\0' };
  int pulses[PULSES][2];  //pulses[][0] = value , pulses[][1] = time(us)
  int pulsesCount;  int lastTime = 0;
  int startTime, t;
  int data0, data1;

  startTime = millis();
  data0 = *_pinIR & _BV(_bitIR);
  lastTime = micros();

  while (((t = millis()) - startTime) < PERIOD) {
    data1 = *_pinIR & _BV(_bitIR);

    if (data0 != data1) {
      pulses[j][0] = data0; //value
      pulses[j][1] = micros() - lastTime; //time im us
      j++;
      data0 = data1;
      lastTime = micros();
    }
  }

  pulsesCount = j - 1;

  j = 0;
  for (i = 0; i < pulsesCount; i++) {
    if (pulses[i][0] != 8) {
      continue;
    }
    if (j != 0 && pulses[i][1] > 2000) {
      break;
    }
    else if (pulses[i][1] < 1000) {
      binary[j++] = '0';
    }
    else if (pulses[i][1] >= 1000 && pulses[i][1] <= 2000) {
      binary[j++] = '1';
    }
  }

  binary[j] = '\0';
  //printf("Binary: %s\n", binary);
  String binaryStr = binary;
  i = 0;
  return binaryStr2DecNew(binary);
}

//Convert binary string to integer
unsigned long IRRemote::binaryStr2DecNew(char* bin) {
  int i, len, j = 0;
  unsigned long ret = 0;

  len = strlen(bin);

  for (i = len - 1; i >= 0; i--) {
    ret += ((unsigned long)(bin[i] - '0')) * (unsigned long)1 << j;
    j++;
  }

  return ret;
}

