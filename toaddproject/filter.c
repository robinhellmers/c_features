/************************************************************************************
  Description:  C FILE

************************************************************************************/
#include "filter.h"

/************************************************************************************
Private global functions
************************************************************************************/
static void M_InputCircularBuffer(FP value); 
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
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_AddSomeValues(U32 n)
{
    FP val = 0;
    for (U32 i=0; i < n; i++)
    {
        val = val + 2;
        Filter_Update(val);
    }
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_Update(FP data)
{
    M_InputCircularBuffer(data);
    M_UpdateMovingAverage();
}



/************************************************************************************
* Description :
* Arguments   :
* Return Value:
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
