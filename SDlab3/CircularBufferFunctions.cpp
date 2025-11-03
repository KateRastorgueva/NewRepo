#include "CircularBufferFunctions.h"

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

    circularBuffer->_buffer = new int[capacity];
    if (circularBuffer->_buffer == nullptr)
    {
        delete circularBuffer;
        return nullptr;
    }

    circularBuffer->_capacity = capacity;
    circularBuffer->_head = 0;
    circularBuffer->_tail = 0;
    circularBuffer->_count = 0;

    return circularBuffer;
}

int GetFreeSpaceCircular(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr)
    {
        return 0;
    }
    return circularBuffer->_capacity - circularBuffer->_count;
}

int GetUsedSpace(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr)
    {
        return 0;
    }
    return circularBuffer->_count;
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
    if (circularBuffer == nullptr || circularBuffer->_count == circularBuffer->_capacity)
    {
        return false;
    }

    circularBuffer->_buffer[circularBuffer->_tail] = value;
    circularBuffer->_tail = (circularBuffer->_tail + 1) % circularBuffer->_capacity;
    circularBuffer->_count++;

    return true;
}

int DequeueCircularBuffer(CircularBuffer* circularBuffer)
{
    if (circularBuffer == nullptr || circularBuffer->_count == 0)
    {
        return -1;
    }
    int value = circularBuffer->_buffer[circularBuffer->_head];
    circularBuffer->_head = (circularBuffer->_head + 1) % circularBuffer->_capacity;
    circularBuffer->_count--;

    return value;
}

void DeleteCircularBuffer(CircularBuffer*& circularBuffer)
{
    if (circularBuffer == nullptr)
    {
        return;
    }

    if (circularBuffer->_buffer != nullptr)
    {
        delete[] circularBuffer->_buffer;
        circularBuffer->_buffer = nullptr;
    }

    delete circularBuffer;
    circularBuffer = nullptr;
}
bool ResizeCircularBuffer(CircularBuffer* circularBuffer, int newCapacity)
{
    if (circularBuffer == nullptr || newCapacity <= 0 || newCapacity < circularBuffer->_count)
    {
        return false;
    }

    int* newBuffer = new int[newCapacity];
    if (newBuffer == nullptr)
    {
        return false;
    }

    // Êîïèğóåì ıëåìåíòû â ïğàâèëüíîì ïîğÿäêå
    for (int i = 0; i < circularBuffer->_count; i++)
    {
        int index = (circularBuffer->_head + i) % circularBuffer->_capacity;
        newBuffer[i] = circularBuffer->_buffer[index];
    }

    delete[] circularBuffer->_buffer;
    circularBuffer->_buffer = newBuffer;
    circularBuffer->_capacity = newCapacity;
    circularBuffer->_head = 0;
    circularBuffer->_tail = circularBuffer->_count % newCapacity;

    return true;
}