#include "TreeVisualizer.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c

/// <summary>
/// Получает максимальную глубину дерева
/// </summary>
/// <typeparam name="TreeNode">Тип узла дерева</typeparam>
/// <param name="node">Корневой узел</param>
/// <returns>Максимальная глубина дерева</returns>
template<typename TreeNode>
int GetTreeMaxDepth(const TreeNode* node)
{
    if (!node)
    {
        return 0;
    }
    return max(GetTreeMaxDepth(node->Left), GetTreeMaxDepth(node->Right)) + 1;
}

/// <summary>
/// Получает отображение строк для бинарного дерева поиска
/// </summary>
/// <param name="root">Корень дерева</param>
/// <returns>Массив строк для отображения</returns>
vector<vector<TreeCellDisplay>> GetBinarySearchTreeRowDisplay(const BinarySearchTreeNode* root)
{
    vector<const BinarySearchTreeNode*> traversalStack;
    vector<vector<const BinarySearchTreeNode*>> rows;

    if (!root)
    {
        return vector<vector<TreeCellDisplay>>();
    }

    const BinarySearchTreeNode* currentNode = root;
    const int maxDepth = GetTreeMaxDepth(root);
    rows.resize(maxDepth);
    int depth = 0;

    while (true)
    {
        if (depth == maxDepth - 1)
        {
            rows[depth].push_back(currentNode);
            if (depth == 0)
            {
                break;
            }
            --depth;
            continue;
        }

        if (traversalStack.size() == depth)
        {
            rows[depth].push_back(currentNode);
            traversalStack.push_back(currentNode);
            if (currentNode)
            {
                currentNode = currentNode->Left;
            }
            ++depth;
            continue;
        }

        if (rows[depth + 1].size() % 2)
        {
            currentNode = traversalStack.back();
            if (currentNode)
            {
                currentNode = currentNode->Right;
            }
            ++depth;
            continue;
        }

        if (depth == 0)
        {
            break;
        }

        traversalStack.pop_back();
        currentNode = traversalStack.back();
        --depth;
    }

    vector<vector<TreeCellDisplay>> rowsDisplay;
    stringstream stringStream;
    for (const vector<const BinarySearchTreeNode*>& row : rows)
    {
        rowsDisplay.emplace_back();
        for (const BinarySearchTreeNode* node : row)
        {
            if (node)
            {
                stringStream << node->Key << "[" << node->Value << "]";
                rowsDisplay.back().push_back(TreeCellDisplay(stringStream.str()));
                stringStream = stringstream();
            }
            else
            {
                rowsDisplay.back().push_back(TreeCellDisplay());
            }
        }
    }
    return rowsDisplay;
}

/// <summary>
/// Получает отображение строк для декартова дерева
/// </summary>
/// <param name="root">Корень дерева</param>
/// <returns>Массив строк для отображения</returns>
vector<vector<TreeCellDisplay>> GetCartesianTreeRowDisplay(const CartesianTreeNode* root)
{
    vector<const CartesianTreeNode*> traversalStack;
    vector<vector<const CartesianTreeNode*>> rows;

    if (!root)
    {
        return vector<vector<TreeCellDisplay>>();
    }

    const CartesianTreeNode* currentNode = root;
    const int maxDepth = GetTreeMaxDepth(root);
    rows.resize(maxDepth);
    int depth = 0;

    while (true)
    {
        if (depth == maxDepth - 1)
        {
            rows[depth].push_back(currentNode);
            if (depth == 0)
            {
                break;
            }
            --depth;
            continue;
        }

        if (traversalStack.size() == depth)
        {
            rows[depth].push_back(currentNode);
            traversalStack.push_back(currentNode);
            if (currentNode)
            {
                currentNode = currentNode->Left;
            }
            ++depth;
            continue;
        }

        if (rows[depth + 1].size() % 2)
        {
            currentNode = traversalStack.back();
            if (currentNode)
            {
                currentNode = currentNode->Right;
            }
            ++depth;
            continue;
        }

        if (depth == 0)
        {
            break;
        }

        traversalStack.pop_back();
        currentNode = traversalStack.back();
        --depth;
    }

    vector<vector<TreeCellDisplay>> rowsDisplay;
    stringstream stringStream;
    for (const vector<const CartesianTreeNode*>& row : rows)
    {
        rowsDisplay.emplace_back();
        for (const CartesianTreeNode* node : row)
        {
            if (node)
            {
                stringStream << node->Key << "[" << node->Value << "](p:" << node->Priority << ")";
                rowsDisplay.back().push_back(TreeCellDisplay(stringStream.str()));
                stringStream = stringstream();
            }
            else
            {
                rowsDisplay.back().push_back(TreeCellDisplay());
            }
        }
    }
    return rowsDisplay;
}

/// <summary>
/// Форматирует строки для отображения бинарного дерева поиска
/// </summary>
/// <param name="rowsDisplay">Данные для отображения</param>
/// <returns>Отформатированные строки</returns>
vector<string> BinarySearchTreeRowFormatter(const vector<vector<TreeCellDisplay>>& rowsDisplay)
{
    using StringSizeType = string::size_type;

    StringSizeType cellWidth = 0;
    for (const vector<TreeCellDisplay>& rowDisplay : rowsDisplay)
    {
        for (const TreeCellDisplay& cell : rowDisplay)
        {
            if (cell.present && cell.valstr.length() > cellWidth)
            {
                cellWidth = cell.valstr.length();
            }
        }
    }

    if (cellWidth % 2 == 0)
    {
        ++cellWidth;
    }
    if (cellWidth < 3)
    {
        cellWidth = 3;
    }

    vector<string> formattedRows;
    StringSizeType rowCount = rowsDisplay.size();
    StringSizeType rowElementCount = 1 << (rowCount - 1);
    StringSizeType leftPad = 0;

    for (StringSizeType rowIndex = 0; rowIndex < rowCount; ++rowIndex)
    {
        const vector<TreeCellDisplay>& currentRow = rowsDisplay[rowCount - rowIndex - 1];
        StringSizeType space = (StringSizeType(1) << rowIndex) * (cellWidth + 1) / 2 - 1;
        string rowString;

        for (StringSizeType columnIndex = 0; columnIndex < rowElementCount; ++columnIndex)
        {
            rowString += string(columnIndex ? leftPad * 2 + 1 : leftPad, ' ');
            if (currentRow[columnIndex].present)
            {
                const string& valueString = currentRow[columnIndex].valstr;
                StringSizeType longPadding = cellWidth - valueString.length();
                StringSizeType shortPadding = longPadding / 2;
                longPadding -= shortPadding;
                rowString += string(columnIndex % 2 ? shortPadding : longPadding, ' ');
                rowString += valueString;
                rowString += string(columnIndex % 2 ? longPadding : shortPadding, ' ');
            }
            else
            {
                rowString += string(cellWidth, ' ');
            }
        }
        formattedRows.push_back(rowString);

        if (rowElementCount == 1)
        {
            break;
        }

        StringSizeType leftSpace = space + 1;
        StringSizeType rightSpace = space - 1;
        for (StringSizeType spaceRow = 0; spaceRow < space; ++spaceRow)
        {
            string connectionRow;
            for (StringSizeType columnIndex = 0; columnIndex < rowElementCount; ++columnIndex)
            {
                if (columnIndex % 2 == 0)
                {
                    connectionRow += string(columnIndex ? leftSpace * 2 + 1 : leftSpace, ' ');
                    connectionRow += currentRow[columnIndex].present ? '/' : ' ';
                    connectionRow += string(rightSpace + 1, ' ');
                }
                else
                {
                    connectionRow += string(rightSpace, ' ');
                    connectionRow += currentRow[columnIndex].present ? '\\' : ' ';
                }
            }
            formattedRows.push_back(connectionRow);
            ++leftSpace;
            --rightSpace;
        }
        leftPad += space + 1;
        rowElementCount /= 2;
    }

    reverse(formattedRows.begin(), formattedRows.end());
    return formattedRows;
}

/// <summary>
/// Форматирует строки для отображения декартова дерева
/// </summary>
/// <param name="rowsDisplay">Данные для отображения</param>
/// <returns>Отформатированные строки</returns>
vector<string> CartesianTreeRowFormatter(const vector<vector<TreeCellDisplay>>& rowsDisplay)
{
    using StringSizeType = string::size_type;

    StringSizeType cellWidth = 0;
    for (const vector<TreeCellDisplay>& rowDisplay : rowsDisplay)
    {
        for (const TreeCellDisplay& cell : rowDisplay)
        {
            if (cell.present && cell.valstr.length() > cellWidth)
            {
                cellWidth = cell.valstr.length();
            }
        }
    }

    if (cellWidth % 2 == 0)
    {
        ++cellWidth;
    }
    if (cellWidth < 3)
    {
        cellWidth = 3;
    }

    vector<string> formattedRows;
    StringSizeType rowCount = rowsDisplay.size();
    StringSizeType rowElementCount = 1 << (rowCount - 1);
    StringSizeType leftPad = 0;

    for (StringSizeType rowIndex = 0; rowIndex < rowCount; ++rowIndex)
    {
        const vector<TreeCellDisplay>& currentRow = rowsDisplay[rowCount - rowIndex - 1];
        StringSizeType space = (StringSizeType(1) << rowIndex) * (cellWidth + 1) / 2 - 1;
        string rowString;

        for (StringSizeType columnIndex = 0; columnIndex < rowElementCount; ++columnIndex)
        {
            rowString += string(columnIndex ? leftPad * 2 + 1 : leftPad, ' ');
            if (currentRow[columnIndex].present)
            {
                const string& valueString = currentRow[columnIndex].valstr;
                StringSizeType longPadding = cellWidth - valueString.length();
                StringSizeType shortPadding = longPadding / 2;
                longPadding -= shortPadding;
                rowString += string(columnIndex % 2 ? shortPadding : longPadding, ' ');
                rowString += valueString;
                rowString += string(columnIndex % 2 ? longPadding : shortPadding, ' ');
            }
            else
            {
                rowString += string(cellWidth, ' ');
            }
        }
        formattedRows.push_back(rowString);

        if (rowElementCount == 1)
        {
            break;
        }

        StringSizeType leftSpace = space + 1;
        StringSizeType rightSpace = space - 1;
        for (StringSizeType spaceRow = 0; spaceRow < space; ++spaceRow)
        {
            string connectionRow;
            for (StringSizeType columnIndex = 0; columnIndex < rowElementCount; ++columnIndex)
            {
                if (columnIndex % 2 == 0)
                {
                    connectionRow += string(columnIndex ? leftSpace * 2 + 1 : leftSpace, ' ');
                    connectionRow += currentRow[columnIndex].present ? '/' : ' ';
                    connectionRow += string(rightSpace + 1, ' ');
                }
                else
                {
                    connectionRow += string(rightSpace, ' ');
                    connectionRow += currentRow[columnIndex].present ? '\\' : ' ';
                }
            }
            formattedRows.push_back(connectionRow);
            ++leftSpace;
            --rightSpace;
        }
        leftPad += space + 1;
        rowElementCount /= 2;
    }

    reverse(formattedRows.begin(), formattedRows.end());
    return formattedRows;
}

/// <summary>
/// Обрезает пробелы слева в строках
/// </summary>
/// <param name="rows">Массив строк</param>
void TrimRowsLeft(vector<string>& rows)
{
    if (rows.empty())
    {
        return;
    }

    string::size_type minSpace = rows.front().length();
    for (const string& row : rows)
    {
        string::size_type firstNonSpace = row.find_first_not_of(' ');
        if (firstNonSpace == string::npos)
        {
            firstNonSpace = row.length();
        }
        if (firstNonSpace == 0)
        {
            return;
        }
        if (firstNonSpace < minSpace)
        {
            minSpace = firstNonSpace;
        }
    }

    for (string& row : rows)
    {
        row.erase(0, minSpace);
    }
}

/// <summary>
/// Отображает бинарное дерево поиска в консоли
/// </summary>
/// <param name="root">Корень дерева</param>
void DisplayBinarySearchTree(const BinarySearchTreeNode* root)
{
    const int depth = GetTreeMaxDepth(root);

    if (depth == 0)
    {
        return;
    }

    const vector<vector<TreeCellDisplay>> rowsDisplay = GetBinarySearchTreeRowDisplay(root);
    vector<string> formattedRows = BinarySearchTreeRowFormatter(rowsDisplay);
    TrimRowsLeft(formattedRows);

    for (const string& row : formattedRows)
    {
        cout << ' ' << row << '\n';
    }
}

/// <summary>
/// Отображает декартово дерево в консоли
/// </summary>
/// <param name="root">Корень дерева</param>
void DisplayCartesianTree(const CartesianTreeNode* root)
{
    const int depth = GetTreeMaxDepth(root);

    if (depth == 0)
    {
        return;
    }

    const vector<vector<TreeCellDisplay>> rowsDisplay = GetCartesianTreeRowDisplay(root);
    vector<string> formattedRows = CartesianTreeRowFormatter(rowsDisplay);
    TrimRowsLeft(formattedRows);

    for (const string& row : formattedRows)
    {
        cout << ' ' << row << '\n';
    }
}