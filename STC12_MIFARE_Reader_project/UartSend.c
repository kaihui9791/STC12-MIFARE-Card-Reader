#include <STC12C5A60S2.H>
#include "UartSend.h"
#include "Value.h"
#include "LED.h"

void UART1_Send(unsigned char A)
{		    
	ES=0;
	SBUF=A;
	//LED1 = 0;
	while(!TI);
	//TI=0;
	ES=1;	
}

void UART1_SendData(unsigned char* As)
{
	int i = 0;
	while(As[i] != '\0'){
		UART1_Send(As[i]);
		i++;
	}
	//LED2 = 0;
}

void UART2_Send(unsigned char A)
{		    
	IE2=0x00;//ES2=0;
	S2BUF=A;
	while(!(S2CON&S2TI));//若S2TI=0，在此等待
	//S2CON&=~S2TI;//S2TI=0
	IE2=0x01;//ES2=1;	
}

void UART2_SendData(unsigned char* As)
{
	int i = 0;
	while(As[i] != '\0'){
		UART2_Send(As[i]);
		i++;
	}
}