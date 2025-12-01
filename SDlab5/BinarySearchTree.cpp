#include "BinarySearchTree.h"
#include "Validator.h"
#include <iostream>

using namespace std;

/// <summary>
/// Проверяет, является ли дерево пустым
/// </summary>
/// <param name="tree">Указатель на дерево</param>
/// <returns>true если дерево пустое, иначе false</returns>
bool IsTreeEmpty(const BinarySearchTree* tree)
{
    return !tree || tree->Root == nullptr;
}

/// <summary>
/// Проверяет, является ли дерево полным
/// </summary>
/// <param name="tree">Указатель на дерево</param>
/// <returns>true если дерево полное, иначе false</returns>
bool IsTreeFull(const BinarySearchTree* tree)
{
    return tree->Size >= maxBinaryTreeSize;
}

/// <summary>
/// Рекурсивно удаляет все узлы дерева
/// </summary>
/// <param name="node">Корневой узел для удаления</param>
void DeleteBinarySearchTreeNodes(BinarySearchTreeNode* node)
{
    if (!node)
    {
        return;
    }

    DeleteBinarySearchTreeNodes(node->Left);
    DeleteBinarySearchTreeNodes(node->Right);
    delete node;
}

/// <summary>
/// Создает пустое бинарное дерево поиска
/// </summary>
/// <returns>Указатель на созданное дерево</returns>
BinarySearchTree* CreateBinarySearchTree()
{
    BinarySearchTree* tree = new BinarySearchTree;
    tree->Root = nullptr;
    tree->Size = 0;
    return tree;
}

/// <summary>
/// Находит место узла в дереве по ключу
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Указатель на указатель на узел или nullptr если дерево пустое</returns>
BinarySearchTreeNode** FindNodeOrInsertLocation(BinarySearchTree* tree, int key)
{
    if (!tree)
    {
        return nullptr;
    }

    BinarySearchTreeNode** current = &(tree->Root);

    while (*current != nullptr)
    {
        if (key < (*current)->Key)
        {
            current = &((*current)->Left);
        }
        else if (key > (*current)->Key)
        {
            current = &((*current)->Right);
        }
        else
        {
            return current;
        }
    }
    return current;
}

/// <summary>
/// Добавляет элемент в бинарное дерево поиска
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool BinarySearchTreeAdd(BinarySearchTree* tree, int key, const string& value)
{
    if (!tree || tree->Size >= maxBinaryTreeSize)
    {
        return false;
    }

    BinarySearchTreeNode** current = FindNodeOrInsertLocation(tree, key);

    if (*current != nullptr)
    {
        return false;
    }

    *current = new BinarySearchTreeNode;
    (*current)->Key = key;
    (*current)->Value = value;
    (*current)->Left = nullptr;
    (*current)->Right = nullptr;

    tree->Size++;
    return true;
}

/// <summary>
/// Находит узел с минимальным ключом в поддереве
/// </summary>
/// <param name="node">Корневой узел поддерева</param>
/// <returns>Указатель на узел с минимальным ключом</returns>
BinarySearchTreeNode* FindMinNode(BinarySearchTreeNode* node)
{
    while (node != nullptr && node->Left != nullptr)
    {
        node = node->Left;
    }
    return node;
}

/// <summary>
/// Удаляет элемент из бинарного дерева поиска
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool BinarySearchTreeRemove(BinarySearchTree* tree, int key)
{
    if (IsTreeEmpty(tree))
    {
        return false;
    }

    BinarySearchTreeNode** current = FindNodeOrInsertLocation(tree, key);

    if (*current == nullptr)
    {
        return false;
    }

    BinarySearchTreeNode* nodeToDelete = *current;

    if (nodeToDelete->Left == nullptr)
    {
        *current = nodeToDelete->Right;
        delete nodeToDelete;
    }
    else if (nodeToDelete->Right == nullptr)
    {
        *current = nodeToDelete->Left;
        delete nodeToDelete;
    }
    else
    {
        BinarySearchTreeNode* minNodeParent = nodeToDelete;
        BinarySearchTreeNode* minNode = nodeToDelete->Right;

        while (minNode->Left != nullptr)
        {
            minNodeParent = minNode;
            minNode = minNode->Left;
        }

        nodeToDelete->Key = minNode->Key;
        nodeToDelete->Value = minNode->Value;

        if (minNodeParent == nodeToDelete)
        {
            minNodeParent->Right = minNode->Right;
        }
        else
        {
            minNodeParent->Left = minNode->Right;
        }
        delete minNode;
    }
    tree->Size--;
    return true;
}

/// <summary>
/// Находит элемент в бинарном дереве поиска
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string BinarySearchTreeFind(const BinarySearchTree* tree, int key)
{
    if (!tree)
    {
        return "";
    }

    BinarySearchTreeNode* current = tree->Root;

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
            return current->Value;
        }
    }

    return "";
}

/// <summary>
/// Находит минимальный элемент в дереве
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <returns>Значение минимального элемента или пустая строка если дерево пустое</returns>
string BinarySearchTreeFindMin(const BinarySearchTree* tree)
{
    if (IsTreeEmpty(tree))
    {
        return "";
    }

    BinarySearchTreeNode* current = tree->Root;
    while (current->Left != nullptr)
    {
        current = current->Left;
    }

    return to_string(current->Key) + "[" + current->Value + "]";
}

/// <summary>
/// Находит максимальный элемент в дереве
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <returns>Значение максимального элемента или пустая строка если дерево пустое</returns>
string BinarySearchTreeFindMax(const BinarySearchTree* tree)
{
    if (IsTreeEmpty(tree))
    {
        return "";
    }

    BinarySearchTreeNode* current = tree->Root;
    while (current->Right != nullptr)
    {
        current = current->Right;
    }

    return to_string(current->Key) + "[" + current->Value + "]";
}

/// <summary>
/// Удаляет бинарное дерево поиска и освобождает память
/// </summary>
/// <param name="tree">Дерево для удаления</param>
void DeleteBinarySearchTree(BinarySearchTree* tree)
{
    if (!tree)
    {
        return;
    }

    DeleteBinarySearchTreeNodes(tree->Root);
    tree->Size = 0;
    delete tree;
}