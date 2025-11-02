#pragma once
#include "Stack.h"

// Функция создания стека
Stack* CreateStack(int capacity);

// Функция помещения элемента в стек
bool Push(Stack* stack, int value);

// Функция извлечения элемента из стека
int Pop(Stack* stack);

// Функция проверки, пуст ли стек
bool IsEmpty(Stack* stack);

// Функция проверки, полон ли стек  
bool IsFull(Stack* stack);

// Функция просмотра верхнего элемента без извлечения
int Peek(Stack* stack);

// Функция удаления стека (очистка памяти)
void DeleteStack(Stack* stack);

bool ResizeStack(Stack* stack, int newCapacity);