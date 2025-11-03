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

template<typename StructureType, typename CreatorFunction>
StructureType* CreateStructure(CreatorFunction creator, const string& structureName)
{
    int capacity = GetValidatedCapacity(structureName);
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    StructureType* structure = creator(capacity);
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

template<typename StructureType, typename AddFunction>
void AddElementToStructure(StructureType*& structure, AddFunction addFunction, const string& structureName)
{
    if (!CheckStructureExists(structure, structureName))
    {
        return;
    }

    int value = GetValueForAddition();
    if (addFunction(structure, value))
    {
        ShowAddSuccess(value, structureName);
    }
    else
    {
        ShowAddError(structureName);
    }
}

template<typename StructureType, typename ExtractFunction, typename IsEmptyFunction>
void ExtractElementFromStructure(StructureType*& structure, ExtractFunction extractFunction,
    IsEmptyFunction isEmptyFunction, const string& structureName)
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

template<typename StructureType, typename ResizeFunction>
void ResizeStructure(StructureType*& structure, ResizeFunction resizeFunction, const string& structureName)
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

template<typename StructureType, typename DeleteFunction>
void DeleteStructure(StructureType*& structure, DeleteFunction deleteFunction, const string& structureName)
{
    bool wasDeleted = (structure != nullptr);
    if (wasDeleted)
    {
        deleteFunction(structure);
        structure = nullptr;
    }
    ShowDeleteMessage(wasDeleted, structureName);
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

void WriteIsDeleteNotCreated(string value)
{
    cout << value << " не создан(а) или удален(а)" << endl;
}

template<typename StructureType>
bool CheckAndPrintHeader(StructureType* structure, const string& name)
{
    cout << name << endl;
    if (structure == nullptr)
    {
        WriteIsDeleteNotCreated(name);
        return false;
    }
    return true;
}

template<typename StructureType, typename IsEmptyFunction>
void PrintContentHeader(StructureType* structure, IsEmptyFunction isEmptyFunction, const string& contentDescription)
{
    cout << contentDescription << ": ";
    if (isEmptyFunction(structure))
    {
        cout << "пусто";
    }
}

void PrintStackInfo(Stack* stack, const string& name)
{
    if (!CheckAndPrintHeader(stack, name))
    {
        return;
    }

    WriteInfo(stack->_capacity, stack->_top);
    WriteFullEmptyInfo(IsEmpty(stack), IsFull(stack));

    PrintContentHeader(stack, IsEmpty, "Содержимое (сверху вниз)");

    if (!IsEmpty(stack))
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
    if (!CheckAndPrintHeader(circularBuffer, name))
    {
        return;
    }

    WriteCircularBufferInfo(circularBuffer->_capacity, circularBuffer->_head, circularBuffer->_tail, circularBuffer->_count);
    WriteFullEmptyInfo(IsCircularBufferEmpty(circularBuffer), GetFreeSpaceCircular(circularBuffer) == 0);
    WriteSpaceInfo(GetUsedSpace(circularBuffer), GetFreeSpaceCircular(circularBuffer));

    PrintContentHeader(circularBuffer, IsCircularBufferEmpty, "Содержимое (начало -> конец)");

    if (!IsCircularBufferEmpty(circularBuffer))
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
    if (!CheckAndPrintHeader(queue, name))
    {
        return;
    }

    WriteFullEmptyInfo(IsQueueEmpty(queue), IsQueueFull(queue));
    WriteSpaceInfo(GetUsedSpace(queue->_circularBuffer), GetFreeSpaceQueue(queue));

    PrintContentHeader(queue, IsQueueEmpty, "Содержимое (начало -> конец)");

    if (!IsQueueEmpty(queue))
    {
        int capacity = GetUsedSpace(queue->_circularBuffer) + GetFreeSpaceQueue(queue);
        Queue* tempQueue = CreateQueue(capacity);

        while (!IsQueueEmpty(queue))
        {
            int value = Dequeue(queue);
            cout << value;
            if (!IsQueueEmpty(queue))
            {
                cout << " -> ";
            }
            Enqueue(tempQueue, value);
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
void WriteEmptyInfo(bool isEmpty)
{
    cout << "Пуст(а): ";
    if (isEmpty)
    {
        cout << "да";
    }
    else
    {
        cout << "нет";
    }
    cout << endl;
}
void PrintQueueTwoStacksInfo(QueueTwoStacks* queue, const string& name)
{
    if (!CheckAndPrintHeader(queue, name))
    {
        return;
    }

    WriteEmptyInfo(IsQueueTwoStacksEmpty(queue));
    PrintStackInfo(queue->_inputStack, "InputStack очереди");
    PrintStackInfo(queue->_outputStack, "OutputStack очереди");

    PrintContentHeader(queue, IsQueueTwoStacksEmpty, "Содержимое очереди (начало -> конец)");

    if (!IsQueueTwoStacksEmpty(queue))
    {
        int capacity = queue->_inputStack->_capacity;
        QueueTwoStacks* tempQueue = CreateQueueTwoStacks(capacity);

        while (!IsQueueTwoStacksEmpty(queue))
        {
            int value = DequeueTwoStacks(queue);
            cout << value;
            if (!IsQueueTwoStacksEmpty(queue))
            {
                cout << " -> ";
            }
            EnqueueQueueTwoStacks(tempQueue, value);
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
void HandleStackMenuChoice(int choice, Stack*& stack)
{
    switch (choice)
    {
    case 1:
        if (CheckStructureNotExists(stack, "Стек"))
        {
            stack = CreateStructure<Stack>(CreateStack, "стек");
        }
        break;

    case 2:
        AddElementToStructure<Stack>(stack, Push, "Стек");
        break;

    case 3:
        ExtractElementFromStructure<Stack>(stack, Pop, IsEmpty, "Стек");
        break;

    case 4:
        ResizeStructure<Stack>(stack, ResizeStack, "стека");
        break;

    case 5:
        DeleteStructure<Stack>(stack, DeleteStack, "Стек");
        break;
    }
}

void HandleCircularBufferMenuChoice(int choice, CircularBuffer*& circularBuffer)
{
    switch (choice)
    {
    case 1:
        if (CheckStructureNotExists(circularBuffer, "Кольцевой буфер"))
        {
            circularBuffer = CreateStructure<CircularBuffer>(CreateCircularBuffer, "кольцевого буфера");
        }
        break;

    case 2:
        AddElementToStructure<CircularBuffer>(circularBuffer, EnqueueCircularBuffer, "Кольцевой буфер");
        break;

    case 3:
        ExtractElementFromStructure<CircularBuffer>(circularBuffer, DequeueCircularBuffer, IsCircularBufferEmpty, "Кольцевой буфер");
        break;

    case 4:
        ResizeStructure<CircularBuffer>(circularBuffer, ResizeCircularBuffer, "кольцевого буфера");
        break;

    case 5:
        DeleteStructure<CircularBuffer>(circularBuffer, DeleteCircularBuffer, "Кольцевой буфер");
        break;
    }
}

void HandleQueueMenuChoice(int choice, Queue*& queue)
{
    switch (choice)
    {
    case 1:
        if (CheckStructureNotExists(queue, "Очередь"))
        {
            queue = CreateStructure<Queue>(CreateQueue, "очередь");
        }
        break;

    case 2:
        AddElementToStructure<Queue>(queue, Enqueue, "Очередь");
        break;

    case 3:
        ExtractElementFromStructure<Queue>(queue, Dequeue, IsQueueEmpty, "Очередь");
        break;

    case 4:
        ResizeStructure<Queue>(queue, ResizeQueue, "очереди");
        break;

    case 5:
        DeleteStructure<Queue>(queue, DeleteQueue, "Очередь");
        break;
    }
}

void HandleQueueTwoStacksMenuChoice(int choice, QueueTwoStacks*& queue)
{
    switch (choice)
    {
    case 1:
        if (CheckStructureNotExists(queue, "Очередь"))
        {
            queue = CreateStructure<QueueTwoStacks>(CreateQueueTwoStacks, "очереди");
        }
        break;

    case 2:
        AddElementToQueueTwoStacks(queue);
        break;

    case 3:
        ExtractElementFromStructure<QueueTwoStacks>(queue, DequeueTwoStacks, IsQueueTwoStacksEmpty, "Очередь");
        break;

    case 4:
        ResizeStructure<QueueTwoStacks>(queue, ResizeQueueTwoStacks, "очереди");
        break;

    case 5:
        DeleteStructure<QueueTwoStacks>(queue, DeleteQueueTwoStacks, "Очередь");
        break;
    }
}

int main()
{
    SetRussianEncoding();

    Stack* myStack = nullptr;
    CircularBuffer* myCircularBuffer = nullptr;
    Queue* myQueue = nullptr;
    QueueTwoStacks* myQueueTwoStacks = nullptr;

    int mainChoice;
    int subChoice;

    cout << "ДЕМОНСТРАЦИЯ СТРУКТУР ДАННЫХ" << endl;

    do
    {
        ShowMainMenu();
        mainChoice = GetValidatedInputInRange(0, 5);

        switch (mainChoice)
        {
        case 0:
            cout << "Выход из программы..." << endl;
            break;

        case 1:
            do
            {
                ShowSectionHeader("РАБОТА СО СТЕКОМ");
                PrintStackInfo(myStack, "Текущий стек");
                ShowStructureMenu("стек");
                subChoice = GetValidatedInputInRange(0, 5);
                HandleStackMenuChoice(subChoice, myStack);
            } while (subChoice != 0);
            break;

        case 2:
            do
            {
                ShowSectionHeader("КОЛЬЦЕВОЙ БУФЕР");
                PrintCircularBufferInfo(myCircularBuffer, "Текущий кольцевой буфер");
                ShowStructureMenu("кольцевой буфер");
                subChoice = GetValidatedInputInRange(0, 5);
                HandleCircularBufferMenuChoice(subChoice, myCircularBuffer);
            } while (subChoice != 0);
            break;

        case 3:
            do
            {
                ShowSectionHeader("ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
                PrintQueueInfo(myQueue, "Текущая очередь");
                ShowStructureMenu("очередь");
                subChoice = GetValidatedInputInRange(0, 5);
                HandleQueueMenuChoice(subChoice, myQueue);
            } while (subChoice != 0);
            break;

        case 4:
            do
            {
                ShowSectionHeader("ОЧЕРЕДЬ (ДВА СТЕКА)");
                PrintQueueTwoStacksInfo(myQueueTwoStacks, "Текущая очередь на двух стеках");
                ShowStructureMenu("очередь");
                subChoice = GetValidatedInputInRange(0, 5);
                HandleQueueTwoStacksMenuChoice(subChoice, myQueueTwoStacks);
            } while (subChoice != 0);
            break;

        case 5:
            ShowSectionHeader("ВСЕ СТРУКТУРЫ ДАННЫХ");
            PrintStackInfo(myStack, "СТЕК");
            PrintCircularBufferInfo(myCircularBuffer, "КОЛЬЦЕВОЙ БУФЕР");
            PrintQueueInfo(myQueue, "ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
            PrintQueueTwoStacksInfo(myQueueTwoStacks, "ОЧЕРЕДЬ (ДВА СТЕКА)");
            break;
        }
    } while (mainChoice != 0);

    DeleteStructure<Stack>(myStack, DeleteStack, "Стек");
    DeleteStructure<CircularBuffer>(myCircularBuffer, DeleteCircularBuffer, "Кольцевой буфер");
    DeleteStructure<Queue>(myQueue, DeleteQueue, "Очередь");
    DeleteStructure<QueueTwoStacks>(myQueueTwoStacks, DeleteQueueTwoStacks, "Очередь");

    return 0;
}