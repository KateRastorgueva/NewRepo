#include "TreeConsoleService.h"
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
    cout << "=== " << title << " ===" << endl;
}

void TreeConsoleService::PrintBinarySearchTreeState(const BinarySearchTree* tree)
{
    if (tree == nullptr)
    {
        PrintError("Дерево не создано");
        return;
    }

    PrintTitle("СОСТОЯНИЕ БИНАРНОГО ДЕРЕВА ПОИСКА");

    if (tree->Root == nullptr)
    {
        PrintInfo("Дерево пустое");
        return;
    }

    DisplayBinarySearchTree(tree->Root);
}

void TreeConsoleService::PrintCartesianTreeState(const CartesianTree* tree)
{
    if (tree == nullptr)
    {
        PrintError("Дерево не создано");
        return;
    }

    PrintTitle("СОСТОЯНИЕ ДЕКАРТОВА ДЕРЕВА");

    if (tree->Root == nullptr)
    {
        PrintInfo("Дерево пустое");
        return;
    }
    DisplayCartesianTree(tree->Root);
}

int TreeConsoleService::GetBinarySearchTreeMaxDepth(const BinarySearchTreeNode* node) {
    if (node == nullptr) return 0;
    const int left_depth = GetBinarySearchTreeMaxDepth(node->Left);
    const int right_depth = GetBinarySearchTreeMaxDepth(node->Right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int TreeConsoleService::GetCartesianTreeMaxDepth(const CartesianTreeNode* node) {
    if (node == nullptr) return 0;
    const int left_depth = GetCartesianTreeMaxDepth(node->Left);
    const int right_depth = GetCartesianTreeMaxDepth(node->Right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

TreeConsoleService::DisplayRows TreeConsoleService::GetBinarySearchTreeRowDisplay(const BinarySearchTreeNode* root) {
    vector<const BinarySearchTreeNode*> traversal_stack;
    vector<vector<const BinarySearchTreeNode*>> rows;

    if (!root) return DisplayRows();

    const BinarySearchTreeNode* p = root;
    const int max_depth = GetBinarySearchTreeMaxDepth(root);
    rows.resize(max_depth);
    int depth = 0;

    for (;;) {
        if (depth == max_depth - 1) {
            rows[depth].push_back(p);
            if (depth == 0) break;
            --depth;
            continue;
        }

        if (traversal_stack.size() == depth) {
            rows[depth].push_back(p);
            traversal_stack.push_back(p);
            if (p) p = p->Left;
            ++depth;
            continue;
        }

        if (rows[depth + 1].size() % 2) {
            p = traversal_stack.back();
            if (p) p = p->Right;
            ++depth;
            continue;
        }

        if (depth == 0) break;

        traversal_stack.pop_back();
        p = traversal_stack.back();
        --depth;
    }

    DisplayRows rows_disp;
    stringstream ss;
    for (const auto& row : rows) {
        rows_disp.emplace_back();
        for (const BinarySearchTreeNode* pn : row) {
            if (pn) {
                ss << pn->Key << "[" << pn->Value << "]";
                rows_disp.back().push_back(CellDisplay(ss.str()));
                ss = stringstream();
            }
            else {
                rows_disp.back().push_back(CellDisplay());
            }
        }
    }
    return rows_disp;
}

TreeConsoleService::DisplayRows TreeConsoleService::GetCartesianTreeRowDisplay(const CartesianTreeNode* root) {
    vector<const CartesianTreeNode*> traversal_stack;
    vector<vector<const CartesianTreeNode*>> rows;

    if (!root) return DisplayRows();

    const CartesianTreeNode* p = root;
    const int max_depth = GetCartesianTreeMaxDepth(root);
    rows.resize(max_depth);
    int depth = 0;

    for (;;) {
        if (depth == max_depth - 1) {
            rows[depth].push_back(p);
            if (depth == 0) break;
            --depth;
            continue;
        }

        if (traversal_stack.size() == depth) {
            rows[depth].push_back(p);
            traversal_stack.push_back(p);
            if (p) p = p->Left;
            ++depth;
            continue;
        }

        if (rows[depth + 1].size() % 2) {
            p = traversal_stack.back();
            if (p) p = p->Right;
            ++depth;
            continue;
        }

        if (depth == 0) break;

        traversal_stack.pop_back();
        p = traversal_stack.back();
        --depth;
    }

    DisplayRows rows_disp;
    stringstream ss;
    for (const auto& row : rows) {
        rows_disp.emplace_back();
        for (const CartesianTreeNode* pn : row) {
            if (pn) {
                ss << pn->Key << "[" << pn->Value << "](p:" << pn->Priority << ")";
                rows_disp.back().push_back(CellDisplay(ss.str()));
                ss = stringstream();
            }
            else {
                rows_disp.back().push_back(CellDisplay());
            }
        }
    }
    return rows_disp;
}

vector<string> TreeConsoleService::BinarySearchTreeRowFormatter(const DisplayRows& rows_disp) {
    using s_t = string::size_type;

    s_t cell_width = 0;
    for (const auto& row_disp : rows_disp) {
        for (const auto& cd : row_disp) {
            if (cd.present && cd.valstr.length() > cell_width) {
                cell_width = cd.valstr.length();
            }
        }
    }

    if (cell_width % 2 == 0) ++cell_width;
    if (cell_width < 3) cell_width = 3;

    vector<string> formatted_rows;
    s_t row_count = rows_disp.size();
    s_t row_elem_count = 1 << (row_count - 1);
    s_t left_pad = 0;

    for (s_t r = 0; r < row_count; ++r) {
        const auto& cd_row = rows_disp[row_count - r - 1];
        s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
        string row;

        for (s_t c = 0; c < row_elem_count; ++c) {
            row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
            if (cd_row[c].present) {
                const string& valstr = cd_row[c].valstr;
                s_t long_padding = cell_width - valstr.length();
                s_t short_padding = long_padding / 2;
                long_padding -= short_padding;
                row += string(c % 2 ? short_padding : long_padding, ' ');
                row += valstr;
                row += string(c % 2 ? long_padding : short_padding, ' ');
            }
            else {
                row += string(cell_width, ' ');
            }
        }
        formatted_rows.push_back(row);

        if (row_elem_count == 1) break;

        s_t left_space = space + 1;
        s_t right_space = space - 1;
        for (s_t sr = 0; sr < space; ++sr) {
            string row;
            for (s_t c = 0; c < row_elem_count; ++c) {
                if (c % 2 == 0) {
                    row += string(c ? left_space * 2 + 1 : left_space, ' ');
                    row += cd_row[c].present ? '/' : ' ';
                    row += string(right_space + 1, ' ');
                }
                else {
                    row += string(right_space, ' ');
                    row += cd_row[c].present ? '\\' : ' ';
                }
            }
            formatted_rows.push_back(row);
            ++left_space;
            --right_space;
        }
        left_pad += space + 1;
        row_elem_count /= 2;
    }

    reverse(formatted_rows.begin(), formatted_rows.end());
    return formatted_rows;
}

vector<string> TreeConsoleService::CartesianTreeRowFormatter(const DisplayRows& rows_disp) {
    using s_t = string::size_type;

    s_t cell_width = 0;
    for (const auto& row_disp : rows_disp) {
        for (const auto& cd : row_disp) {
            if (cd.present && cd.valstr.length() > cell_width) {
                cell_width = cd.valstr.length();
            }
        }
    }

    if (cell_width % 2 == 0) ++cell_width;
    if (cell_width < 3) cell_width = 3;

    vector<string> formatted_rows;
    s_t row_count = rows_disp.size();
    s_t row_elem_count = 1 << (row_count - 1);
    s_t left_pad = 0;

    for (s_t r = 0; r < row_count; ++r) {
        const auto& cd_row = rows_disp[row_count - r - 1];
        s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
        string row;

        for (s_t c = 0; c < row_elem_count; ++c) {
            row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
            if (cd_row[c].present) {
                const string& valstr = cd_row[c].valstr;
                s_t long_padding = cell_width - valstr.length();
                s_t short_padding = long_padding / 2;
                long_padding -= short_padding;
                row += string(c % 2 ? short_padding : long_padding, ' ');
                row += valstr;
                row += string(c % 2 ? long_padding : short_padding, ' ');
            }
            else {
                row += string(cell_width, ' ');
            }
        }
        formatted_rows.push_back(row);

        if (row_elem_count == 1) break;

        s_t left_space = space + 1;
        s_t right_space = space - 1;
        for (s_t sr = 0; sr < space; ++sr) {
            string row;
            for (s_t c = 0; c < row_elem_count; ++c) {
                if (c % 2 == 0) {
                    row += string(c ? left_space * 2 + 1 : left_space, ' ');
                    row += cd_row[c].present ? '/' : ' ';
                    row += string(right_space + 1, ' ');
                }
                else {
                    row += string(right_space, ' ');
                    row += cd_row[c].present ? '\\' : ' ';
                }
            }
            formatted_rows.push_back(row);
            ++left_space;
            --right_space;
        }
        left_pad += space + 1;
        row_elem_count /= 2;
    }

    reverse(formatted_rows.begin(), formatted_rows.end());
    return formatted_rows;
}

void TreeConsoleService::TrimRowsLeft(vector<string>& rows) {
    if (!rows.size()) return;
    auto min_space = rows.front().length();
    for (const auto& row : rows) {
        auto i = row.find_first_not_of(' ');
        if (i == string::npos) i = row.length();
        if (i == 0) return;
        if (i < min_space) min_space = i;
    }
    for (auto& row : rows) {
        row.erase(0, min_space);
    }
}

void TreeConsoleService::PrintFormattedBinarySearchTree(const BinarySearchTreeNode* root) {
    const int d = GetBinarySearchTreeMaxDepth(root);

    if (d == 0) {
        cout << " <empty tree>\n";
        return;
    }

    const auto rows_disp = GetBinarySearchTreeRowDisplay(root);
    auto formatted_rows = BinarySearchTreeRowFormatter(rows_disp);
    TrimRowsLeft(formatted_rows);

    for (const auto& row : formatted_rows) {
        cout << ' ' << row << '\n';
    }
}

void TreeConsoleService::PrintFormattedCartesianTree(const CartesianTreeNode* root) {
    const int d = GetCartesianTreeMaxDepth(root);

    if (d == 0) {
        cout << " <empty tree>\n";
        return;
    }

    const auto rows_disp = GetCartesianTreeRowDisplay(root);
    auto formatted_rows = CartesianTreeRowFormatter(rows_disp);
    TrimRowsLeft(formatted_rows);

    for (const auto& row : formatted_rows) {
        cout << ' ' << row << '\n';
    }
}

void TreeConsoleService::DisplayBinarySearchTree(const BinarySearchTreeNode* root) {
    PrintFormattedBinarySearchTree(root);
}

void TreeConsoleService::DisplayCartesianTree(const CartesianTreeNode* root) {
    PrintFormattedCartesianTree(root);
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
    if (method.empty()) {
        cout << "Элемент добавлен" << endl;
    }
    else {
        cout << "Элемент добавлен (" << method << ")" << endl;
    }
}

void TreeConsoleService::PrintElementRemoved(const string& method)
{
    if (method.empty()) {
        cout << "Элемент удален" << endl;
    }
    else {
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