/************************************************************************************
  Description:  C FILE

************************************************************************************/
#include "filter.h"

/************************************************************************************
Private global functions
************************************************************************************/
static BOOL M_IsBufferFilled();
static void M_OutputBufferFilled();
static void M_InputCircularBuffer(FP value);
static FP M_getOldestValue();
static void M_OutputOldestIndex();
static void M_UpdateMovingAverage();


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
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_InitCircularBuffer()
{
    memset(&m_circularBuffer, 0, sizeof (LEVEL_CIRCULAR_BUFFER_T));
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_InitMovingAverage()
{
    memset(&m_movingAverage, 0, sizeof (LEVEL_MOVING_AVERAGE_T));
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_OutputWholeBuffer()
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
void Filter_AddValues(U32 n)
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
        Filter_OutputWholeBuffer();
        printf("\n");
    }
}

/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_ResetMovingAverage()
{
    memset(&m_circularBuffer, 0, sizeof m_circularBuffer);
    memset(&m_movingAverage, 0, sizeof m_movingAverage);

    printf("RESET BUFFER *****************************************\n\n");
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
