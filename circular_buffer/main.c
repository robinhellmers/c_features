#include <stdio.h>
#include "filter.h"




int main(void)
{
    Filter_InitCircularBuffers(5); 
    Filter_InitMovingAverage();


    Filter_OutputBuffers(); printf("\n\n");

    Filter_AddSomeValues(13, 0);
    Filter_OutputBuffers(); printf("\n\n");

    Filter_Reset(2, 0);
    Filter_OutputBuffers(); printf("\n\n");
    
    Filter_AddSomeValues(3, 0);
    Filter_OutputBuffers(); printf("\n\n");

    Filter_Reset(10, 0);
    Filter_OutputBuffers(); printf("\n\n");
    Filter_AddSomeValues(11, 0);
    Filter_OutputBuffers(); printf("\n\n");

    Filter_Reset(3, 2);
    Filter_OutputBuffers();
    Filter_AddSomeValues(2, 2);
    Filter_OutputBuffers();

    Filter_Reset(7, 4);
    Filter_OutputBuffers();
    Filter_AddSomeValues(9, 4);
    Filter_OutputBuffers();

    Filter_AddSomeValues(3, 2);
    Filter_OutputBuffers();
    

    
    return 0;
}