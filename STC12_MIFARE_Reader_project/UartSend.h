#ifndef __UartSend_H_  //检测是否被定义
#define __UartSend_H_  //未定义则为初次调用该头文件，则定义该宏
#include <STC12C5A60S2.H>

void UART1_Send(unsigned char A);
void UART1_SendData(unsigned char* As);
void UART2_Send(unsigned char A);
void UART2_SendData(unsigned char* As);

#endif //结束如果