#include "CircularBufferConsole.h"
#include "Validator.h"
#include "ConsoleService.h"
#include <iostream>
using namespace std;

/// <summary>
/// Отображает меню операций с кольцевым буфером
/// </summary>
void ShowCircularBufferStructureMenu()
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать кольцевой буфер" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить кольцевой буфер" << endl;
}
/// <summary>
/// Выводит подробную информацию о состоянии кольцевого буфера
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="name">Название для отображения в заголовке</param>
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
/// <summary>
/// Создает новый кольцевой буфер с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданный буфер или nullptr при отмене</returns>
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
CircularBuffer* CreateCircularBufferMenu();

/// <summary>
/// Добавляет элемент в кольцевой буфер с запросом значения у пользователя
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
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
/// <summary>
/// Извлекает элемент из кольцевого буфера с отображением результата
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
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
/// <summary>
/// Изменяет размер кольцевого буфера с запросом нового размера у пользователя
/// </summary>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
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
/// <summary>
/// Удаляет кольцевой буфер с освобождением памяти
/// </summary>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
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
/// <summary>
/// Обрабатывает главное меню работы с кольцевым буфером
/// </summary>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
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