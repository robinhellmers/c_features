/************************************************************************************
  Description:  C FILE

************************************************************************************/
#include "filter.h"

/************************************************************************************
Private global functions
************************************************************************************/
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
void Filter_InitCircularBuffer(U32 bufferSize)
{
    memset(&m_circularBuffer, 0, sizeof (LEVEL_CIRCULAR_BUFFER_T));
    
    if (bufferSize > MAX_SIZE_CIRCULAR_BUFFER)
        m_circularBuffer.bufferSize = MAX_SIZE_CIRCULAR_BUFFER;
    else if (bufferSize == 0)
        m_circularBuffer.bufferSize = SIZE_CIRCULAR_BUFFER_MEDIUM;
    else
        m_circularBuffer.bufferSize = bufferSize;
    
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
* Description : Output buffer part set to be used
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_OutputBuffer()
{
    printf("BUFFER:   ");
    for (U32 i = 0; i < m_circularBuffer.bufferSize; i++)
    {
        printf("%" PRIf "   ", m_circularBuffer.circularBuffer[i]);
    }
    printf("\n");
}

/************************************************************************************
* Description : Adds some test values
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_AddSomeValues(U32 n)
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
        Filter_OutputBuffer();
        printf("\n");
    }
}

/************************************************************************************
* Description : Adds some test values
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_Update(FP data)
{
    M_InputCircularBuffer(data);
    M_UpdateMovingAverage();
}

/************************************************************************************
* Description : Resets circular buffer and moving average
* Arguments   : bufferSize - Size to use in buffer
                             0 = same size as before
                            >MAX_SIZE_CIRCULAR_BUFFER = MAX_SIZE_CIRCULAR_BUFFER
* Return Value: NONE
************************************************************************************/
void Filter_Reset(U32 bufferSize)
{
    if (bufferSize > MAX_SIZE_CIRCULAR_BUFFER)
        bufferSize = MAX_SIZE_CIRCULAR_BUFFER;
    else if (bufferSize == 0)
        bufferSize = m_circularBuffer.bufferSize;

    memset(&m_circularBuffer, 0, sizeof m_circularBuffer);
    memset(&m_movingAverage, 0, sizeof m_movingAverage);

    m_circularBuffer.bufferSize = bufferSize;

    printf("RESET BUFFER *****************************************\n\n");
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
BOOL M_IsBufferFilled()
{
    if (m_circularBuffer.bufferSizeUsed == m_circularBuffer.bufferSize)
        return TRUE;
    else
        return FALSE;
}








/************************************************************************************
Private functions
************************************************************************************/





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

    if (m_circularBuffer.writeIndex + 1 == m_circularBuffer.bufferSize) // End of buffer
        m_circularBuffer.writeIndex = 0;
    else
        m_circularBuffer.writeIndex++;


    if (m_circularBuffer.bufferSizeUsed == m_circularBuffer.bufferSize)
    {
        if (m_circularBuffer.oldestIndex + 1 == m_circularBuffer.bufferSize) // End of buffer
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
    if (m_movingAverage.elementsInSum < m_circularBuffer.bufferSize)
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
