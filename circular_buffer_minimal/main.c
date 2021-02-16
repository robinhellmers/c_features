#include <stdio.h>
#include "filter_minimal.h"




int main(void)
{
    Filter_InitCircularBuffers(5);
    Filter_InitMovingAverages(); 
    Filter_OutputBuffers();

    Filter_AddSomeValues(0, 13);
    Filter_OutputBuffers();
 
    Filter_Reset(0, 0); 
    Filter_OutputBuffers();
    
    Filter_AddSomeValues(0, 3);
    Filter_OutputBuffers();

    Filter_AddSomeValues(2, 7);
    Filter_OutputBuffers();
    Filter_OutputFilteredValues();
    
    return 0;
}