#pragma once
#include <string>
#include "BinarySearchTree.h"
#include "CartesianTree.h"

using namespace std;

/// <summary>
/// Сервисный класс для вывода информации о деревьях в консоль
/// </summary>
class TreeConsoleService
{
public:
    /// <summary>
    /// Выводит заголовок в консоль
    /// </summary>
    /// <param name="title">Текст заголовка</param>
    static void PrintTitle(const string& title);

    /// <summary>
    /// Выводит сообщение с префиксом в консоль
    /// </summary>
    /// <param name="prefix">Префикс сообщения</param>
    /// <param name="message">Текст сообщения</param>
    static void PrintMessage(const string& prefix, const string& message);

    /// <summary>
    /// Выводит состояние бинарного дерева поиска
    /// </summary>
    /// <param name="tree">Дерево для отображения</param>
    static void PrintBinarySearchTreeState(const BinarySearchTree* tree);

    /// <summary>
    /// Выводит состояние декартова дерева
    /// </summary>
    /// <param name="tree">Дерево для отображения</param>
    static void PrintCartesianTreeState(const CartesianTree* tree);

    /// <summary>
    /// Выводит узел бинарного дерева поиска
    /// </summary>
    /// <param name="node">Узел для отображения</param>
    /// <param name="prefix">Префикс для форматирования</param>
    /// <param name="isLeft">Является ли узел левым потомком</param>
    static void PrintBinarySearchTreeNode(const BinarySearchTreeNode* node, const string& prefix = "", bool isLeft = true);

    /// <summary>
    /// Выводит узел декартова дерева
    /// </summary>
    /// <param name="node">Узел для отображения</param>
    /// <param name="prefix">Префикс для форматирования</param>
    /// <param name="isLeft">Является ли узел левым потомком</param>
    static void PrintCartesianTreeNode(const CartesianTreeNode* node, const string& prefix = "", bool isLeft = true);
};