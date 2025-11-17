#include "Queue.h"
#include "CircularBuffer.h"

/// <summary>
/// Создает новую очередь с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемой очереди</param>
/// <returns>Указатель на созданную очередь или nullptr при ошибке</returns>
Queue* CreateQueue(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

    Queue* queue = new Queue;
    if (!queue)
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
/// <summary>
/// Добавляет элемент в конец очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если очередь полна</returns>
bool Enqueue(Queue* queue, int value)
{
    if (!queue)
    {
        return false;
    }
    return EnqueueCircularBuffer(queue->CircularBuffer, value);
}
/// <summary>
/// Извлекает элемент из начала очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>Извлеченный элемент или -1 если очередь пуста</returns>
int Dequeue(Queue* queue)
{
    if (!queue)
    {
        return -1;
    }
    return DequeueCircularBuffer(queue->CircularBuffer);
}
/// <summary>
/// Освобождает память, занятую очередью
/// </summary>
/// <param name="queue">Указатель на очередь для удаления</param>
void DeleteQueue(Queue* queue)
{
    if (!queue)
    {
        return;
    }

    if (queue->CircularBuffer != nullptr)
    {
        DeleteCircularBuffer(queue->CircularBuffer);
    }

    delete queue;
}
/// <summary>
/// Проверяет, является ли очередь пустой
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>true если очередь пуста, иначе false</returns>
bool IsQueueEmpty(Queue* queue)
{
    if (!queue)
    {
        return true;
    }
    return GetUsedSpace(queue->CircularBuffer) == 0;
}
/// <summary>
/// Проверяет, является ли очередь полной
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>true если очередь полна, иначе false</returns>
bool IsQueueFull(Queue* queue)
{
    if (!queue)
    {
        return true;
    }
    return GetFreeSpaceCircular(queue->CircularBuffer) == 0;
}
/// <summary>
/// Изменяет размер очереди, сохраняя существующие элементы
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="newCapacity">Новая вместимость очереди</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeQueue(Queue* queue, int newCapacity)
{
    if (!queue)
    {
        return false;
    }
    return ResizeCircularBuffer(queue->CircularBuffer, newCapacity);
}
/// <summary>
/// Вычисляет количество свободного места в очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>Количество свободных мест в очереди</returns>
int GetFreeSpaceQueue(Queue* queue)
{
    if (!queue || queue->CircularBuffer == nullptr)
    {
        return 0;
    }
    return GetFreeSpaceCircular(queue->CircularBuffer);
}