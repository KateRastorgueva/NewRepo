#pragma once
#include "ListNode.h"
#include <string>

class DoublyLinkedList {
private:
    ListNode* _head;
    ListNode* _tail;
    int _size;

    void CopyFrom(const DoublyLinkedList& other);
    void AddNodeToEmptyList(ListNode* newNode);
    void AddNodeToFront(ListNode* newNode);
    void AddNodeToBack(ListNode* newNode);
    void RemoveSingleElement();
    void InsertBetween(ListNode* prevNode, ListNode* nextNode, const std::string& value);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    void PushFront(const std::string& value);
    void PushBack(const std::string& value);
    void PopFront();
    void PopBack();
    void InsertAfter(ListNode* node, const std::string& value);
    void InsertBefore(ListNode* node, const std::string& value);
    void Remove(ListNode* node);
    void Clear();

    ListNode* LinearSearch(const std::string& value);
    void Sort();

    bool IsEmpty() const;
    int GetSize() const;
    ListNode* GetHead() const;
    ListNode* GetTail() const;
};