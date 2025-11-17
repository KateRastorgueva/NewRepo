#include "TreeConsoleService.h"
#include <iostream>
#include <queue>

using namespace std;

void TreeConsoleService::PrintTitle(const string& title)
{
    cout << endl;
    cout << "=== " << title << " ===" << endl;
}

void TreeConsoleService::PrintBinarySearchTreeState(const BinarySearchTree* tree)
{
    if (tree == nullptr)
    {
        cout << "Ошибка: Дерево не создано" << endl;
        return;
    }

    PrintTitle("СОСТОЯНИЕ БИНАРНОГО ДЕРЕВА ПОИСКА");

    if (tree->Root == nullptr)
    {
        cout << "Информация: Дерево пустое" << endl;
        return;
    }

    PrintBSTLevelOrder(tree->Root);
    cout << endl;
}

void TreeConsoleService::PrintCartesianTreeState(const CartesianTree* tree)
{
    if (tree == nullptr)
    {
        cout << "Ошибка: Дерево не создано" << endl;
        return;
    }

    PrintTitle("СОСТОЯНИЕ ДЕКАРТОВА ДЕРЕВА");

    if (tree->Root == nullptr)
    {
        cout << "Информация: Дерево пустое" << endl;
        return;
    }

    PrintCartesianLevelOrder(tree->Root);
    cout << endl;
}

void TreeConsoleService::PrintBSTLevelOrder(const BinarySearchTreeNode* root)
{
    if (root == nullptr) return;

    queue<const BinarySearchTreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        int levelSize = nodeQueue.size();

        for (int i = 0; i < levelSize; i++)
        {
            const BinarySearchTreeNode* currentNode = nodeQueue.front();
            nodeQueue.pop();

            cout << currentNode->Key << "[" << currentNode->Value << "] ";

            if (currentNode->Left != nullptr)
                nodeQueue.push(currentNode->Left);
            if (currentNode->Right != nullptr)
                nodeQueue.push(currentNode->Right);
        }
        cout << endl;
    }
}

void TreeConsoleService::PrintCartesianLevelOrder(const CartesianTreeNode* root)
{
    if (root == nullptr) return;

    queue<const CartesianTreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        int levelSize = nodeQueue.size();

        for (int i = 0; i < levelSize; i++)
        {
            const CartesianTreeNode* currentNode = nodeQueue.front();
            nodeQueue.pop();

            cout << currentNode->Key << "[" << currentNode->Value << "](p:" << currentNode->Priority << ") ";

            if (currentNode->Left != nullptr)
                nodeQueue.push(currentNode->Left);
            if (currentNode->Right != nullptr)
                nodeQueue.push(currentNode->Right);
        }
        cout << endl;
    }
}