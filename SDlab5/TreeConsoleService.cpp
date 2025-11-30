#include "TreeConsoleService.h"
#include "Validator.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

void TreeConsoleService::PrintTitle(const string& title)
{
    cout << endl;
    cout << "    " << title << endl;
}

int TreeConsoleService::GetKeyInput(const string& value)
{
    cout << value;
    return GetValidatedInput("");
}

string TreeConsoleService::GetValueInput()
{
    string value;
    cout << "Введите значение: ";
    getline(cin, value);
    return value;
}

int TreeConsoleService::GetPriorityInput()
{
    cout << "Введите приоритет: ";
    return GetValidatedInput("");
}

void TreeConsoleService::PrintBinarySearchTreeState(const BinarySearchTree* tree)
{
    if (!tree)
    {
        PrintError("Дерево не создано");
        return;
    }

    PrintTitle("СОСТОЯНИЕ БИНАРНОГО ДЕРЕВА ПОИСКА");

    if (!tree->Root)
    {
        PrintInfo("Дерево пустое");
        return;
    }

    PrintFormattedBinarySearchTree(tree->Root);
}

void TreeConsoleService::PrintCartesianTreeState(const CartesianTree* tree)
{
    if (!tree)
    {
        PrintError("Дерево не создано");
        return;
    }

    PrintTitle("СОСТОЯНИЕ ДЕКАРТОВА ДЕРЕВА");

    if (!tree->Root)
    {
        PrintInfo("Дерево пустое");
        return;
    }

    PrintFormattedCartesianTree(tree->Root);
}

template<typename TreeNode>
int TreeConsoleService::GetTreeMaxDepth(const TreeNode* node)
{
    if (!node)
    {
        return 0;
    }

    const int leftDepth = GetTreeMaxDepth(node->Left);
    const int rightDepth = GetTreeMaxDepth(node->Right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void TreeConsoleService::PrintError(const string& message)
{
    cout << "Ошибка: " << message << endl;
}

void TreeConsoleService::PrintSuccess(const string& message)
{
    cout << "✓ " << message << endl;
}

void TreeConsoleService::PrintInfo(const string& message)
{
    cout << "Информация: " << message << endl;
}

void TreeConsoleService::PrintWarning(const string& message)
{
    cout << "Внимание: " << message << endl;
}

void TreeConsoleService::PrintTreeCreated(const string& treeType)
{
    cout << treeType << " создано" << endl;
}

void TreeConsoleService::PrintTreeDeleted(const string& treeType)
{
    cout << treeType << " удалено" << endl;
}

void TreeConsoleService::PrintElementAdded(const string& method)
{
    if (method.empty())
    {
        cout << "Элемент добавлен" << endl;
    }
    else
    {
        cout << "Элемент добавлен (" << method << ")" << endl;
    }
}

void TreeConsoleService::PrintElementRemoved(const string& method)
{
    if (method.empty())
    {
        cout << "Элемент удален" << endl;
    }
    else
    {
        cout << "Элемент удален (" << method << ")" << endl;
    }
}

void TreeConsoleService::PrintElementFound(const string& value)
{
    cout << "Найдено: " << value << endl;
}

void TreeConsoleService::PrintElementNotFound()
{
    cout << "Элемент не найден" << endl;
}

void TreeConsoleService::PrintTreeIsEmpty()
{
    cout << "Дерево пустое" << endl;
}

void TreeConsoleService::PrintKeyAlreadyExists()
{
    cout << "Ошибка: Ключ уже существует" << endl;
}

void TreeConsoleService::PrintMaxSizeReached(int maxSize)
{
    cout << "Ошибка: Достигнут максимальный размер дерева (" << maxSize << " элементов)" << endl;
}

void TreeConsoleService::PrintTreeGenerated(int elementsAdded, const string& treeType)
{
    cout << "Сгенерировано случайное " << treeType << " с " << elementsAdded << " элементами" << endl;
}

// Блок функций для визуального отображения дерева (перенесен в конец)

TreeConsoleService::DisplayRows TreeConsoleService::GetBinarySearchTreeRowDisplay(const BinarySearchTreeNode* root)
{
    vector<const BinarySearchTreeNode*> traversalStack;
    vector<vector<const BinarySearchTreeNode*>> rows;

    if (!root)
    {
        return DisplayRows();
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

    DisplayRows rowsDisplay;
    stringstream stringStream;
    for (const vector<const BinarySearchTreeNode*>& row : rows)
    {
        rowsDisplay.emplace_back();
        for (const BinarySearchTreeNode* node : row)
        {
            if (node)
            {
                stringStream << node->Key << "[" << node->Value << "]";
                rowsDisplay.back().push_back(CellDisplay(stringStream.str()));
                stringStream = stringstream();
            }
            else
            {
                rowsDisplay.back().push_back(CellDisplay());
            }
        }
    }
    return rowsDisplay;
}

TreeConsoleService::DisplayRows TreeConsoleService::GetCartesianTreeRowDisplay(const CartesianTreeNode* root)
{
    vector<const CartesianTreeNode*> traversalStack;
    vector<vector<const CartesianTreeNode*>> rows;

    if (!root)
    {
        return DisplayRows();
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

    DisplayRows rowsDisplay;
    stringstream stringStream;
    for (const vector<const CartesianTreeNode*>& row : rows)
    {
        rowsDisplay.emplace_back();
        for (const CartesianTreeNode* node : row)
        {
            if (node)
            {
                stringStream << node->Key << "[" << node->Value << "](p:" << node->Priority << ")";
                rowsDisplay.back().push_back(CellDisplay(stringStream.str()));
                stringStream = stringstream();
            }
            else
            {
                rowsDisplay.back().push_back(CellDisplay());
            }
        }
    }
    return rowsDisplay;
}

vector<string> TreeConsoleService::BinarySearchTreeRowFormatter(const DisplayRows& rowsDisplay)
{
    using StringSizeType = string::size_type;

    StringSizeType cellWidth = 0;
    for (const DisplayRow& rowDisplay : rowsDisplay)
    {
        for (const CellDisplay& cell : rowDisplay)
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
        const DisplayRow& currentRow = rowsDisplay[rowCount - rowIndex - 1];
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

vector<string> TreeConsoleService::CartesianTreeRowFormatter(const DisplayRows& rowsDisplay)
{
    using StringSizeType = string::size_type;

    StringSizeType cellWidth = 0;
    for (const DisplayRow& rowDisplay : rowsDisplay)
    {
        for (const CellDisplay& cell : rowDisplay)
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
        const DisplayRow& currentRow = rowsDisplay[rowCount - rowIndex - 1];
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

void TreeConsoleService::TrimRowsLeft(vector<string>& rows)
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

void TreeConsoleService::PrintFormattedBinarySearchTree(const BinarySearchTreeNode* root)
{
    const int depth = GetTreeMaxDepth(root);

    if (depth == 0)
    {
        cout << " <empty tree>\n";
        return;
    }

    const DisplayRows rowsDisplay = GetBinarySearchTreeRowDisplay(root);
    vector<string> formattedRows = BinarySearchTreeRowFormatter(rowsDisplay);
    TrimRowsLeft(formattedRows);

    for (const string& row : formattedRows)
    {
        cout << ' ' << row << '\n';
    }
}

void TreeConsoleService::PrintFormattedCartesianTree(const CartesianTreeNode* root)
{
    const int depth = GetTreeMaxDepth(root);

    if (depth == 0)
    {
        cout << " <empty tree>\n";
        return;
    }

    const DisplayRows rowsDisplay = GetCartesianTreeRowDisplay(root);
    vector<string> formattedRows = CartesianTreeRowFormatter(rowsDisplay);
    TrimRowsLeft(formattedRows);

    for (const string& row : formattedRows)
    {
        cout << ' ' << row << '\n';
    }
}