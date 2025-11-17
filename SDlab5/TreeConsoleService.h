#pragma once
#include <string>
#include "BinarySearchTree.h"
#include "CartesianTree.h"

using namespace std;

class TreeConsoleService
{
public:
    static void PrintTitle(const string& title);
    static void PrintBinarySearchTreeState(const BinarySearchTree* tree);
    static void PrintCartesianTreeState(const CartesianTree* tree);

private:
    static void PrintBSTLevelOrder(const BinarySearchTreeNode* root);
    static void PrintCartesianLevelOrder(const CartesianTreeNode* root);
    static int GetBSTHeight(const BinarySearchTreeNode* node);
    static int GetCartesianHeight(const CartesianTreeNode* node);
    static void PrintBSTLevel(const BinarySearchTreeNode* node, int level);
    static void PrintCartesianLevel(const CartesianTreeNode* node, int level);
};