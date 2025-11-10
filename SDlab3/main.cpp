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

void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void ShowMainMenu()
{
    cout << "\nÃËÀÂÍÎÅ ÌÅÍÞ" << endl;
    cout << "0 - Âûõîä èç ïðîãðàììû" << endl;
    cout << "1 - Ðàáîòà ñî ñòåêîì" << endl;
    cout << "2 - Ðàáîòà ñ êîëüöåâûì áóôåðîì" << endl;
    cout << "3 - Ðàáîòà ñ î÷åðåäüþ (êîëüöåâîé áóôåð)" << endl;
    cout << "4 - Ðàáîòà ñ î÷åðåäüþ (äâà ñòåêà)" << endl;
    cout << "5 - Ïîêàçàòü âñå ñòðóêòóðû" << endl;
}

void ShowAllStructures(Stack* stack, CircularBuffer* circularBuffer, Queue* queue, QueueTwoStacks* queueTwoStacks)
{
    cout << "\nÂÑÅ ÑÒÐÓÊÒÓÐÛ ÄÀÍÍÛÕ" << endl;
    PrintStackInfo(stack, "ÑÒÅÊ");
    PrintCircularBufferInfo(circularBuffer, "ÊÎËÜÖÅÂÎÉ ÁÓÔÅÐ");
    PrintQueueInfo(queue, "Î×ÅÐÅÄÜ (ÊÎËÜÖÅÂÎÉ ÁÓÔÅÐ)");
    PrintQueueTwoStacksInfo(queueTwoStacks, "Î×ÅÐÅÄÜ (ÄÂÀ ÑÒÅÊÀ)");
 
}

void CleanupStructures(Stack*& stack, CircularBuffer*& circularBuffer, Queue*& queue, QueueTwoStacks*& queueTwoStacks)
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

int main()
{
    SetRussianEncoding();

    Stack* myStack = nullptr;
    CircularBuffer* myCircularBuffer = nullptr;
    Queue* myQueue = nullptr;
    QueueTwoStacks* myQueueTwoStacks = nullptr;

    int mainChoice;

    cout << "ÄÅÌÎÍÑÒÐÀÖÈß ÑÒÐÓÊÒÓÐ ÄÀÍÍÛÕ" << endl;

    do
    {
        ShowMainMenu();
        mainChoice = GetValidatedInputInRange(0, 5);

        switch (mainChoice)
        {
        case 0:
            cout << "Âûõîä èç ïðîãðàììû..." << endl;
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

    CleanupStructures(myStack, myCircularBuffer, myQueue, myQueueTwoStacks);
    return 0;
}