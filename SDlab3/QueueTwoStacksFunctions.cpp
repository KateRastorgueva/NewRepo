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

void DeleteQueueTwoStacks(QueueTwoStacks*& queue)
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
    queue = nullptr;
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

    // Считаем общее количество элементов
    int totalElements = (queue->_inputStack->_top + 1) + (queue->_outputStack->_top + 1);
    if (newCapacity < totalElements)
    {
        return false; // Новый размер слишком мал
    }

    // Создаем новую временную очередь для сохранения правильного порядка
    QueueTwoStacks* tempQueue = CreateQueueTwoStacks(newCapacity);
    if (tempQueue == nullptr)
    {
        return false;
    }

    // Переносим все элементы из исходной очереди во временную, сохраняя порядок
    // Сначала переносим outputStack (это начало очереди)
    Stack* tempStack = CreateStack(queue->_outputStack->_capacity);
    if (tempStack != nullptr)
    {
        // Сохраняем outputStack в правильном порядке
        while (!IsEmpty(queue->_outputStack))
        {
            int value = Pop(queue->_outputStack);
            Push(tempStack, value);
        }
        // Восстанавливаем из tempStack в tempQueue (теперь в правильном порядке)
        while (!IsEmpty(tempStack))
        {
            int value = Pop(tempStack);
            EnqueueQueueTwoStacks(tempQueue, value);
        }
        DeleteStack(tempStack);
    }

    // Затем переносим inputStack (это конец очереди)
    tempStack = CreateStack(queue->_inputStack->_capacity);
    if (tempStack != nullptr)
    {
        // Сохраняем inputStack в правильном порядке
        while (!IsEmpty(queue->_inputStack))
        {
            int value = Pop(queue->_inputStack);
            Push(tempStack, value);
        }
        // Восстанавливаем из tempStack в tempQueue
        while (!IsEmpty(tempStack))
        {
            int value = Pop(tempStack);
            EnqueueQueueTwoStacks(tempQueue, value);
        }
        DeleteStack(tempStack);
    }

    // Заменяем старые стеки новыми
    DeleteStack(queue->_inputStack);
    DeleteStack(queue->_outputStack);

    queue->_inputStack = tempQueue->_inputStack;
    queue->_outputStack = tempQueue->_outputStack;

    // Освобождаем временную структуру
    tempQueue->_inputStack = nullptr;
    tempQueue->_outputStack = nullptr;
    DeleteQueueTwoStacks(tempQueue);

    return true;
}