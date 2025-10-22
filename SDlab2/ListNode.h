#pragma once

template <typename T>
class ListNode {
public:
    T data;
    ListNode<T>* next;
    ListNode<T>* prev;

    ListNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};