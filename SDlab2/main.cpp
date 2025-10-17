#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "PerformanceTester.h"

using namespace std;

// Функции для вывода списков
void print_forward(const DoublyLinkedList<string>& list) {
    if (list.is_empty()) {
        cout << "List is empty!" << endl;
        return;
    }

    ListNode<string>* current = list.get_head();
    cout << "List (forward): ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void print_backward(const DoublyLinkedList<string>& list) {
    if (list.is_empty()) {
        cout << "List is empty!" << endl;
        return;
    }

    ListNode<string>* current = list.get_tail();
    cout << "List (backward): ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}

static void displayMainMenu() {
    cout << "\n=== Doubly Linked List Manager ===\n";
    cout << "1. List Operations\n";
    cout << "2. Performance Measurements\n";
    cout << "3. Individual Operation Tests\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

static void displayListMenu() {
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
    cout << "Enter your choice: ";
}

// Функция для получения ввода (всегда строка)
string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Функция для работы со списком строк
void handleListOperations() {
    DoublyLinkedList<string> list;
    int choice = 0;

    // Генерация начального списка со строками (включая числа как строки)
    cout << "Generating initial list with sample values...\n";

    string sampleData[] = { "56", "hello", "41", "world", "19", "test", "100", "data" };
    for (int i = 0; i < 6; i++) {
        list.push_back(sampleData[i]);
    }

    cout << "Initial list: ";
    print_forward(list);
    cout << "Note: All values are stored as strings, including numbers!\n";

    do {
        displayListMenu();

        string choiceStr = getInput("Enter your choice: ");
        try {
            choice = stoi(choiceStr);
        }
        catch (...) {
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            string value = getInput("Enter value to add to front: ");
            list.push_front(value);
            cout << "Element '" << value << "' added to front.\n";
            break;
        }

        case 2: {
            string value = getInput("Enter value to add to back: ");
            list.push_back(value);
            cout << "Element '" << value << "' added to back.\n";
            break;
        }

        case 3:
            if (!list.is_empty()) {
                string removed = list.get_head()->data;
                list.pop_front();
                cout << "Element '" << removed << "' removed from front.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 4:
            if (!list.is_empty()) {
                string removed = list.get_tail()->data;
                list.pop_back();
                cout << "Element '" << removed << "' removed from back.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 5: {
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string target = getInput("Enter target value to insert after: ");
            string value = getInput("Enter value to insert: ");

            auto node = list.linear_search(target);
            if (node) {
                list.insert_after(node, value);
                cout << "Element '" << value << "' inserted after '" << target << "'.\n";
            }
            else {
                cout << "Target element '" << target << "' not found!\n";
            }
            break;
        }

        case 6: {
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string target = getInput("Enter target value to insert before: ");
            string value = getInput("Enter value to insert: ");

            auto node = list.linear_search(target);
            if (node) {
                list.insert_before(node, value);
                cout << "Element '" << value << "' inserted before '" << target << "'.\n";
            }
            else {
                cout << "Target element '" << target << "' not found!\n";
            }
            break;
        }

        case 7: {
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string value = getInput("Enter value to remove: ");

            auto node = list.linear_search(value);
            if (node) {
                list.remove(node);
                cout << "Element '" << value << "' removed.\n";
            }
            else {
                cout << "Element '" << value << "' not found!\n";
            }
            break;
        }

        case 8: {
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string value = getInput("Enter value to search: ");

            auto node = list.linear_search(value);
            if (node) {
                cout << "Element '" << value << "' found in the list.\n";
            }
            else {
                cout << "Element '" << value << "' not found!\n";
            }
            break;
        }

        case 9:
            if (!list.is_empty()) {
                list.sort();
                cout << "List sorted successfully (lexicographical order).\n";
            }
            else {
                cout << "List is empty!\n";
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
        if (choice >= 1 && choice <= 10 && !list.is_empty()) {
            cout << "Current list: ";
            print_forward(list);
        }

    } while (choice != 15);
}

int main() {
    srand(time(0));
    int mainChoice = 0;

    cout << "=== Doubly Linked List Manager ===\n";
    cout << "All data is stored as strings. You can mix numbers and text!\n";

    do {
        displayMainMenu();

        string choiceStr;
        cout << "Enter your choice: ";
        getline(cin, choiceStr);

        try {
            mainChoice = stoi(choiceStr);
        }
        catch (...) {
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (mainChoice) {
        case 1:
            cout << "\n--- List Operations ---\n";
            cout << "Working with strings. Examples: '56', 'hello', '41', 'test'\n";
            handleListOperations();
            break;

        case 2:
            cout << "\n--- Performance Measurements ---\n";
            PerformanceTester::performMeasurements();
            break;

        case 3:
            cout << "\n--- Individual Operation Tests ---\n";
            PerformanceTester::measureIndividualOperations();
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