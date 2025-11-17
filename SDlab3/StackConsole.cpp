#include "StackConsole.h"
#include "Validator.h"
#include "ConsoleService.h"
#include <iostream>
using namespace std;

/// <summary>
/// Отображает меню операций со стеком
/// </summary>
void ShowStackStructureMenu()
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать стек" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить стек" << endl;
}
/// <summary>
/// Выводит подробную информацию о состоянии стека
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="name">Название для отображения в заголовке</param>
void PrintStackInfo(Stack* stack, const string& name)
{
    if (!CheckAndPrintHeader(stack, name))
    {
        return;
    }

    WriteInfo(stack->Capacity, stack->Top);
    WriteFullEmptyInfo(IsEmpty(stack), IsFull(stack));

    PrintContentHeader(IsEmpty(stack), "Содержимое (сверху вниз)");

    if (!IsEmpty(stack))
    {
        Stack* tempStack = CreateStack(stack->Capacity);
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

/// <summary>
/// Создает новый стек с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданный стек или nullptr при отмене</returns>
Stack* CreateStackMenu()
{
    int capacity = GetValidatedCapacity("стек");
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
        ShowCreationError("Стек");
    }
    return stack;
}
/// <summary>
/// Добавляет элемент в стек с запросом значения у пользователя
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void AddElementToStack(Stack* stack)
{
    if (!CheckStructureExists(stack, "Стек"))
    {
        return;
    }

    int value = GetValueForAddition();
    if (Push(stack, value))
    {
        ShowAddSuccess(value, "Стек");
    }
    else
    {
        ShowAddError("Стек");
    }
}
/// <summary>
/// Извлекает элемент из стека с отображением результата
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void ExtractElementFromStack(Stack* stack)
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
/// <summary>
/// Изменяет размер стека с запросом нового размера у пользователя
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void ResizeStackMenu(Stack*& stack)
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
/// <summary>
/// Удаляет стек с освобождением памяти
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void DeleteStackMenu(Stack*& stack)
{
    bool wasDeleted = (stack != nullptr);
    if (wasDeleted)
    {
        DeleteStack(stack);
        stack = nullptr;
    }
    ShowDeleteMessage(wasDeleted, "Стек");
}
/// <summary>
/// Обрабатывает главное меню работы со стеком
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void HandleStackMenu(Stack*& stack)
{
    int choice;
    do
    {
        cout << "\nРАБОТА СО СТЕКОМ" << endl;
        PrintStackInfo(stack, "Текущий стек");
        ShowStackStructureMenu();
        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 1: 
        {
            if (CheckStructureNotExists(stack, "Стек"))
            {
                stack = CreateStackMenu();
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
            ResizeStackMenu(stack);
            break;
        }
        case 5: 
        {
            DeleteStackMenu(stack);
            break;
        } 
        }
    } while (choice != 0);
}