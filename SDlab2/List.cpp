#include "List.h"
#include <iostream>

// Конструктор по умолчанию
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0)
{
}

// Деструктор
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

// Вспомогательная функция для копирования списка
template <typename T>
void DoublyLinkedList<T>::copy_from(const DoublyLinkedList& other)
{
    ListNode<T>* current = other.head;
    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
}

// Конструктор копирования
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0)
{
    copy_from(other);
}

// Оператор присваивания
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    return *this;
}

// Вспомогательная функция для добавления узла
template <typename T>
void DoublyLinkedList<T>::add_node_to_empty_list(ListNode<T>* new_node)
{
    head = tail = new_node;
}

template <typename T>
void DoublyLinkedList<T>::add_node_to_front(ListNode<T>* new_node)
{
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
}

template <typename T>
void DoublyLinkedList<T>::add_node_to_back(ListNode<T>* new_node)
{
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
}

// Добавление в начало
template <typename T>
void DoublyLinkedList<T>::push_front(const T& value)
{
    ListNode<T>* new_node = new ListNode<T>(value);

    if (is_empty())
    {
        add_node_to_empty_list(new_node);
    }
    else
    {
        add_node_to_front(new_node);
    }
    size++;
}

// Добавление в конец
template <typename T>
void DoublyLinkedList<T>::push_back(const T& value)
{
    ListNode<T>* new_node = new ListNode<T>(value);

    if (is_empty())
    {
        add_node_to_empty_list(new_node);
    }
    else
    {
        add_node_to_back(new_node);
    }
    size++;
}

// Вспомогательная функция для удаления единственного элемента
template <typename T>
void DoublyLinkedList<T>::remove_single_element()
{
    head = tail = nullptr;
}

// Удаление из начала
template <typename T>
void DoublyLinkedList<T>::pop_front()
{
    if (is_empty())
    {
        return;
    }

    ListNode<T>* temp = head;
    if (head == tail)
    {
        remove_single_element();
    }
    else
    {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    size--;
}

// Удаление из конца
template <typename T>
void DoublyLinkedList<T>::pop_back()
{
    if (is_empty())
    {
        return;
    }

    ListNode<T>* temp = tail;
    if (head == tail)
    {
        remove_single_element();
    }
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    size--;
}

// Вспомогательная функция для вставки между узлами
template <typename T>
void DoublyLinkedList<T>::insert_between(ListNode<T>* prev_node, ListNode<T>* next_node, const T& value)
{
    ListNode<T>* new_node = new ListNode<T>(value);
    new_node->prev = prev_node;
    new_node->next = next_node;
    prev_node->next = new_node;
    next_node->prev = new_node;
    size++;
}

// Вставка после определенного элемента
template <typename T>
void DoublyLinkedList<T>::insert_after(ListNode<T>* node, const T& value)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == tail)
    {
        push_back(value);
    }
    else
    {
        insert_between(node, node->next, value);
    }
}

// Вставка перед определенного элемента
template <typename T>
void DoublyLinkedList<T>::insert_before(ListNode<T>* node, const T& value)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == head)
    {
        push_front(value);
    }
    else
    {
        insert_between(node->prev, node, value);
    }
}

// Удаление элемента
template <typename T>
void DoublyLinkedList<T>::remove(ListNode<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == head)
    {
        pop_front();
    }
    else if (node == tail)
    {
        pop_back();
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }
}

// Очистка списка
template <typename T>
void DoublyLinkedList<T>::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
}

// Линейный поиск
template <typename T>
ListNode<T>* DoublyLinkedList<T>::linear_search(const T& value)
{
    ListNode<T>* current = head;
    while (current != nullptr)
    {
        if (current->data == value)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Сортировка (пузырьковая)
template <typename T>
void DoublyLinkedList<T>::sort()
{
    if (size <= 1) return;

    bool swapped;
    do
    {
        swapped = false;
        ListNode<T>* current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->data > current->next->data)
            {
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
bool DoublyLinkedList<T>::is_empty() const
{
    return head == nullptr;
}

// Получение размера
template <typename T>
int DoublyLinkedList<T>::get_size() const
{
    return size;
}

// Получение головы
template <typename T>
ListNode<T>* DoublyLinkedList<T>::get_head() const
{
    return head;
}

// Получение хвоста
template <typename T>
ListNode<T>* DoublyLinkedList<T>::get_tail() const
{
    return tail;
}

// Вспомогательная функция для печати списка
template <typename T>
bool DoublyLinkedList<T>::print_list(bool forward) const
{
    if (is_empty())
    {
        return false;
    }

    ListNode<T>* current = forward ? head : tail;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = forward ? current->next : current->prev;
    }
    std::cout << std::endl;
    return true;
}

// Печать в прямом порядке
template <typename T>
bool DoublyLinkedList<T>::print_forward() const
{
    return print_list(true);
}

// Печать в обратном порядке
template <typename T>
bool DoublyLinkedList<T>::print_backward() const
{
    return print_list(false);
}
// для корректной работы шаблонного класса при раздельной компиляции реализации 
template class DoublyLinkedList<int>;
template class DoublyLinkedList<std::string>;