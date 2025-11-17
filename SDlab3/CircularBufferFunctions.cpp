#include "CircularBuffer.h"

/// <summary>
/// Создает новый экземпляр кольцевого буфера с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемого буфера</param>
/// <returns>Указатель на созданный буфер или nullptr при ошибке выделения памяти</returns>
CircularBuffer* CreateCircularBuffer(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

    CircularBuffer* circularBuffer = new CircularBuffer;
    if (!circularBuffer)
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
/// <summary>
/// Вычисляет количество свободного места в кольцевом буфере
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>Количество свободных ячеек в буфере</returns>
int GetFreeSpaceCircular(CircularBuffer* circularBuffer)
{
    if (!circularBuffer)
    {
        return 0;
    }
    return circularBuffer->Capacity - circularBuffer->Count;
}
/// <summary>
/// Вычисляет количество занятого места в кольцевом буфере
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>Количество занятых ячеек в буфере</returns>
int GetUsedSpace(CircularBuffer* circularBuffer)
{
    if (!circularBuffer)
    {
        return 0;
    }
    return circularBuffer->Count;
}
/// <summary>
/// Проверяет, является ли кольцевой буфер пустым
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>true если буфер пуст, иначе false</returns>
bool IsCircularBufferEmpty(CircularBuffer* сircularBuffer)
{
    if (!сircularBuffer)
    {
        return true;
    }
    return GetUsedSpace(сircularBuffer) == 0;
}
/// <summary>
/// Добавляет элемент в конец кольцевого буфера
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если буфер полон</returns>
bool EnqueueCircularBuffer(CircularBuffer* circularBuffer, int value)
{
    if (!circularBuffer || circularBuffer->Count == circularBuffer->Capacity)
    {
        return false;
    }

    circularBuffer->Buffer[circularBuffer->Tail] = value;
    circularBuffer->Tail = (circularBuffer->Tail + 1) % circularBuffer->Capacity;
    circularBuffer->Count++;

    return true;
}
/// <summary>
/// Извлекает элемент из начала кольцевого буфера
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>Извлеченный элемент или -1 если буфер пуст</returns>
int DequeueCircularBuffer(CircularBuffer* circularBuffer)
{
    if (!circularBuffer || circularBuffer->Count == 0)
    {
        return -1;
    }
    int value = circularBuffer->Buffer[circularBuffer->Head];
    circularBuffer->Head = (circularBuffer->Head + 1) % circularBuffer->Capacity;
    circularBuffer->Count--;

    return value;
}
/// <summary>
/// Освобождает память, занятую кольцевым буфером
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер для удаления</param>
void DeleteCircularBuffer(CircularBuffer* circularBuffer)
{
    if (!circularBuffer)
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
/// <summary>
/// Изменяет размер кольцевого буфера, сохраняя существующие элементы
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="newCapacity">Новая вместимость буфера</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
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