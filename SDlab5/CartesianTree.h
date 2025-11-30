#pragma once
#include <string>

using namespace std;

/// <summary>
/// Узел декартова дерева
/// </summary>
struct CartesianTreeNode
{
    /// <summary>
    /// Ключ узла для поиска и упорядочивания
    /// </summary>
    int Key;

    /// <summary>
    /// Значение данных, хранящееся в узле
    /// </summary>
    string Value;

    /// <summary>
    /// Приоритет узла для поддержки свойства кучи
    /// </summary>
    int Priority;

    /// <summary>
    /// Указатель на левого потомка
    /// </summary>
    CartesianTreeNode* Left;

    /// <summary>
    /// Указатель на правого потомка
    /// </summary>
    CartesianTreeNode* Right;
};

/// <summary>
/// Декартово дерево
/// </summary>
struct CartesianTree
{
    /// <summary>
    /// Указатель на корневой узел дерева
    /// </summary>
    CartesianTreeNode* Root;

    /// <summary>
    /// Текущее количество элементов в дереве
    /// </summary>
    int Size;
};

/// <summary>
/// Проверяет, является ли дерево полным
/// </summary>
/// <param name="tree">Указатель на дерево</param>
/// <returns>true если дерево полное, иначе false</returns>
bool IsTreeFull(const CartesianTree* tree);

/// <summary>
/// Проверяет, является ли дерево пустым
/// </summary>
/// <param name="tree">Указатель на дерево</param>
/// <returns>true если дерево пустое, иначе false</returns>
bool IsTreeEmpty(const CartesianTree* tree);

/// <summary>
/// Проверяет существование ключа в дереве
/// </summary>
/// <param name="tree">Указатель на дерево</param>
/// <param name="key">Ключ для проверки</param>
/// <returns>true если ключ существует, иначе false</returns>
bool KeyExists(const CartesianTree* tree, int key);

/// <summary>
/// Создает новый узел декартова дерева
/// </summary>
/// <param name="key">Ключ узла</param>
/// <param name="value">Значение узла</param>
/// <param name="priority">Приоритет узла</param>
/// <returns>Указатель на созданный узел</returns>
CartesianTreeNode* CreateCartesianTreeNode(int key, const string& value, int priority);

/// <summary>
/// Разделяет декартово дерево по ключу
/// </summary>
/// <param name="tree">Дерево для разделения</param>
/// <param name="key">Ключ разделения</param>
/// <param name="left">Левый результат разделения</param>
/// <param name="right">Правый результат разделения</param>
void CartesianTreeSplit(CartesianTreeNode* tree, int key, CartesianTreeNode*& left, CartesianTreeNode*& right);

/// <summary>
/// Сливает два декартовых дерева
/// </summary>
/// <param name="left">Левое дерево</param>
/// <param name="right">Правое дерево</param>
/// <returns>Указатель на объединенное дерево</returns>
CartesianTreeNode* CartesianTreeMerge(CartesianTreeNode* left, CartesianTreeNode* right);

/// <summary>
/// Рекурсивно удаляет все узлы декартова дерева
/// </summary>
/// <param name="node">Корневой узел для удаления</param>
void DeleteCartesianTreeNodes(CartesianTreeNode* node);

/// <summary>
/// Создает пустое декартово дерево
/// </summary>
/// <returns>Указатель на созданное дерево</returns>
CartesianTree* CreateCartesianTree();

/// <summary>
/// Добавляет элемент в декартово дерево (неоптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <param name="priority">Приоритет добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool CartesianTreeAddUnoptimized(CartesianTree* tree, int key, const string& value, int priority);

/// <summary>
/// Добавляет элемент в декартово дерево (оптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <param name="priority">Приоритет добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool CartesianTreeAddOptimized(CartesianTree* tree, int key, const string& value, int priority);

/// <summary>
/// Удаляет элемент из декартова дерева (неоптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool CartesianTreeRemoveUnoptimized(CartesianTree* tree, int key);

/// <summary>
/// Удаляет элемент из декартова дерева (оптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool CartesianTreeRemoveOptimized(CartesianTree* tree, int key);

/// <summary>
/// Находит элемент в декартовом дереве
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string CartesianTreeFind(const CartesianTree* tree, int key);

/// <summary>
/// Удаляет декартово дерево и освобождает память
/// </summary>
/// <param name="tree">Дерево для удаления</param>
void DeleteCartesianTree(CartesianTree* tree);

/// <summary>
/// Получает приоритет элемента по ключу
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ элемента</param>
/// <returns>Приоритет элемента или -1 если элемент не найден</returns>
int CartesianTreeGetPriority(const CartesianTree* tree, int key);