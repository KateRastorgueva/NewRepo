#include "BinarySearchTree.h"
#include "TreeConstants.h"
#include <iostream>

using namespace std;

void DeleteBinarySearchTreeNodes(BinarySearchTreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    DeleteBinarySearchTreeNodes(node->Left);
    DeleteBinarySearchTreeNodes(node->Right);
    delete node;
}

BinarySearchTree* CreateBinarySearchTree()
{
    BinarySearchTree* tree = new BinarySearchTree;
    tree->Root = nullptr;
    tree->Size = 0;
    return tree;
}

bool BinarySearchTreeAdd(BinarySearchTree* tree, int key, const string& value)
{
    if (tree == nullptr)
    {
        return false;
    }

    if (tree->Size >= maxBinaryTreeSize) {
        return false;
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
            return false;
        }
    }

    *current = new BinarySearchTreeNode;
    (*current)->Key = key;
    (*current)->Value = value;
    (*current)->Left = nullptr;
    (*current)->Right = nullptr;

    tree->Size++;
    return true;
}

BinarySearchTreeNode* FindMinNode(BinarySearchTreeNode* node)
{
    while (node != nullptr && node->Left != nullptr)
    {
        node = node->Left;
    }
    return node;
}

bool BinarySearchTreeRemove(BinarySearchTree* tree, int key)
{
    if (tree == nullptr || tree->Root == nullptr)
    {
        return false;
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
                    minNodeParent->Right = minNode->Right;
                else
                    minNodeParent->Left = minNode->Right;

                delete minNode;
            }
            tree->Size--;
            return true;
        }
    }

    return false;
}

string BinarySearchTreeFind(const BinarySearchTree* tree, int key)
{
    if (tree == nullptr)
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

string BinarySearchTreeFindMin(const BinarySearchTree* tree)
{
    if (tree == nullptr || tree->Root == nullptr)
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

string BinarySearchTreeFindMax(const BinarySearchTree* tree)
{
    if (tree == nullptr || tree->Root == nullptr)
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


void DeleteBinarySearchTree(BinarySearchTree* tree)
{
    if (tree == nullptr)
    {
        return;
    }

    DeleteBinarySearchTreeNodes(tree->Root);
    tree->Size = 0;
    delete tree;
}