#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "ListItem.h"

template <typename T>
class DoublyLinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;

public:
    // Конструктор по умолчанию
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор
    ~DoublyLinkedList() {
        clear();
    }

    // Конструктор копирования
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
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
    void push_front(const T& value) {
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
    void push_back(const T& value) {
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
    void pop_front() {
        if (is_empty()) {
            throw "Cannot pop from empty list";
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
    void pop_back() {
        if (is_empty()) {
            throw "Cannot pop from empty list";
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
    void insert_after(ListNode<T>* node, const T& value) {
        if (node == nullptr) {
            throw "Node cannot be null";
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
    void insert_before(ListNode<T>* node, const T& value) {
        if (node == nullptr) {
            throw "Node cannot be null";
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
    void remove(ListNode<T>* node) {
        if (node == nullptr) {
            throw "Node cannot be null";
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
    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

    // Линейный поиск
    ListNode<T>* linear_search(const T& value) {
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
    void sort() {
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
    bool is_empty() const {
        return head == nullptr;
    }

    // Получение размера
    int get_size() const {
        return size;
    }

    // Получение головы
    ListNode<T>* get_head() const {
        return head;
    }

    // Получение хвоста
    ListNode<T>* get_tail() const {
        return tail;
    }

    // Печать в прямом порядке
    void print_forward() const {
        ListNode<T>* current = head;
        cout << "List (forward): ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Печать в обратном порядке
    void print_backward() const {
        ListNode<T>* current = tail;
        cout << "List (backward): ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};