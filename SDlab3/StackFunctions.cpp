#include "StackFunctions.h"

// Функция создания стека
Stack* CreateStack(int capacity)
{
    // Проверка валидности capacity
    if (capacity <= 0)
    {
        return nullptr;
    }

    // Выделение памяти для структуры стека
    Stack* stack = new Stack;
    if (stack == nullptr)
    {
        return nullptr;
    }

    // Выделение памяти для буфера
    stack->_buffer = new int[capacity];
    if (stack->_buffer == nullptr)
    {
        delete stack;
        return nullptr;
    }

    // Инициализация полей стека
    stack->_capacity = capacity;
    stack->_top = -1;

    return stack;
}

// Функция проверки, пуст ли стек
bool IsEmpty(Stack* stack)
{
    if (stack == nullptr)
    {
        return true;
    }
    return stack->_top == -1;
}

// Функция проверки, полон ли стек
bool IsFull(Stack* stack)
{
    if (stack == nullptr)
    {
        return true;
    }
    return stack->_top == stack->_capacity - 1;
}

// Функция помещения элемента в стек
void Push(Stack* stack, int value)
{
    if (stack == nullptr || IsFull(stack))
    {
        return;
    }

    stack->_top++;
    stack->_buffer[stack->_top] = value;
}

// Функция извлечения элемента из стека
int Pop(Stack* stack)
{
    if (stack == nullptr || IsEmpty(stack))
    {
        return -1; // Возвращаем значение ошибки
    }

    int value = stack->_buffer[stack->_top];
    stack->_top--;
    return value;
}

// Функция просмотра верхнего элемента без извлечения
int Peek(Stack* stack)
{
    if (stack == nullptr || IsEmpty(stack))
    {
        return -1;
    }

    return stack->_buffer[stack->_top];
}

// Функция удаления стека (очистка памяти)
void DeleteStack(Stack* stack)
{
    if (stack == nullptr)
    {
        return;
    }
    // Удаляем буфер
    if (stack->_buffer != nullptr)
    {
        delete[] stack->_buffer;
        stack->_buffer = nullptr;
    }
    delete stack;
}