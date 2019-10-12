#ifndef __FIFO_H_  //检测是否被定义
#define __FIFO_H_  //未定义则为初次调用该头文件，则定义该宏
#define BUFFER_MAX 90//缓冲区大小

void bufferPop(unsigned char* _buf);
void bufferPush(const unsigned char _buf);

typedef struct _circle_buffer{
unsigned char head_pos; 
unsigned char tail_pos; 
unsigned char circle_buffer[BUFFER_MAX]; 
}circle_buffer;

extern circle_buffer buffer;

#endif //结束如果