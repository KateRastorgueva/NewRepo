#include "QueueTwoStacksConsole.h"
#include "Validator.h"
#include "ConsoleService.h"
#include "StackConsole.h"
#include <iostream>
using namespace std;

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

void ShowQueueTwoStacksStructureMenu()
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать очередь" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить очередь" << endl;
}

void PrintQueueTwoStacksInfo(QueueTwoStacks* queue, const string& name)
{
    if (!CheckAndPrintHeader(queue, name))
    {
        return;
    }

    WriteEmptyInfo(IsQueueTwoStacksEmpty(queue));
    PrintStackInfo(queue->InputStack, "InputStack очереди");
    PrintStackInfo(queue->OutputStack, "OutputStack очереди");

    PrintContentHeader(IsQueueTwoStacksEmpty(queue), "Содержимое очереди (начало -> конец)");

    if (!IsQueueTwoStacksEmpty(queue))
    {
        int capacity = queue->InputStack->Capacity;
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

QueueTwoStacks* CreateQueueTwoStacksMenu()
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
        ShowCreationError("Очередь");
    }
    return queue;
}

void AddElementToQueueTwoStacks(QueueTwoStacks* queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

    int value = GetValueForAddition();
    if (EnqueueQueueTwoStacks(queue, value))
    {
        ShowAddSuccess(value, "очередь");
    }
    else
    {
        ShowAddError("Очередь");
    }
}
void ExtractElementFromQueueTwoStacks(QueueTwoStacks* queue)
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

void ResizeQueueTwoStacksMenu(QueueTwoStacks*& queue)
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

void DeleteQueueTwoStacksMenu(QueueTwoStacks*& queue)
{
    bool wasDeleted = (queue != nullptr);
    if (wasDeleted)
    {
        DeleteQueueTwoStacks(queue);
        queue = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Очередь");
}

void HandleQueueTwoStacksMenu(QueueTwoStacks*& queue)
{
    int choice;
    do
    {
        cout << "\nОЧЕРЕДЬ (ДВА СТЕКА)" << endl;
        PrintQueueTwoStacksInfo(queue, "Текущая очередь на двух стеках");
        ShowQueueTwoStacksStructureMenu();
        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 1:
            if (CheckStructureNotExists(queue, "Очередь"))
            {
                queue = CreateQueueTwoStacksMenu();
            }
            break;
        case 2:
            AddElementToQueueTwoStacks(queue);
            break;
        case 3:
            ExtractElementFromQueueTwoStacks(queue);
            break;
        case 4:
            ResizeQueueTwoStacksMenu(queue);
            break;
        case 5:
            DeleteQueueTwoStacksMenu(queue);
            break;
        }
    } while (choice != 0);
}