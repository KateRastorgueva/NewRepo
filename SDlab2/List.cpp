#include "List.h"
#include <iostream>

// Конструктор по умолчанию
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : _head(nullptr), _tail(nullptr), _size(0)
{
}

// Деструктор
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    Clear();
}

// Вспомогательная функция для копирования списка
template <typename T>
void DoublyLinkedList<T>::CopyFrom(const DoublyLinkedList& other)
{
    ListNode<T>* current = other._head;
    while (current != nullptr)
    {
        PushBack(current->data);
        current = current->next;
    }
}

// Конструктор копирования
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : _head(nullptr), _tail(nullptr), _size(0)
{
    CopyFrom(other);
}

// Оператор присваивания
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
    if (this != &other)
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

// Вспомогательная функция для добавления узла
template <typename T>
void DoublyLinkedList<T>::AddNodeToEmptyList(ListNode<T>* newNode)
{
    _head = _tail = newNode;
}

template <typename T>
void DoublyLinkedList<T>::AddNodeToFront(ListNode<T>* newNode)
{
    newNode->next = _head;
    _head->prev = newNode;
    _head = newNode;
}

template <typename T>
void DoublyLinkedList<T>::AddNodeToBack(ListNode<T>* newNode)
{
    _tail->next = newNode;
    newNode->prev = _tail;
    _tail = newNode;
}

// Добавление в начало
template <typename T>
void DoublyLinkedList<T>::PushFront(const T& value)
{
    ListNode<T>* newNode = new ListNode<T>(value);

    if (IsEmpty())
    {
        AddNodeToEmptyList(newNode);
    }
    else
    {
        AddNodeToFront(newNode);
    }
    _size++;
}

// Добавление в конец
template <typename T>
void DoublyLinkedList<T>::PushBack(const T& value)
{
    ListNode<T>* newNode = new ListNode<T>(value);

    if (IsEmpty())
    {
        AddNodeToEmptyList(newNode);
    }
    else
    {
        AddNodeToBack(newNode);
    }
    _size++;
}

// Вспомогательная функция для удаления единственного элемента
template <typename T>
void DoublyLinkedList<T>::RemoveSingleElement()
{
    _head = _tail = nullptr;
}

// Удаление из начала
template <typename T>
void DoublyLinkedList<T>::PopFront()
{
    if (IsEmpty())
    {
        return;
    }

    ListNode<T>* temp = _head;
    if (_head == _tail)
    {
        RemoveSingleElement();
    }
    else
    {
        _head = _head->next;
        _head->prev = nullptr;
    }
    delete temp;
    _size--;
}

// Удаление из конца
template <typename T>
void DoublyLinkedList<T>::PopBack()
{
    if (IsEmpty())
    {
        return;
    }

    ListNode<T>* temp = _tail;
    if (_head == _tail)
    {
        RemoveSingleElement();
    }
    else
    {
        _tail = _tail->prev;
        _tail->next = nullptr;
    }
    delete temp;
    _size--;
}

// Вспомогательная функция для вставки между узлами
template <typename T>
void DoublyLinkedList<T>::InsertBetween(ListNode<T>* prevNode, ListNode<T>* nextNode, const T& value)
{
    ListNode<T>* newNode = new ListNode<T>(value);
    newNode->prev = prevNode;
    newNode->next = nextNode;
    prevNode->next = newNode;
    nextNode->prev = newNode;
    _size++;
}

// Вставка после определенного элемента
template <typename T>
void DoublyLinkedList<T>::InsertAfter(ListNode<T>* node, const T& value)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == _tail)
    {
        PushBack(value);
    }
    else
    {
        InsertBetween(node, node->next, value);
    }
}

// Вставка перед определенного элемента
template <typename T>
void DoublyLinkedList<T>::InsertBefore(ListNode<T>* node, const T& value)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == _head)
    {
        PushFront(value);
    }
    else
    {
        InsertBetween(node->prev, node, value);
    }
}

// Удаление элемента
template <typename T>
void DoublyLinkedList<T>::Remove(ListNode<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node == _head)
    {
        PopFront();
    }
    else if (node == _tail)
    {
        PopBack();
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        _size--;
    }
}

// Очистка списка
template <typename T>
void DoublyLinkedList<T>::Clear()
{
    while (!IsEmpty())
    {
        PopFront();
    }
}

// Линейный поиск
template <typename T>
ListNode<T>* DoublyLinkedList<T>::LinearSearch(const T& value)
{
    ListNode<T>* current = _head;
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
void DoublyLinkedList<T>::Sort()
{
    if (_size <= 1) return;

    bool swapped;
    do
    {
        swapped = false;
        ListNode<T>* current = _head;

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
bool DoublyLinkedList<T>::IsEmpty() const
{
    return _head == nullptr;
}

// Получение размера
template <typename T>
int DoublyLinkedList<T>::GetSize() const
{
    return _size;
}

// Получение головы
template <typename T>
ListNode<T>* DoublyLinkedList<T>::GetHead() const
{
    return _head;
}

// Получение хвоста
template <typename T>
ListNode<T>* DoublyLinkedList<T>::GetTail() const
{
    return _tail;
}

// Вспомогательная функция для печати списка
template <typename T>
bool DoublyLinkedList<T>::PrintList(bool forward) const
{
    if (IsEmpty())
    {
        return false;
    }

    ListNode<T>* current = forward ? _head : _tail;
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
bool DoublyLinkedList<T>::PrintForward() const
{
    return PrintList(true);
}

// Печать в обратном порядке
template <typename T>
bool DoublyLinkedList<T>::PrintBackward() const
{
    return PrintList(false);
}

// для корректной работы шаблонного класса при раздельной компиляции реализации 
template class DoublyLinkedList<int>;
template class DoublyLinkedList<std::string>;