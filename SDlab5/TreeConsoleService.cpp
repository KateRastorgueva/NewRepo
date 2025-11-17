#include "TreeConsoleService.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
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

    DisplayBinarySearchTree(tree->Root);
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
    DisplayCartesianTree(tree->Root);
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

int TreeConsoleService::GetBinarySearchTreeHeight(const BinarySearchTreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(GetBinarySearchTreeHeight(node->Left), GetBinarySearchTreeHeight(node->Right));
}

void TreeConsoleService::GetBinarySearchTreeLine(const BinarySearchTreeNode* root, int depth, vector<int>& vals, vector<string>& dataVals) {
    const int PLACEHOLDER = -999999;
    if (depth <= 0 && root != nullptr) {
        vals.push_back(root->Key);
        dataVals.push_back(root->Value);
        return;
    }
    if (root->Left != nullptr)
        GetBinarySearchTreeLine(root->Left, depth - 1, vals, dataVals);
    else if (depth - 1 <= 0) {
        vals.push_back(PLACEHOLDER);
        dataVals.push_back("");
    }
    if (root->Right != nullptr)
        GetBinarySearchTreeLine(root->Right, depth - 1, vals, dataVals);
    else if (depth - 1 <= 0) {
        vals.push_back(PLACEHOLDER);
        dataVals.push_back("");
    }
}

void TreeConsoleService::DisplayBinarySearchTree(const BinarySearchTreeNode* root) {
    if (root == nullptr) {
        cout << "<empty tree>" << endl;
        return;
    }

    int height = GetBinarySearchTreeHeight(root);
    if (height == 0) {
        cout << "<empty tree>" << endl;
        return;
    }

    vector<vector<string>> lines;

    for (int i = 0; i < height; i++) {
        vector<int> keys;
        vector<string> values;
        GetBinarySearchTreeLine(root, i, keys, values);

        vector<string> line;
        for (size_t j = 0; j < keys.size(); j++) {
            if (keys[j] != -999999) {
                stringstream ss;
                ss << keys[j] << "[" << values[j] << "]";
                line.push_back(ss.str());
            }
            else {
                line.push_back("");
            }
        }
        lines.push_back(line);
    }

    int maxWidth = 0;
    for (const auto& line : lines) {
        for (const auto& item : line) {
            if (item.length() > maxWidth) {
                maxWidth = item.length();
            }
        }
    }

    if (maxWidth % 2 == 0) maxWidth += 1;

    for (int i = 0; i < height; i++) {
        int spacesBefore = (1 << (height - i - 1)) - 1;
        int spacesBetween = (1 << (height - i)) - 1;
        for (int s = 0; s < spacesBefore * (maxWidth / 2 + 1); s++)
            cout << " ";
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (!lines[i][j].empty()) {
                cout << lines[i][j];
                int padding = maxWidth - lines[i][j].length();
                for (int p = 0; p < padding; p++) cout << " ";
            }
            else {
                for (int p = 0; p < maxWidth; p++) cout << " ";
            }

            if (j < lines[i].size() - 1) {
                for (int s = 0; s < spacesBetween * (maxWidth / 2 + 1); s++)
                    cout << " ";
            }
        }
        cout << endl;
        if (i < height - 1) {
            for (int s = 0; s < spacesBefore * (maxWidth / 2 + 1); s++)
                cout << " ";

            for (size_t j = 0; j < lines[i].size(); j++) {
                if (!lines[i][j].empty()) {
                    bool hasLeft = (j * 2 < lines[i + 1].size()) && !lines[i + 1][j * 2].empty();
                    bool hasRight = (j * 2 + 1 < lines[i + 1].size()) && !lines[i + 1][j * 2 + 1].empty();

                    if (hasLeft) {
                        cout << "/";
                        for (int p = 1; p < maxWidth / 2; p++) cout << " ";
                    }
                    else {
                        for (int p = 0; p < maxWidth / 2 + 1; p++) cout << " ";
                    }

                    if (hasRight) {
                        for (int p = 0; p < maxWidth / 2; p++) cout << " ";
                        cout << "\\";
                    }
                    else {
                        for (int p = 0; p < maxWidth / 2 + 1; p++) cout << " ";
                    }
                }
                else {
                    for (int p = 0; p < maxWidth + 1; p++) cout << " ";
                }
                if (j < lines[i].size() - 1) {
                    for (int s = 0; s < spacesBetween * (maxWidth / 2 + 1) - maxWidth - 1; s++)
                        cout << " ";
                }
            }
            cout << endl;
        }
    }
}

int TreeConsoleService::GetCartesianHeight(const CartesianTreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(GetCartesianHeight(node->Left), GetCartesianHeight(node->Right));
}

void TreeConsoleService::GetCartesianLine(const CartesianTreeNode* root, int depth, vector<int>& vals, vector<string>& dataVals, vector<int>& priorities) {
    const int PLACEHOLDER = -999999;
    if (depth <= 0 && root != nullptr) {
        vals.push_back(root->Key);
        dataVals.push_back(root->Value);
        priorities.push_back(root->Priority);
        return;
    }
    if (root->Left != nullptr)
        GetCartesianLine(root->Left, depth - 1, vals, dataVals, priorities);
    else if (depth - 1 <= 0) {
        vals.push_back(PLACEHOLDER);
        dataVals.push_back("");
        priorities.push_back(PLACEHOLDER);
    }
    if (root->Right != nullptr)
        GetCartesianLine(root->Right, depth - 1, vals, dataVals, priorities);
    else if (depth - 1 <= 0) {
        vals.push_back(PLACEHOLDER);
        dataVals.push_back("");
        priorities.push_back(PLACEHOLDER);
    }
}

void TreeConsoleService::DisplayCartesianTree(const CartesianTreeNode* root) {
    if (root == nullptr) {
        cout << "<empty tree>" << endl;
        return;
    }

    int height = GetCartesianHeight(root);
    if (height == 0) {
        cout << "<empty tree>" << endl;
        return;
    }

    vector<vector<string>> lines;

    for (int i = 0; i < height; i++) {
        vector<int> keys;
        vector<string> values;
        vector<int> priorities;
        GetCartesianLine(root, i, keys, values, priorities);

        vector<string> line;
        for (size_t j = 0; j < keys.size(); j++) {
            if (keys[j] != -999999) {
                stringstream ss;
                ss << keys[j] << "[" << values[j] << "](p:" << priorities[j] << ")";
                line.push_back(ss.str());
            }
            else {
                line.push_back("");
            }
        }
        lines.push_back(line);
    }
    int maxWidth = 0;
    for (const auto& line : lines) {
        for (const auto& item : line) {
            if (item.length() > maxWidth) {
                maxWidth = item.length();
            }
        }
    }

    if (maxWidth % 2 == 0) maxWidth += 1;
    for (int i = 0; i < height; i++) {
        int spacesBefore = (1 << (height - i - 1)) - 1;
        int spacesBetween = (1 << (height - i)) - 1;

        for (int s = 0; s < spacesBefore * (maxWidth / 2 + 1); s++)
            cout << " ";

        for (size_t j = 0; j < lines[i].size(); j++) {
            if (!lines[i][j].empty()) {
                cout << lines[i][j];
                int padding = maxWidth - lines[i][j].length();
                for (int p = 0; p < padding; p++) cout << " ";
            }
            else {
                for (int p = 0; p < maxWidth; p++) cout << " ";
            }
            if (j < lines[i].size() - 1) {
                for (int s = 0; s < spacesBetween * (maxWidth / 2 + 1); s++)
                    cout << " ";
            }
        }
        cout << endl;

        if (i < height - 1) {
            for (int s = 0; s < spacesBefore * (maxWidth / 2 + 1); s++)
                cout << " ";

            for (size_t j = 0; j < lines[i].size(); j++) {
                if (!lines[i][j].empty()) {
                    bool hasLeft = (j * 2 < lines[i + 1].size()) && !lines[i + 1][j * 2].empty();
                    bool hasRight = (j * 2 + 1 < lines[i + 1].size()) && !lines[i + 1][j * 2 + 1].empty();

                    if (hasLeft) {
                        cout << "/";
                        for (int p = 1; p < maxWidth / 2; p++) cout << " ";
                    }
                    else {
                        for (int p = 0; p < maxWidth / 2 + 1; p++) cout << " ";
                    }

                    if (hasRight) {
                        for (int p = 0; p < maxWidth / 2; p++) cout << " ";
                        cout << "\\";
                    }
                    else {
                        for (int p = 0; p < maxWidth / 2 + 1; p++) cout << " ";
                    }
                }
                else {
                    for (int p = 0; p < maxWidth + 1; p++) cout << " ";
                }

                if (j < lines[i].size() - 1) {
                    for (int s = 0; s < spacesBetween * (maxWidth / 2 + 1) - maxWidth - 1; s++)
                        cout << " ";
                }
            }
            cout << endl;
        }
    }
}