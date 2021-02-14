#include <stdio.h>
#include "filter_minimal.h"




int main(void)
{
    Filter_InitCircularBuffer();
    Filter_InitMovingAverage();

    Filter_AddSomeValues(13);
 
    Filter_Reset(); 
    
    Filter_AddSomeValues(3);

    Filter_Reset();
    
    return 0;
}