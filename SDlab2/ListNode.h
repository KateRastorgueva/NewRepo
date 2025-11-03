#pragma once
#include <string>

/// <summary>
/// Класс, представляющий узел двусвязного списка
/// </summary>
class ListNode
{
public:
    /// <summary>
    /// Данные, хранящиеся в узле
    /// </summary>
    std::string Data;
    /// <summary>
    /// Указатель на следующий узел
    /// </summary>
    ListNode* Next;
    /// <summary>
    /// Указатель на предыдущий узел
    /// </summary>
    ListNode* Previous;

    /// <summary>
    /// Конструктор узла
    /// </summary>
    /// <param name="value">Значение для хранения в узле</param>
    ListNode(const std::string& value) : Data(value), Next(nullptr), Previous(nullptr) {}
};