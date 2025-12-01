#pragma once
#include <string>
#include <vector>
#include "BinarySearchTree.h"
#include "CartesianTree.h"

using namespace std;

/// <summary>
/// Структура для отображения ячейки дерева
/// <see href="https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c"/>
/// </summary>
struct TreeCellDisplay
{
    string valueString;
    bool present;

    TreeCellDisplay() : present(false) {}
    TreeCellDisplay(string valueString) : valueString(valueString), present(true) {}
};

/// <summary>
/// Отображает бинарное дерево поиска в консоли
/// </summary>
/// <param name="root">Корень дерева</param>
void DisplayBinarySearchTree(const BinarySearchTreeNode* root);

/// <summary>
/// Отображает декартово дерево в консоли
/// </summary>
/// <param name="root">Корень дерева</param>
void DisplayCartesianTree(const CartesianTreeNode* root);