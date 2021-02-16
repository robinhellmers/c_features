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
    
    Filter_AddSomeValues(0, 3);
    Filter_OutputBuffers(); printf("\n\n");

    Filter_Reset(0, 10);
    Filter_OutputBuffers(); printf("\n\n");
    Filter_AddSomeValues(0, 11);
    Filter_OutputBuffers(); printf("\n\n");

    Filter_Reset(2, 3);
    Filter_OutputBuffers();
    Filter_AddSomeValues(2, 2);
    Filter_OutputBuffers();

    Filter_Reset(4, 7);
    Filter_OutputBuffers();
    Filter_AddSomeValues(4, 9);
    Filter_OutputBuffers();

    Filter_AddSomeValues(2, 3);
    Filter_OutputBuffers();
    

    
    return 0;
}