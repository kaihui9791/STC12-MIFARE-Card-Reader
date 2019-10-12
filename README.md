# 目录
1. 简介
2. 硬件设计与底层代码
3. 软件设计

## 硬件设计与底层代码
本设计以Intel 8051增强架构STC12系列为中央处理器，用于处理各模块之间的数据通信，WIFI模块与读卡器模块通过UART方式与单片机相连，计算机软件与单片机通过ESP8266通信或下发指令。

### 元器件选型
单片机：STC12c5a60s2
WIFI模块：ESP8266
读卡模块：TX522B

### 系统工作流程
如同大多数无线系统首次配置流程一样，先自身生成热点供其他设备连入，接收其他设备的WIFI配置后将自身连接到指定的WIFI实现互联网通讯，从而无需外部输入设备即可完成网络配置。本系统在首次启动后，单片机自动将WIFI模块配置为AP模式，生成一个没有与互联网连接的无限局域网，计算机连接后即可正常获取数据或者修改网络配置。因为软件部分所内置的数据库通信模块需要互联网连接，而直接生成的热点是无法访问互联网的，所以如果需要数据库通信模块正常工作，需要将WIFI模块通过软件配置为Station模式并且连接上可以访问互联网的热点。如果事先将WIFI模块配置为Station模式，因为Station模式需要在单片机内部程序里预先编写好已知的SSID与密码，若系统需要在不同地方使用，则每次都需要重新更改内部程序并重新烧录，不便使用，使用AP模式后再由计算机配置网络可以避免此问题。

### 底层代码
初始化模块：UartInit.c
FIFO模块：FIFO.c
串口发送模块：UartSend.c
延时模块：Delayms.c
WIFI初始化模块：UartInit.c
主函数：main.c

main.c
```
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

```

## 软件设计
用户界面编写：Labview+Database Connectivity Toolkit
远程服务器：LNMP

### 软件模块
TCP网络通讯模块，硬件网络配置模块，远程数据库，数据库交互模块，网页显示数据库数据