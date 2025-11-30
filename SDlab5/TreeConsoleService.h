#pragma once
#include <string>
#include <vector>
#include "BinarySearchTree.h"
#include "CartesianTree.h"

using namespace std;

class TreeConsoleService
{
public:
    struct CellDisplay
    {
        string valstr;
        bool present;

        CellDisplay() : present(false) {}
        CellDisplay(string valstr) : valstr(valstr), present(true) {}
    };

    using DisplayRow = vector<CellDisplay>;
    using DisplayRows = vector<DisplayRow>;

    // Основные публичные методы
    static void PrintTitle(const string& title);
    static void PrintBinarySearchTreeState(const BinarySearchTree* tree);
    static void PrintCartesianTreeState(const CartesianTree* tree);
    static void DisplayBinarySearchTree(const BinarySearchTreeNode* root);
    static void DisplayCartesianTree(const CartesianTreeNode* root);
    static int GetPriorityInput();

    // Методы для вывода сообщений
    static void PrintError(const string& message);
    static void PrintSuccess(const string& message);
    static void PrintInfo(const string& message);
    static void PrintWarning(const string& message);
    static string GetValueInput();
    static int GetKeyInput(const string& value = "Введите ключ: ");

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
    // Вспомогательные функции для работы с деревьями
    template<typename TreeNode>
    static int GetTreeMaxDepth(const TreeNode* node);

    static DisplayRows GetBinarySearchTreeRowDisplay(const BinarySearchTreeNode* root);
    static DisplayRows GetCartesianTreeRowDisplay(const CartesianTreeNode* root);
    static vector<string> BinarySearchTreeRowFormatter(const DisplayRows& rowsDisplay);
    static vector<string> CartesianTreeRowFormatter(const DisplayRows& rowsDisplay);
    static void TrimRowsLeft(vector<string>& rows);
    static void PrintFormattedBinarySearchTree(const BinarySearchTreeNode* root);
    static void PrintFormattedCartesianTree(const CartesianTreeNode* root);
};