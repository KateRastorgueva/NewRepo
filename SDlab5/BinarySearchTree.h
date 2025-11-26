#pragma once
#include <string>
#include "TreeConstants.h" 
using namespace std;

/// <summary>
/// Узел бинарного дерева поиска
/// </summary>
struct BinarySearchTreeNode
{
    int Key;
    string Value;
    BinarySearchTreeNode* Left;
    BinarySearchTreeNode* Right;
};

/// <summary>
/// Бинарное дерево поиска
/// </summary>
struct BinarySearchTree
{
    BinarySearchTreeNode* Root;
    int Size;
};
/// <summary>
/// Создает пустое бинарное дерево поиска
/// </summary>
/// <returns>Указатель на созданное дерево</returns>
BinarySearchTree* CreateBinarySearchTree();

/// <summary>
/// Добавляет элемент в бинарное дерево поиска
/// </summary>
/// <param name="tree">Дерево для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool BinarySearchTreeAdd(BinarySearchTree* tree, int key, const string& value);

/// <summary>
/// Удаляет элемент из бинарного дерева поиска
/// </summary>
/// <param name="tree">Дерево для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool BinarySearchTreeRemove(BinarySearchTree* tree, int key);

/// <summary>
/// Находит элемент в бинарном дереве поиска
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string BinarySearchTreeFind(const BinarySearchTree* tree, int key);

/// <summary>
/// Находит минимальный элемент в дереве
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <returns>Значение минимального элемента или пустая строка если дерево пустое</returns>
string BinarySearchTreeFindMin(const BinarySearchTree* tree);

/// <summary>
/// Находит максимальный элемент в дереве
/// </summary>
/// <param name="tree">Дерево для поиска</param>
/// <returns>Значение максимального элемента или пустая строка если дерево пустое</returns>
string BinarySearchTreeFindMax(const BinarySearchTree* tree);

/// <summary>
/// Удаляет бинарное дерево поиска и освобождает память
/// </summary>
/// <param name="tree">Дерево для удаления</param>
void DeleteBinarySearchTree(BinarySearchTree* tree);
void DeleteBinarySearchTreeNodes(BinarySearchTreeNode* node);