#pragma once

template <typename T>
struct ListNode {
    T data;
    ListNode* prev;
    ListNode* next;

    ListNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};