#ifndef FILTER_MINIMAL_H
#define FILTER_MINIMAL_H

/*******************************************************************************
  Description:
*******************************************************************************/
 
/******************************************************************************
Includes
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

/******************************************************************************
Defines and enums
******************************************************************************/
#define LEVEL_SCALE_SENSORS         5

#define SIZE_CIRCULAR_BUFFER_MEDIUM 20
#define SIZE_CIRCULAR_BUFFER_FAST   5
#define SIZE_CIRCULAR_BUFFER_SLOW   100
#define MAX_SIZE_CIRCULAR_BUFFER    100

#define PRIf    ".3f"
#define PRIbool PRIu8
#define TRUE    1
#define FALSE   0

typedef uint8_t     U8;
typedef uint32_t    U32;
typedef uint64_t    U64;
typedef float       FP;
typedef uint8_t     BOOL;

/******************************************************************************
Struct and unions
******************************************************************************/
typedef struct
{
    FP circularBuffer[MAX_SIZE_CIRCULAR_BUFFER];

    U32 bufferSizeUsed;
    U32 bufferSize;

    U32 writeIndex;
    U32 oldestIndex;
    U32 newestIndex;
    
    FP oldValue;
}FILTER_CIRCULAR_BUFFER_T;;

typedef struct
{
    FP sum;
    FP movingAverage;
    U32 elementsInSum;
}FILTER_MOVING_AVERAGE_T;

/******************************************************************************
Exported variables
******************************************************************************/

/******************************************************************************
Exported functions
******************************************************************************/
void Filter_InitCircularBuffers(U32 bufferSize);
void Filter_InitMovingAverages();
void Filter_Update(U8 index, FP data);
void Filter_Reset(U8 index, U32 bufferSize);
void Filter_OutputBuffer(U8 index);
void Filter_OutputBuffers();
void Filter_OutputFilteredValues();
void Filter_AddSomeValues(U8 index, U32 n);
BOOL Filter_IsBufferFilled(U8 index);
FP Filter_GetFilteredValue(U8 index);


#endif
