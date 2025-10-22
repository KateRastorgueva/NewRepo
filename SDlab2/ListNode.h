#pragma once

template <typename T>
class ListNode {
public:
    T Data;
    ListNode<T>* Next;
    ListNode<T>* Prev;

    ListNode(const T& value) : Data(value), Next(nullptr), Prev(nullptr) {}
};