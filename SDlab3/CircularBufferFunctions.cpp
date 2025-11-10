#include "CircularBuffer.h"

CircularBuffer* CreateCircularBuffer(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

    CircularBuffer* circularBuffer = new CircularBuffer;
    if (circularBuffer == nullptr)
    {
        return nullptr;
    }

    circularBuffer->Buffer = new int[capacity];
    if (circularBuffer->Buffer == nullptr)
    {
        delete circularBuffer;
        return nullptr;
    }

    circularBuffer->Capacity = capacity;
    circularBuffer->Head = 0;
    circularBuffer->Tail = 0;
    circularBuffer->Count = 0;

    return circularBuffer;
}

int GetFreeSpaceCircular(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr)
    {
        return 0;
    }
    return circularBuffer->Capacity - circularBuffer->Count;
}

int GetUsedSpace(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr)
    {
        return 0;
    }
    return circularBuffer->Count;
}
bool IsCircularBufferEmpty(CircularBuffer* ñircularBuffer)
{
    if (ñircularBuffer == nullptr)
    {
        return true;
    }
    return GetUsedSpace(ñircularBuffer) == 0;
}

bool EnqueueCircularBuffer(CircularBuffer* circularBuffer, int value)
{
    if (circularBuffer == nullptr || circularBuffer->Count == circularBuffer->Capacity)
    {
        return false;
    }

    circularBuffer->Buffer[circularBuffer->Tail] = value;
    circularBuffer->Tail = (circularBuffer->Tail + 1) % circularBuffer->Capacity;
    circularBuffer->Count++;

    return true;
}

int DequeueCircularBuffer(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr || circularBuffer->Count == 0)
    {
        return -1;
    }
    int value = circularBuffer->Buffer[circularBuffer->Head];
    circularBuffer->Head = (circularBuffer->Head + 1) % circularBuffer->Capacity;
    circularBuffer->Count--;

    return value;
}

void DeleteCircularBuffer(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr)
    {
        return;
    }

    if (circularBuffer->Buffer != nullptr)
    {
        delete[] circularBuffer->Buffer;
        circularBuffer->Buffer = nullptr;
    }

    delete circularBuffer;
}
bool ResizeCircularBuffer(CircularBuffer* circularBuffer, int newCapacity)
{
    if (circularBuffer == nullptr || newCapacity <= 0 || newCapacity < circularBuffer->Count)
    {
        return false;
    }

    int* newBuffer = new int[newCapacity];
    if (newBuffer == nullptr)
    {
        return false;
    }

    for (int i = 0; i < circularBuffer->Count; i++)
    {
        int index = (circularBuffer->Head + i) % circularBuffer->Capacity;
        newBuffer[i] = circularBuffer->Buffer[index];
    }

    delete[] circularBuffer->Buffer;
    circularBuffer->Buffer = newBuffer;
    circularBuffer->Capacity = newCapacity;
    circularBuffer->Head = 0;
    circularBuffer->Tail = circularBuffer->Count;
    if (circularBuffer->Tail == circularBuffer->Capacity)
    {
        circularBuffer->Tail = 0;
    }

    return true;
}