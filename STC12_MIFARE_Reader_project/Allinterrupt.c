#include <STC12C5A60S2.H>
#include "Value.h"
#include "FIFO.h"
#include "LED.h"

void UART1() interrupt 4
{
	if(RI)
	{
		bufferPush(SBUF);
		RI = 0;
		LED7 = 0;
	}
	if(TI)
	{
		TI = 0;
		LED8 = 0;
	}
}

void UART2() interrupt 8
{
	if(S2CON & S2RI)
	{
		S2CON &= ~S2RI;//清RI
	}
	if(S2CON & S2TI)
	{
		S2CON &= ~S2TI;//清TI
	}
}

void Int0() interrupt 0
{

}

//Main函数中IT0 = 1;EX0 = 1;EA = 1;