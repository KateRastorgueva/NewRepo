#include "QueueTwoStacksFunctions.h"
#include "StackFunctions.h"

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

    queue->_inputStack = CreateStack(capacity);
    queue->_outputStack = CreateStack(capacity);

    if (queue->_inputStack == nullptr || queue->_outputStack == nullptr)
    {
        if (queue->_inputStack != nullptr)
        {
            DeleteStack(queue->_inputStack);
        }
        if (queue->_outputStack != nullptr)
        {
            DeleteStack(queue->_outputStack);
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
    return Push(queue->_inputStack, value);
}

int DequeueTwoStacks(QueueTwoStacks* queue)
{
    if (queue == nullptr)
    {
        return -1;
    }

    if (IsEmpty(queue->_outputStack))
    {
        while (!IsEmpty(queue->_inputStack))
        {
            int value = Pop(queue->_inputStack);
            Push(queue->_outputStack, value);
        }
    }

    if (IsEmpty(queue->_outputStack))
    {
        return -1;
    }

    return Pop(queue->_outputStack);
}

void DeleteQueueTwoStacks(QueueTwoStacks* queue)
{
    if (queue == nullptr)
    {
        return;
    }

    if (queue->_inputStack != nullptr)
    {
        DeleteStack(queue->_inputStack);
    }

    if (queue->_outputStack != nullptr)
    {
        DeleteStack(queue->_outputStack);
    }

    delete queue;
}

bool IsQueueTwoStacksEmpty(QueueTwoStacks* queue)
{
    if (queue == nullptr)
    {
        return true;
    }
    return IsEmpty(queue->_inputStack) && IsEmpty(queue->_outputStack);
}
bool ResizeQueueTwoStacks(QueueTwoStacks* queue, int newCapacity)
{
    if (queue == nullptr || newCapacity <= 0)
    {
        return false;
    }

    // Создаем временные стеки нового размера
    Stack* newInputStack = CreateStack(newCapacity);
    Stack* newOutputStack = CreateStack(newCapacity);

    if (newInputStack == nullptr || newOutputStack == nullptr)
    {
        if (newInputStack != nullptr) DeleteStack(newInputStack);
        if (newOutputStack != nullptr) DeleteStack(newOutputStack);
        return false;
    }

    // Копируем элементы из inputStack
    while (!IsEmpty(queue->_inputStack))
    {
        int value = Pop(queue->_inputStack);
        Push(newInputStack, value);
    }

    // Копируем элементы из outputStack
    while (!IsEmpty(queue->_outputStack))
    {
        int value = Pop(queue->_outputStack);
        Push(newOutputStack, value);
    }

    // Заменяем старые стеки
    DeleteStack(queue->_inputStack);
    DeleteStack(queue->_outputStack);

    queue->_inputStack = newInputStack;
    queue->_outputStack = newOutputStack;

    return true;
}