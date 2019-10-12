#include "Delayms.h"
#include "FIFO.h"
#include "UartSend.h"
#include "LED.h"
#include "ESPInit.h"
#include <STRING.H>

/*void ESPInit_MODE()
{
	Delayms(1000);
	while(buffer.circle_buffer[1] != 'K'){
	buffer.head_pos = 0;
	buffer.tail_pos = 0;
	UART1_SendData("AT+CWMODE=2\r\n");
	LED6 = 0;
	Delayms(500);
	UART1_Send(buffer.circle_buffer[1]);	
	//counter++;
	//if(counter > 5){
	//UART1_SendData("AT+RST\r\n");
	//Delayms(1000);
	//}
	}
	LED1 = 0; //模式设定完成指示灯
	UART1_SendData("AT+RST\r\n");	
	memset(buffer.circle_buffer, 0, sizeof(unsigned char)*16);
}*/

/*void ESPInit_MODE()
{
	Delayms(1000);
		while(cnt < 5)
			switch(cnt)
*/				


/*void ESPInit_MODE()
{
	UART1_SendData("AT+CWMODE=2\r\n");
	Delayms(1000);
	UART1_SendData("AT+RST\r\n");
	Delayms(1000);
	UART1_SendData("AT+CIPMUX=1\r\n"); 
	Delayms(1000);
	UART1_SendData("AT+CIPSERVER=1,2080\r\n");
	Delayms(1000);
}
*/
int SFLAG = 0;
void ESPInit_MODE()
{
	int count = 0;
	while(count <5){
	switch(count){
		case 0 :
			UART2_SendData("AT+CWMODE=2\r\n");
			Delayms(1000);
			count++;
			break;
		case 1 :
			UART2_SendData("AT+RST\r\n");
			Delayms(1000);
			count++;
			break;
		case 2 :
			UART2_SendData("AT+CIPMUX=1\r\n");
			Delayms(1000);
			count++;
			break;
		case 3 :
			buffer.head_pos = 0;
			buffer.tail_pos = 0;
			//memset(buffer.circle_buffer, 0, sizeof(unsigned char)*105);
			count++;
			break;
		case 4 :
			SFLAG = 1;
			UART2_SendData("AT+CIPSERVER=1,2080\r\n");
			Delayms(1000);			
			if(buffer.circle_buffer[buffer.tail_pos - 3] == 'K'){			
				LED7 = 0;
				count++;}
			else{
				count = 0;
				SFLAG = 0;}
			break;
		default :
			count = 0;
	}
}
}			