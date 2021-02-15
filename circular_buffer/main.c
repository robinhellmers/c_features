#include <stdio.h>
#include "filter.h"




int main(void)
{
    Filter_InitCircularBuffer(1);
    Filter_InitMovingAverage();


    Filter_OutputBuffer(); printf("\n\n");

    Filter_AddSomeValues(13);

    Filter_Reset(2); 
    
    Filter_AddSomeValues(3);

    Filter_Reset(10);
    Filter_AddSomeValues(11);

    Filter_Reset(0);
    Filter_OutputBuffer();
    

    
    return 0;
}