#include <stdio.h>
#include "filter_minimal.h"




int main(void)
{
    Filter_InitCircularBuffer(5);
    Filter_InitMovingAverage(); 
    Filter_OutputBuffer();

    Filter_AddSomeValues(13);
    Filter_OutputBuffer();
 
    Filter_Reset(0); 
    Filter_OutputBuffer();
    
    Filter_AddSomeValues(3);
    Filter_OutputBuffer();

    Filter_Reset(3);
    Filter_OutputBuffer();
    
    return 0;
}