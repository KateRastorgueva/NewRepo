#include "TreeConsoleService.h"
#include <iostream>

void TreeConsoleService::PrintTitle(const string& title)
{
    cout << endl;
    cout << "=== " << title << " ===" << endl;
}

void TreeConsoleService::PrintBinarySearchTreeState(const BinarySearchTree* tree)
{
    if (tree == nullptr)
    {
        cout << "Îøèáêà: Äåðåâî íå ñîçäàíî" << endl;
        return;
    }

    PrintTitle("ÑÎÑÒÎßÍÈÅ ÁÈÍÀÐÍÎÃÎ ÄÅÐÅÂÀ ÏÎÈÑÊÀ");

    if (tree->Root == nullptr)
    {
        cout << "Èíôîðìàöèÿ: Äåðåâî ïóñòîå" << endl;
        return;
    }

    PrintBinarySearchTreeNode(tree->Root);
    cout << endl;
}

void TreeConsoleService::PrintCartesianTreeState(const CartesianTree* tree)
{
    if (tree == nullptr)
    {
        cout << "Îøèáêà: Äåðåâî íå ñîçäàíî" << endl;
        return;
    }

    PrintTitle("ÑÎÑÒÎßÍÈÅ ÄÅÊÀÐÒÎÂÀ ÄÅÐÅÂÀ");

    if (tree->Root == nullptr)
    {
        cout << "Èíôîðìàöèÿ: Äåðåâî ïóñòîå" << endl;
        return;
    }

    PrintCartesianTreeNode(tree->Root);
    cout << endl;
}

void TreeConsoleService::PrintBinarySearchTreeNode(const BinarySearchTreeNode* node, const string& prefix, bool isLeft)
{
    if (node == nullptr)
    {
        return;
    }

    cout << prefix;
    cout << (isLeft ? "??? " : "??? ");
    cout << node->Key << " [" << node->Value << "]" << endl;

    string newPrefix = prefix + (isLeft ? "?   " : "    ");
    PrintBinarySearchTreeNode(node->Left, newPrefix, true);
    PrintBinarySearchTreeNode(node->Right, newPrefix, false);
}

void TreeConsoleService::PrintCartesianTreeNode(const CartesianTreeNode* node, const string& prefix, bool isLeft)
{
    if (node == nullptr)
    {
        return;
    }

    cout << prefix;
    cout << (isLeft ? "??? " : "??? ");
    cout << node->Key << " [" << node->Value << "] (ïðèîðèòåò: " << node->Priority << ")" << endl;

    string newPrefix = prefix + (isLeft ? "?   " : "    ");
    PrintCartesianTreeNode(node->Left, newPrefix, true);
    PrintCartesianTreeNode(node->Right, newPrefix, false);
}