#include "Queue.h"
#include "CircularBuffer.h"

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

    queue->CircularBuffer = CreateCircularBuffer(capacity);
    if (queue->CircularBuffer == nullptr)
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
    return EnqueueCircularBuffer(queue->CircularBuffer, value);
}

int Dequeue(Queue* queue)
{
    if (queue == nullptr)
    {
        return -1;
    }
    return DequeueCircularBuffer(queue->CircularBuffer);
}

void DeleteQueue(Queue* queue)
{
    if (queue == nullptr)
    {
        return;
    }

    if (queue->CircularBuffer != nullptr)
    {
        DeleteCircularBuffer(queue->CircularBuffer);
    }

    delete queue;
}

bool IsQueueEmpty(Queue* queue)
{
    if (queue == nullptr)
    {
        return true;
    }
    return GetUsedSpace(queue->CircularBuffer) == 0;
}

bool IsQueueFull(Queue* queue)
{
    if (queue == nullptr)
    {
        return true;
    }
    return GetFreeSpaceCircular(queue->CircularBuffer) == 0;
}

bool ResizeQueue(Queue* queue, int newCapacity)
{
    if (queue == nullptr)
    {
        return false;
    }
    return ResizeCircularBuffer(queue->CircularBuffer, newCapacity);
}
int GetFreeSpaceQueue(Queue* queue)
{
    if (queue == nullptr || queue->CircularBuffer == nullptr)
    {
        return 0;
    }
    return GetFreeSpaceCircular(queue->CircularBuffer);
}