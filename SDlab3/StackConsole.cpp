#include "StackConsole.h"
#include "Validator.h"
#include "ConsoleService.h"
#include <iostream>
using namespace std;

void ShowStackStructureMenu()
{
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать стек" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Извлечь элемент" << endl;
    cout << "4 - Изменить размер" << endl;
    cout << "5 - Удалить стек" << endl;
}

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
            if (CheckStructureNotExists(stack, "Стек"))
            {
                stack = CreateStackMenu();
            }
            break;
        case 2:
            AddElementToStack(stack);
            break;
        case 3:
            ExtractElementFromStack(stack);
            break;
        case 4:
            ResizeStackMenu(stack);
            break;
        case 5:
            DeleteStackMenu(stack);
            break;
        }
    } while (choice != 0);
}