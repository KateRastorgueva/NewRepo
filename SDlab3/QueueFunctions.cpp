#include "QueueFunctions.h"
#include "CircularBufferFunctions.h"

Queue* CreateQueue(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

    Queue* queue = new Queue;
    if (queue == nullptr)
    {
        return nullptr;
    }

    queue->_circularBuffer = CreateCircularBuffer(capacity);
    if (queue->_circularBuffer == nullptr)
    {
        delete queue;
        return nullptr;
    }

    return queue;
}

bool Enqueue(Queue* queue, int value)
{
    if (queue == nullptr)
    {
        return false;
    }
    return EnqueueCircularBuffer(queue->_circularBuffer, value);
}

int Dequeue(Queue* queue)
{
    if (queue == nullptr)
    {
        return -1;
    }
    return DequeueCircularBuffer(queue->_circularBuffer);
}

void DeleteQueue(Queue*& queue)
{
    if (queue == nullptr)
    {
        return;
    }

    if (queue->_circularBuffer != nullptr)
    {
        DeleteCircularBuffer(queue->_circularBuffer);
    }

    delete queue;
    queue = nullptr;
}

bool IsQueueEmpty(Queue* queue)
{
    if (queue == nullptr)
    {
        return true;
    }
    return GetUsedSpace(queue->_circularBuffer) == 0;
}

bool IsQueueFull(Queue* queue)
{
    if (queue == nullptr)
    {
        return true;
    }
    return GetFreeSpaceCircular(queue->_circularBuffer) == 0;
}

bool ResizeQueue(Queue* queue, int newCapacity)
{
    if (queue == nullptr)
    {
        return false;
    }
    return ResizeCircularBuffer(queue->_circularBuffer, newCapacity);
}
int GetFreeSpaceQueue(Queue* queue)
{
    if (queue == nullptr || queue->_circularBuffer == nullptr)
    {
        return 0;
    }
    return GetFreeSpaceCircular(queue->_circularBuffer);
}