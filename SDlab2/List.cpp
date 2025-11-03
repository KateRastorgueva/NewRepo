#include "List.h"
#include <iostream>
using namespace std;

/// <summary>
/// Конструктор по умолчанию
/// </summary>
DoublyLinkedList::DoublyLinkedList() : _head(nullptr), _tail(nullptr), _size(0)
{
}

/// <summary>
/// Деструктор
/// </summary>
DoublyLinkedList::~DoublyLinkedList()
{
    Clear();
}

/// <summary>
/// Копирует данные из другого списка
/// </summary>
/// <param name="other">Исходный список для копирования</param>
void DoublyLinkedList::CopyFrom(const DoublyLinkedList& other)
{
    ListNode* current = other._head;
    while (current != nullptr)
    {
        PushBack(current->Data);
        current = current->Next;
    }
}

/// <summary>
/// Конструктор копирования
/// </summary>
/// <param name="other">Исходный список для копирования</param>
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) : _head(nullptr), _tail(nullptr), _size(0)
{
    CopyFrom(other);
}

/// <summary>
/// Оператор присваивания
/// </summary>
/// <param name="other">Исходный список для копирования</param>
/// <returns>Ссылка на текущий список</returns>
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other)
{
    if (this != &other)
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

/// <summary>
/// Добавляет узел в пустой список
/// </summary>
/// <param name="newNode">Новый узел для добавления</param>
void DoublyLinkedList::AddNodeToEmptyList(ListNode* newNode)
{
    _head = _tail = newNode;
}

/// <summary>
/// Добавляет узел в начало непустого списка
/// </summary>
/// <param name="newNode">Новый узел для добавления</param>
void DoublyLinkedList::AddNodeToFront(ListNode* newNode)
{
    newNode->Next = _head;
    _head->Previous = newNode;
    _head = newNode;
}

/// <summary>
/// Добавляет узел в конец непустого списка
/// </summary>
/// <param name="newNode">Новый узел для добавления</param>
void DoublyLinkedList::AddNodeToBack(ListNode* newNode)
{
    _tail->Next = newNode;
    newNode->Previous = _tail;
    _tail = newNode;
}

/// <summary>
/// Добавляет элемент в начало списка
/// </summary>
/// <param name="value">Значение для добавления</param>
void DoublyLinkedList::PushFront(const std::string& value)
{
    ListNode* newNode = new ListNode(value);

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

/// <summary>
/// Добавляет элемент в конец списка
/// </summary>
/// <param name="value">Значение для добавления</param>
void DoublyLinkedList::PushBack(const std::string& value)
{
    ListNode* newNode = new ListNode(value);

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

/// <summary>
/// Удаляет единственный элемент списка
/// </summary>
void DoublyLinkedList::RemoveSingleElement()
{
    _head = _tail = nullptr;
}

/// <summary>
/// Удаляет элемент из начала списка
/// </summary>
void DoublyLinkedList::PopFront()
{
    if (IsEmpty())
    {
        return;
    }

    ListNode* temporary= _head;
    if (_head == _tail)
    {
        RemoveSingleElement();
    }
    else
    {
        _head = _head->Next;
        _head->Previous = nullptr;
    }
    delete temporary;
    _size--;
}

/// <summary>
/// Удаляет элемент из конца списка
/// </summary>
void DoublyLinkedList::PopBack()
{
    if (IsEmpty())
    {
        return;
    }

    ListNode* temporary= _tail;
    if (_head == _tail)
    {
        RemoveSingleElement();
    }
    else
    {
        _tail = _tail->Previous;
        _tail->Next = nullptr;
    }
    delete temporary;
    _size--;
}

/// <summary>
/// Вставляет узел между двумя существующими узлами
/// </summary>
/// <param name="prevNode">Предыдущий узел</param>
/// <param name="nextNode">Следующий узел</param>
/// <param name="value">Значение для вставки</param>
void DoublyLinkedList::InsertBetween(ListNode* prevNode, ListNode* nextNode, const std::string& value)
{
    ListNode* newNode = new ListNode(value);
    newNode->Previous = prevNode;
    newNode->Next = nextNode;
    prevNode->Next = newNode;
    nextNode->Previous = newNode;
    _size++;
}

/// <summary>
/// Вставляет элемент после указанного узла
/// </summary>
/// <param name="node">Узел, после которого выполняется вставка</param>
/// <param name="value">Значение для вставки</param>
void DoublyLinkedList::InsertAfter(ListNode* node, const std::string& value)
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
        InsertBetween(node, node->Next, value);
    }
}

/// <summary>
/// Вставляет элемент перед указанным узлом
/// </summary>
/// <param name="node">Узел, перед которым выполняется вставка</param>
/// <param name="value">Значение для вставки</param>
void DoublyLinkedList::InsertBefore(ListNode* node, const std::string& value)
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
        InsertBetween(node->Previous, node, value);
    }
}

/// <summary>
/// Удаляет указанный узел из списка
/// </summary>
/// <param name="node">Узел для удаления</param>
void DoublyLinkedList::Remove(ListNode* node)
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
        node->Previous->Next = node->Next;
        node->Next->Previous = node->Previous;
        delete node;
        _size--;
    }
}

/// <summary>
/// Очищает список, удаляя все элементы
/// </summary>
void DoublyLinkedList::Clear()
{
    while (!IsEmpty())
    {
        PopFront();
    }
}

/// <summary>
/// Выполняет линейный поиск элемента в списке
/// </summary>
/// <param name="value">Значение для поиска</param>
/// <returns>Указатель на найденный узел или nullptr</returns>
ListNode* DoublyLinkedList::LinearSearch(const std::string& value)
{
    ListNode* current = _head;
    while (current != nullptr)
    {
        if (current->Data == value)
        {
            return current;
        }
        current = current->Next;
    }
    return nullptr;
}

/// <summary>
/// Сортирует список методом пузырька
/// </summary>
void DoublyLinkedList::Sort()
{
    if (_size <= 1) return;

    bool swapped;
    do
    {
        swapped = false;
        ListNode* current = _head;

        while (current != nullptr && current->Next != nullptr)
        {
            if (current->Data > current->Next->Data)
            {
                string temporary= current->Data;
                current->Data = current->Next->Data;
                current->Next->Data = temporary;
                current->Next->Data = temporary;
                swapped = true;
            }
            current = current->Next;
        }
    } while (swapped);
}

/// <summary>
/// Проверяет, является ли список пустым
/// </summary>
/// <returns>true если список пуст, иначе false</returns>
bool DoublyLinkedList::IsEmpty() const
{
    return _head == nullptr;
}

/// <summary>
/// Возвращает количество элементов в списке
/// </summary>
/// <returns>Размер списка</returns>
int DoublyLinkedList::GetSize() const
{
    return _size;
}

/// <summary>
/// Возвращает указатель на голову списка
/// </summary>
/// <returns>Указатель на первый узел</returns>
ListNode* DoublyLinkedList::GetHead() const
{
    return _head;
}

/// <summary>
/// Возвращает указатель на хвост списка
/// </summary>
/// <returns>Указатель на последний узел</returns>
ListNode* DoublyLinkedList::GetTail() const
{
    return _tail;
}