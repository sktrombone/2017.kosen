/**********************************************************
msecwait�֐���1�b���Ƃ�LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void waitmsec(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<4190;j++);    /*4190�͎����ɂ���ċ��߂��l 25MHz�쓮*/
	}
}

main()
{
	initLed();
	while(1) {
		turnOnLed(0); /*LED0��ON*/
		turnOnLed(1); /*LED1��ON*/
		waitmsec(500);
		
		turnOffLed(0); /*LED0��OFF*/
		turnOffLed(1); /*LED1��OFF*/
		waitmsec(500);
	}
}
