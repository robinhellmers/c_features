#include <stdio.h>
#include "filter.h"




int main(void)
{
    Filter_InitCircularBuffer(5);
    Filter_InitMovingAverage();


    Filter_OutputBuffer(); printf("\n\n");

    Filter_AddValues(13);

    Filter_Reset(2); 
    
    Filter_AddValues(3);

    Filter_Reset(10);
    Filter_AddValues(11);

    Filter_Reset(0);
    Filter_OutputBuffer();
    

    
    return 0;
}