// Main.cpp
#include "List.h"
using namespace std;

int main() {
    // Тестирование списка
    DoublyLinkedList<int> list;

    // Добавление элементов
    list.push_back(10);
    list.push_back(30);
    list.push_front(5);
    list.push_back(20);

    cout << "Исходный список:" << endl;
    list.print_forward();

    // Сортировка
    list.sort();
    cout << "После сортировки:" << endl;
    list.print_forward();

    // Поиск
    auto found = list.linear_search(20);
    if (found) {
        cout << "Найден элемент: " << found->data << endl;
    }

    cout << "Программа завершена успешно!" << endl;
    return 0;
}