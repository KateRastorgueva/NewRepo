#include "CircularBufferConsole.h"
#include "Validator.h"
#include "ConsoleService.h"
#include <iostream>
using namespace std;

void ShowCircularBufferStructureMenu()
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать кольцевой буфер" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить кольцевой буфер" << endl;
}

void PrintCircularBufferInfo(CircularBuffer* circularBuffer, const string& name)
{
    if (!CheckAndPrintHeader(circularBuffer, name))
    {
        return;
    }

    WriteCircularBufferInfo(circularBuffer->Capacity, circularBuffer->Head, circularBuffer->Tail, circularBuffer->Count);
    WriteFullEmptyInfo(IsCircularBufferEmpty(circularBuffer), GetFreeSpaceCircular(circularBuffer) == 0);
    WriteSpaceInfo(GetUsedSpace(circularBuffer), GetFreeSpaceCircular(circularBuffer));

    PrintContentHeader(IsCircularBufferEmpty(circularBuffer), "Содержимое (начало -> конец)");

    if (!IsCircularBufferEmpty(circularBuffer))
    {
        for (int i = 0; i < circularBuffer->Count; i++)
        {
            int index = (circularBuffer->Head + i) % circularBuffer->Capacity;
            cout << circularBuffer->Buffer[index];
            if (i < circularBuffer->Count - 1)
            {
                cout << " -> ";
            }
        }
    }
    cout << endl << endl;
}

CircularBuffer* CreateCircularBufferMenu()
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
        ShowCreationError("Кольцевой буфер");
    }
    return circularBuffer;
}

void AddElementToCircularBuffer(CircularBuffer* circularBuffer)
{
    if (!CheckStructureExists(circularBuffer, "Кольцевой буфер"))
    {
        return;
    }

    int value = GetValueForAddition();
    if (EnqueueCircularBuffer(circularBuffer, value))
    {
        ShowAddSuccess(value, "Кольцевой буфер");
    }
    else
    {
        ShowAddError("Кольцевой буфер");
    }
}

void ExtractElementFromCircularBuffer(CircularBuffer* circularBuffer)
{
    if (!CheckStructureExists(circularBuffer, "Кольцевой буфер"))
    {
        return;
    }

    if (CheckStructureEmpty(IsCircularBufferEmpty(circularBuffer), "Кольцевой буфер"))
    {
        return;
    }

    int value = DequeueCircularBuffer(circularBuffer);
    ShowExtractedElement(value);
}

void ResizeCircularBufferMenu(CircularBuffer*& circularBuffer)
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

void DeleteCircularBufferMenu(CircularBuffer*& circularBuffer)
{
    bool wasDeleted = (circularBuffer != nullptr);
    if (wasDeleted)
    {
        DeleteCircularBuffer(circularBuffer);
        circularBuffer = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Кольцевой буфер");
}

void HandleCircularBufferMenu(CircularBuffer*& circularBuffer)
{
    int choice;
    do
    {
        cout << "\nКОЛЬЦЕВОЙ БУФЕР" << endl;
        PrintCircularBufferInfo(circularBuffer, "Текущий кольцевой буфер");
        ShowCircularBufferStructureMenu();
        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 1:
            if (CheckStructureNotExists(circularBuffer, "Кольцевой буфер"))
            {
                circularBuffer = CreateCircularBufferMenu();
            }
            break;
        case 2:
            AddElementToCircularBuffer(circularBuffer);
            break;
        case 3:
            ExtractElementFromCircularBuffer(circularBuffer);
            break;
        case 4:
            ResizeCircularBufferMenu(circularBuffer);
            break;
        case 5:
            DeleteCircularBufferMenu(circularBuffer);
            break;
        }
    } while (choice != 0);
}