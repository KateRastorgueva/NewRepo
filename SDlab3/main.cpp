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

int GetValidatedInputInRange(int min, int max)
{
    int value;

    while (true)
    {
        value = GetValidatedInput("Выберите действие: ");
        if (value >= min && value <= max)
        {
            return value;
        }
        cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
    }
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

void WriteInfo(int capacity, int top)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Вершина (top): " << top << endl;
}

void WriteFullEmptyInfo(bool isEmpty, bool isFull)
{
    cout << "Пуст(а): " << (isEmpty ? "да" : "нет") << endl;
    cout << "Полон(а): " << (isFull ? "да" : "нет") << endl;
}

void WriteCircularBufferInfo(int capacity, int head, int tail, int count)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Голова (head): " << head << endl;
    cout << "Хвост (tail): " << tail << endl;
    cout << "Количество элементов: " << count << endl;
}

void WriteSpaceInfo(int used, int free)
{
    cout << "Занято мест: " << used << endl;
    cout << "Свободно мест: " << free << endl;
}

// Универсальные функции для работы со структурами
bool ValidateCapacity(int capacity)
{
    if (capacity <= 0)
    {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return false;
    }
    return true;
}

int GetValidatedCapacity(const string& structureName)
{
    return GetValidatedInput("Введите вместимость " + structureName + ": ");
}

int GetValueForAddition()
{
    return GetValidatedInput("Введите значение для добавления: ");
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
void ShowExtractedElement(int value)
{
    if (value != -1)
    {
        cout << "Извлечен элемент: " << value << endl;
    }
    else
    {
        cout << "Ошибка извлечения элемента!" << endl;
    }
}

// Функции создания структур
Stack* CreateStructureStack()
{
    int capacity = GetValidatedCapacity("стека");
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
    int capacity = GetValidatedCapacity("очереди");
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
    int capacity = GetValidatedCapacity("очереди");
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
    int capacity = GetValidatedCapacity("кольцевого буфера");
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

// Функции добавления элементов
void AddElementToStack(Stack*& stack)
{
    if (!CheckStructureExists(stack, "Стек"))
    {
        return;
    }

    int value = GetValueForAddition();
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

    int value = GetValueForAddition();
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

    int value = GetValueForAddition();
    EnqueueQueueTwoStacks(queue, value);
    ShowAddSuccess(value, "очередь");
}

void AddElementToCircularBuffer(CircularBuffer*& circularBuffer)
{
    if (!CheckStructureExists(circularBuffer, "Кольцевой буфер"))
    {
        return;
    }

    int value = GetValueForAddition();
    if (EnqueueCircularBuffer(circularBuffer, value))
    {
        ShowAddSuccess(value, "кольцевой буфер");
    }
    else
    {
        ShowAddError("Кольцевой буфер");
    }
}

// Функции извлечения элементов
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
    ShowExtractedElement(value);
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
    ShowExtractedElement(value);
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
    ShowExtractedElement(value);
}

// Функции изменения размера
void ResizeStack(Stack*& stack)
{
    if (!CheckStructureExists(stack, "Стек"))
    {
        return;
    }

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

void ResizeQueue(Queue*& queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

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

void ResizeQueueTwoStacks(QueueTwoStacks*& queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

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

void ResizeCircularBuffer(CircularBuffer*& circularBuffer)
{
    if (!CheckStructureExists(circularBuffer, "Кольцевой буфер"))
    {
        return;
    }

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

// Функции удаления структур
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
void WriteIsDeleteNotCreated(string value)
{
    cout<<value<< "не создан(а) или удален(а)" << endl;
}
// Функции вывода информации о структурах
void PrintStackInfo(Stack* stack, const string& name)
{
    cout << name << endl;
    if (stack == nullptr)
    {
        WriteIsDeleteNotCreated("Стек");
        return;
    }

    WriteInfo(stack->_capacity, stack->_top);
    WriteFullEmptyInfo(IsEmpty(stack), IsFull(stack));

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
        WriteIsDeleteNotCreated("Кольцевой буфер");
        return;
    }

    WriteCircularBufferInfo(circularBuffer->_capacity, circularBuffer->_head, circularBuffer->_tail, circularBuffer->_count);
    WriteFullEmptyInfo(GetUsedSpace(circularBuffer) == 0, GetFreeSpaceCircular(circularBuffer) == 0);
    WriteSpaceInfo(GetUsedSpace(circularBuffer), GetFreeSpaceCircular(circularBuffer));

    cout << "Содержимое (начало -> конец): ";
    if (GetUsedSpace(circularBuffer) == 0)
    {
        cout << "пусто";
    }
    else
    {
        for (int i = 0; i < circularBuffer->_count; i++)
        {
            int index = (circularBuffer->_head + i) % circularBuffer->_capacity;
            cout << circularBuffer->_buffer[index];
            if (i < circularBuffer->_count - 1)
            {
                cout << " -> ";
            }
        }
    }
    cout << endl << endl;
}
void PrintQueueInfo(Queue* queue, const string& name)
{
    cout << name << endl;
    if (queue == nullptr)
    {
        WriteIsDeleteNotCreated("Очередь");
        return;
    }

    WriteFullEmptyInfo(IsQueueEmpty(queue), IsQueueFull(queue));
    WriteSpaceInfo(GetUsedSpace(queue->_circularBuffer), GetFreeSpaceQueue(queue));

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
        WriteIsDeleteNotCreated("Очередь на двух стеках");
        return;
    }

    cout << "Пуста: " << (IsQueueTwoStacksEmpty(queue) ? "да" : "нет") << endl;

    PrintStackInfo(queue->_inputStack, "InputStack очереди");
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
            EnqueueQueueTwoStacks(tempQueue, value);
            count++;
        }

        while (!IsQueueTwoStacksEmpty(tempQueue))
        {
            int value = DequeueTwoStacks(tempQueue);
            EnqueueQueueTwoStacks(queue, value);
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
        ResizeStack(stack);
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
        ResizeCircularBuffer(circularBuffer);
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
        ResizeQueue(queue);
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
        ResizeQueueTwoStacks(queue);
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
        mainChoice = GetValidatedInputInRange(0, 5);

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
                ShowStructureMenu("стек");
                subChoice = GetValidatedInputInRange(0, 5);
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
                ShowStructureMenu("кольцевой буфер");
                subChoice = GetValidatedInputInRange(0, 5);
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
                ShowStructureMenu("очередь");
                subChoice = GetValidatedInputInRange(0, 5);
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
                ShowStructureMenu("очередь");
                subChoice = GetValidatedInputInRange(0, 5);
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
/*#include <iostream>
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

void ShowExceptionNeedCorrectNumber()
{
    cout << "Ошибка! Введите корректное число: ";
}

void ShowExceptionNumberTooLarge()
{
    cout << "Число слишком большое! Введите меньшее число: ";
}

bool IsValidIntegerString(const string& inputString)
{
    if (inputString.empty())
    {
        return false;
    }

    for (int index = 0; index < inputString.length(); index++)
    {
        if (inputString[index] < '0' || inputString[index] > '9')
        {
            return false;
        }
    }

    if (inputString.length() > 1 && inputString[0] == '0')
    {
        return false;
    }

    if (inputString.length() > 1)
    {
        bool allZeros = true;
        for (int index = 0; index < inputString.length(); index++)
        {
            if (inputString[index] != '0')
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

int GetValidatedInput(const string& promptMessage)
{
    string inputString;

    while (true)
    {
        cout << promptMessage;
        getline(cin, inputString);

        if (!IsValidIntegerString(inputString))
        {
            ShowExceptionNeedCorrectNumber();
            continue;
        }

        if (inputString.length() > 10)
        {
            ShowExceptionNumberTooLarge();
            continue;
        }

        int resultValue = 0;
        for (int index = 0; index < inputString.length(); index++)
        {
            int digit = inputString[index] - '0';

            if (resultValue > (2147483647 - digit) / 10)
            {
                ShowExceptionNumberTooLarge();
                break;
            }

            resultValue = resultValue * 10 + digit;

            if (index == inputString.length() - 1)
            {
                return resultValue;
            }
        }
    }
}

int GetValidatedInputInRange(int minimumValue, int maximumValue)
{
    int inputValue;

    while (true)
    {
        inputValue = GetValidatedInput("Выберите действие: ");
        if (inputValue >= minimumValue && inputValue <= maximumValue)
        {
            return inputValue;
        }
        cout << "Ошибка! Введите число от " << minimumValue << " до " << maximumValue << ": ";
    }
}

bool ValidateCapacity(int capacityValue)
{
    if (capacityValue <= 0)
    {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return false;
    }
    return true;
}

// Общие функции для вывода текста
void ShowSectionHeader(const string& sectionTitle)
{
    cout << "\n" << sectionTitle << endl;
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

void ShowExtractedElement(int value)
{
    if (value != -1)
    {
        cout << "Извлечен элемент: " << value << endl;
    }
    else
    {
        cout << "Ошибка извлечения элемента!" << endl;
    }
}

void ShowResizeSuccess(int newCapacity, const string& structureName)
{
    cout << "Размер " << structureName << " изменен на " << newCapacity << endl;
}

void ShowResizeError(const string& structureName)
{
    cout << "Ошибка изменения размера " << structureName << "!" << endl;
}

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

int GetValidatedCapacity(const string& structureName)
{
    return GetValidatedInput("Введите вместимость " + structureName + ": ");
}

// Обобщенная функция создания структур
void* CreateStructureGeneric(const string& structureName, void* (*createFunction)(int))
{
    int capacity = GetValidatedCapacity(structureName);
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    void* structure = createFunction(capacity);
    if (structure != nullptr)
    {
        ShowCreationSuccess(structureName);
    }
    else
    {
        ShowCreationError(structureName);
    }
    return structure;
}

// Вспомогательные функции для проверки структур
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

bool CheckStructureEmpty(bool isEmpty, const string& structureName)
{
    if (isEmpty)
    {
        cout << structureName << " пуст(а/ая)! Невозможно извлечь элемент." << endl;
        return true;
    }
    return false;
}

// Обобщенная функция для добавления элементов
void AddElementToStructureGeneric(void* structure, const string& structureName, bool (*addFunction)(void*, int))
{
    if (!CheckStructureExists(structure, structureName))
    {
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    bool success = addFunction(structure, value);

    if (success)
    {
        ShowAddSuccess(value, structureName);
    }
    else
    {
        ShowAddError(structureName);
    }
}

// Обобщенная функция для извлечения элементов
void ExtractElementFromStructureGeneric(void* structure, const string& structureName,
    bool (*isEmptyFunction)(void*),
    int (*extractFunction)(void*))
{
    if (!CheckStructureExists(structure, structureName))
    {
        return;
    }

    if (CheckStructureEmpty(isEmptyFunction(structure), structureName))
    {
        return;
    }

    int value = extractFunction(structure);
    ShowExtractedElement(value);
}

// Обобщенная функция изменения размера
void ResizeStructureGeneric(void* structure, const string& structureName, bool (*resizeFunction)(void*, int))
{
    if (!CheckStructureExists(structure, structureName))
    {
        return;
    }

    int newCapacity = GetValidatedInput("Введите новый размер " + structureName + ": ");
    if (resizeFunction(structure, newCapacity))
    {
        ShowResizeSuccess(newCapacity, structureName);
    }
    else
    {
        ShowResizeError(structureName);
    }
}

// Обобщенная функция удаления структур
void DeleteStructureGeneric(void*& structure, const string& structureName, void (*deleteFunction)(void*&))
{
    bool wasDeleted = (structure != nullptr);
    if (wasDeleted)
    {
        deleteFunction(structure);
        structure = nullptr;
    }
    ShowDeleteMessage(wasDeleted, structureName);
}
// Функции для вывода информации
void WriteInfo(int capacity, int top)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Вершина (top): " << top << endl;
}

void WriteFullEmptyInfo(bool isEmpty, bool isFull)
{
    cout << "Пуст(а): " << (isEmpty ? "да" : "нет") << endl;
    cout << "Полон(а): " << (isFull ? "да" : "нет") << endl;
}

// Обобщенная функция для вывода информации о контейнерах
void PrintContainerInfo(void* container, const string& name, bool isStack)
{
    cout << name << endl;

    if (container == nullptr) {
        cout << (isStack ? "Стек" : "Кольцевой буфер") << " не создан или удален" << endl;
        return;
    }

    if (isStack) {
        Stack* stack = (Stack*)container;
        WriteInfo(stack->_capacity, stack->_top);
        WriteFullEmptyInfo(IsEmpty(stack), IsFull(stack));

        cout << "Содержимое (сверху вниз): ";
        if (IsEmpty(stack)) {
            cout << "пусто";
        }
        else {
            Stack* tempStack = CreateStack(stack->_capacity);
            int count = 0;

            while (!IsEmpty(stack)) {
                int value = Pop(stack);
                Push(tempStack, value);
                count++;
            }

            for (int i = 0; i < count; i++) {
                int value = Pop(tempStack);
                cout << value;
                if (i < count - 1) {
                    cout << " <- ";
                }
                Push(stack, value);
            }
            DeleteStack(tempStack);
        }
    }
    else {
        CircularBuffer* circularBuffer = (CircularBuffer*)container;
        cout << "Вместимость: " << circularBuffer->_capacity << endl;
        cout << "Голова (head): " << circularBuffer->_head << endl;
        cout << "Хвост (tail): " << circularBuffer->_tail << endl;
        cout << "Количество элементов: " << circularBuffer->_count << endl;
        WriteFullEmptyInfo(circularBuffer->_count == 0, circularBuffer->_count == circularBuffer->_capacity);
        cout << "Занято мест: " << circularBuffer->_count << endl;
        cout << "Свободно мест: " << (circularBuffer->_capacity - circularBuffer->_count) << endl;

        cout << "Содержимое (начало -> конец): ";
        if (circularBuffer->_count == 0) {
            cout << "пусто";
        }
        else {
            for (int i = 0; i < circularBuffer->_count; i++) {
                int index = (circularBuffer->_head + i) % circularBuffer->_capacity;
                cout << circularBuffer->_buffer[index];
                if (i < circularBuffer->_count - 1) {
                    cout << " -> ";
                }
            }
        }
    }
    cout << endl << endl;
}

// Обобщенная функция для вывода информации об очередях
void PrintQueueInfoGeneric(void* queue, const string& name, int queueType)
{
    cout << name << endl;

    if (queue == nullptr) {
        cout << "Очередь не создана или удалена" << endl;
        return;
    }

    if (queueType == 0) {
        Queue* queuePointer = (Queue*)queue;
        WriteFullEmptyInfo(IsQueueEmpty(queuePointer), IsQueueFull(queuePointer));
        cout << "Занято мест: " << GetUsedSpace(queuePointer->_circularBuffer) << endl;
        cout << "Свободно мест: " << GetFreeSpaceQueue(queuePointer) << endl;
    }
    else {
        QueueTwoStacks* queuePointer = (QueueTwoStacks*)queue;
        PrintContainerInfo(queuePointer->_inputStack, "InputStack очереди", true);
        PrintContainerInfo(queuePointer->_outputStack, "OutputStack очереди", true);
    }

    cout << "Содержимое очереди (начало -> конец): ";

    bool isEmpty = (queueType == 0) ? IsQueueEmpty((Queue*)queue) :
        IsQueueTwoStacksEmpty((QueueTwoStacks*)queue);

    if (isEmpty) {
        cout << "пусто";
    }
    else {
        int capacity;
        void* tempQueue;

        if (queueType == 0) {
            Queue* queuePointer = (Queue*)queue;
            capacity = GetUsedSpace(queuePointer->_circularBuffer) + GetFreeSpaceQueue(queuePointer);
            tempQueue = CreateQueue(capacity);
        }
        else {
            QueueTwoStacks* queuePointer = (QueueTwoStacks*)queue;
            capacity = queuePointer->_inputStack->_capacity;
            tempQueue = CreateQueueTwoStacks(capacity);
        }

        int count = 0;

        while (queueType == 0 ? !IsQueueEmpty((Queue*)queue) :
            !IsQueueTwoStacksEmpty((QueueTwoStacks*)queue)) {
            int value;
            if (queueType == 0) {
                value = Dequeue((Queue*)queue);
            }
            else {
                value = DequeueTwoStacks((QueueTwoStacks*)queue);
            }

            cout << value;

            bool tempEmpty = (queueType == 0) ? IsQueueEmpty((Queue*)queue) :
                IsQueueTwoStacksEmpty((QueueTwoStacks*)queue);

            if (!tempEmpty) {
                cout << " -> ";
            }

            if (queueType == 0) {
                Enqueue((Queue*)tempQueue, value);
            }
            else {
                EnqueueQueueTwoStacks((QueueTwoStacks*)tempQueue, value);
            }
            count++;
        }

        while (queueType == 0 ? !IsQueueEmpty((Queue*)tempQueue) :
            !IsQueueTwoStacksEmpty((QueueTwoStacks*)tempQueue)) {
            int value;
            if (queueType == 0) {
                value = Dequeue((Queue*)tempQueue);
                Enqueue((Queue*)queue, value);
            }
            else {
                value = DequeueTwoStacks((QueueTwoStacks*)tempQueue);
                EnqueueQueueTwoStacks((QueueTwoStacks*)queue, value);
            }
        }

        if (queueType == 0) {
            DeleteQueue((Queue*&)tempQueue);
        }
        else {
            DeleteQueueTwoStacks((QueueTwoStacks*&)tempQueue);
        }
    }
    cout << endl << endl;
}
// Обобщенные функции меню
void ShowStructureMenu(const string& structureName)
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать " << structureName << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить " << structureName << endl;
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

// Универсальный обработчик меню для всех структур данных
void HandleStructureMenuChoice(int choice, void*& structure, const string& structureName,
    void* (*createFunction)(int), bool (*addElementFunction)(void*, int), bool (*isEmptyFunction)(void*),
    int (*extractElementFunction)(void*), bool (*resizeFunction)(void*, int), void (*deleteFunction)(void*&))
{
    switch (choice)
    {
    case 1:
    {
        if (CheckStructureNotExists(structure, structureName))
        {
            structure = CreateStructureGeneric(structureName, createFunction);
        }
        break;
    }

    case 2:
    {
        AddElementToStructureGeneric(structure, structureName, addElementFunction);
        break;
    }

    case 3:
    {
        ExtractElementFromStructureGeneric(structure, structureName, isEmptyFunction, extractElementFunction);
        break;
    }

    case 4:
    {
        ResizeStructureGeneric(structure, structureName, resizeFunction);
        break;
    }

    case 5:
    {
        DeleteStructureGeneric(structure, structureName, deleteFunction);
        break;
    }
    }
}

int main()
{
    SetRussianEncoding();

    Stack* stackPointer = nullptr;
    CircularBuffer* circularBufferPointer = nullptr;
    Queue* queuePointer = nullptr;
    QueueTwoStacks* queueTwoStacksPointer = nullptr;

    int mainMenuChoice, subMenuChoice;

    cout << "ДЕМОНСТРАЦИЯ СТРУКТУР ДАННЫХ" << endl;

    do
    {
        ShowMainMenu();
        mainMenuChoice = GetValidatedInputInRange(0, 5);

        switch (mainMenuChoice)
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
                PrintContainerInfo(stackPointer, "Текущий стек", true);
                ShowStructureMenu("стек");
                subMenuChoice = GetValidatedInputInRange(0, 5);
                HandleStructureMenuChoice(
                    subMenuChoice,
                    (void*&)stackPointer,
                    "Стек",
                    (void* (*)(int))CreateStack,
                    (bool (*)(void*, int))Push,
                    (bool (*)(void*))IsEmpty,
                    (int (*)(void*))Pop,
                    (bool (*)(void*, int))ResizeStack,
                    (void (*)(void*&))DeleteStack
                );
            } while (subMenuChoice != 0);
            break;
        }

        case 2:
        {
            do
            {
                ShowSectionHeader("КОЛЬЦЕВОЙ БУФЕР");
                PrintContainerInfo(circularBufferPointer, "Текущий кольцевой буфер", false);
                ShowStructureMenu("кольцевой буфер");
                subMenuChoice = GetValidatedInputInRange(0, 5);
                HandleStructureMenuChoice(
                    subMenuChoice,
                    (void*&)circularBufferPointer,
                    "Кольцевой буфер",
                    (void* (*)(int))CreateCircularBuffer,
                    (bool (*)(void*, int))EnqueueCircularBuffer,
                    (bool (*)(void*))IsCircularBufferEmpty,
                    (int (*)(void*))DequeueCircularBuffer,
                    (bool (*)(void*, int))ResizeCircularBuffer,
                    (void (*)(void*&))DeleteCircularBuffer
                );
            } while (subMenuChoice != 0);
            break;
        }

        case 3:
        {
            do
            {
                ShowSectionHeader("ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
                PrintQueueInfoGeneric(queuePointer, "Текущая очередь", 0);
                ShowStructureMenu("очередь");
                subMenuChoice = GetValidatedInputInRange(0, 5);
                HandleStructureMenuChoice(
                    subMenuChoice,
                    (void*&)queuePointer,
                    "Очередь",
                    (void* (*)(int))CreateQueue,
                    (bool (*)(void*, int))Enqueue,
                    (bool (*)(void*))IsQueueEmpty,
                    (int (*)(void*))Dequeue,
                    (bool (*)(void*, int))ResizeQueue,
                    (void (*)(void*&))DeleteQueue
                );
            } while (subMenuChoice != 0);
            break;
        }

        case 4:
        {
            do
            {
                ShowSectionHeader("ОЧЕРЕДЬ (ДВА СТЕКА)");
                PrintQueueInfoGeneric(queueTwoStacksPointer, "Текущая очередь на двух стеках", 1);
                subMenuChoice = GetValidatedInputInRange(0, 5);
                HandleStructureMenuChoice(
                    subMenuChoice,
                    (void*&)queueTwoStacksPointer,
                    "Очередь",
                    (void* (*)(int))CreateQueueTwoStacks,
                    (bool (*)(void*, int))EnqueueQueueTwoStacks,
                    (bool (*)(void*))IsQueueTwoStacksEmpty,
                    (int (*)(void*))DequeueTwoStacks,
                    (bool (*)(void*, int))ResizeQueueTwoStacks,
                    (void (*)(void*&))DeleteQueueTwoStacks
                );
            } while (subMenuChoice != 0);
            break;
        }

        case 5:
        {
            ShowSectionHeader("ВСЕ СТРУКТУРЫ ДАННЫХ");
            PrintContainerInfo(stackPointer, "СТЕК", true);
            PrintContainerInfo(circularBufferPointer, "КОЛЬЦЕВОЙ БУФЕР", false);
            PrintQueueInfoGeneric(queuePointer, "ОЧЕРЕДЬ", 0);
            PrintQueueInfoGeneric(queueTwoStacksPointer, "ОЧЕРЕДЬ (ДВА СТЕКА)", 1);
            break;
        }
        }
    } while (mainMenuChoice != 0);

    // Очистка памяти перед выходом через универсальную функцию
    DeleteStructureGeneric((void*&)stackPointer, "Стек", (void (*)(void*&))DeleteStack);
    DeleteStructureGeneric((void*&)circularBufferPointer, "Кольцевой буфер", (void (*)(void*&))DeleteCircularBuffer);
    DeleteStructureGeneric((void*&)queuePointer, "Очередь", (void (*)(void*&))DeleteQueue);
    DeleteStructureGeneric((void*&)queueTwoStacksPointer, "Очередь", (void (*)(void*&))DeleteQueueTwoStacks);

    return 0;
}*/