#pragma once
#include <string>

class ListNode {
public:
    std::string Data;
    ListNode* Next;
    ListNode* Previous;

    ListNode(const std::string& value) : Data(value), Next(nullptr), Previous(nullptr) {}
};