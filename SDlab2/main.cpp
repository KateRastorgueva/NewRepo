#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <climits>
#include "List.h"
#include "PerformanceTester.h"

using namespace std;

static void PrintListEmptyMessage()
{
    cout << "List is empty!\n";
}

void PrintList(const DoublyLinkedList<string>& list, bool forward)
{
    if (list.IsEmpty())
    {
        PrintListEmptyMessage();
        return;
    }

    ListNode<string>* current = forward ? list.GetHead() : list.GetTail();
    while (current != nullptr)
    {
        cout << current->Data << " ";
        current = forward ? current->Next : current->Previous;
    }
    cout << endl;
}

void PrintForward(const DoublyLinkedList<string>& list)
{
    cout << "List (forward): ";
    PrintList(list, true);
}

void PrintBackward(const DoublyLinkedList<string>& list)
{
    cout << "List (backward): ";
    PrintList(list, false);
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

static void InvalidInputNeedDigit()
{
    cout << "Invalid input! Please enter digits only.\n";
}

static void InvalidInput()
{
    cout << "Invalid choice! Please try again.\n";
}

static int GetNumericInput(const string& prompt, int minValue = INT_MIN, int maxValue = INT_MAX, bool singleDigitOnly = true)
{
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            cout << "Empty input! Please enter a number.\n";
            continue;
        }

        // Для меню проверяем, что ввод состоит ровно из одной цифры
        if (singleDigitOnly && input.length() > 1) {
            cout << "Invalid input! Please enter a single digit.\n";
            continue;
        }

        // Проверяем, что ввод состоит только из цифр и возможного минуса в начале
        bool isValid = true;
        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];
            // Проверяем, что символ находится в допустимом диапазоне для isdigit
            if (static_cast<unsigned char>(c) > 127) {
                cout << "Invalid input! Please enter digits only.\n";
                isValid = false;
                break;
            }

            if (!isdigit(static_cast<unsigned char>(c)) && !(i == 0 && c == '-')) {
                cout << "Invalid input! Please enter digits only.\n";
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            continue;
        }

        try {
            long value = stol(input);
            if (value < minValue || value > maxValue) {
                cout << "Number out of range! Please enter between "
                    << minValue << " and " << maxValue << ".\n";
                continue;
            }
            return static_cast<int>(value);
        }
        catch (const out_of_range&) {
            cout << "Number too large! Please enter a smaller number.\n";
        }
        catch (const exception&) {
            cout << "Invalid input! Please enter a valid number.\n";
        }
    }
}

string GetInput(const string& prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

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

static ListNode<string>* FindElementWithValidation(DoublyLinkedList<string>& list, const string& prompt)
{
    if (list.IsEmpty())
    {
        PrintListEmptyMessage();
        return nullptr;
    }

    string value = GetInput(prompt);
    ListNode<string>* node = list.LinearSearch(value);

    if (!node)
    {
        cout << "Element '" << value << "' not found!\n";
    }

    return node;
}

static void HandleInsertOperation(DoublyLinkedList<string>& list, const string& positionType)
{
    ListNode<string>* targetNode = FindElementWithValidation(list, "Enter target value to insert " + positionType + ": ");
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

static void HandleRemoveByValue(DoublyLinkedList<string>& list)
{
    ListNode<string>* node = FindElementWithValidation(list, "Enter value to remove: ");
    if (!node)
    {
        return;
    }

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
    ListNode<string>* node = list.LinearSearch(value);
    PrintElementFound(value, node != nullptr);
}

static void DisplayMainMenu()
{
    cout << "\n=== Doubly Linked List Manager ===\n";
    cout << "1. List Operations\n";
    cout << "2. Performance Measurements\n";
    cout << "0. Exit\n";
}

static void DisplayListMenu()
{
    cout << "\n=== List Operations ===\n";
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
static void PrintCurrentListState(const DoublyLinkedList<string>& list)
{
    cout << "Current list state:\n";
    cout << "Size: " << list.GetSize() << "\n";
    PrintForward(list);
}
void HandleListOperations()
{
    DoublyLinkedList<string> list;
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
        choice = GetNumericInput("Enter your choice: ", 1, 16, true);
        if (choice == -1)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                HandleAddOperation(list, "front");
                PrintCurrentListState(list);
                break;
            }

            case 2:
            {
                HandleAddOperation(list, "back");
                PrintCurrentListState(list);
                break;
            }

            case 3:
            {
                HandleRemoveEndOperation(list, "front");
                PrintCurrentListState(list);
                break;
            }

            case 4:
            {
                HandleRemoveEndOperation(list, "back");
                PrintCurrentListState(list);
                break;
            }

            case 5:
            {
                HandleInsertOperation(list, "after");
                PrintCurrentListState(list);
                break;
            }

            case 6:
            {
                HandleInsertOperation(list, "before");
                PrintCurrentListState(list);
                break;
            }

            case 7:
            {
                HandleRemoveByValue(list);
                PrintCurrentListState(list);
                break;
            }

            case 8:
            {
                HandleSearchOperation(list);
                PrintCurrentListState(list);
                break;
            }

            case 9:
            {
                if (!list.IsEmpty())
                {
                    list.Sort();
                    cout << "List sorted successfully (lexicographical order).\n";
                    PrintCurrentListState(list);
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
                cout << "List cleared.\n";
                PrintCurrentListState(list);
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
                cout << "List is " << (list.IsEmpty() ? "empty" : "not empty") << "\n";
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
    } while (choice != 16);
}

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

int main()
{
    srand(time(0));
    int mainChoice = 0;

    cout << "=== Doubly Linked List Manager ===\n";
    cout << "All data is stored as strings. You can mix numbers and text!\n";

    do
    {
        DisplayMainMenu();
        mainChoice = GetNumericInput("Enter your choice: ", 0, 2, true);

        switch (mainChoice)
        {
        case 1:
        {
            cout << "\n--- List Operations ---\n";
            cout << "Working with strings. Examples: '56', 'hello', '41', 'test'\n";
            HandleListOperations();
            break;
        }

        case 2:
        {
            cout << "\n--- Performance Measurements ---\n";
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