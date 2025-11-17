#include "QueueTwoStacks.h"
#include "Stack.h"

/// <summary>
/// Создает новую очередь на двух стеках с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемой очереди</param>
/// <returns>Указатель на созданную очередь или nullptr при ошибке</returns>
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
/// <summary>
/// Добавляет элемент в очередь на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если очередь полна</returns>
bool EnqueueQueueTwoStacks(QueueTwoStacks* queue, int value)
{
    if (queue == nullptr)
    {
        return false;
    }
    return Push(queue->InputStack, value);
}
/// <summary>
/// Извлекает элемент из очереди на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>Извлеченный элемент или -1 если очередь пуста</returns>
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

/// <summary>
/// Освобождает память, занятую очередью на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь для удаления</param>
void DeleteQueueTwoStacks(QueueTwoStacks* queue)
{
    if (!queue)
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
/// <summary>
/// Проверяет, является ли очередь на двух стеках пустой
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>true если очередь пуста, иначе false</returns>
bool IsQueueTwoStacksEmpty(QueueTwoStacks* queue)
{
    if (!queue)
    {
        return true;
    }
    return IsEmpty(queue->InputStack) && IsEmpty(queue->OutputStack);
}

/// <summary>
/// Изменяет размер очереди на двух стеках, сохраняя существующие элементы
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="newCapacity">Новая вместимость очереди</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeQueueTwoStacks(QueueTwoStacks* queue, int newCapacity)
{
    if (!queue || newCapacity <= 0)
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
        // Сохраняем outputStack в правильном порядке
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

    // Освобождаем временную структуру
    tempQueue->InputStack = nullptr;
    tempQueue->OutputStack = nullptr;
    DeleteQueueTwoStacks(tempQueue);

    return true;
}