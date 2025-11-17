#include "Stack.h"

/// <summary>
/// Создает новый экземпляр стека с указанной вместимостью
/// </summary>
/// <param name="capacity">Вместимость создаваемого стека</param>
/// <returns>Указатель на созданный стек или nullptr при ошибке выделения памяти</returns>
Stack* CreateStack(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

    // Выделение памяти для структуры
    Stack* stack = new Stack;
    if (stack == nullptr)
    {
        return nullptr;
    }

    // Выделение памяти для буфера
    stack->Buffer = new int[capacity];
    if (stack->Buffer == nullptr)
    {
        delete stack;
        return nullptr;
    }

    // Инициализация полей стека
    stack->Capacity = capacity;
    stack->Top = -1;

    return stack;
}

/// <summary>
/// Проверяет, является ли стек пустым
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <returns>true если стек пуст, иначе false</returns>
bool IsEmpty(Stack* stack)
{
    return stack == nullptr || stack->Top == -1;
}

/// <summary>
/// Проверяет, является ли стек полным
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <returns>true если стек полон, иначе false</returns>
bool IsFull(Stack* stack)
{
    return stack == nullptr || stack->Top == stack->Capacity - 1;
}
/// <summary>
/// Добавляет элемент на вершину стека
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="value">Значение для добавления</param>
/// <returns>true если элемент успешно добавлен, false если стек полон</returns>
bool Push(Stack* stack, int value)
{
    if (stack == nullptr || IsFull(stack))
    {
        return false;
    }

    stack->Top++;
    stack->Buffer[stack->Top] = value;
    return true;
}

/// <summary>
/// Извлекает элемент с вершины стека
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <returns>Извлеченный элемент или -1 если стек пуст</returns>
int Pop(Stack* stack)
{
    if (stack == nullptr || IsEmpty(stack))
    {
        return -1;
    }

    int value = stack->Buffer[stack->Top];
    stack->Top--;
    return value;
}

/// <summary>
/// Освобождает память, занятую стеком
/// </summary>
/// <param name="stack">Указатель на стек для удаления</param>
void DeleteStack(Stack* stack)
{
    if (stack == nullptr)
    {
        return;
    }
    if (stack->Buffer != nullptr)
    {
        delete[] stack->Buffer;
        stack->Buffer = nullptr;
    }
    delete stack;
}
/// <summary>
/// Изменяет размер стека, сохраняя существующие элементы
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="newCapacity">Новая вместимость стека</param>
/// <returns>true если изменение размера успешно, false при ошибке</returns>
bool ResizeStack(Stack* stack, int newCapacity)
{
    if (stack == nullptr || newCapacity <= 0 || newCapacity <= stack->Top)
    {
        return false;
    }
    int* newBuffer = new int[newCapacity];
    if (newBuffer == nullptr)
    {
        return false;
    }

    for (int i = 0; i <= stack->Top; i++)
    {
        newBuffer[i] = stack->Buffer[i];
    }

    delete[] stack->Buffer;
    stack->Buffer = newBuffer;
    stack->Capacity = newCapacity;

    return true;
}