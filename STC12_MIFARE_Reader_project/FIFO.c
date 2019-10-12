#include "FIFO.h"
circle_buffer buffer;
void bufferPop(unsigned char* _buf)
{
if(buffer.head_pos==buffer.tail_pos) //如果头尾接触表示缓冲区为空
*_buf=0xFF;
else
{
*_buf=buffer.circle_buffer[buffer.head_pos]; //如果缓冲区非空则取头节点值并偏移头节点
if(++buffer.head_pos>=BUFFER_MAX)
buffer.head_pos=0;
}
}

void bufferPush(const unsigned char _buf)
{ 
buffer.circle_buffer[buffer.tail_pos]=_buf; //从尾部追加
if(++buffer.tail_pos>=BUFFER_MAX) //尾节点偏移
buffer.tail_pos=0; //大于数组最大长度 制零 形成环形队列
if(buffer.tail_pos==buffer.head_pos) //如果尾部节点追到头部节点 则修改头节点偏移位置丢弃早期数据
if(++buffer.head_pos>=BUFFER_MAX)
buffer.head_pos=0;

}