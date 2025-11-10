#pragma once

/// <summary>
/// Структура, представляющая стек для хранения целых чисел
/// </summary>
struct Stack
{
    /// <summary>
    /// Динамический массив для хранения элементов стека
    /// </summary>
    int* Buffer;

    /// <summary>
    /// Максимальная вместимость стека
    /// </summary>
    int Capacity;

    /// <summary>
    /// Индекс вершины стека (-1 означает пустой стек)
    /// </summary>
    int Top;
};

/// <summary>
/// Создает новый экземпляр стека с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемого стека</param>
/// <returns>Указатель на созданный стек или nullptr при ошибке выделения памяти</returns>
Stack* CreateStack(int capacity);

/// <summary>
/// Добавляет элемент на вершину стека
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если стек полон</returns>
bool Push(Stack* stack, int value);

/// <summary>
/// Извлекает элемент с вершины стека
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <returns>Извлеченный элемент или -1 если стек пуст</returns>
int Pop(Stack* stack);

/// <summary>
/// Проверяет, является ли стек пустым
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <returns>true если стек пуст, иначе false</returns>
bool IsEmpty(Stack* stack);

/// <summary>
/// Проверяет, является ли стек полным
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <returns>true если стек полон, иначе false</returns>
bool IsFull(Stack* stack);

/// <summary>
/// Освобождает память, занятую стеком
/// </summary>
/// <param name="stack">Указатель на стек для удаления</param>
void DeleteStack(Stack* stack);

/// <summary>
/// Изменяет размер стека, сохраняя существующие элементы
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="newCapacity">Новая вместимость стека</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeStack(Stack* stack, int newCapacity);