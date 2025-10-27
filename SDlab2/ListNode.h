#pragma once

template <typename T>
class ListNode {
public:
    T Data;
    ListNode<T>* Next;
    ListNode<T>* Previous;

    ListNode(const T& value) : Data(value), Next(nullptr), Previous(nullptr) {}
};