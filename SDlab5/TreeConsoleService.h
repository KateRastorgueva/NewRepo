#ifndef TREECONSOLESERVICE_H
#define TREECONSOLESERVICE_H

#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include <string>
#include <vector>

class TreeConsoleService
{
public:
    static void PrintTitle(const std::string& title);
    static void PrintBinarySearchTreeState(const BinarySearchTree* tree);
    static void PrintCartesianTreeState(const CartesianTree* tree);

private:
    struct CellDisplay {
        std::string valstr;
        bool present;
        CellDisplay() : present(false) {}
        CellDisplay(std::string valstr) : valstr(valstr), present(true) {}
    };

    using DisplayRows = std::vector<std::vector<CellDisplay>>;

    static void DisplayBinarySearchTree(const BinarySearchTreeNode* root);
    static void DisplayCartesianTree(const CartesianTreeNode* root);

    // Binary Search Tree display functions
    static DisplayRows GetBSTRowDisplay(const BinarySearchTreeNode* root);
    static std::vector<std::string> BSTRowFormatter(const DisplayRows& rows_disp);
    static void TrimRowsLeft(std::vector<std::string>& rows);
    static void PrintFormattedBST(const BinarySearchTreeNode* root);

    // Cartesian Tree display functions  
    static DisplayRows GetCartesianRowDisplay(const CartesianTreeNode* root);
    static std::vector<std::string> CartesianRowFormatter(const DisplayRows& rows_disp);
    static void PrintFormattedCartesian(const CartesianTreeNode* root);

    static int GetBSTMaxDepth(const BinarySearchTreeNode* node);
    static int GetCartesianMaxDepth(const CartesianTreeNode* node);
};

#endif