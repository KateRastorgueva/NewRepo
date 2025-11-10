#include "Stack.h"

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

// Функция проверки, пуст ли стек
bool IsEmpty(Stack* stack)
{
    if (stack == nullptr) 
    {
        return true;
    }
    return stack->Top == -1;
}

// Функция проверки, полон ли стек
bool IsFull(Stack* stack)
{
    if (stack == nullptr)
    {
        return true;
    }
    return stack->Top == stack->Capacity - 1;
}

// Функция помещения элемента в стек
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

// Функция извлечения элемента из стека
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

bool ResizeStack(Stack* stack, int newCapacity)
{
    if (stack == nullptr || newCapacity <= 0)
    {
        return false;
    }

    if (newCapacity <= stack->Top)
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