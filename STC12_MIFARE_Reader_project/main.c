#include <STC12C5A60S2.H>
#include "ESPInit.h"
#include "UartInit.h"
#include "LED.h"
#include "Value.h"
#include "FIFO.h"
#include "Delayms.h"
#include "UartSend.h"
#include <STRING.H>

unsigned int FLAG = 0;
unsigned char dat = 0;
unsigned char len = 0;
unsigned int count = 0;
unsigned int cot = 0;
unsigned int bits = 0;
unsigned int TXmode = 1;

void main()
{
	EA = 1;
	UartInit1();
	UartInit2();
	//Timer0Init();
	Delayms(1000);
	ESPInit_MODE();
	//SFLAG = 1;
	while(1){
		switch(FLAG){
			case 1 :
				bufferPop(&dat);
				UART1_Send(dat);
					switch(dat){
						case 0x0A :
						UART2_Send(dat);
						if(cot == 2){					
						Delayms(2000);
						Delayms(2000);
						Delayms(2000);
						Delayms(2000);
						Delayms(2000);
						cot++;}
						else{
						Delayms(1000);
						cot++;}							
						break;
						case 0xFE :
						FLAG = 0;
						LED1 = 0;
						SFLAG = 1;
						cot = 0;
						break;
						default :
						UART2_Send(dat);
					}
					break;
				/*case 2 :
					len = buffer.circle_buffer[buffer.head_pos + 3];
					UART1_SendData("AT+CIPSEND=0,");
					UART1_Send(len+48);
					UART1_SendData("\r\n");
					int i = 7;
					for(i < len)
					
					FLAG = 0;
				
					break;
					*/
					case 2 :
					switch(TXmode){
						case 0 :
						UART2_SendData("AT+CIPSEND=0,6\r\n");
						Delayms(500);
						for(bits=5;bits<9;bits++)
					{
							UART2_Send(buffer.circle_buffer[bits]);
					}
							UART2_SendData("\r\n");
						break;
						case 1 :
						UART2_SendData("AT+CIPSEND=0,38\r\n");
						Delayms(500);
						for(bits=5;bits<41;bits++)
					{
							UART2_Send(buffer.circle_buffer[bits]);
					}
							UART2_SendData("\r\n");
							break;  
					}
						FLAG = 0;
						SFLAG = 1;
					break;
					/*case 3 :
					TXmode = 0;
					FLAG = 0;
					SFLAG = 1;
					break;
					case 4 :
					TXmode = 1;
					FLAG = 0;
					SFLAG = 1;
					break;
					*/
			default :
				Delayms(50);
			}	
		
}
}
//串口1 ESP8266触发代码，用于备用
/*void UART1() interrupt 4
{
	if(RI && SFLAG == 1)
	{
		switch(SBUF){
			case 0xFC :
				memset(buffer.circle_buffer, 0, sizeof(unsigned char)*90);
				buffer.head_pos = 0;
				buffer.tail_pos = 0;
				RI = 0;
				break;
			case 0xFE :
				FLAG = 1;
				bufferPush(0xFE);
				RI = 0;
				LED8 = ~LED8;
				SFLAG = 0;
				break;
			default :
				bufferPush(SBUF);
				RI = 0;
		}
	}
	else if (RI)
		RI = 0;
	
	if(TI)
	{
		TI = 0;
	}
}
*/
void UART1() interrupt 4
{
	if(RI && SFLAG == 1){
		switch(SBUF){
			case 0x20 :
			memset(buffer.circle_buffer, 0, sizeof(unsigned char)*90);
			buffer.head_pos = 0;
			buffer.tail_pos = 0;	
			bufferPush(0x20);
			RI = 0;
			break;
			case 0x03 :
			FLAG = 2;
			bufferPush(0x03);
			RI = 0;
			SFLAG = 0;
			break;
			default:
			bufferPush(SBUF);
			RI = 0;
		}
	}
	else if(RI && SFLAG == 0)
		RI = 0;
			
	if(TI)
		TI = 0;
}
	
void UART2() interrupt 8
{
	if(S2CON & S2RI && SFLAG == 1)
	{
		switch(S2BUF){
			case 0xFC :
				memset(buffer.circle_buffer, 0, sizeof(unsigned char)*90);
				buffer.head_pos = 0;
				buffer.tail_pos = 0;
				S2CON &= ~S2RI;
				break;
			case 0xFE :
				FLAG = 1;
				bufferPush(0xFE);
				S2CON &= ~S2RI;
				LED8 = ~LED8;
				SFLAG = 0;
				break;
			/*case 0xFA :
				FLAG = 3;
				S2CON &= ~S2RI;
				SFLAG = 0;
				break;
			case 0xFB :
				FLAG = 4;
				S2CON &= ~S2RI;
				SFLAG = 0;
				break;
			*/
			default :
				bufferPush(S2BUF);
				S2CON &= ~S2RI;
		}
	}
	else if (S2CON & S2RI && SFLAG == 0)
		S2CON &= ~S2RI;
	
	if(S2CON & S2TI)
	{
		S2CON &= ~S2TI;
	}
}


//串口1调试串口2用代码
/*
void UART2() interrupt 8
{
	if(S2CON & S2RI &&SFLAG == 1)
	{
		S2CON &= ~S2RI;//清RI
		bufferPush(S2BUF);
	}
	else if (S2CON & S2RI && SFLAG == 0)
		S2CON &= ~S2RI;
	
	if(S2CON & S2TI)
	{
		S2CON &= ~S2TI;//清TI
	}
}
*/
