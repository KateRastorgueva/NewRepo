#pragma once
#include "Stack.h"

/// <summary>
/// Структура, представляющая очередь на основе двух стеков
/// </summary>
struct QueueTwoStacks
{
    /// <summary>
    /// Стек для добавления элементов (входной стек)
    /// </summary>
    Stack* InputStack;

    /// <summary>
    /// Стек для извлечения элементов (выходной стек)
    /// </summary>
    Stack* OutputStack;
};

/// <summary>
/// Создает новую очередь на двух стеках с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемой очереди</param>
/// <returns>Указатель на созданную очередь или nullptr при ошибке</returns>
QueueTwoStacks* CreateQueueTwoStacks(int capacity);

/// <summary>
/// Добавляет элемент в очередь на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если очередь полна</returns>
bool EnqueueQueueTwoStacks(QueueTwoStacks* queue, int value);

/// <summary>
/// Извлекает элемент из очереди на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>Извлеченный элемент или -1 если очередь пуста</returns>
int DequeueTwoStacks(QueueTwoStacks* queue);

/// <summary>
/// Освобождает память, занятую очередью на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь для удаления</param>
void DeleteQueueTwoStacks(QueueTwoStacks* queue);

/// <summary>
/// Проверяет, является ли очередь на двух стеках пустой
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <returns>true если очередь пуста, иначе false</returns>
bool IsQueueTwoStacksEmpty(QueueTwoStacks* queue);

/// <summary>
/// Изменяет размер очереди на двух стеках, сохраняя существующие элементы
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="newCapacity">Новая вместимость очереди</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeQueueTwoStacks(QueueTwoStacks* queue, int newCapacity);