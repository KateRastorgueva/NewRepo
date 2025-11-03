#pragma once
#include "ListNode.h"
#include <string>

/// <summary>
/// Класс, представляющий двусвязный список строк
/// </summary>
class DoublyLinkedList
{
private:
    ListNode* _head;
    ListNode* _tail;
    int _size;

    /// <summary>
    /// Копирует данные из другого списка
    /// </summary>
    /// <param name="other">Исходный список для копирования</param>
    void CopyFrom(const DoublyLinkedList& other);

    /// <summary>
    /// Добавляет узел в пустой список
    /// </summary>
    /// <param name="newNode">Новый узел для добавления</param>
    void AddNodeToEmptyList(ListNode* newNode);

    /// <summary>
    /// Добавляет узел в начало списка
    /// </summary>
    /// <param name="newNode">Новый узел для добавления</param>
    void AddNodeToFront(ListNode* newNode);

    /// <summary>
    /// Добавляет узел в конец списка
    /// </summary>
    /// <param name="newNode">Новый узел для добавления</param>
    void AddNodeToBack(ListNode* newNode);

    /// <summary>
    /// Удаляет единственный элемент списка
    /// </summary>
    void RemoveSingleElement();

    /// <summary>
    /// Вставляет узел между двумя существующими узлами
    /// </summary>
    /// <param name="prevNode">Предыдущий узел</param>
    /// <param name="nextNode">Следующий узел</param>
    /// <param name="value">Значение для вставки</param>
    void InsertBetween(ListNode* prevNode, ListNode* nextNode, const std::string& value);

public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    DoublyLinkedList();

    /// <summary>
    /// Деструктор
    /// </summary>
    ~DoublyLinkedList();

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other">Исходный список для копирования</param>
    DoublyLinkedList(const DoublyLinkedList& other);

    /// <summary>
    /// Оператор присваивания
    /// </summary>
    /// <param name="other">Исходный список для копирования</param>
    /// <returns>Ссылка на текущий список</returns>
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    /// <summary>
    /// Добавляет элемент в начало списка
    /// </summary>
    /// <param name="value">Значение для добавления</param>
    void PushFront(const std::string& value);

    /// <summary>
    /// Добавляет элемент в конец списка
    /// </summary>
    /// <param name="value">Значение для добавления</param>
    void PushBack(const std::string& value);

    /// <summary>
    /// Удаляет элемент из начала списка
    /// </summary>
    void PopFront();

    /// <summary>
    /// Удаляет элемент из конца списка
    /// </summary>
    void PopBack();

    /// <summary>
    /// Вставляет элемент после указанного узла
    /// </summary>
    /// <param name="node">Узел, после которого выполняется вставка</param>
    /// <param name="value">Значение для вставки</param>
    void InsertAfter(ListNode* node, const std::string& value);

    /// <summary>
    /// Вставляет элемент перед указанным узлом
    /// </summary>
    /// <param name="node">Узел, перед которым выполняется вставка</param>
    /// <param name="value">Значение для вставки</param>
    void InsertBefore(ListNode* node, const std::string& value);

    /// <summary>
    /// Удаляет указанный узел из списка
    /// </summary>
    /// <param name="node">Узел для удаления</param>
    void Remove(ListNode* node);

    /// <summary>
    /// Очищает список, удаляя все элементы
    /// </summary>
    void Clear();

    /// <summary>
    /// Выполняет линейный поиск элемента в списке
    /// </summary>
    /// <param name="value">Значение для поиска</param>
    /// <returns>Указатель на найденный узел или nullptr</returns>
    ListNode* LinearSearch(const std::string& value);

    /// <summary>
    /// Сортирует список методом пузырька
    /// </summary>
    void Sort();

    /// <summary>
    /// Проверяет, является ли список пустым
    /// </summary>
    /// <returns>true если список пуст, иначе false</returns>
    bool IsEmpty() const;

    /// <summary>
    /// Возвращает количество элементов в списке
    /// </summary>
    /// <returns>Размер списка</returns>
    int GetSize() const;

    /// <summary>
    /// Возвращает указатель на голову списка
    /// </summary>
    /// <returns>Указатель на первый узел</returns>
    ListNode* GetHead() const;

    /// <summary>
    /// Возвращает указатель на хвост списка
    /// </summary>
    /// <returns>Указатель на последний узел</returns>
    ListNode* GetTail() const;
};