#include <stdio.h>
#include "filter.h"




int main(void)
{
    Filter_InitCircularBuffer();
    Filter_InitMovingAverage();


    Filter_OutputWholeBuffer(); printf("\n\n");

    Filter_AddValues(13);

    Filter_ResetMovingAverage(); 
    
    Filter_AddValues(3);

    Filter_ResetMovingAverage();
    Filter_OutputWholeBuffer();
    

    
    return 0;
}