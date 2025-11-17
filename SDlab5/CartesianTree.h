#pragma once
#include <string>

using namespace std;

/// <summary>
/// Узел декартова дерева
/// </summary>
struct CartesianTreeNode
{
    int Key;
    int Priority;
    string Value;
    CartesianTreeNode* Left;
    CartesianTreeNode* Right;
};
 
/// <summary>
/// Декартово дерево
/// </summary>
struct CartesianTree
{
    CartesianTreeNode* Root;
};

/// <summary>
/// Создает пустое декартово дерево
/// </summary>
/// <returns>Указатель на созданное дерево</returns>
CartesianTree* CreateCartesianTree();

/// <summary>
/// Разделяет декартово дерево по ключу
/// </summary>
/// <param name="tree">Дерево для разделения</param>
/// <param name="key">Ключ для разделения</param>
/// <param name="left">Выходной параметр для левого поддерева</param>
/// <param name="right">Выходной параметр для правого поддерева</param>
void CartesianTreeSplit(CartesianTreeNode* tree, int key, CartesianTreeNode*& left, CartesianTreeNode*& right);

/// <summary>
/// Сливает два декартовых дерева
/// </summary>
/// <param name="left">Левое дерево</param>
/// <param name="right">Правое дерево</param>
/// <returns>Результирующее дерево после слияния</returns>
CartesianTreeNode* CartesianTreeMerge(CartesianTreeNode* left, CartesianTreeNode* right);

/// <summary>
/// Добавляет элемент в декартово дерево (неоптимизированный алгоритм)
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <param name="priority">Приоритет элемента</param>
/// <returns>true если элемент добавлен</returns>
bool CartesianTreeAddUnoptimized(CartesianTree* tree, int key, const string& value, int priority);

/// <summary>
/// Добавляет элемент в декартово дерево (оптимизированный алгоритм)
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <param name="priority">Приоритет элемента</param>
/// <returns>true если элемент добавлен</returns>
bool CartesianTreeAddOptimized(CartesianTree* tree, int key, const string& value, int priority);

/// <summary>
/// Удаляет элемент из декартова дерева (неоптимизированный алгоритм)
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален</returns>
bool CartesianTreeRemoveUnoptimized(CartesianTree* tree, int key);

/// <summary>
/// Удаляет элемент из декартова дерева (оптимизированный алгоритм)
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален</returns>
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