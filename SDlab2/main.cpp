// SDlab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

static void displayMainMenu() {
    cout << "\n=== Doubly Linked List Operations ===\n";
    cout << "1. Work with integer list\n";
    cout << "2. Work with string list\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

static void displayListMenu(const string& listType) {
    cout << "\n=== " << listType << " List Operations ===\n";
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

template<typename T>
void handleListOperations(DoublyLinkedList<T>& list, const string& listType);

// Специализация для int
template<>
void handleListOperations<int>(DoublyLinkedList<int>& list, const string& listType) {
    int choice = 0;

    // Генерация начального списка
    cout << "Generating initial list with random values...\n";
    for (int i = 0; i < 5; i++) {
        int randomValue = rand() % 100 + 1; // случайные числа от 1 до 100
        list.push_back(randomValue);
    }
    cout << "Initial list: ";
    list.print_forward();

    do {
        displayListMenu(listType);
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add to front
            int value = 0;
            cout << "Enter value to add to front: ";
            cin >> value;
            list.push_front(value);
            cout << "Element added to front.\n";
            break;
        }

        case 2: {
            // Add to back
            int value = 0;
            cout << "Enter value to add to back: ";
            cin >> value;
            list.push_back(value);
            cout << "Element added to back.\n";
            break;
        }

        case 3:
            // Remove from front
            if (!list.is_empty()) {
                list.pop_front();
                cout << "Element removed from front.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 4:
            // Remove from back
            if (!list.is_empty()) {
                list.pop_back();
                cout << "Element removed from back.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 5: {
            // Insert after element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            int target = 0, value = 0;
            cout << "Enter target value to insert after: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            auto node = list.linear_search(target);
            if (node) {
                list.insert_after(node, value);
                cout << "Element inserted after " << target << ".\n";
            }
            else {
                cout << "Target element not found!\n";
            }
            break;
        }

        case 6: {
            // Insert before element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            int target = 0, value = 0;
            cout << "Enter target value to insert before: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            auto node = list.linear_search(target);
            if (node) {
                list.insert_before(node, value);
                cout << "Element inserted before " << target << ".\n";
            }
            else {
                cout << "Target element not found!\n";
            }
            break;
        }

        case 7: {
            // Remove specific element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            int value = 0;
            cout << "Enter value to remove: ";
            cin >> value;
            auto node = list.linear_search(value);
            if (node) {
                list.remove(node);
                cout << "Element " << value << " removed.\n";
            }
            else {
                cout << "Element not found!\n";
            }
            break;
        }

        case 8: {
            // Search for element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            int value = 0;
            cout << "Enter value to search: ";
            cin >> value;
            auto node = list.linear_search(value);
            if (node) {
                cout << "Element " << value << " found in the list.\n";
            }
            else {
                cout << "Element " << value << " not found!\n";
            }
            break;
        }

        case 9:
            // Sort list
            if (!list.is_empty()) {
                list.sort();
                cout << "List sorted successfully.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 10:
            // Clear list
            list.clear();
            cout << "List cleared.\n";
            break;

        case 11:
            // Display forward
            if (!list.is_empty()) {
                cout << "List (forward): ";
                list.print_forward();
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 12:
            // Display backward
            if (!list.is_empty()) {
                cout << "List (backward): ";
                list.print_backward();
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 13:
            // Display size
            cout << "List size: " << list.get_size() << "\n";
            break;

        case 14:
            // Check if empty
            cout << "List is " << (list.is_empty() ? "empty" : "not empty") << "\n";
            break;

        case 15:
            // Back to main menu
            cout << "Returning to main menu...\n";
            return;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

        // Show current list state after each operation
        if (choice >= 1 && choice <= 10 && !list.is_empty()) {
            cout << "Current list state: ";
            list.print_forward();
        }
        cout << "Current list: ";
        list.print_forward();

    } while (choice != 15);
}

// Специализация для string
template<>
void handleListOperations<string>(DoublyLinkedList<string>& list, const string& listType) {
    int choice = 0;

    // Генерация начального списка
    cout << "Generating initial list with sample values...\n";
    string sampleStrings[] = { "apple", "banana", "cherry", "date", "elderberry" };
    for (int i = 0; i < 5; i++) {
        list.push_back(sampleStrings[i]);
    }
    cout << "Initial list: ";
    list.print_forward();

    do {
        displayListMenu(listType);
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add to front
            string value;
            cout << "Enter value to add to front: ";
            cin >> value;
            list.push_front(value);
            cout << "Element added to front.\n";
            break;
        }

        case 2: {
            // Add to back
            string value;
            cout << "Enter value to add to back: ";
            cin >> value;
            list.push_back(value);
            cout << "Element added to back.\n";
            break;
        }
        case 3:
            // Remove from front
            if (!list.is_empty()) {
                list.pop_front();
                cout << "Element removed from front.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 4:
            // Remove from back
            if (!list.is_empty()) {
                list.pop_back();
                cout << "Element removed from back.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 5: {
            // Insert after element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string target, value;
            cout << "Enter target value to insert after: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            auto node = list.linear_search(target);
            if (node) {
                list.insert_after(node, value);
                cout << "Element inserted after " << target << ".\n";
            }
            else {
                cout << "Target element not found!\n";
            }
            break;
        }

        case 6: {
            // Insert before element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string target, value;
            cout << "Enter target value to insert before: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            auto node = list.linear_search(target);
            if (node) {
                list.insert_before(node, value);
                cout << "Element inserted before " << target << ".\n";
            }
            else {
                cout << "Target element not found!\n";
            }
            break;
        }

        case 7: {
            // Remove specific element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string value;
            cout << "Enter value to remove: ";
            cin >> value;
            auto node = list.linear_search(value);
            if (node) {
                list.remove(node);
                cout << "Element " << value << " removed.\n";
            }
            else {
                cout << "Element not found!\n";
            }
            break;
        }

        case 8: {
            // Search for element
            if (list.is_empty()) {
                cout << "List is empty!\n";
                break;
            }
            string value;
            cout << "Enter value to search: ";
            cin >> value;
            auto node = list.linear_search(value);
            if (node) {
                cout << "Element " << value << " found in the list.\n";
            }
            else {
                cout << "Element " << value << " not found!\n";
            }
            break;
        }

        case 9:
            // Sort list
            if (!list.is_empty()) {
                list.sort();
                cout << "List sorted successfully.\n";
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 10:
            // Clear list
            list.clear();
            cout << "List cleared.\n";
            break;

        case 11:
            // Display forward
            if (!list.is_empty()) {
                cout << "List (forward): ";
                list.print_forward();
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 12:
            // Display backward
            if (!list.is_empty()) {
                cout << "List (backward): ";
                list.print_backward();
            }
            else {
                cout << "List is empty!\n";
            }
            break;

        case 13:
            // Display size
            cout << "List size: " << list.get_size() << "\n";
            break;

        case 14:
            // Check if empty
            cout << "List is " << (list.is_empty() ? "empty" : "not empty") << "\n";
            break;

        case 15:
            // Back to main menu
            cout << "Returning to main menu...\n";
            return;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

        // Show current list state after each operation
        if (choice >= 1 && choice <= 10 && !list.is_empty()) {
            cout << "Current list state: ";
            list.print_forward();
        }
        cout << "Current list: ";
        list.print_forward();

    } while (choice != 15);
}

int main()
{
    srand(time(0));

    DoublyLinkedList<int> intList;
    DoublyLinkedList<string> stringList;
    int mainChoice = 0;

    cout << "=== Doubly Linked List Manager ===\n";

    do {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            cout << "\n--- Integer List Operations ---\n";
            handleListOperations(intList, "Integer");
            break;

        case 2:
            cout << "\n--- String List Operations ---\n";
            handleListOperations(stringList, "String");
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