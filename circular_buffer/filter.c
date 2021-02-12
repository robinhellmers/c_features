/************************************************************************************
  Description:  C FILE

************************************************************************************/
#include "moving_average_with_circular_buffer_V2.0.h"

/************************************************************************************
Private global functions
************************************************************************************/
static BOOL M_IsBufferFilled();
static void M_OutputBufferFilled();
static void M_InputCircularBuffer(FP value);
static FP M_getOldestValue();
static void M_OutputOldestIndex();
static void M_OutputWholeBuffer();
static void M_ResetMovingAverage();
static void M_UpdateMovingAverage();
static void M_AddValues(U32 n);
static void M_InitCircularBuffer();
static void M_InitMovingAverage();


/************************************************************************************
Private global variables
************************************************************************************/
static LEVEL_CIRCULAR_BUFFER_T m_circularBuffer;
static LEVEL_MOVING_AVERAGE_T m_movingAverage;

/************************************************************************************
Exported variables
************************************************************************************/

/************************************************************************************
Exported functions
************************************************************************************/



/************************************************************************************
* Description : Stub function
* Arguments   : -
* Return Value: -
************************************************************************************/



int main(void)
{
    M_InitCircularBuffer(&m_circularBuffer);
    M_InitMovingAverage(&m_movingAverage);


    M_OutputWholeBuffer(); printf("\n\n");

    M_AddValues(13);

    M_ResetMovingAverage();
    
    M_AddValues(3);

    M_ResetMovingAverage();
    M_OutputWholeBuffer();
    

    
    return 0;
}




/************************************************************************************
Private functions
************************************************************************************/


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static BOOL M_IsBufferFilled()
{
    if (m_circularBuffer.bufferSizeUsed == SIZE_CIRCULAR_BUFFER)
        return TRUE;
    else
        return FALSE;
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_OutputBufferFilled()
{
    printf("Buffer filled: ");
    if (M_IsBufferFilled() == TRUE)
        printf("TRUE\n");
    else
        printf("FALSE\n");
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_InputCircularBuffer(FP value)
{
    m_circularBuffer.oldValue = m_circularBuffer.circularBuffer[m_circularBuffer.oldestIndex];
    m_circularBuffer.circularBuffer[m_circularBuffer.writeIndex] = value;
    m_circularBuffer.newestIndex = m_circularBuffer.writeIndex;

    if (m_circularBuffer.writeIndex + 1 == SIZE_CIRCULAR_BUFFER) // End of buffer
        m_circularBuffer.writeIndex = 0;
    else
        m_circularBuffer.writeIndex++;


    if (m_circularBuffer.bufferSizeUsed == SIZE_CIRCULAR_BUFFER)
    {
        if (m_circularBuffer.oldestIndex + 1 == SIZE_CIRCULAR_BUFFER) // End of buffer
            m_circularBuffer.oldestIndex = 0;
        else
            m_circularBuffer.oldestIndex++;
    }
    else
        m_circularBuffer.bufferSizeUsed++;
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static FP M_getOldestValue()
{
    return m_circularBuffer.circularBuffer[m_circularBuffer.oldestIndex];
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_OutputOldestIndex()
{
    printf("Oldest index = %" PRIu32 " with value = %" PRIf "\n",
           m_circularBuffer.oldestIndex,
           m_circularBuffer.circularBuffer[m_circularBuffer.oldestIndex]);
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_OutputWholeBuffer()
{
    printf("BUFFER:   ");
    for (U32 i = 0; i < SIZE_CIRCULAR_BUFFER; i++)
    {
        printf("%" PRIf "   ", m_circularBuffer.circularBuffer[i]);
    }
    printf("\n");
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_ResetMovingAverage()
{
    memset(&m_circularBuffer, 0, sizeof m_circularBuffer);
    memset(&m_movingAverage, 0, sizeof m_movingAverage);

    printf("RESET BUFFER *****************************************\n\n");
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_UpdateMovingAverage()
{
    if (m_movingAverage.elementsInSum < SIZE_CIRCULAR_BUFFER)
    {
        m_movingAverage.sum += m_circularBuffer.circularBuffer[m_circularBuffer.newestIndex];
        m_movingAverage.elementsInSum++;
    }
    else
    {
        m_movingAverage.sum = m_movingAverage.sum - m_circularBuffer.oldValue
                      + m_circularBuffer.circularBuffer[m_circularBuffer.newestIndex];
    }

    m_movingAverage.movingAverage = m_movingAverage.sum/m_movingAverage.elementsInSum;
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_AddValues(U32 n)
{
    U64 val = 0;
    for (U32 i=0; i < n; i++)
    {
        val = val + 2;
        printf("%" PRIu32 ". INPUT\n", i);
        M_InputCircularBuffer((FP) val);
        M_UpdateMovingAverage();
        printf("%" PRIu32 ". UPDATED MOVING AVERAGE: %" PRIf "\n", i, m_movingAverage.movingAverage);
        printf("%" PRIu32 ". OUTPUT\n", i);
        M_OutputOldestIndex();
        printf("%" PRIu32 ". END\n", i);
        printf("Buffer size used: %" PRIu32 "\n", m_circularBuffer.bufferSizeUsed);
        M_OutputBufferFilled();
        M_OutputWholeBuffer();
        printf("\n");
    }
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_InitCircularBuffer()
{
    memset(&m_circularBuffer, 0, sizeof (LEVEL_CIRCULAR_BUFFER_T));
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_InitMovingAverage()
{
    memset(&m_movingAverage, 0, sizeof (LEVEL_MOVING_AVERAGE_T));
}