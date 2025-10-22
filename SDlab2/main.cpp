#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "PerformanceTester.h"
#include <cctype>

using namespace std;

// Вспомогательные функции для вывода
void PrintForward(const DoublyLinkedList<string>& list)
{
    cout << "List (forward): ";
    if (!list.PrintForward())
    {
        cout << "List is empty!" << endl;
    }
}

void PrintBackward(const DoublyLinkedList<string>& list)
{
    cout << "List (backward): ";
    if (!list.PrintBackward())
    {
        cout << "List is empty!" << endl;
    }
}

static void PrintListEmptyMessage()
{
    cout << "List is empty!\n";
}

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

static void PrintCurrentListState(const DoublyLinkedList<string>& list)
{
    cout << "Current list: ";
    PrintForward(list);
}

static int GetNumericInput(const string& prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);

    for (char c : input) {
        if (c < '0' || c > '9') {
            cout << "Invalid input! Please enter digits only.\n";
            return -1;
        }
    }

    try {
        return stoi(input);
    }
    catch (exception& e) {
        cout << "Invalid input! Please enter digits only.\n";
        return -1;
    }
}

// Функция для получения ввода (всегда строка)
string GetInput(const string& prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Добавляем недостающие функции
static void HandleAddOperation(DoublyLinkedList<string>& list, const string& position)
{
    string value = GetInput("Enter value to add to " + position + ": ");
    if (position == "front")
    {
        list.PushFront(value);
    }
    else
    {
        list.PushBack(value);
    }
    PrintElementOperation(value, "added to", position);
}

static void HandleRemoveEndOperation(DoublyLinkedList<string>& list, const string& position)
{
    if (!list.IsEmpty())
    {
        string removed = (position == "front") ? list.GetHead()->Data : list.GetTail()->Data;
        if (position == "front")
        {
            list.PopFront();
        }
        else
        {
            list.PopBack();
        }
        PrintElementOperation(removed, "removed from", position);
    }
    else
    {
        PrintListEmptyMessage();
    }
}

// Вспомогательная функция для поиска элемента с обработкой ошибок
static ListNode<string>* FindElementWithValidation(DoublyLinkedList<string>& list, const string& prompt)
{
    if (list.IsEmpty())
    {
        PrintListEmptyMessage();
        return nullptr;
    }

    string value = GetInput(prompt);
    auto node = list.LinearSearch(value);

    if (!node)
    {
        cout << "Element '" << value << "' not found!\n";
    }

    return node;
}

static void HandleInsertOperation(DoublyLinkedList<string>& list, const string& positionType)
{
    auto targetNode = FindElementWithValidation(list, "Enter target value to insert " + positionType + ": ");
    if (!targetNode) return;

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

static void HandleRemoveByValue(DoublyLinkedList<string>& list)
{
    auto node = FindElementWithValidation(list, "Enter value to remove: ");
    if (!node) return;

    string value = node->Data;
    list.Remove(node);
    PrintElementOperation(value, "removed");
}

static void HandleSearchOperation(DoublyLinkedList<string>& list)
{
    if (list.IsEmpty())
    {
        PrintListEmptyMessage();
        return;
    }

    string value = GetInput("Enter value to search: ");
    auto node = list.LinearSearch(value);
    PrintElementFound(value, node != nullptr);
}

// Меню
static void DisplayMainMenu()
{
    cout << "\n=== Doubly Linked List Manager ===" << endl;
    cout << "1. List Operations" << endl;
    cout << "2. Performance Measurements" << endl;
    cout << "0. Exit" << endl;
}

static void DisplayListMenu()
{
    cout << "\n=== List Operations ===" << endl;
    cout << "1. Add element to front" << endl;
    cout << "2. Add element to back" << endl;
    cout << "3. Remove element from front" << endl;
    cout << "4. Remove element from back" << endl;
    cout << "5. Insert after element" << endl;
    cout << "6. Insert before element" << endl;
    cout << "7. Remove specific element" << endl;
    cout << "8. Search for element" << endl;
    cout << "9. Sort list" << endl;
    cout << "10. Clear list" << endl;
    cout << "11. Display list forward" << endl;
    cout << "12. Display list backward" << endl;
    cout << "13. Display list size" << endl;
    cout << "14. Check if list is empty" << endl;
    cout << "15. Back to main menu" << endl;
}

// Функция для работы со списком строк
void HandleListOperations()
{
    DoublyLinkedList<string> list;
    int choice = 0;

    // Генерация начального списка
    cout << "Generating initial list with sample values..." << endl;
    string sampleData[] = { "56", "hello", "41", "world", "19", "test", "100", "data" };
    for (int i = 0; i < 6; i++)
    {
        list.PushBack(sampleData[i]);
    }

    cout << "Initial list: ";
    PrintForward(list);
    cout << "Note: All values are stored as strings, including numbers!" << endl;

    do
    {
        DisplayListMenu();
        choice = GetNumericInput("Enter your choice: ");
        if (choice == -1) continue;

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
            if (!list.IsEmpty())
            {
                list.Sort();
                cout << "List sorted successfully (lexicographical order)." << endl;
            }
            else
            {
                PrintListEmptyMessage();
            }
            break;
        }

        case 10:
        {
            list.Clear();
            cout << "List cleared." << endl;
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
            cout << "List size: " << list.GetSize() << endl;
            break;
        }

        case 14:
        {
            cout << "List is " << (list.IsEmpty() ? "empty" : "not empty") << endl;
            break;
        }

        case 15:
        {
            cout << "Returning to main menu..." << endl;
            return;
        }

        default:
        {
            cout << "Invalid choice! Please try again." << endl;
        }
        }

        // Показываем текущее состояние списка после операций
        if (choice >= 1 && choice <= 10 && !list.IsEmpty())
        {
            PrintCurrentListState(list);
        }

    } while (choice != 15);
}

void HandlePerformanceMeasurements()
{
    int resultsCount;
    auto results = PerformanceTester::PerformMeasurements(resultsCount);

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

int main()
{
    srand(time(0));
    int mainChoice = 0;

    cout << "=== Doubly Linked List Manager ===" << endl;
    cout << "All data is stored as strings. You can mix numbers and text!" << endl;

    do
    {
        DisplayMainMenu();
        mainChoice = GetNumericInput("Enter your choice: ");
        if (mainChoice == -1) continue;

        switch (mainChoice)
        {
        case 1:
        {
            cout << "\n--- List Operations ---" << endl;
            cout << "Working with strings. Examples: '56', 'hello', '41', 'test'" << endl;
            HandleListOperations();
            break;
        }

        case 2:
        {
            cout << "\n--- Performance Measurements ---" << endl;
            HandlePerformanceMeasurements();
            break;
        }

        case 0:
        {
            cout << "Thank you for using Doubly Linked List Manager. Goodbye!" << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice! Please try again." << endl;
        }
        }

    } while (mainChoice != 0);

    return 0;
}