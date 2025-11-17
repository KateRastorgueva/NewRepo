#include <iostream>
#include <windows.h>
#include "Stack.h"
#include "Queue.h"
#include "QueueTwoStacks.h"
#include "CircularBuffer.h"
#include "Validator.h"
#include "ConsoleService.h"
#include "StackConsole.h"
#include "CircularBufferConsole.h"
#include "QueueConsole.h"
#include "QueueTwoStacksConsole.h"

using namespace std;

/// <summary>
/// Устанавливает русскую кодировку консоли
/// </summary>
void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

/// <summary>
/// Отображает главное меню программы
/// </summary>
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

/// <summary>
/// Отображает информацию о всех структурах данных
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="queue">Указатель на очередь</param>
/// <param name="queueTwoStacks">Указатель на очередь из двух стеков</param>
void ShowAllStructures(Stack* stack, CircularBuffer* circularBuffer, Queue* queue, QueueTwoStacks* queueTwoStacks)
{
    cout << "\nВСЕ СТРУКТУРЫ ДАННЫХ" << endl;
    PrintStackInfo(stack, "СТЕК");
    PrintCircularBufferInfo(circularBuffer, "КОЛЬЦЕВОЙ БУФЕР");
    PrintQueueInfo(queue, "ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
    PrintQueueTwoStacksInfo(queueTwoStacks, "ОЧЕРЕДЬ (ДВА СТЕКА)");
}

/// <summary>
/// Очищает все структуры данных и освобождает память
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
/// <param name="queue">Ссылка на указатель очереди</param>
/// <param name="queueTwoStacks">Ссылка на указатель очереди из двух стеков</param>
void CleanUpStructures(Stack*& stack, CircularBuffer*& circularBuffer, Queue*& queue, QueueTwoStacks*& queueTwoStacks)
{
    if (stack)
    {
        DeleteStack(stack);
        stack = nullptr;
    }
    if (circularBuffer)
    {
        DeleteCircularBuffer(circularBuffer);
        circularBuffer = nullptr;
    }
    if (queue)
    {
        DeleteQueue(queue);
        queue = nullptr;
    }
    if (queueTwoStacks)
    {
        DeleteQueueTwoStacks(queueTwoStacks);
        queueTwoStacks = nullptr;
    }
}

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main()
{
    SetRussianEncoding();

    Stack* myStack = nullptr;
    CircularBuffer* myCircularBuffer = nullptr;
    Queue* myQueue = nullptr;
    QueueTwoStacks* myQueueTwoStacks = nullptr;

    int mainChoice;

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
            HandleStackMenu(myStack);
            break;
        case 2:
            HandleCircularBufferMenu(myCircularBuffer);
            break;
        case 3:
            HandleQueueMenu(myQueue);
            break;
        case 4:
            HandleQueueTwoStacksMenu(myQueueTwoStacks);
            break;
        case 5:
            ShowAllStructures(myStack, myCircularBuffer, myQueue, myQueueTwoStacks);
            break;
        }
    } while (mainChoice != 0);

    CleanUpStructures(myStack, myCircularBuffer, myQueue, myQueueTwoStacks);
    return 0;
}