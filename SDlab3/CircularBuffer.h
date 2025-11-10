#pragma once
#include <stdbool.h>

/// <summary>
/// Структура, представляющая кольцевой буфер для хранения целых чисел
/// </summary>
struct CircularBuffer
{
    /// <summary>
    /// Динамический массив для хранения элементов буфера
    /// </summary>
    int* Buffer;

    /// <summary>
    /// Максимальная вместимость буфера
    /// </summary>
    int Capacity;

    /// <summary>
    /// Индекс начала очереди (откуда извлекаются элементы)
    /// </summary>
    int Head;

    /// <summary>
    /// Индекс конца очереди (куда добавляются элементы)
    /// </summary>
    int Tail;

    /// <summary>
    /// Текущее количество элементов в буфере
    /// </summary>
    int Count;
};

/// <summary>
/// Создает новый экземпляр кольцевого буфера с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемого буфера</param>
/// <returns>Указатель на созданный буфер или nullptr при ошибке выделения памяти</returns>
CircularBuffer* CreateCircularBuffer(int capacity);

/// <summary>
/// Вычисляет количество свободного места в кольцевом буфере
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>Количество свободных ячеек в буфере</returns>
int GetFreeSpaceCircular(CircularBuffer* circularBuffer);

/// <summary>
/// Вычисляет количество занятого места в кольцевом буфере
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>Количество занятых ячеек в буфере</returns>
int GetUsedSpace(CircularBuffer* circularBuffer);

/// <summary>
/// Проверяет, является ли кольцевой буфер пустым
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>true если буфер пуст, иначе false</returns>
bool IsCircularBufferEmpty(CircularBuffer* circularBuffer);

/// <summary>
/// Добавляет элемент в конец кольцевого буфера
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если буфер полон</returns>
bool EnqueueCircularBuffer(CircularBuffer* circularBuffer, int value);

/// <summary>
/// Извлекает элемент из начала кольцевого буфера
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <returns>Извлеченный элемент или -1 если буфер пуст</returns>
int DequeueCircularBuffer(CircularBuffer* circularBuffer);

/// <summary>
/// Освобождает память, занятую кольцевым буфером
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер для удаления</param>
void DeleteCircularBuffer(CircularBuffer* circularBuffer);

/// <summary>
/// Изменяет размер кольцевого буфера, сохраняя существующие элементы
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="newCapacity">Новая вместимость буфера</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeCircularBuffer(CircularBuffer* circularBuffer, int newCapacity);