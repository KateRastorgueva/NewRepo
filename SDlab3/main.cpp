#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <sstream>
#include "StackFunctions.h"
#include "QueueFunctions.h"
#include "QueueTwoStacksFunctions.h"
#include "CircularBufferFunctions.h"
#include "CircularBuffer.h"

using namespace std;

// Установка русской кодировки для Windows
void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void ExceptionNeedCorrectNumber()
{
    cout << "Ошибка! Введите корректное число: ";
}

void ExceptionNumberBig()
{
    cout << "Число слишком большое! Введите меньшее число: ";
}

bool IsValidIntegerString(const string& value)
{
    if (value.empty())
    {
        return false;
    }

    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] < '0' || value[i] > '9')
        {
            return false;
        }
    }

    if (value.length() > 1 && value[0] == '0')
    {
        return false;
    }

    if (value.length() > 1)
    {
        bool allZeros = true;
        for (int i = 0; i < value.length(); i++)
        {
            if (value[i] != '0')
            {
                allZeros = false;
                break;
            }
        }
        if (allZeros)
        {
            return false;
        }
    }

    return true;
}

int GetValidatedInput(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (!IsValidIntegerString(input))
        {
            ExceptionNeedCorrectNumber();
            continue;
        }
        if (input.length() > 10)
        {
            ExceptionNumberBig();
            continue;
        }

        int result = 0;
        for (int i = 0; i < input.length(); i++)
        {
            int digit = input[i] - '0';

            if (result > (2147483647 - digit) / 10)
            {
                ExceptionNumberBig();
                break;
            }

            result = result * 10 + digit;

            if (i == input.length() - 1)
            {
                return result;
            }
        }
    }
}

int GetValidatedInputInRange(const string& prompt, int min, int max)
{
    int value;

    while (true)
    {
        value = GetValidatedInput(prompt);
        if (value >= min && value <= max)
        {
            return value;
        }
        cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
    }
}

bool ValidateCapacity(int capacity)
{
    if (capacity <= 0)
    {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return false;
    }
    return true;
}

// Общие функции для вывода текста
void ShowSectionHeader(const string& title)
{
    cout << "\n" << title << endl;
}

void ShowCreationSuccess(const string& structureName)
{
    cout << structureName << " создан(а) успешно!" << endl;
}

void ShowCreationError(const string& structureName)
{
    cout << "Ошибка создания " << structureName << "!" << endl;
}

void ShowAddSuccess(int value, const string& structureName)
{
    cout << "Элемент " << value << " добавлен в " << structureName << "." << endl;
}

void ShowAddError(const string& structureName)
{
    cout << structureName << " полон(а)! Невозможно добавить элемент." << endl;
}

void ShowResizeSuccess(int newCapacity, const string& structureName)
{
    cout << "Размер " << structureName << " изменен на " << newCapacity << endl;
}

void ShowResizeError(const string& structureName)
{
    cout << "Ошибка изменения размера " << structureName << "!" << endl;
}

Stack* CreateStructureStack()
{
    int capacity = GetValidatedInput("Введите вместимость стека: ");
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    Stack* stack = CreateStack(capacity);
    if (stack != nullptr)
    {
        ShowCreationSuccess("Стек");
    }
    else
    {
        ShowCreationError("стека");
    }
    return stack;
}

Queue* CreateStructureQueue()
{
    int capacity = GetValidatedInput("Введите вместимость очереди: ");
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    Queue* queue = CreateQueue(capacity);
    if (queue != nullptr)
    {
        ShowCreationSuccess("Очередь");
    }
    else
    {
        ShowCreationError("очереди");
    }
    return queue;
}

QueueTwoStacks* CreateStructureQueueTwoStacks()
{
    int capacity = GetValidatedInput("Введите вместимость очереди: ");
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    QueueTwoStacks* queue = CreateQueueTwoStacks(capacity);
    if (queue != nullptr)
    {
        ShowCreationSuccess("Очередь");
    }
    else
    {
        ShowCreationError("очереди");
    }
    return queue;
}

CircularBuffer* CreateStructureCircularBuffer()
{
    int capacity = GetValidatedInput("Введите вместимость кольцевого буфера: ");
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    CircularBuffer* circularBuffer = CreateCircularBuffer(capacity);
    if (circularBuffer != nullptr)
    {
        ShowCreationSuccess("Кольцевой буфер");
    }
    else
    {
        ShowCreationError("кольцевого буфера");
    }
    return circularBuffer;
}

// Вспомогательные функции для проверки существования структур
bool CheckStructureExists(void* structure, const string& structureName)
{
    if (structure == nullptr)
    {
        cout << structureName << " не создан(а)!" << endl;
        return false;
    }
    return true;
}

bool CheckStructureNotExists(void* structure, const string& structureName)
{
    if (structure != nullptr)
    {
        cout << structureName << " уже существует! Удалите сначала." << endl;
        return false;
    }
    return true;
}

// Общая функция проверки пустоты структуры
bool CheckStructureEmpty(bool isEmpty, const string& structureName)
{
    if (isEmpty)
    {
        cout << structureName << " пуст(а/ая)! Невозможно извлечь элемент." << endl;
        return true;
    }
    return false;
}

// Общая функция вывода извлеченного элемента
void ShowExtractedElement(int value, bool success = true)
{
    if (success && value != -1)
    {
        cout << "Извлечен элемент: " << value << endl;
    }
    else
    {
        cout << "Ошибка извлечения элемента!" << endl;
    }
}

void AddElementToCircularBuffer(CircularBuffer*& circularBuffer)
{
    if (!CheckStructureExists(circularBuffer, "Кольцевой буфер"))
    {
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    if (EnqueueCircularBuffer(circularBuffer, value))
    {
        ShowAddSuccess(value, "кольцевой буфер");
    }
    else
    {
        ShowAddError("Кольцевой буфер");
    }
}

void AddElementToStack(Stack*& stack)
{
    if (!CheckStructureExists(stack, "Стек"))
    {
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    if (Push(stack, value))
    {
        ShowAddSuccess(value, "стек");
    }
    else
    {
        ShowAddError("Стек");
    }
}

void AddElementToQueue(Queue*& queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    if (Enqueue(queue, value))
    {
        ShowAddSuccess(value, "очередь");
    }
    else
    {
        ShowAddError("Очередь");
    }
}

void AddElementToQueueTwoStacks(QueueTwoStacks*& queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    EnqueueTwoStacks(queue, value);
    ShowAddSuccess(value, "очередь");
}

// Упрощенные функции извлечения элементов
void ExtractElementFromStack(Stack*& stack)
{
    if (!CheckStructureExists(stack, "Стек"))
    {
        return;
    }

    if (CheckStructureEmpty(IsEmpty(stack), "Стек"))
    {
        return;
    }

    int value = Pop(stack);
    ShowExtractedElement(value);
}

void ExtractElementFromQueue(Queue*& queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

    if (CheckStructureEmpty(IsQueueEmpty(queue), "Очередь"))
    {
        return;
    }

    int value = Dequeue(queue);
    ShowExtractedElement(value, value != -1);
}

void ExtractElementFromQueueTwoStacks(QueueTwoStacks*& queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

    if (CheckStructureEmpty(IsQueueTwoStacksEmpty(queue), "Очередь"))
    {
        return;
    }

    int value = DequeueTwoStacks(queue);
    ShowExtractedElement(value, value != -1);
}

void ExtractElementFromCircularBuffer(CircularBuffer*& circularBuffer)
{
    if (!CheckStructureExists(circularBuffer, "Кольцевой буфер"))
    {
        return;
    }

    if (CheckStructureEmpty(GetUsedSpace(circularBuffer) == 0, "Кольцевой буфер"))
    {
        return;
    }

    int value = DequeueCircularBuffer(circularBuffer);
    ShowExtractedElement(value, value != -1);
}


// Общая функция для вывода сообщений об удалении
void ShowDeleteMessage(bool wasDeleted, const string& structureName)
{
    if (wasDeleted)
    {
        cout << structureName << " удален(а)." << endl;
    }
    else
    {
        cout << structureName << " уже удален(а) или не создан(а)." << endl;
    }
}

// Упрощенные функции удаления структур
void DeleteStructureStack(Stack*& stack)
{
    bool wasDeleted = (stack != nullptr);
    if (wasDeleted)
    {
        DeleteStack(stack);
        stack = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Стек");
}

void DeleteStructureQueue(Queue*& queue)
{
    bool wasDeleted = (queue != nullptr);
    if (wasDeleted)
    {
        DeleteQueue(queue);
        queue = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Очередь");
}

void DeleteStructureQueueTwoStacks(QueueTwoStacks*& queue)
{
    bool wasDeleted = (queue != nullptr);
    if (wasDeleted)
    {
        DeleteQueueTwoStacks(queue);
        queue = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Очередь");
}

void DeleteStructureCircularBuffer(CircularBuffer*& circularBuffer)
{
    bool wasDeleted = (circularBuffer != nullptr);
    if (wasDeleted)
    {
        DeleteCircularBuffer(circularBuffer);
        circularBuffer = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Кольцевой буфер");
}

// Функции для вывода характеристик структур
void PrintStackInfo(Stack* stack, const string& name)
{
    cout << name << endl;
    if (stack == nullptr)
    {
        cout << "Стек не создан или удален" << endl;
        return;
    }

    cout << "Вместимость: " << stack->_capacity << endl;
    cout << "Вершина (top): " << stack->_top << endl;
    cout << "Пуст: " << (IsEmpty(stack) ? "да" : "нет") << endl;
    cout << "Полон: " << (IsFull(stack) ? "да" : "нет") << endl;

    cout << "Содержимое (сверху вниз): ";
    if (IsEmpty(stack))
    {
        cout << "пусто";
    }
    else
    {
        Stack* tempStack = CreateStack(stack->_capacity);
        int count = 0;

        while (!IsEmpty(stack))
        {
            int value = Pop(stack);
            Push(tempStack, value);
            count++;
        }

        for (int i = 0; i < count; i++)
        {
            int value = Pop(tempStack);
            cout << value;
            if (i < count - 1)
            {
                cout << " <- ";
            }
            Push(stack, value);
        }

        DeleteStack(tempStack);
    }
    cout << endl << endl;
}

void PrintCircularBufferInfo(CircularBuffer* circularBuffer, const string& name)
{
    cout << name << endl;
    if (circularBuffer == nullptr)
    {
        cout << "Кольцевой буфер не создан или удален" << endl;
        return;
    }

    cout << "Вместимость: " << circularBuffer->_capacity << endl;
    cout << "Голова (head): " << circularBuffer->_head << endl;
    cout << "Хвост (tail): " << circularBuffer->_tail << endl;
    cout << "Количество элементов: " << circularBuffer->_count << endl;
    cout << "Пуст: " << (GetUsedSpace(circularBuffer) == 0 ? "да" : "нет") << endl;
    cout << "Полон: " << (GetFreeSpaceCircular(circularBuffer) == 0 ? "да" : "нет") << endl;
    cout << "Занято мест: " << GetUsedSpace(circularBuffer) << endl;
    cout << "Свободно мест: " << GetFreeSpaceCircular(circularBuffer) << endl;

    cout << "Содержимое (начало -> конец): ";
    if (GetUsedSpace(circularBuffer) == 0)
    {
        cout << "пусто";
    }
    else
    {
        CircularBuffer* tempBuffer = CreateCircularBuffer(circularBuffer->_capacity);
        int count = circularBuffer->_count;

        for (int i = 0; i < count; i++)
        {
            int value = DequeueCircularBuffer(circularBuffer);
            cout << value;
            if (i < count - 1)
            {
                cout << " -> ";
            }
            EnqueueCircularBuffer(tempBuffer, value);
        }

        for (int i = 0; i < count; i++)
        {
            int value = DequeueCircularBuffer(tempBuffer);
            EnqueueCircularBuffer(circularBuffer, value);
        }

        DeleteCircularBuffer(tempBuffer);
    }
    cout << endl << endl;
}

void PrintQueueInfo(Queue* queue, const string& name)
{
    cout << name << endl;
    if (queue == nullptr)
    {
        cout << "Очередь не создана или удалена" << endl;
        return;
    }

    cout << "Пуста: " << (IsQueueEmpty(queue) ? "да" : "нет") << endl;
    cout << "Полна: " << (IsQueueFull(queue) ? "да" : "нет") << endl;
    cout << "Занято мест: " << GetUsedSpace(queue->_circularBuffer) << endl;
    cout << "Свободно мест: " << GetFreeSpaceQueue(queue) << endl;

    cout << "Содержимое (начало -> конец): ";
    if (IsQueueEmpty(queue))
    {
        cout << "пусто";
    }
    else
    {
        int capacity = GetUsedSpace(queue->_circularBuffer) + GetFreeSpaceQueue(queue);
        Queue* tempQueue = CreateQueue(capacity);
        int count = 0;

        while (!IsQueueEmpty(queue))
        {
            int value = Dequeue(queue);
            cout << value;
            if (!IsQueueEmpty(queue))
            {
                cout << " -> ";
            }
            Enqueue(tempQueue, value);
            count++;
        }

        while (!IsQueueEmpty(tempQueue))
        {
            int value = Dequeue(tempQueue);
            Enqueue(queue, value);
        }

        DeleteQueue(tempQueue);
    }
    cout << endl;
}

void PrintQueueTwoStacksInfo(QueueTwoStacks* queue, const string& name)
{
    cout << name << endl;
    if (queue == nullptr)
    {
        cout << "Очередь на двух стеках не создана или удалена" << endl;
        return;
    }

    cout << "Пуста: " << (IsQueueTwoStacksEmpty(queue) ? "да" : "нет") << endl;

    cout << "InputStack: ";
    PrintStackInfo(queue->_inputStack, "InputStack очереди");

    cout << "OutputStack: ";
    PrintStackInfo(queue->_outputStack, "OutputStack очереди");

    cout << "Содержимое очереди (начало -> конец): ";
    if (IsQueueTwoStacksEmpty(queue))
    {
        cout << "пусто";
    }
    else
    {
        int capacity = queue->_inputStack->_capacity;
        QueueTwoStacks* tempQueue = CreateQueueTwoStacks(capacity);
        int count = 0;

        while (!IsQueueTwoStacksEmpty(queue))
        {
            int value = DequeueTwoStacks(queue);
            cout << value;
            if (!IsQueueTwoStacksEmpty(queue))
            {
                cout << " -> ";
            }
            EnqueueTwoStacks(tempQueue, value);
            count++;
        }

        while (!IsQueueTwoStacksEmpty(tempQueue))
        {
            int value = DequeueTwoStacks(tempQueue);
            EnqueueTwoStacks(queue, value);
        }

        DeleteQueueTwoStacks(tempQueue);
    }
    cout << endl << endl;
}

// Функции меню
void ShowStructureMenu(const string& structureName)
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать " << structureName << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить " << structureName << endl;
}

void ShowStackMenu()
{
    ShowStructureMenu("стек");
}

void ShowCircularBufferMenu()
{
    ShowStructureMenu("кольцевой буфер");
}

void ShowQueueMenu()
{
    ShowStructureMenu("очередь");
}

void ShowQueueTwoStacksMenu()
{
    ShowStructureMenu("очередь");
}

void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Работа со стеком" << endl;
    cout << "2 - Работа с кольцевым буфером" << endl;
    cout << "3 - Работа с очередью (кольцевой буфер)" << endl;
    cout << "4 - Работа с очередью (два стека)" << endl;
    cout << "5 - Показать все структуры" << endl;
}

// Обработчики выбора меню
void HandleStackMenuChoice(int choice, Stack*& stack)
{
    switch (choice)
    {
    case 1:
    {
        if (CheckStructureNotExists(stack, "Стек"))
        {
            stack = CreateStructureStack();
        }
        break;
    }

    case 2:
    {
        AddElementToStack(stack);
        break;
    }

    case 3:
    {
        ExtractElementFromStack(stack);
        break;
    }

    case 4:
    {
        if (CheckStructureExists(stack, "Стек"))
        {
            int newCapacity = GetValidatedInput("Введите новый размер стека: ");
            if (ResizeStack(stack, newCapacity))
            {
                ShowResizeSuccess(newCapacity, "стека");
            }
            else
            {
                ShowResizeError("стека");
            }
        }
        break;
    }

    case 5:
    {
        DeleteStructureStack(stack);
        break;
    }
    }
}

void HandleCircularBufferMenuChoice(int choice, CircularBuffer*& circularBuffer)
{
    switch (choice)
    {
    case 1:
    {
        if (CheckStructureNotExists(circularBuffer, "Кольцевой буфер"))
        {
            circularBuffer = CreateStructureCircularBuffer();
        }
        break;
    }

    case 2:
    {
        AddElementToCircularBuffer(circularBuffer);
        break;
    }

    case 3:
    {
        ExtractElementFromCircularBuffer(circularBuffer);
        break;
    }

    case 4:
    {
        if (CheckStructureExists(circularBuffer, "Кольцевой буфер"))
        {
            int newCapacity = GetValidatedInput("Введите новый размер кольцевого буфера: ");
            if (ResizeCircularBuffer(circularBuffer, newCapacity))
            {
                ShowResizeSuccess(newCapacity, "кольцевого буфера");
            }
            else
            {
                ShowResizeError("кольцевого буфера");
            }
        }
        break;
    }

    case 5:
    {
        DeleteStructureCircularBuffer(circularBuffer);
        break;
    }
    }
}

void HandleQueueMenuChoice(int choice, Queue*& queue)
{
    switch (choice)
    {
    case 1:
    {
        if (CheckStructureNotExists(queue, "Очередь"))
        {
            queue = CreateStructureQueue();
        }
        break;
    }

    case 2:
    {
        AddElementToQueue(queue);
        break;
    }

    case 3:
    {
        ExtractElementFromQueue(queue);
        break;
    }

    case 4:
    {
        if (CheckStructureExists(queue, "Очередь"))
        {
            int newCapacity = GetValidatedInput("Введите новый размер очереди: ");
            if (ResizeQueue(queue, newCapacity))
            {
                ShowResizeSuccess(newCapacity, "очереди");
            }
            else
            {
                ShowResizeError("очереди");
            }
        }
        break;
    }

    case 5:
    {
        DeleteStructureQueue(queue);
        break;
    }
    }
}

void HandleQueueTwoStacksMenuChoice(int choice, QueueTwoStacks*& queue)
{
    switch (choice)
    {
    case 1:
    {
        if (CheckStructureNotExists(queue, "Очередь"))
        {
            queue = CreateStructureQueueTwoStacks();
        }
        break;
    }

    case 2:
    {
        AddElementToQueueTwoStacks(queue);
        break;
    }

    case 3:
    {
        ExtractElementFromQueueTwoStacks(queue);
        break;
    }

    case 4:
    {
        if (CheckStructureExists(queue, "Очередь"))
        {
            int newCapacity = GetValidatedInput("Введите новый размер очереди: ");
            if (ResizeQueueTwoStacks(queue, newCapacity))
            {
                ShowResizeSuccess(newCapacity, "очереди");
            }
            else
            {
                ShowResizeError("очереди");
            }
        }
        break;
    }

    case 5:
    {
        DeleteStructureQueueTwoStacks(queue);
        break;
    }
    }
}

int main()
{
    SetRussianEncoding();

    Stack* myStack = nullptr;
    CircularBuffer* myCircularBuffer = nullptr;
    Queue* myQueue = nullptr;
    QueueTwoStacks* myQueueTwoStacks = nullptr;

    int mainChoice, subChoice;

    cout << "ДЕМОНСТРАЦИЯ СТРУКТУР ДАННЫХ" << endl;

    do
    {
        ShowMainMenu();
        mainChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);

        switch (mainChoice)
        {
        case 0:
        {
            cout << "Выход из программы..." << endl;
            break;
        }

        case 1:
        {
            do
            {
                ShowSectionHeader("РАБОТА СО СТЕКОМ");
                PrintStackInfo(myStack, "Текущий стек");
                ShowStackMenu();
                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 6);
                HandleStackMenuChoice(subChoice, myStack);
            } while (subChoice != 0);
            break;
        }

        case 2:
        {
            do
            {
                ShowSectionHeader("КОЛЬЦЕВОЙ БУФЕР");
                PrintCircularBufferInfo(myCircularBuffer, "Текущий кольцевой буфер");
                ShowCircularBufferMenu();
                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);
                HandleCircularBufferMenuChoice(subChoice, myCircularBuffer);
            } while (subChoice != 0);
            break;
        }

        case 3:
        {
            do
            {
                ShowSectionHeader("ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
                PrintQueueInfo(myQueue, "Текущая очередь");
                ShowQueueMenu();
                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);
                HandleQueueMenuChoice(subChoice, myQueue);
            } while (subChoice != 0);
            break;
        }

        case 4:
        {
            do
            {
                ShowSectionHeader("ОЧЕРЕДЬ (ДВА СТЕКА)");
                PrintQueueTwoStacksInfo(myQueueTwoStacks, "Текущая очередь на двух стеках");
                ShowQueueTwoStacksMenu();
                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);
                HandleQueueTwoStacksMenuChoice(subChoice, myQueueTwoStacks);
            } while (subChoice != 0);
            break;
        }

        case 5:
        {
            ShowSectionHeader("ВСЕ СТРУКТУРЫ ДАННЫХ");
            PrintStackInfo(myStack, "СТЕК");
            PrintCircularBufferInfo(myCircularBuffer, "КОЛЬЦЕВОЙ БУФЕР");
            PrintQueueInfo(myQueue, "ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
            PrintQueueTwoStacksInfo(myQueueTwoStacks, "ОЧЕРЕДЬ (ДВА СТЕКА)");
            break;
        }
        }
    } while (mainChoice != 0);

    // Очистка памяти перед выходом
    DeleteStructureStack(myStack);
    DeleteStructureCircularBuffer(myCircularBuffer);
    DeleteStructureQueue(myQueue);
    DeleteStructureQueueTwoStacks(myQueueTwoStacks);

    return 0;
}