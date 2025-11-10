#pragma once
#include "CircularBuffer.h"

/// <summary>
/// Структура, представляющая очередь на основе кольцевого буфера
/// </summary>
struct Queue
{
    /// <summary>
    /// Указатель на внутренний кольцевой буфер
    /// </summary>
    CircularBuffer* CircularBuffer;
};

/// <summary>
/// Создает новую очередь с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемой очереди</param>
/// <returns>Указатель на созданную очередь или nullptr при ошибке</returns>
Queue* CreateQueue(int capacity);

/// <summary>
/// Добавляет элемент в конец очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если очередь полна</returns>
bool Enqueue(Queue* queue, int value);

/// <summary>
/// Извлекает элемент из начала очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>Извлеченный элемент или -1 если очередь пуста</returns>
int Dequeue(Queue* queue);

/// <summary>
/// Освобождает память, занятую очередью
/// </summary>
/// <param name="queue">Указатель на очередь для удаления</param>
void DeleteQueue(Queue* queue);

/// <summary>
/// Проверяет, является ли очередь пустой
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>true если очередь пуста, иначе false</returns>
bool IsQueueEmpty(Queue* queue);

/// <summary>
/// Проверяет, является ли очередь полной
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>true если очередь полна, иначе false</returns>
bool IsQueueFull(Queue* queue);

/// <summary>
/// Изменяет размер очереди, сохраняя существующие элементы
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="newCapacity">Новая вместимость очереди</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeQueue(Queue* queue, int newCapacity);

/// <summary>
/// Вычисляет количество свободного места в очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>Количество свободных мест в очереди</returns>
int GetFreeSpaceQueue(Queue* queue);