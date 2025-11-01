#include "List.h"
#include <iostream>
using namespace std;

DoublyLinkedList::DoublyLinkedList() : _head(nullptr), _tail(nullptr), _size(0)
{
}

DoublyLinkedList::~DoublyLinkedList()
{
    Clear();
}

void DoublyLinkedList::CopyFrom(const DoublyLinkedList& other)
{
    ListNode* current = other._head;
    while (current != nullptr)
    {
        PushBack(current->Data);
        current = current->Next;
    }
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) : _head(nullptr), _tail(nullptr), _size(0)
{
    CopyFrom(other);
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other)
{
    if (this != &other)
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

void DoublyLinkedList::AddNodeToEmptyList(ListNode* newNode)
{
    _head = _tail = newNode;
}

void DoublyLinkedList::AddNodeToFront(ListNode* newNode)
{
    newNode->Next = _head;
    _head->Previous = newNode;
    _head = newNode;
}

void DoublyLinkedList::AddNodeToBack(ListNode* newNode)
{
    _tail->Next = newNode;
    newNode->Previous = _tail;
    _tail = newNode;
}

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

void DoublyLinkedList::RemoveSingleElement()
{
    _head = _tail = nullptr;
}

void DoublyLinkedList::PopFront()
{
    if (IsEmpty())
    {
        return;
    }

    ListNode* temp = _head;
    if (_head == _tail)
    {
        RemoveSingleElement();
    }
    else
    {
        _head = _head->Next;
        _head->Previous = nullptr;
    }
    delete temp;
    _size--;
}

void DoublyLinkedList::PopBack()
{
    if (IsEmpty())
    {
        return;
    }

    ListNode* temp = _tail;
    if (_head == _tail)
    {
        RemoveSingleElement();
    }
    else
    {
        _tail = _tail->Previous;
        _tail->Next = nullptr;
    }
    delete temp;
    _size--;
}

void DoublyLinkedList::InsertBetween(ListNode* prevNode, ListNode* nextNode, const std::string& value)
{
    ListNode* newNode = new ListNode(value);
    newNode->Previous = prevNode;
    newNode->Next = nextNode;
    prevNode->Next = newNode;
    nextNode->Previous = newNode;
    _size++;
}

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

void DoublyLinkedList::Clear()
{
    while (!IsEmpty())
    {
        PopFront();
    }
}

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
                // Обмен данными
                std::string temp = current->Data;
                current->Data = current->Next->Data;
                current->Next->Data = temp;
                swapped = true;
            }
            current = current->Next;
        }
    } while (swapped);
}

bool DoublyLinkedList::IsEmpty() const
{
    return _head == nullptr;
}

int DoublyLinkedList::GetSize() const
{
    return _size;
}

ListNode* DoublyLinkedList::GetHead() const
{
    return _head;
}

ListNode* DoublyLinkedList::GetTail() const
{
    return _tail;
}