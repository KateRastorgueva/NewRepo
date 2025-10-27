#pragma once
#include "ListNode.h"
#include <iostream>
#include <string>

template <typename T>
class DoublyLinkedList {
private:
    ListNode<T>* _head;
    ListNode<T>* _tail;
    int _size;

    // Приватные вспомогательные методы
    void CopyFrom(const DoublyLinkedList& other);
    void AddNodeToEmptyList(ListNode<T>* newNode);
    void AddNodeToFront(ListNode<T>* newNode);
    void AddNodeToBack(ListNode<T>* newNode);
    void RemoveSingleElement();
    void InsertBetween(ListNode<T>* prevNode, ListNode<T>* nextNode, const T& value);

public:
    // Конструкторы и деструктор
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    // Основные операции
    void PushFront(const T& value);
    void PushBack(const T& value);
    void PopFront();
    void PopBack();
    void InsertAfter(ListNode<T>* node, const T& value);
    void InsertBefore(ListNode<T>* node, const T& value);
    void Remove(ListNode<T>* node);
    void Clear();

    // Поиск и сортировка
    ListNode<T>* LinearSearch(const T& value);
    void Sort();

    // Геттеры и проверки
    bool IsEmpty() const;
    int GetSize() const;
    ListNode<T>* GetHead() const;
    ListNode<T>* GetTail() const;

};