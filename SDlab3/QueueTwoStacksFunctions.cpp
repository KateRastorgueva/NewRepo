#include "QueueTwoStacks.h"
#include "Stack.h"

QueueTwoStacks* CreateQueueTwoStacks(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

    QueueTwoStacks* queue = new QueueTwoStacks;
    if (queue == nullptr)
    {
        return nullptr;
    }

    queue->InputStack = CreateStack(capacity);
    queue->OutputStack = CreateStack(capacity);

    if (queue->InputStack == nullptr || queue->OutputStack == nullptr)
    {
        if (queue->InputStack != nullptr)
        {
            DeleteStack(queue->InputStack);
        }
        if (queue->OutputStack != nullptr)
        {
            DeleteStack(queue->OutputStack);
        }
        delete queue;
        return nullptr;
    }

    return queue;
}
bool EnqueueQueueTwoStacks(QueueTwoStacks* queue, int value)
{
    if (queue == nullptr)
    {
        return false;
    }
    return Push(queue->InputStack, value);
}

int DequeueTwoStacks(QueueTwoStacks* queue)
{
    if (queue == nullptr)
    {
        return -1;
    }

    if (IsEmpty(queue->OutputStack))
    {
        while (!IsEmpty(queue->InputStack))
        {
            int value = Pop(queue->InputStack);
            Push(queue->OutputStack, value);
        }
    }

    if (IsEmpty(queue->OutputStack))
    {
        return -1;
    }

    return Pop(queue->OutputStack);
}

void DeleteQueueTwoStacks(QueueTwoStacks* queue)
{
    if (queue == nullptr)
    {
        return;
    }

    if (queue->InputStack != nullptr)
    {
        DeleteStack(queue->InputStack);
    }

    if (queue->OutputStack != nullptr)
    {
        DeleteStack(queue->OutputStack);
    }

    delete queue;
}

bool IsQueueTwoStacksEmpty(QueueTwoStacks* queue)
{
    if (queue == nullptr)
    {
        return true;
    }
    return IsEmpty(queue->InputStack) && IsEmpty(queue->OutputStack);
}
bool ResizeQueueTwoStacks(QueueTwoStacks* queue, int newCapacity)
{
    if (queue == nullptr || newCapacity <= 0)
    {
        return false;
    }

    int totalElements = (queue->InputStack->Top + 1) + (queue->OutputStack->Top + 1);
    if (newCapacity < totalElements)
    {
        return false;
    }
    QueueTwoStacks* tempQueue = CreateQueueTwoStacks(newCapacity);
    if (tempQueue == nullptr)
    {
        return false;
    }
    //  начало очереди
    Stack* tempStack = CreateStack(queue->OutputStack->Capacity);
    if (tempStack != nullptr)
    {
        // —охран€ем outputStack в правильном пор€дке
        while (!IsEmpty(queue->OutputStack))
        {
            int value = Pop(queue->OutputStack);
            Push(tempStack, value);
        }
        while (!IsEmpty(tempStack))
        {
            int value = Pop(tempStack);
            EnqueueQueueTwoStacks(tempQueue, value);
        }
        DeleteStack(tempStack);
    }

    // конец очереди
    tempStack = CreateStack(queue->InputStack->Capacity);
    if (tempStack != nullptr)
    {
        while (!IsEmpty(queue->InputStack))
        {
            int value = Pop(queue->InputStack);
            Push(tempStack, value);
        }
        while (!IsEmpty(tempStack))
        {
            int value = Pop(tempStack);
            EnqueueQueueTwoStacks(tempQueue, value);
        }
        DeleteStack(tempStack);
    }

    DeleteStack(queue->InputStack);
    DeleteStack(queue->OutputStack);

    queue->InputStack = tempQueue->InputStack;
    queue->OutputStack = tempQueue->OutputStack;

    // ќсвобождаем временную структуру
    tempQueue->InputStack = nullptr;
    tempQueue->OutputStack = nullptr;
    DeleteQueueTwoStacks(tempQueue);

    return true;
}