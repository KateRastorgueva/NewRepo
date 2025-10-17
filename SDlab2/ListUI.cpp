#include "ListUI.h"
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
ListUI<T>::ListUI(DoublyLinkedList<T>& listRef, const std::string& type)
    : list(listRef), listType(type) {
}

// ”нифицированна€ проверка пустоты
template<typename T>
bool ListUI<T>::checkEmpty() const {
    if (list.is_empty()) {
        cout << "List is empty!\n";
        return true;
    }
    return false;
}

// ”нифицированный поиск с валидацией
template<typename T>
ListNode<T>* ListUI<T>::searchAndValidate(const T& target, const std::string& operation) {
    auto node = list.linear_search(target);
    if (!node) {
        cout << "Element " << target << " not found for " << operation << "!\n";
    }
    return node;
}

// ”нифицированный вывод состо€ни€
template<typename T>
void ListUI<T>::showCurrentState() const {
    if (!list.is_empty()) {
        cout << "Current list: ";
        list.print_forward();
    }
}

template<typename T>
void ListUI<T>::displayListMenu() const {
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

// —пециализации дл€ int
template<>
int ListUI<int>::getInputValue(const std::string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    return value;
}

template<>
void ListUI<int>::generateInitialData() {
    cout << "Generating initial list with random values...\n";
    for (int i = 0; i < 5; i++) {
        int randomValue = rand() % 100 + 1;
        list.push_back(randomValue);
    }
    showCurrentState();
}

// —пециализации дл€ string
template<>
std::string ListUI<std::string>::getInputValue(const std::string& prompt) {
    string value;
    cout << prompt;
    cin >> value;
    return value;
}

template<>
void ListUI<std::string>::generateInitialData() {
    cout << "Generating initial list with sample values...\n";
    string sampleStrings[] = { "apple", "banana", "cherry", "date", "elderberry" };
    for (int i = 0; i < 5; i++) {
        list.push_back(sampleStrings[i]);
    }
    showCurrentState();
}

// ќптимизированные методы операций
template<typename T>
void ListUI<T>::handleAddToFront() {
    T value = getInputValue("Enter value to add to front: ");
    list.push_front(value);
    cout << "Element added to front.\n";
    showCurrentState();
}

template<typename T>
void ListUI<T>::handleAddToBack() {
    T value = getInputValue("Enter value to add to back: ");
    list.push_back(value);
    cout << "Element added to back.\n";
    showCurrentState();
}

template<typename T>
void ListUI<T>::handleRemoveFromFront() {
    if (checkEmpty()) return;
    list.pop_front();
    cout << "Element removed from front.\n";
    showCurrentState();
}

template<typename T>
void ListUI<T>::handleRemoveFromBack() {
    if (checkEmpty()) return;
    list.pop_back();
    cout << "Element removed from back.\n";
    showCurrentState();
}

template<typename T>
void ListUI<T>::handleInsertAfter() {
    if (checkEmpty()) return;

    T target = getInputValue("Enter target value to insert after: ");
    T value = getInputValue("Enter value to insert: ");

    auto node = searchAndValidate(target, "insert after");
    if (node) {
        list.insert_after(node, value);
        cout << "Element inserted after " << target << ".\n";
        showCurrentState();
    }
}

template<typename T>
void ListUI<T>::handleInsertBefore() {
    if (checkEmpty()) return;

    T target = getInputValue("Enter target value to insert before: ");
    T value = getInputValue("Enter value to insert: ");

    auto node = searchAndValidate(target, "insert before");
    if (node) {
        list.insert_before(node, value);
        cout << "Element inserted before " << target << ".\n";
        showCurrentState();
    }
}

template<typename T>
void ListUI<T>::handleRemoveSpecific() {
    if (checkEmpty()) return;

    T value = getInputValue("Enter value to remove: ");
    auto node = searchAndValidate(value, "removal");
    if (node) {
        list.remove(node);
        cout << "Element " << value << " removed.\n";
        showCurrentState();
    }
}

template<typename T>
void ListUI<T>::handleSearch() {
    if (checkEmpty()) return;

    T value = getInputValue("Enter value to search: ");
    auto node = list.linear_search(value);
    if (node) {
        cout << "Element " << value << " found in the list.\n";
    }
    else {
        cout << "Element " << value << " not found!\n";
    }
}

template<typename T>
void ListUI<T>::handleSort() {
    if (checkEmpty()) return;
    list.sort();
    cout << "List sorted successfully.\n";
    showCurrentState();
}

template<typename T>
void ListUI<T>::handleClear() {
    list.clear();
    cout << "List cleared.\n";
}

template<typename T>
void ListUI<T>::handleDisplayForward() const {
    if (checkEmpty()) return;
    list.print_forward();
}

template<typename T>
void ListUI<T>::handleDisplayBackward() const {
    if (checkEmpty()) return;
    list.print_backward();
}

template<typename T>
void ListUI<T>::handleDisplaySize() const {
    cout << "List size: " << list.get_size() << "\n";
}

template<typename T>
void ListUI<T>::handleCheckEmpty() const {
    cout << "List is " << (list.is_empty() ? "empty" : "not empty") << "\n";
}

template<typename T>
void ListUI<T>::run() {
    generateInitialData();

    int choice = 0;
    do {
        displayListMenu();
        cin >> choice;

        switch (choice) {
        case 1: handleAddToFront(); break;
        case 2: handleAddToBack(); break;
        case 3: handleRemoveFromFront(); break;
        case 4: handleRemoveFromBack(); break;
        case 5: handleInsertAfter(); break;
        case 6: handleInsertBefore(); break;
        case 7: handleRemoveSpecific(); break;
        case 8: handleSearch(); break;
        case 9: handleSort(); break;
        case 10: handleClear(); break;
        case 11: handleDisplayForward(); break;
        case 12: handleDisplayBackward(); break;
        case 13: handleDisplaySize(); break;
        case 14: handleCheckEmpty(); break;
        case 15: cout << "Returning to main menu...\n"; return;
        default: cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 15);
}

// явна€ инстанциаци€ дл€ нужных типов
template class ListUI<int>;
template class ListUI<std::string>;