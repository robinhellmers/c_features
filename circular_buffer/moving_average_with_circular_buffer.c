#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>


#define SIZE_CIRCULAR_BUFFER 5

#define PRIf    ".3f"
#define TRUE    1
#define FALSE   0

typedef uint8_t     U8;
typedef uint32_t    U32;
typedef uint64_t    U64;
typedef float       FP;
typedef uint8_t     BOOL;
             

FP m_circularBuffer[SIZE_CIRCULAR_BUFFER];

U32 m_bufferSizeUsed = 0;
U32 m_writeIndex = 0;
U32 m_oldestIndex = 0;
U32 m_newestIndex = 0;
U32 m_elementsInSum = 0;
FP  m_oldValue = 0;


FP m_sum = 0;
FP m_movingAverage = 0;



void M_InputCircularBuffer(FP value)
{
    m_oldValue = m_circularBuffer[m_oldestIndex];
    m_circularBuffer[m_writeIndex] = value;
    m_newestIndex = m_writeIndex;

    if (m_writeIndex + 1 == SIZE_CIRCULAR_BUFFER) // End of buffer
        m_writeIndex = 0;
    else
        m_writeIndex++;


    if (m_bufferSizeUsed == SIZE_CIRCULAR_BUFFER)
    {
        if (m_oldestIndex + 1 == SIZE_CIRCULAR_BUFFER) // End of buffer
            m_oldestIndex = 0;
        else
            m_oldestIndex++;
    }
    else
        m_bufferSizeUsed++;
}

FP M_getOldestValue()
{
    return m_circularBuffer[m_oldestIndex];
}

void M_OutputOldestIndex()
{
    printf("Oldest index = %" PRIu32 " with value = %" PRIf "\n", m_oldestIndex, m_circularBuffer[m_oldestIndex]);
}

void M_OutputWholeBuffer()
{
    printf("BUFFER:   ");
    for (U32 i = 0; i < SIZE_CIRCULAR_BUFFER; i++)
    {
        printf("%" PRIf "   ", m_circularBuffer[i]);
    }
    printf("\n");
}

void M_ResetMovingAverage()
{
    memset(m_circularBuffer, 0, sizeof m_circularBuffer);
    
    m_bufferSizeUsed = 0;
    m_writeIndex = 0;
    m_oldestIndex = 0;
    m_newestIndex = 0;
    m_elementsInSum = 0;
    m_oldValue = 0;
    m_sum = 0;
    m_movingAverage = 0;

    printf("RESET BUFFER *****************************************\n\n");
}

void M_UpdateMovingAverage()
{
    if (m_elementsInSum < SIZE_CIRCULAR_BUFFER)
    {
        m_sum += m_circularBuffer[m_newestIndex];
        m_elementsInSum++;
    }
    else
    {
        m_sum = m_sum - m_oldValue
                      + m_circularBuffer[m_newestIndex];
    }

    m_movingAverage = m_sum/m_elementsInSum;
}

void M_AddValues(U32 n)
{
    U64 val = 0;
    for (U32 i=0; i < n; i++)
    {
        val = val + 5;
        printf("%" PRIu32 ". INPUT\n", i);
        M_InputCircularBuffer((FP) val);
        M_UpdateMovingAverage();
        printf("%" PRIu32 ". UPDATED MOVING AVERAGE: %" PRIf "\n", i, m_movingAverage);
        printf("%" PRIu32 ". OUTPUT\n", i);
        M_OutputOldestIndex();
        printf("%" PRIu32 ". END\n", i);
        printf("Buffer size used: %" PRIu32 "\n", m_bufferSizeUsed);
        M_OutputWholeBuffer();
        printf("\n");
    }
}

int main(void)
{
    memset(m_circularBuffer, 0, sizeof m_circularBuffer);

    M_OutputWholeBuffer(); printf("\n\n");

    M_AddValues(13);

    M_ResetMovingAverage();
    
    M_AddValues(3);

    M_ResetMovingAverage();
    M_OutputWholeBuffer();
    

    
    return 0;
}