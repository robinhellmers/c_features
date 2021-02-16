/************************************************************************************
  Description:  C FILE

************************************************************************************/
#include "filter.h"

/************************************************************************************
Private global functions
************************************************************************************/
static void M_InputCircularBuffer(U8 index, FP value);
static void M_UpdateMovingAverage(U8 index);
static void M_OutputBufferFilled(U8 index);
static void M_OutputOldestIndex(U8 index);


/************************************************************************************
Private global variables
********************************************a****************************************/
static FILTER_CIRCULAR_BUFFER_T m_circularBuffer[LEVEL_SCALE_SENSORS];
static FILTER_MOVING_AVERAGE_T m_movingAverage[LEVEL_SCALE_SENSORS];

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
void Filter_InitCircularBuffers(U32 bufferSize)
{
    memset(m_circularBuffer, 0, sizeof m_circularBuffer);
    
    for (U8 i=0; i<LEVEL_SCALE_SENSORS; i++)
    {
        if (bufferSize > MAX_SIZE_CIRCULAR_BUFFER)
            m_circularBuffer[i].bufferSize = MAX_SIZE_CIRCULAR_BUFFER;
        else if (bufferSize == 0)
            m_circularBuffer[i].bufferSize = SIZE_CIRCULAR_BUFFER_MEDIUM;
        else
            m_circularBuffer[i].bufferSize = bufferSize;
    }
}

/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_InitMovingAverages()
{
    memset(m_movingAverage, 0, sizeof m_movingAverage);
}


/************************************************************************************
* Description : Output buffer part set to be used
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_OutputBuffer(U8 index)
{
    printf("BUFFER %" PRIu8 ":   ", index);
    for (U32 i = 0; i < m_circularBuffer[index].bufferSize; i++)
    {
        printf("%" PRIf "   ", m_circularBuffer[index].circularBuffer[i]);
    }
    printf("\n");
}

/************************************************************************************
* Description : Output buffer part set to be used
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_OutputBuffers()
{
    for (U8 index=0; index < LEVEL_SCALE_SENSORS; index++)
    {
        Filter_OutputBuffer(index);
    }
    printf("\n\n");
}

/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_OutputFilteredValues()
{
    printf("\n\nMoving Av.: \n");
    for (U8 index=0; index < LEVEL_SCALE_SENSORS; index++)
    {
        printf("Index %" PRIu8 ": %" PRIf "\n",
                index, 
                Filter_GetFilteredValue(index));
    }
}

/************************************************************************************
* Description : Adds some test values
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_AddSomeValues(U8 index, U32 n)
{
    U64 val = 0;
    for (U32 i=0; i < n; i++)
    {
        val = val + 2;
        printf("%" PRIu32 ". INDEX: %" PRIu8 "\n", i, index);
        printf("INPUT VALUE: %" PRIu64 "\n", val);
        M_InputCircularBuffer(index, (FP) val);
        M_UpdateMovingAverage(index);
        printf("UPDATED MOVING AVERAGE: %" PRIf "\n", m_movingAverage[index].movingAverage);
        M_OutputOldestIndex(index);
        printf("BUFFER SIZE USED: %" PRIu32 "\n", m_circularBuffer[index].bufferSizeUsed);
        M_OutputBufferFilled(index);
        Filter_OutputBuffer(index);
        printf("\n");
    }
}

/************************************************************************************
* Description : Adds some test values
* Arguments   :
* Return Value:
************************************************************************************/
void Filter_Update(U8 index, FP data)
{
    M_InputCircularBuffer(index, data);
    M_UpdateMovingAverage(index);
}

/************************************************************************************
* Description : Resets circular buffer and moving average
* Arguments   : bufferSize - Size to use in buffer
                             0 = same size as before
                            >MAX_SIZE_CIRCULAR_BUFFER = MAX_SIZE_CIRCULAR_BUFFER
* Return Value: NONE
************************************************************************************/
void Filter_Reset(U8 index, U32 bufferSize)
{
    if (bufferSize > MAX_SIZE_CIRCULAR_BUFFER)
        bufferSize = MAX_SIZE_CIRCULAR_BUFFER;
    else if (bufferSize == 0)
        bufferSize = m_circularBuffer[index].bufferSize;

    memset(&m_circularBuffer[index], 0, sizeof (FILTER_CIRCULAR_BUFFER_T));
    memset(&m_movingAverage[index], 0, sizeof (FILTER_MOVING_AVERAGE_T));

    m_circularBuffer[index].bufferSize = bufferSize;

    printf("RESET BUFFER %" PRIu8 " with buffer size %" PRIu32 " **************************************************************\n\n", index, bufferSize);
}

/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
BOOL Filter_IsBufferFilled(U8 index)
{
    if (m_circularBuffer[index].bufferSizeUsed == m_circularBuffer[index].bufferSize)
        return TRUE;
    else
        return FALSE;
}

/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
FP Filter_GetFilteredValue(U8 index)
{
    return m_movingAverage[index].movingAverage;
}













/************************************************************************************
Private functions
************************************************************************************/



/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_OutputBufferFilled(U8 index)
{
    printf("BUFFER FILLED: ");
    if (Filter_IsBufferFilled(index) == TRUE)
        printf("TRUE\n");
    else
        printf("FALSE\n");
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_InputCircularBuffer(U8 index, FP value)
{
    m_circularBuffer[index].oldValue = m_circularBuffer[index].circularBuffer[m_circularBuffer[index].oldestIndex];
    m_circularBuffer[index].circularBuffer[m_circularBuffer[index].writeIndex] = value;
    m_circularBuffer[index].newestIndex = m_circularBuffer[index].writeIndex;

    if (m_circularBuffer[index].writeIndex + 1 == m_circularBuffer[index].bufferSize) // End of buffer
        m_circularBuffer[index].writeIndex = 0;
    else
        m_circularBuffer[index].writeIndex++;


    if (m_circularBuffer[index].bufferSizeUsed == m_circularBuffer[index].bufferSize)
    {
        if (m_circularBuffer[index].oldestIndex + 1 == m_circularBuffer[index].bufferSize) // End of buffer
            m_circularBuffer[index].oldestIndex = 0;
        else
            m_circularBuffer[index].oldestIndex++;
    }
    else
        m_circularBuffer[index].bufferSizeUsed++;
}


/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_OutputOldestIndex(U8 index)
{
    printf("OLDEST INDEX = %" PRIu32 " WITH VALUE: %" PRIf "\n",
           m_circularBuffer[index].oldestIndex,
           m_circularBuffer[index].circularBuffer[m_circularBuffer[index].oldestIndex]);
}





/************************************************************************************
* Description :
* Arguments   :
* Return Value:
************************************************************************************/
static void M_UpdateMovingAverage(U8 index)
{
    if (m_movingAverage[index].elementsInSum < m_circularBuffer[index].bufferSize)
    {
        m_movingAverage[index].sum += m_circularBuffer[index].circularBuffer[m_circularBuffer[index].newestIndex];
        m_movingAverage[index].elementsInSum++;
    }
    else
    {
        m_movingAverage[index].sum = m_movingAverage[index].sum - m_circularBuffer[index].oldValue
                    + m_circularBuffer[index].circularBuffer[m_circularBuffer[index].newestIndex];
    }

    m_movingAverage[index].movingAverage = m_movingAverage[index].sum/m_movingAverage[index].elementsInSum;
}

