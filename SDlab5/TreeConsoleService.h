#pragma once
#include <string>
#include <vector>
#include "BinarySearchTree.h"
#include "CartesianTree.h"

using namespace std;

class TreeConsoleService
{
public:
    // Структуры должны быть объявлены перед использованием
    struct CellDisplay {
        string valstr;
        bool present;
        CellDisplay() : present(false) {}
        CellDisplay(string valstr) : valstr(valstr), present(true) {}
    };

    using DisplayRows = vector<vector<CellDisplay>>;

    // Существующие функции
    static void PrintTitle(const string& title);
    static void PrintBinarySearchTreeState(const BinarySearchTree* tree);
    static void PrintCartesianTreeState(const CartesianTree* tree);
    static void DisplayBinarySearchTree(const BinarySearchTreeNode* root);
    static void DisplayCartesianTree(const CartesianTreeNode* root);

    // Новые функции для вывода сообщений
    static void PrintError(const string& message);
    static void PrintSuccess(const string& message);
    static void PrintInfo(const string& message);
    static void PrintWarning(const string& message);

    static void PrintTreeCreated(const string& treeType);
    static void PrintTreeDeleted(const string& treeType);
    static void PrintElementAdded(const string& method = "");
    static void PrintElementRemoved(const string& method = "");
    static void PrintElementFound(const string& value);
    static void PrintElementNotFound();
    static void PrintTreeIsEmpty();
    static void PrintKeyAlreadyExists();
    static void PrintMaxSizeReached(int maxSize);
    static void PrintTreeGenerated(int elementsAdded, const string& treeType);

private:
    // Вспомогательные функции
    static int GetBinarySearchTreeMaxDepth(const BinarySearchTreeNode* node);
    static int GetCartesianTreeMaxDepth(const CartesianTreeNode* node);
    static DisplayRows GetBinarySearchTreeRowDisplay(const BinarySearchTreeNode* root);
    static DisplayRows GetCartesianTreeRowDisplay(const CartesianTreeNode* root);
    static vector<string> BinarySearchTreeRowFormatter(const DisplayRows& rows_disp);
    static vector<string> CartesianTreeRowFormatter(const DisplayRows& rows_disp);
    static void TrimRowsLeft(vector<string>& rows);
    static void PrintFormattedBinarySearchTree(const BinarySearchTreeNode* root);
    static void PrintFormattedCartesianTree(const CartesianTreeNode* root);
};