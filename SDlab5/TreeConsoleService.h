#pragma once
#include <string>
#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include <vector>

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
    static int GetBinarySearchTreeHeight(const BinarySearchTreeNode* node);
    static int GetCartesianHeight(const CartesianTreeNode* node);
    static void GetBinarySearchTreeLine(const BinarySearchTreeNode* root, int depth, vector<int>& vals, vector<string>& dataVals);
    static void GetCartesianLine(const CartesianTreeNode* root, int depth, vector<int>& vals, vector<string>& dataVals, vector<int>& priorities);
    static void DisplayBinarySearchTree(const BinarySearchTreeNode* root);
    static void DisplayCartesianTree(const CartesianTreeNode* root);
};