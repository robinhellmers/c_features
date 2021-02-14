#ifndef FILTER_H
#define FILTER_H

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
#define SIZE_CIRCULAR_BUFFER 5

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
    FP circularBuffer[SIZE_CIRCULAR_BUFFER];

    U32 bufferSizeUsed;

    U32 writeIndex;
    U32 oldestIndex;
    U32 newestIndex;
    
    FP oldValue;
}LEVEL_CIRCULAR_BUFFER_T;

typedef struct
{
    FP sum;
    FP movingAverage;
    U32 elementsInSum;
}LEVEL_MOVING_AVERAGE_T;

/******************************************************************************
Exported variables
******************************************************************************/

/******************************************************************************
Exported functions
******************************************************************************/
void Filter_InitCircularBuffer();
void Filter_InitMovingAverage();
void Filter_OutputWholeBuffer();
void Filter_AddValues(U32 n);
void Filter_ResetMovingAverage();


#endif
