#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>


#define SIZE_CIRCULAR_BUFFER 5


typedef uint8_t     U8;
typedef uint32_t    U32;
typedef float       FP;

U8 m_circularBuffer[SIZE_CIRCULAR_BUFFER];

U32 m_bufferSizeUsed = 0;
U32 m_writeIndex = 0;
U32 m_oldestIndex = 0;


void M_InputCircularBuffer(U8 value)
{

    if (m_bufferSizeUsed == SIZE_CIRCULAR_BUFFER)
    {
        if (m_oldestIndex + 1 == SIZE_CIRCULAR_BUFFER) // End of buffer
            m_oldestIndex = 0;
        else
            m_oldestIndex++;
    }
    else
        m_bufferSizeUsed++;


    m_circularBuffer[m_writeIndex] = value;


    if (m_writeIndex + 1 == SIZE_CIRCULAR_BUFFER) // End of buffer
        m_writeIndex = 0;
    else
        m_writeIndex++;

}

void M_OutputOldestIndex()
{
    printf("Oldest index = %" PRIu32 " with value = %" PRIu8 "\n", m_oldestIndex, m_circularBuffer[m_oldestIndex]);
}

void M_OutputWholeBuffer()
{
    printf("BUFFER:   ");
    for (U8 i = 0; i < SIZE_CIRCULAR_BUFFER; i++)
    {
        printf("%" PRIu8 "   ", m_circularBuffer[i]);
    }
    printf("\n");
}

void M_ResetCircularBuffer()
{
    memset(m_circularBuffer, 0, sizeof m_circularBuffer);
    m_writeIndex = 0;
    m_oldestIndex = 0;
    m_bufferSizeUsed = 0;
}

int main(void)
{
    memset(m_circularBuffer, 0, sizeof m_circularBuffer);

    M_OutputWholeBuffer();
    printf("\n\n");

    U8 val = 0;
    for (U8 i=0; i < 10; i++)
    {
        val = val + 5;
        printf("%" PRIu8 ". INPUT\n", i);
        M_InputCircularBuffer(val);
        printf("%" PRIu8 ". OUTPUT\n", i);
        M_OutputOldestIndex();
        printf("%" PRIu8 ". END\n", i);
        printf("Buffer size used: %" PRIu32 "\n", m_bufferSizeUsed);
        M_OutputWholeBuffer();
        printf("\n");
    }

    printf("RESET BUFFER *****************************************\n");
    M_ResetCircularBuffer();
    
    val = 0;
    for (U8 i=0; i < 10; i++)
    {
        val = val + 5;
        printf("%" PRIu8 ". INPUT\n", i);
        M_InputCircularBuffer(val);
        printf("%" PRIu8 ". OUTPUT\n", i);
        M_OutputOldestIndex();
        printf("%" PRIu8 ". END\n", i);
        printf("Buffer size used: %" PRIu32 "\n", m_bufferSizeUsed);
        M_OutputWholeBuffer();
        printf("\n");
    }
    
    return 0;
}