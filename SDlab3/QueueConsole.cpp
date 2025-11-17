#include "QueueConsole.h"
#include "Validator.h"
#include "ConsoleService.h"
#include <iostream>
using namespace std;
/// <summary>
/// Отображает меню операций с очередью на кольцевом буфере
/// </summary>
void ShowQueueStructureMenu()
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать очередь" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить очередь" << endl;
}
/// <summary>
/// Выводит подробную информацию о состоянии очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="name">Название для отображения в заголовке</param>
void PrintQueueInfo(Queue* queue, const string& name)
{
    if (!CheckAndPrintHeader(queue, name))
    {
        return;
    }

    WriteFullEmptyInfo(IsQueueEmpty(queue), IsQueueFull(queue));
    WriteSpaceInfo(GetUsedSpace(queue->CircularBuffer), GetFreeSpaceQueue(queue));

    PrintContentHeader(IsQueueEmpty(queue), "Содержимое (начало -> конец)");

    if (!IsQueueEmpty(queue))
    {
        int capacity = GetUsedSpace(queue->CircularBuffer) + GetFreeSpaceQueue(queue);
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
            Enqueue(queue, Dequeue(tempQueue));
        }

        DeleteQueue(tempQueue);
    }
    cout << endl;
}
/// <summary>
/// Создает новую очередь с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданную очередь или nullptr при отмене</returns>
Queue* CreateQueueMenu()
{
    int capacity = GetValidatedCapacity("очередь");
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
        ShowCreationError("Очередь");
    }
    return queue;
}
/// <summary>
/// Добавляет элемент в очередь с запросом значения у пользователя
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void AddElementToQueue(Queue* queue)
{
    if (!CheckStructureExists(queue, "Очередь"))
    {
        return;
    }

    int value = GetValueForAddition();
    if (Enqueue(queue, value))
    {
        ShowAddSuccess(value, "Очередь");
    }
    else
    {
        ShowAddError("Очередь");
    }
}
/// <summary>
/// Извлекает элемент из очереди с отображением результата
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void ExtractElementFromQueue(Queue* queue)
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
/// <summary>
/// Изменяет размер очереди с запросом нового размера у пользователя
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void ResizeQueueMenu(Queue*& queue)
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
/// <summary>
/// Удаляет очередь с освобождением памяти
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void DeleteQueueMenu(Queue*& queue)
{
    bool wasDeleted = (queue != nullptr);
    if (wasDeleted)
    {
        DeleteQueue(queue);
        queue = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Очередь");
}
/// <summary>
/// Обрабатывает главное меню работы с очередью
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void HandleQueueMenu(Queue*& queue)
{
    int choice;
    do
    {
        cout << "\nОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)" << endl;
        PrintQueueInfo(queue, "Текущая очередь");
        ShowQueueStructureMenu();
        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 1:
        {
            if (CheckStructureNotExists(queue, "Очередь"))
            {
                queue = CreateQueueMenu();
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
            ResizeQueueMenu(queue);
            break;
        }     
        case 5:
        {
            DeleteQueueMenu(queue);
            break;
        }
        }
    } while (choice != 0);
}