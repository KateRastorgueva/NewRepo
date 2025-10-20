#pragma once
#include "ListItem.h"
#include <iostream>
#include <string>

template <typename T>
class DoublyLinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;

public:
    //! \brief Конструктор по умолчанию.
    DoublyLinkedList();

    //! \brief Деструктор.
    ~DoublyLinkedList();

    //! \brief Конструктор копирования.
    DoublyLinkedList(const DoublyLinkedList& other);

    //! \brief Оператор присваивания.
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    //! \brief Добавление в начало.
    void push_front(const T& value);

    //! \brief Добавление в конец.
    void push_back(const T& value);

    //! \brief Удаление из начала.
    void pop_front();

    //! \brief Удаление из конца.
    void pop_back();

    //! \brief Вставка после определенного элемента.
    void insert_after(ListNode<T>* node, const T& value);

    //! \brief Вставка перед определенным элементом.
    void insert_before(ListNode<T>* node, const T& value);

    //! \brief Удаление элемента.
    void remove(ListNode<T>* node);

    //! \brief Очистка списка.
    void clear();

    //! \brief Линейный поиск.
    ListNode<T>* linear_search(const T& value);

    //! \brief Сортировка (пузырьковая).
    void sort();

    //! \brief Проверка на пустоту.
    bool is_empty() const;

    //! \brief Получение размера.
    int get_size() const;

    //! \brief Получение головы.
    ListNode<T>* get_head() const;

    //! \brief Получение хвоста.
    ListNode<T>* get_tail() const;

    //! \brief Печать в прямом порядке.
    bool print_forward() const;

    //! \brief Печать в обратном порядке.
    bool print_backward() const;

};