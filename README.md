# IRRemote
IR Remote Control Library for Arduino

This is simple and compact library to read the signal from IR Remote control and return the code send as an unsigned long. If you want to see a typical analysis of an IR signal, please visit this [link](https://www.hackster.io/Flying_Carlos/using-ir-remote-control-in-raspberry-pi-with-a-sofware-in-c-13149b). 
I'm using raw pins instead of using digitalRead() function because the last one is too slow to handle the remote signal(more than six times). This poses one problem because raw pins definition is different from one processor to another. I did this library using Arduino Uno that has an ATMEL micro. If you want to use an arduino with another processor and pins definition, you have to change the code at line 15 and replace with the pin definition of your micro.

## How to use

You have to instantiate the class IRRemote using the Arduino digital pin number. Allowed pins are 0 to 13, i.e.:

`#define IRPIN 11`

`IRRemote ir(IRPIN);`

Then to read the IR code just use:

`unsigned long code = ir.read();`
