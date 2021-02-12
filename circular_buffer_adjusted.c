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
        printf("Buffer is filled! Overwriting oldest index: %" PRIu32 "\n", m_oldestIndex);
        m_oldestIndex++;
        if (m_oldestIndex == SIZE_CIRCULAR_BUFFER)
        {
            m_oldestIndex = 0;
        }
        printf("Oldest index is now set to: %" PRIu32 "\n", m_oldestIndex);
        m_bufferSizeUsed--; // As will be added later
    }

    m_circularBuffer[m_writeIndex] = value;
    m_writeIndex++;
    if (m_writeIndex == SIZE_CIRCULAR_BUFFER)
    {
        m_writeIndex = 0;
    }

    m_bufferSizeUsed++;

    printf("CHECKING LENGTH: m_writeIndex - m_oldestIndex = %" PRIu32 "\n", 
           abs(m_writeIndex-m_oldestIndex));

    
    
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
        M_OutputWholeBuffer();
        printf("\n");
    }

    printf("RESET BUFFER\n");
    M_ResetCircularBuffer();
    
    U8 val = 0;
    for (U8 i=0; i < 10; i++)
    {
        val = val + 5;
        printf("%" PRIu8 ". INPUT\n", i);
        M_InputCircularBuffer(val);
        printf("%" PRIu8 ". OUTPUT\n", i);
        M_OutputOldestIndex();
        printf("%" PRIu8 ". END\n", i);
        M_OutputWholeBuffer();
        printf("\n");
    }
    
    return 0;
}