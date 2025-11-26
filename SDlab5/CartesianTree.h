#pragma once
#include <string>

using namespace std;

struct CartesianTreeNode
{
    int Key;
    string Value;
    int Priority;
    CartesianTreeNode* Left;
    CartesianTreeNode* Right;
};

struct CartesianTree
{
    CartesianTreeNode* Root;
    int Size;
};

CartesianTree* CreateCartesianTree();
void DeleteCartesianTree(CartesianTree* tree);
bool CartesianTreeAddUnoptimized(CartesianTree* tree, int key, const string& value, int priority);
bool CartesianTreeAddOptimized(CartesianTree* tree, int key, const string& value, int priority);
bool CartesianTreeRemoveUnoptimized(CartesianTree* tree, int key);
bool CartesianTreeRemoveOptimized(CartesianTree* tree, int key);
string CartesianTreeFind(const CartesianTree* tree, int key);
void CartesianTreeSplit(CartesianTreeNode* tree, int key, CartesianTreeNode*& left, CartesianTreeNode*& right);
CartesianTreeNode* CartesianTreeMerge(CartesianTreeNode* left, CartesianTreeNode* right);