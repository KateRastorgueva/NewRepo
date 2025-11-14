#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree* CreateBinarySearchTree()
{
    BinarySearchTree* tree = new BinarySearchTree;
    tree->Root = nullptr;
    return tree;
}

bool BinarySearchTreeAdd(BinarySearchTree* tree, int key, const string& value)
{
    if (tree == nullptr)
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
            return false;
        }
    }

    *current = new BinarySearchTreeNode;
    (*current)->Key = key;
    (*current)->Value = value;
    (*current)->Left = nullptr;
    (*current)->Right = nullptr;

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
            }
            else if (nodeToDelete->Right == nullptr)
            {
                *current = nodeToDelete->Left;
            }
            else
            {
                BinarySearchTreeNode* minNode = FindMinNode(nodeToDelete->Right);
                nodeToDelete->Key = minNode->Key;
                nodeToDelete->Value = minNode->Value;

                BinarySearchTreeNode** temp = &(nodeToDelete->Right);
                while ((*temp)->Key != minNode->Key)
                {
                    temp = &((*temp)->Left);
                }
                *temp = minNode->Right;
                nodeToDelete = minNode;
            }

            delete nodeToDelete;
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

    return current->Value;
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

    return current->Value;
}

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

void DeleteBinarySearchTree(BinarySearchTree* tree)
{
    if (tree == nullptr)
    {
        return;
    }

    DeleteBinarySearchTreeNodes(tree->Root);
    delete tree;
}