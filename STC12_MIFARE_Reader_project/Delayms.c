#include "Delayms.h"

void Delayms(unsigned int n)
{
    unsigned int i,j;
    for(j=n;j>0;j--)
    for(i=950;i>0;i--);
}