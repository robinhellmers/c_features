


#include <stdio.h>
#include <string.h>


#define SIZE_OF_BUFFER 8

int bufferLength = 0;
int readIndex = 0;
int writeIndex = 0;

int circularBuffer[SIZE_OF_BUFFER];

void writeNumber(int number, int* buffer)
{
    *buffer = number;
}

void inputCircularBuffer(int number)
{
    if (bufferLength == SIZE_OF_BUFFER)
    {
        printf("Buffer is full!\n");
    }

    writeNumber(5, &circularBuffer[writeIndex]);
    bufferLength++;
    writeIndex++;

    if (writeIndex == SIZE_OF_BUFFER)
    {
        writeIndex = 0;
    }
}

void outputCircularBuffer()
{
    if (bufferLength == 0)
    {
        printf("Buffer is empty!\n");
        return;
    }

    // Popping first element in the buffer
    printf("The output value is %d\n", circularBuffer[readIndex]);
    bufferLength--;
    readIndex++;
}

int main()
{
    
    memset(circularBuffer, 0, sizeof circularBuffer);

    inputCircularBuffer(5);
    outputCircularBuffer();


    return 0;
}