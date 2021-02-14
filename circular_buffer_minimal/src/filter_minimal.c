/************************************************************************************
  Description:  C FILE

************************************************************************************/
#include "filter_minimal.h"

/************************************************************************************
Private global functions
************************************************************************************/
static BOOL M_IsBufferFilled();
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
void Filter_AddSomeValues(U32 n)
{
    U64 val = 0;
    for (U32 i=0; i < n; i++)
    {
        val = val + 2;
        M_InputCircularBuffer((FP) val);
        M_UpdateMovingAverage();
    }
}

/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_Reset()
{
    memset(&m_circularBuffer, 0, sizeof m_circularBuffer);
    memset(&m_movingAverage, 0, sizeof m_movingAverage);
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
