#include "List.h"
#include <iostream>

// Конструктор по умолчанию
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// Деструктор
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// Конструктор копирования
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    ListNode<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

// Оператор присваивания
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
    if (this != &other) {
        clear();
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data); 
            current = current->next;
        }
    }
    return *this;
}

// Добавление в начало
template <typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    ListNode<T>* new_node = new ListNode<T>(value);

    if (is_empty()) {
        head = tail = new_node;
    }
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    size++;
}

// Добавление в конец
template <typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    ListNode<T>* new_node = new ListNode<T>(value);

    if (is_empty()) {
        head = tail = new_node;
    }
    else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    size++;
}

// Удаление из начала
template <typename T>
void DoublyLinkedList<T>::pop_front() {
    if (is_empty()) {
        return; // Пустой список - ничего не делаем
    }

    ListNode<T>* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    size--;
}

// Удаление из конца
template <typename T>
void DoublyLinkedList<T>::pop_back() {
    if (is_empty()) {
        return; // Пустой список - ничего не делаем
    }

    ListNode<T>* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    size--;
}

// Вставка после определенного элемента
template <typename T>
void DoublyLinkedList<T>::insert_after(ListNode<T>* node, const T& value) {
    if (node == nullptr) {
        return; // Невалидный узел - ничего не делаем
    }

    if (node == tail) {
        push_back(value);
    }
    else {
        ListNode<T>* new_node = new ListNode<T>(value);
        new_node->prev = node;
        new_node->next = node->next;
        node->next->prev = new_node;
        node->next = new_node;
        size++;
    }
}

// Вставка перед определенным элементом
template <typename T>
void DoublyLinkedList<T>::insert_before(ListNode<T>* node, const T& value) {
    if (node == nullptr) {
        return; // Невалидный узел - ничего не делаем
    }

    if (node == head) {
        push_front(value);
    }
    else {
        ListNode<T>* new_node = new ListNode<T>(value);
        new_node->next = node;
        new_node->prev = node->prev;
        node->prev->next = new_node;
        node->prev = new_node;
        size++;
    }
}

// Удаление элемента
template <typename T>
void DoublyLinkedList<T>::remove(ListNode<T>* node) {
    if (node == nullptr) {
        return; // Невалидный узел - ничего не делаем
    }

    if (node == head) {
        pop_front();
    }
    else if (node == tail) {
        pop_back();
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }
}

// Очистка списка
template <typename T>
void DoublyLinkedList<T>::clear() {
    while (!is_empty()) {
        pop_front();
    }
}

// Линейный поиск
template <typename T>
ListNode<T>* DoublyLinkedList<T>::linear_search(const T& value) {
    ListNode<T>* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Сортировка (пузырьковая)
template <typename T>
void DoublyLinkedList<T>::sort() {
    if (size <= 1) return;

    bool swapped;
    do {
        swapped = false;
        ListNode<T>* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->data > current->next->data) {
                // Обмен данными
                T temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Проверка на пустоту
template <typename T>
bool DoublyLinkedList<T>::is_empty() const {
    return head == nullptr;
}

// Получение размера
template <typename T>
int DoublyLinkedList<T>::get_size() const {
    return size;
}

// Получение головы
template <typename T>
ListNode<T>* DoublyLinkedList<T>::get_head() const {
    return head;
}

// Получение хвоста
template <typename T>
ListNode<T>* DoublyLinkedList<T>::get_tail() const {
    return tail;
}
template <typename T>
bool DoublyLinkedList<T>::print_forward() const {
    if (is_empty()) {
        return false;  // Список пуст
    }

    ListNode<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
    return true; 
}

// Печать в обратном порядке
template <typename T>
bool DoublyLinkedList<T>::print_backward() const {
    if (is_empty()) {
        return false;
    }

    ListNode<T>* current = tail;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
    return true; 
}

// Явная инстанциация
template class DoublyLinkedList<int>;
template class DoublyLinkedList<std::string>;
// Явная инстанциация для нужных типов
template class DoublyLinkedList<int>;
template class DoublyLinkedList<std::string>;