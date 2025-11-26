#include "CartesianTree.h"
#include "TreeConstants.h"
#include <iostream>

using namespace std;
void CartesianTreeSplit(CartesianTreeNode* tree, int key, CartesianTreeNode*& left, CartesianTreeNode*& right)
{
    if (tree == nullptr)
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

CartesianTreeNode* CartesianTreeMerge(CartesianTreeNode* left, CartesianTreeNode* right)
{
    if (left == nullptr)
    {
        return right;
    }
    if (right == nullptr)
    {
        return left;
    }

    if (left->Priority > right->Priority)
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
void DeleteCartesianTreeNodes(CartesianTreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    DeleteCartesianTreeNodes(node->Left);
    DeleteCartesianTreeNodes(node->Right);
    delete node;
}

CartesianTree* CreateCartesianTree()
{
    CartesianTree* tree = new CartesianTree;
    tree->Root = nullptr;
    tree->Size = 0;
    return tree;
}

bool CartesianTreeAddUnoptimized(CartesianTree* tree, int key, const string& value, int priority)
{
    if (tree == nullptr)
    {
        return false;
    }

    if (tree->Size >= maxCartesianTreeSize) {
        return false;
    }

    if (!CartesianTreeFind(tree, key).empty())
    {
        return false;
    }

    CartesianTreeNode* left = nullptr;
    CartesianTreeNode* right = nullptr;
    CartesianTreeSplit(tree->Root, key, left, right);

    CartesianTreeNode* newNode = new CartesianTreeNode;
    newNode->Key = key;
    newNode->Value = value;
    newNode->Priority = priority;
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    CartesianTreeNode* mergedLeft = CartesianTreeMerge(left, newNode);
    tree->Root = CartesianTreeMerge(mergedLeft, right);

    tree->Size++;
    return true;
}

bool CartesianTreeAddOptimized(CartesianTree* tree, int key, const string& value, int priority)
{
    if (tree == nullptr)
    {
        return false;
    }

    if (tree->Size >= maxCartesianTreeSize) {
        return false;
    }

    if (!CartesianTreeFind(tree, key).empty())
    {
        return false;
    }

    CartesianTreeNode* newNode = new CartesianTreeNode;
    newNode->Key = key;
    newNode->Value = value;
    newNode->Priority = priority;
    newNode->Left = nullptr;
    newNode->Right = nullptr;

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
        parent = *current;
        if (key < (*current)->Key)
        {
            current = &((*current)->Left);
        }
        else
        {
            current = &((*current)->Right);
        }
    }

    CartesianTreeNode* left = nullptr;
    CartesianTreeNode* right = nullptr;
    CartesianTreeSplit(*current, key, left, right);

    newNode->Left = left;
    newNode->Right = right;

    if (parent == nullptr)
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
bool CartesianTreeRemoveUnoptimized(CartesianTree* tree, int key)
{
    if (tree == nullptr || tree->Root == nullptr)
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

bool CartesianTreeRemoveOptimized(CartesianTree* tree, int key)
{
    if (tree == nullptr || tree->Root == nullptr)
    {
        return false;
    }

    CartesianTreeNode** current = &(tree->Root);
    CartesianTreeNode* parent = nullptr;

    while (*current != nullptr && (*current)->Key != key)
    {
        parent = *current;
        if (key < (*current)->Key)
        {
            current = &((*current)->Left);
        }
        else
        {
            current = &((*current)->Right);
        }
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

string CartesianTreeFind(const CartesianTree* tree, int key)
{
    if (tree == nullptr)
    {
        return "";
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
            return current->Value;
        }
    }

    return "";
}
void DeleteCartesianTree(CartesianTree* tree)
{
    if (tree == nullptr)
    {
        return;
    }

    DeleteCartesianTreeNodes(tree->Root);
    tree->Size = 0;
    delete tree;
}