#include "CartesianTree.h"
#include "Validator.h"
#include "Constants.h"
#include <iostream>

using namespace std;

/// <summary>
/// Находит узел в декартовом дереве по указанному ключу
/// </summary>
/// <param name="tree">Указатель на декартово дерево</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Указатель на найденный узел или nullptr, если узел не найден</returns>
CartesianTreeNode* FindCartesianTreeNode(const CartesianTree* tree, int key)
{
    if (!tree)
    {
        return nullptr;
    }

    CartesianTreeNode* current = tree->Root;

    while (current != nullptr)
    {
        if (key < current->Key)
        {
            current = current->Left;
        }
        else if (key > current->Key)
        {
            current = current->Right;
        }
        else
        {
            return current;
        }
    }

    return nullptr;
}

/// <summary>
/// Проверяет, является ли декартово дерево полным
/// </summary>
/// <param name="tree">Указатель на декартово дерево</param>
/// <returns>true если дерево полное, иначе false</returns>
bool IsTreeFull(const CartesianTree* tree)
{
    return tree->Size >= maxCartesianTreeSize;
}

/// <summary>
/// Проверяет, является ли декартово дерево пустым
/// </summary>
/// <param name="tree">Указатель на декартово дерево</param>
/// <returns>true если дерево пустое, иначе false</returns>
bool IsTreeEmpty(const CartesianTree* tree)
{
    return tree == nullptr || tree->Root == nullptr;
}

/// <summary>
/// Перемещает указатель на указатель на узел в зависимости от ключа (для изменения структуры)
/// </summary>
/// <param name="current">Указатель на указатель на текущий узел</param>
/// <param name="parent">Ссылка на указатель родителя</param>
/// <param name="key">Ключ для сравнения</param>
/// <returns>true если двигались влево, false если вправо</returns>
bool MoveCartesianTreeNodePointer(CartesianTreeNode**& current, CartesianTreeNode*& parent, int key)
{
    parent = *current;
    if (key < (*current)->Key)
    {
        current = &((*current)->Left);
        return true;
    }
    else
    {
        current = &((*current)->Right);
        return false;
    }
}

/// <summary>
/// Проверяет существование ключа в декартовом дереве
/// </summary>
/// <param name="tree">Указатель на декартово дерево</param>
/// <param name="key">Ключ для проверки</param>
/// <returns>true если ключ существует, иначе false</returns>
bool KeyExists(const CartesianTree* tree, int key)
{
    return FindCartesianTreeNode(tree, key) != nullptr;
}

/// <summary>
/// Создает новый узел декартова дерева
/// </summary>
/// <param name="key">Ключ узла</param>
/// <param name="value">Значение узла</param>
/// <param name="priority">Приоритет узла</param>
/// <returns>Указатель на созданный узел</returns>
CartesianTreeNode* CreateCartesianTreeNode(int key, const string& value, int priority)
{
    CartesianTreeNode* node = new CartesianTreeNode;
    node->Key = key;
    node->Value = value;
    node->Priority = priority;
    node->Left = nullptr;
    node->Right = nullptr;
    return node;
}

/// <summary>
/// Разделяет декартово дерево по ключу
/// </summary>
/// <param name="tree">Дерево для разделения</param>
/// <param name="key">Ключ разделения</param>
/// <param name="left">Левый результат разделения</param>
/// <param name="right">Правый результат разделения</param>
void CartesianTreeSplit(CartesianTreeNode* tree, int key, CartesianTreeNode*& left, CartesianTreeNode*& right)
{
    if (!tree)
    {
        left = nullptr;
        right = nullptr;
    }
    else if (tree->Key <= key)
    {
        CartesianTreeNode* newRight = nullptr;
        CartesianTreeSplit(tree->Right, key, newRight, right);
        left = tree;
        left->Right = newRight;
    }
    else
    {
        CartesianTreeNode* newLeft = nullptr;
        CartesianTreeSplit(tree->Left, key, left, newLeft);
        right = tree;
        right->Left = newLeft;
    }
}

/// <summary>
/// Сливает два декартовых дерева
/// </summary>
/// <param name="left">Левое дерево</param>
/// <param name="right">Правое дерево</param>
/// <returns>Указатель на объединенное дерево</returns>
CartesianTreeNode* CartesianTreeMerge(CartesianTreeNode* left, CartesianTreeNode* right)
{
    if (!left)
    {
        return right;
    }
    if (!right)
    {
        return left;
    }

    if (left->Priority > right->Priority)
    {
        left->Right = CartesianTreeMerge(left->Right, right);
        return left;
    }
    else if (left->Priority < right->Priority)
    {
        right->Left = CartesianTreeMerge(left, right->Left);
        return right;
    }
    else
    {
        if (left->Key < right->Key)
        {
            left->Right = CartesianTreeMerge(left->Right, right);
            return left;
        }
        else
        {
            right->Left = CartesianTreeMerge(left, right->Left);
            return right;
        }
    }
}

/// <summary>
/// Рекурсивно удаляет все узлы декартова дерева
/// </summary>
/// <param name="node">Корневой узел для удаления</param>
void DeleteCartesianTreeNodes(CartesianTreeNode* node)
{
    if (!node)
    {
        return;
    }

    DeleteCartesianTreeNodes(node->Left);
    DeleteCartesianTreeNodes(node->Right);
    delete node;
}

/// <summary>
/// Создает пустое декартово дерево
/// </summary>
/// <returns>Указатель на созданное дерево</returns>
CartesianTree* CreateCartesianTree()
{
    CartesianTree* tree = new CartesianTree;
    tree->Root = nullptr;
    tree->Size = 0;
    return tree;
}

/// <summary>
/// Добавляет элемент в декартово дерево (неоптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <param name="priority">Приоритет добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool CartesianTreeAddUnoptimized(CartesianTree* tree, int key, const string& value, int priority)
{
    if (!tree)
    {
        return false;
    }

    if (IsTreeFull(tree))
    {
        return false;
    }

    if (KeyExists(tree, key))
    {
        return false;
    }

    CartesianTreeNode* left = nullptr;
    CartesianTreeNode* right = nullptr;
    CartesianTreeSplit(tree->Root, key, left, right);

    CartesianTreeNode* newNode = CreateCartesianTreeNode(key, value, priority);

    CartesianTreeNode* mergedLeft = CartesianTreeMerge(left, newNode);
    tree->Root = CartesianTreeMerge(mergedLeft, right);

    tree->Size++;
    return true;
}

/// <summary>
/// Добавляет элемент в декартово дерево (оптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <param name="priority">Приоритет добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool CartesianTreeAddOptimized(CartesianTree* tree, int key, const string& value, int priority)
{
    if (!tree)
    {
        return false;
    }

    if (IsTreeFull(tree))
    {
        return false;
    }

    if (KeyExists(tree, key))
    {
        return false;
    }

    CartesianTreeNode* newNode = CreateCartesianTreeNode(key, value, priority);

    if (tree->Root == nullptr)
    {
        tree->Root = newNode;
        tree->Size = 1;
        return true;
    }

    CartesianTreeNode** current = &(tree->Root);
    CartesianTreeNode* parent = nullptr;

    while (*current != nullptr && (*current)->Priority > priority)
    {
        MoveCartesianTreeNodePointer(current, parent, key);
    }

    CartesianTreeNode* left = nullptr;
    CartesianTreeNode* right = nullptr;
    CartesianTreeSplit(*current, key, left, right);

    newNode->Left = left;
    newNode->Right = right;

    if (!parent)
    {
        tree->Root = newNode;
    }
    else if (key < parent->Key)
    {
        parent->Left = newNode;
    }
    else
    {
        parent->Right = newNode;
    }

    tree->Size++;
    return true;
}

/// <summary>
/// Удаляет элемент из декартова дерева (неоптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool CartesianTreeRemoveUnoptimized(CartesianTree* tree, int key)
{
    if (IsTreeEmpty(tree))
    {
        return false;
    }

    CartesianTreeNode* left1 = nullptr;
    CartesianTreeNode* right1 = nullptr;
    CartesianTreeSplit(tree->Root, key - 1, left1, right1);

    CartesianTreeNode* left2 = nullptr;
    CartesianTreeNode* right2 = nullptr;
    CartesianTreeSplit(right1, key, left2, right2);

    if (left2 != nullptr)
    {
        delete left2;
        tree->Root = CartesianTreeMerge(left1, right2);
        tree->Size--;
        return true;
    }
    else
    {
        tree->Root = CartesianTreeMerge(left1, right1);
        return false;
    }
}

/// <summary>
/// Удаляет элемент из декартова дерева (оптимизированный метод)
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool CartesianTreeRemoveOptimized(CartesianTree* tree, int key)
{
    if (IsTreeEmpty(tree))
    {
        return false;
    }

    CartesianTreeNode** current = &(tree->Root);
    CartesianTreeNode* parent = nullptr;

    while (*current != nullptr && (*current)->Key != key)
    {
        MoveCartesianTreeNodePointer(current, parent, key);
    }

    if (*current == nullptr)
    {
        return false;
    }

    CartesianTreeNode* nodeToDelete = *current;
    *current = CartesianTreeMerge(nodeToDelete->Left, nodeToDelete->Right);
    delete nodeToDelete;

    tree->Size--;
    return true;
}

/// <summary>
/// Находит элемент в декартовом дереве
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string CartesianTreeFind(const CartesianTree* tree, int key)
{
    CartesianTreeNode* node = FindCartesianTreeNode(tree, key);
    if (node != nullptr)
    {
        return node->Value;
    }
    return "";
}

/// <summary>
/// Удаляет декартово дерево и освобождает память
/// </summary>
/// <param name="tree">Дерево для удаления</param>
void DeleteCartesianTree(CartesianTree* tree)
{
    if (!tree)
    {
        return;
    }

    DeleteCartesianTreeNodes(tree->Root);
    tree->Size = 0;
    delete tree;
}

/// <summary>
/// Получает приоритет элемента по ключу
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ элемента</param>
/// <returns>Приоритет элемента или -1 если элемент не найден</returns>
int CartesianTreeGetPriority(const CartesianTree* tree, int key)
{
    CartesianTreeNode* node = FindCartesianTreeNode(tree, key);
    if (node != nullptr)
    {
        return node->Priority;
    }
    return -1;
}