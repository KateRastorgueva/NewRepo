#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <climits>
#include "List.h"
#include "PerformanceTester.h"

using namespace std;
/// <summary>
/// Выводит фразу список пустой 
/// </summary>
void ShowIsEmpty(bool input)
{
    if (input)
    {
        cout << "List is empty!\n";
    }
    else
    {
        cout << "List is not empty!\n";
    }
}
/// <summary>
/// Проверяет, что список не пуст, и выводит сообщение если пуст
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
/// <returns>true если список не пуст, false если пуст</returns>
static bool ValidateListNotEmpty(const DoublyLinkedList& list)
{
    if (list.IsEmpty())
    {
        ShowIsEmpty(true);
        return false;
    }
    return true;
}

/// <summary>
/// Выводит элементы списка в указанном направлении
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
/// <param name="forward">true для прямого порядка, false для обратного</param>
void PrintList(const DoublyLinkedList& list, bool forward)
{
    if (!ValidateListNotEmpty(list))
    {
        return;
    }

    ListNode* current;

    if (forward == true)
    {
        current = list.GetHead();
    }
    else
    {
        current = list.GetTail();
    }
    while (current != nullptr)
    {
        cout << current->Data << " ";
        if (forward == true)
        {
            current = current->Next;
        }
        else
        {
            current = current->Previous;
        }
    }
    cout << endl;
}

/// <summary>
/// Выводит список в прямом порядке
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
void PrintForward(const DoublyLinkedList& list)
{
    cout << "List (forward): ";
    PrintList(list, true);
}

/// <summary>
/// Выводит список в обратном порядке
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
void PrintBackward(const DoublyLinkedList& list)
{
    cout << "List (backward): ";
    PrintList(list, false);
}

/// <summary>
/// Выводит сообщение о выполнении операции с элементом
/// </summary>
/// <param name="value">Значение элемента</param>
/// <param name="operation">Название операции</param>
/// <param name="position">Позиция операции (опционально)</param>
static void PrintElementOperation(const string& value, const string& operation, const string& position = "")
{
    if (position.empty())
    {
        cout << "Element '" << value << "' " << operation << ".\n";
    }
    else
    {
        cout << "Element '" << value << "' " << operation << " " << position << ".\n";
    }
}

/// <summary>
/// Выводит результат поиска элемента
/// </summary>
/// <param name="value">Искомое значение</param>
/// <param name="found">Результат поиска</param>
static void PrintElementFound(const string& value, bool found)
{
    if (found)
    {
        cout << "Element '" << value << "' found in the list.\n";
    }
    else
    {
        cout << "Element '" << value << "' not found!\n";
    }
}

/// <summary>
/// Выводит сообщение о неверном вводе
/// </summary>
static void InvalidInput()
{
    cout << "Invalid choice! Please try again.\n";
}

/// <summary>
/// Проверяет, является ли символ ASCII цифрой
/// </summary>
/// <param name="element">Проверяемый символ</param>
/// <returns>true если символ цифра, иначе false</returns>
static bool IsAsciiDigit(char element)
{
    return element >= '0' && element <= '9';
}

/// <summary>
/// Выводит сообщение об ошибке диапазона
/// </summary>
/// <param name="minValue">Минимальное допустимое значение</param>
/// <param name="maxValue">Максимальное допустимое значение</param>
static void PrintRangeError(int minValue, int maxValue)
{
    cout << "Please enter a number between " << minValue << " and " << maxValue << ".\n";
}

/// <summary>
/// Проверяет, содержит ли строка только цифры
/// </summary>
/// <param name="value">Проверяемая строка</param>
/// <param name="allowNegative">Разрешить отрицательные числа</param>
/// <returns>true если строка содержит только цифры, иначе false</returns>
static bool ContainsOnlyDigits(const string& value, bool allowNegative = false)
{
    for (int i = 0; i < value.length(); i++)
    {
        char element = value[i];
        if (!IsAsciiDigit(element))
        {
            if (!(allowNegative && i == 0 && element == '-'))
            {
                return false;
            }
        }
    }
    return true;
}

/// <summary>
/// Проверяет наличие ведущих нулей в строке
/// </summary>
/// <param name="value">Проверяемая строка</param>
/// <returns>true если есть ведущие нули, иначе false</returns>
static bool HasLeadingZeros(const string& value)
{
    if (value.length() > 1)
    {
        if (value[0] == '0')
        {
            return true;
        }
        if (value[0] == '-' && value[1] == '0')
        {
            return true;
        }
    }
    return false;
}

/// <summary>
/// Получает числовой ввод от пользователя с валидацией
/// </summary>
/// <param name="prompt">Приглашение для ввода</param>
/// <param name="minValue">Минимальное допустимое значение</param>
/// <param name="maxValue">Максимальное допустимое значение</param>
/// <returns>Введенное пользователем число</returns>
static int GetNumericInput(const string& prompt, int minValue = -2147483648, int maxValue = 2147483647)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "Empty input! Please enter a number.\n";
            continue;
        }

        bool allowNegative = (minValue < 0);
        if (!ContainsOnlyDigits(input, allowNegative) || HasLeadingZeros(input))
        {
            InvalidInput();
            continue;
        }

        try
        {
            long value = stol(input);
            if (value < minValue || value > maxValue)
            {
                PrintRangeError(minValue, maxValue);
                continue;
            }
            return value;
        }
        catch (const exception&)
        {
            InvalidInput();
        }
    }
}

/// <summary>
/// Получает строковый ввод от пользователя
/// </summary>
/// <param name="prompt">Приглашение для ввода</param>
/// <returns>Введенная пользователем строка</returns>
string GetInput(const string& prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

/// <summary>
/// Проверяет, является ли позиция "front"
/// </summary>
/// <param name="position">Проверяемая позиция</param>
/// <returns>true если позиция "front", иначе false</returns>
static bool IsFrontPosition(const string& position)
{
    return position == "front";
}

/// <summary>
/// Возвращает отображаемое имя позиции
/// </summary>
/// <param name="position">Позиция</param>
/// <returns>Отображаемое имя позиции</returns>
static string GetPositionDisplayName(const string& position)
{
    if (position == "front")
    {
        return "front";
    }
    else
    {
        return "back";
    }
}


/// <summary>
/// Обрабатывает операцию добавления элемента
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
/// <param name="position">Позиция добавления ("front" или "back")</param>
static void HandleAddOperation(DoublyLinkedList& list, const string& position)
{
    string value = GetInput("Enter value to add to " + GetPositionDisplayName(position) + ": ");
    if (IsFrontPosition(position))
    {
        list.PushFront(value);
    }
    else
    {
        list.PushBack(value);
    }
    PrintElementOperation(value, "added to", GetPositionDisplayName(position));
}

/// <summary>
/// Обрабатывает операцию удаления элемента с конца
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
/// <param name="position">Позиция удаления ("front" или "back")</param>
static void HandleRemoveEndOperation(DoublyLinkedList& list, const string& position)
{
    if (!ValidateListNotEmpty(list))
    {
        return;
    }

    string removed;
    if (IsFrontPosition(position) == true)
    {
        removed = list.GetHead()->Data;
    }
    else
    {
        removed = list.GetTail()->Data;
    }
    if (IsFrontPosition(position))
    {
        list.PopFront();
    }
    else
    {
        list.PopBack();
    }
    PrintElementOperation(removed, "removed from", GetPositionDisplayName(position));
}

/// <summary>
/// Находит элемент с валидацией списка
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
/// <param name="prompt">Приглашение для ввода</param>
/// <returns>Указатель на найденный узел или nullptr</returns>
static ListNode* FindElementWithValidation(DoublyLinkedList& list, const string& prompt)
{
    if (!ValidateListNotEmpty(list))
    {
        return nullptr;
    }

    string value = GetInput(prompt);
    ListNode* node = list.LinearSearch(value);

    if (!node)
    {
        cout << "Element '" << value << "' not found!\n";
    }

    return node;
}

/// <summary>
/// Обрабатывает операцию вставки элемента
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
/// <param name="positionType">Тип позиции ("after" или "before")</param>
static void HandleInsertOperation(DoublyLinkedList& list, const string& positionType)
{
    ListNode* targetNode = FindElementWithValidation(list, "Enter target value to insert " + positionType + ": ");
    if (!targetNode)
    {
        return;
    }

    string value = GetInput("Enter value to insert: ");

    if (positionType == "after")
    {
        list.InsertAfter(targetNode, value);
    }
    else
    {
        list.InsertBefore(targetNode, value);
    }
    PrintElementOperation(value, "inserted " + positionType, targetNode->Data);
}

/// <summary>
/// Обрабатывает операцию удаления элемента по значению
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
static void HandleRemoveByValue(DoublyLinkedList& list)
{
    ListNode* node = FindElementWithValidation(list, "Enter value to remove: ");
    if (!node)
    {
        return;
    }

    string value = node->Data;
    list.Remove(node);
    PrintElementOperation(value, "removed");
}

/// <summary>
/// Обрабатывает операцию поиска элемента
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
static void HandleSearchOperation(DoublyLinkedList& list)
{
    if (!ValidateListNotEmpty(list))
    {
        return;
    }

    string value = GetInput("Enter value to search: ");
    ListNode* node = list.LinearSearch(value);
    PrintElementFound(value, node != nullptr);
}


/// <summary>
/// Отображает главное меню
/// </summary>
static void DisplayMainMenu()
{
    cout << "\n     Doubly Linked List Manager\n";
    cout << "1. List Operations\n";
    cout << "2. Performance Measurements\n";
    cout << "0. Exit\n";
}

/// <summary>
/// Отображает меню операций со списком
/// </summary>
static void DisplayListMenu()
{
    cout << "\n    List Operations \n";
    cout << "1. Add element to front\n";
    cout << "2. Add element to back\n";
    cout << "3. Remove element from front\n";
    cout << "4. Remove element from back\n";
    cout << "5. Insert after element\n";
    cout << "6. Insert before element\n";
    cout << "7. Remove specific element\n";
    cout << "8. Search for element\n";
    cout << "9. Sort list\n";
    cout << "10. Clear list\n";
    cout << "11. Display list forward\n";
    cout << "12. Display list backward\n";
    cout << "13. Display list size\n";
    cout << "14. Check if list is empty\n";
    cout << "15. Display current list state\n";
    cout << "16. Back to main menu\n";
}

/// <summary>
/// Выводит текущее состояние списка
/// </summary>
/// <param name="list">Ссылка на двусвязный список</param>
static void PrintCurrentListState(const DoublyLinkedList& list)
{
    cout << "Current list state:\n";
    cout << "Size: " << list.GetSize() << "\n";
    PrintForward(list);
}

/// <summary>
/// Обрабатывает операции со списком
/// </summary>
void HandleListOperations()
{
    DoublyLinkedList list;
    int choice = 0;

    cout << "Generating initial list with sample values...\n";
    string sampleData[] = { "56", "hello", "41", "world", "19", "test", "100", "data" };
    for (int i = 0; i < 6; i++)
    {
        list.PushBack(sampleData[i]);
    }

    PrintCurrentListState(list);

    do
    {
        DisplayListMenu();
        choice = GetNumericInput("Enter your choice: ", 1, 16);

        switch (choice)
        {
        case 1:
        {
            HandleAddOperation(list, "front");
            break;
        }
        case 2:
        {
            HandleAddOperation(list, "back");
            break;
        }
        case 3:
        {
            HandleRemoveEndOperation(list, "front");
            break;
        }
        case 4:
        {
            HandleRemoveEndOperation(list, "back");
            break;
        }
        case 5:
        {
            HandleInsertOperation(list, "after");
            break;
        }
        case 6:
        {
            HandleInsertOperation(list, "before");
            break;
        }
        case 7:
        {
            HandleRemoveByValue(list);
            break;
        }
        case 8:
        {
            HandleSearchOperation(list);
            break;
        }
        case 9:
        {
            if (!ValidateListNotEmpty(list))
            {
                break;
            }
            list.Sort();
            cout << "List sorted successfully.\n";
            break;
        }
        case 10:
        {
            list.Clear();
            cout << "List cleared.\n";
            break;
        }
        case 11:
        {
            PrintForward(list);
            break;
        }
        case 12:
        {
            PrintBackward(list);
            break;
        }
        case 13:
        {
            cout << "List size: " << list.GetSize() << "\n";
            break;
        }
        case 14:
        {
            if (list.IsEmpty() == true)
            {
                ShowIsEmpty(true);
            }
            else
            {
                ShowIsEmpty(false);
            }
            break;
        }
        case 15:
        {
            PrintCurrentListState(list);
            break;
        }
        case 16:
        {
            cout << "Returning to main menu...\n";
            return;
        }
        default:
        {
            InvalidInput();
        }
        }

        if (choice >= 1 && choice <= 10)
        {
            PrintCurrentListState(list);
        }

    } while (choice != 16);
}

/// <summary>
/// Обрабатывает измерения производительности
/// </summary>
void HandlePerformanceMeasurements()
{
    int resultsCount;
    MeasurementResults* results = PerformanceTester::PerformMeasurements(resultsCount);

    for (int i = 0; i < resultsCount; i++)
    {
        cout << "--- Testing with list size: " << results[i].Size << " ---" << endl;
        cout << "PushFront (avg): " << results[i].PushFrontTime << " ns" << endl;
        cout << "PushBack (avg): " << results[i].PushBackTime << " ns" << endl;
        cout << "PopFront (avg): " << results[i].PopFrontTime << " ns" << endl;
        cout << "PopBack (avg): " << results[i].PopBackTime << " ns" << endl;
        cout << "Search (avg): " << results[i].SearchTime << " ns" << endl;
        cout << "Sort (avg): " << results[i].SortTime << " microseconds" << endl;
        cout << endl;
    }
}


/// <summary>
/// Главная функция приложения
/// </summary>
/// <returns>Код завершения программы</returns>
int main()
{
    srand(time(0));
    int mainChoice = 0;

    cout << "All data is stored as strings. You can mix numbers and text!\n";

    do
    {
        DisplayMainMenu();
        mainChoice = GetNumericInput("Enter your choice: ", 0, 2);

        switch (mainChoice)
        {
        case 1:
        {
            cout << "\n    List Operations\n";
            cout << "Working with strings. Examples: '56', 'hello', '41', 'test'\n";
            HandleListOperations();
            break;
        }
        case 2:
        {
            cout << "\n   Performance Measurements\n";
            HandlePerformanceMeasurements();
            break;
        }
        case 0:
        {
            cout << "Thank you for using Doubly Linked List Manager. Goodbye!\n";
            break;
        }
        }

    } while (mainChoice != 0);

    return 0;
}