#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "PerformanceTester.h"

using namespace std;

// Вспомогательные функции для вывода
void print_forward(const DoublyLinkedList<string>& list)
{
    std::cout << "List (forward): ";
    if (!list.print_forward())
    {
        std::cout << "List is empty!" << std::endl;
    }
}

void print_backward(const DoublyLinkedList<string>& list)
{
    std::cout << "List (backward): ";
    if (!list.print_backward())
    {
        std::cout << "List is empty!" << std::endl;
    }
}

static void printListEmptyMessage()
{
    cout << "List is empty!\n";
}

static void printElementOperation(const string& value, const string& operation, const string& position = "")
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

static void printElementFound(const string& value, bool found)
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

static void printCurrentListState(const DoublyLinkedList<string>& list)
{
    cout << "Current list: ";
    print_forward(list);
}

static int getNumericInput(const string& prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    try
    {
        return stoi(input);
    }
    catch (...)
    {
        cout << "Invalid input! Please enter a number.\n";
        return -1;
    }
}

// Функция для получения ввода (всегда строка)
string getInput(const string& prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Добавляем недостающие функции
static void handleAddOperation(DoublyLinkedList<string>& list, const string& position)
{
    string value = getInput("Enter value to add to " + position + ": ");
    if (position == "front")
    {
        list.push_front(value);
    }
    else
    {
        list.push_back(value);
    }
    printElementOperation(value, "added to", position);
}

static void handleRemoveEndOperation(DoublyLinkedList<string>& list, const string& position)
{
    if (!list.is_empty())
    {
        string removed = (position == "front") ? list.get_head()->data : list.get_tail()->data;
        if (position == "front")
        {
            list.pop_front();
        }
        else
        {
            list.pop_back();
        }
        printElementOperation(removed, "removed from", position);
    }
    else
    {
        printListEmptyMessage();
    }
}

// Вспомогательная функция для поиска элемента с обработкой ошибок
static ListNode<string>* findElementWithValidation(DoublyLinkedList<string>& list, const string& prompt)
{
    if (list.is_empty())
    {
        printListEmptyMessage();
        return nullptr;
    }

    string value = getInput(prompt);
    auto node = list.linear_search(value);

    if (!node)
    {
        cout << "Element '" << value << "' not found!\n";
    }

    return node;
}

static void handleInsertOperation(DoublyLinkedList<string>& list, const string& positionType)
{
    auto target_node = findElementWithValidation(list, "Enter target value to insert " + positionType + ": ");
    if (!target_node) return;

    string value = getInput("Enter value to insert: ");

    if (positionType == "after")
    {
        list.insert_after(target_node, value);
    }
    else
    {
        list.insert_before(target_node, value);
    }
    printElementOperation(value, "inserted " + positionType, target_node->data);
}

static void handleRemoveByValue(DoublyLinkedList<string>& list)
{
    auto node = findElementWithValidation(list, "Enter value to remove: ");
    if (!node) return;

    string value = node->data;
    list.remove(node);
    printElementOperation(value, "removed");
}

static void handleSearchOperation(DoublyLinkedList<string>& list)
{
    if (list.is_empty())
    {
        printListEmptyMessage();
        return;
    }

    string value = getInput("Enter value to search: ");
    auto node = list.linear_search(value);
    printElementFound(value, node != nullptr);
}

// Меню
static void displayMainMenu()
{
    cout << "\n=== Doubly Linked List Manager ===\n";
    cout << "1. List Operations\n";
    cout << "2. Performance Measurements\n";
    cout << "0. Exit\n";
}

static void displayListMenu()
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
    cout << "15. Back to main menu\n";
}

// Функция для работы со списком строк
void handleListOperations()
{
    DoublyLinkedList<string> list;
    int choice = 0;

    // Генерация начального списка
    cout << "Generating initial list with sample values...\n";
    string sampleData[] = { "56", "hello", "41", "world", "19", "test", "100", "data" };
    for (int i = 0; i < 6; i++)
    {
        list.push_back(sampleData[i]);
    }

    cout << "Initial list: ";
    print_forward(list);
    cout << "Note: All values are stored as strings, including numbers!\n";

    do
    {
        displayListMenu();
        choice = getNumericInput("Enter your choice: ");
        if (choice == -1) continue;

        switch (choice)
        {
        case 1:
            handleAddOperation(list, "front");
            break;

        case 2:
            handleAddOperation(list, "back");
            break;

        case 3:
            handleRemoveEndOperation(list, "front");
            break;

        case 4:
            handleRemoveEndOperation(list, "back");
            break;

        case 5:
            handleInsertOperation(list, "after");
            break;

        case 6:
            handleInsertOperation(list, "before");
            break;

        case 7:
            handleRemoveByValue(list);
            break;

        case 8:
            handleSearchOperation(list);
            break;

        case 9:
            if (!list.is_empty())
            {
                list.sort();
                cout << "List sorted successfully (lexicographical order).\n";
            }
            else
            {
                printListEmptyMessage();
            }
            break;

        case 10:
            list.clear();
            cout << "List cleared.\n";
            break;

        case 11:
            print_forward(list);
            break;

        case 12:
            print_backward(list);
            break;

        case 13:
            cout << "List size: " << list.get_size() << "\n";
            break;

        case 14:
            cout << "List is " << (list.is_empty() ? "empty" : "not empty") << "\n";
            break;

        case 15:
            cout << "Returning to main menu...\n";
            return;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

        // Показываем текущее состояние списка после операций
        if (choice >= 1 && choice <= 10 && !list.is_empty())
        {
            printCurrentListState(list);
        }

    } while (choice != 15);
}

void handlePerformanceMeasurements()
{
    auto results = PerformanceTester::performMeasurements();

    for (const auto& result : results)
    {
        cout << "--- Testing with list size: " << result.size << " ---" << endl;
        cout << "PushFront (avg): " << result.pushFrontTime << " ns" << endl;
        cout << "PushBack (avg): " << result.pushBackTime << " ns" << endl;
        cout << "PopFront (avg): " << result.popFrontTime << " ns" << endl;
        cout << "PopBack (avg): " << result.popBackTime << " ns" << endl;
        cout << "Search (avg): " << result.searchTime << " ns" << endl;
        cout << "Sort (avg): " << result.sortTime << " microseconds" << endl;
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
        displayMainMenu();
        mainChoice = getNumericInput("Enter your choice: ");
        if (mainChoice == -1) continue;

        switch (mainChoice)
        {
        case 1:
            cout << "\n--- List Operations ---\n";
            cout << "Working with strings. Examples: '56', 'hello', '41', 'test'\n";
            handleListOperations();
            break;

        case 2:
            cout << "\n--- Performance Measurements ---\n";
            handlePerformanceMeasurements();
            break;

        case 0:
            cout << "Thank you for using Doubly Linked List Manager. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (mainChoice != 0);

    return 0;
}