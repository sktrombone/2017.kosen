/**********************************************************
msecwait関数で1秒ごとのLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190は実測によって求めた値 25MHz駆動*/
	}
}

main()
{
	initLed();
	while(1) {
		turnOnLed(1); /*LED0のON*/
		waitmsec(500);
		turnOffLed(1); /*LED0のON*/
		waitmsec(500);
		turnOnLed(1); /*LED0のON*/
		waitmsec(500);
		turnOffLed(1); /*LED0のON*/
		waitmsec(500);
		
		turnOnLed(0); /*LED0のON*/
		waitmsec(500);
		turnOffLed(0); /*LED0のON*/
		waitmsec(500);
		turnOnLed(0); /*LED0のON*/
		waitmsec(500);
		turnOffLed(0); /*LED0のON*/
		waitmsec(500);
		
		turnOnLed(1); /*LED0のON*/
		waitmsec(500);
		turnOffLed(1); /*LED0のON*/
		waitmsec(500);
		
		turnOnLed(0); /*LED0のON*/
		waitmsec(500);
		turnOffLed(0); /*LED0のON*/
		waitmsec(500);

				
	}
}
