#pragma once
#include <string>
#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include "TreeVisualizer.h"

using namespace std;

/// <summary>
/// Выводит заголовок в консоль
/// </summary>
/// <param name="title">Текст заголовка</param>
void PrintTitle(const string& title);

/// <summary>
/// Выводит состояние бинарного дерева поиска
/// </summary>
/// <param name="tree">Указатель на дерево</param>
void PrintBinarySearchTreeState(const BinarySearchTree* tree);

/// <summary>
/// Выводит состояние декартова дерева
/// </summary>
/// <param name="tree">Указатель на дерево</param>
void PrintCartesianTreeState(const CartesianTree* tree);

/// <summary>
/// Получает приоритет от пользователя
/// </summary>
/// <returns>Введенный приоритет</returns>
int GetPriorityInput();

/// <summary>
/// Выводит сообщение об ошибке
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintError(const string& message);

/// <summary>
/// Выводит сообщение об успехе
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintSuccess(const string& message);

/// <summary>
/// Выводит информационное сообщение
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintInfo(const string& message);

/// <summary>
/// Выводит предупреждение
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintWarning(const string& message);

/// <summary>
/// Получает значение от пользователя
/// </summary>
/// <returns>Введенное значение</returns>
string GetValueInput();

/// <summary>
/// Получает ключ от пользователя
/// </summary>
/// <param name="value">Сообщение для ввода</param>
/// <returns>Введенный ключ</returns>
int GetKeyInput(const string& value = "Введите ключ: ");

/// <summary>
/// Выводит сообщение о создании дерева
/// </summary>
/// <param name="treeType">Тип дерева</param>
void PrintTreeCreated(const string& treeType);

/// <summary>
/// Выводит сообщение об удалении дерева
/// </summary>
/// <param name="treeType">Тип дерева</param>
void PrintTreeDeleted(const string& treeType);

/// <summary>
/// Выводит сообщение о добавлении элемента
/// </summary>
/// <param name="method">Метод добавления</param>
void PrintElementAdded(const string& method = "");

/// <summary>
/// Выводит сообщение об удалении элемента
/// </summary>
/// <param name="method">Метод удаления</param>
void PrintElementRemoved(const string& method = "");

/// <summary>
/// Выводит сообщение о найденном элементе
/// </summary>
/// <param name="value">Значение элемента</param>
void PrintElementFound(const string& value);

/// <summary>
/// Выводит сообщение о ненайденном элементе
/// </summary>
void PrintElementNotFound();

/// <summary>
/// Выводит сообщение о пустом дереве
/// </summary>
void PrintTreeIsEmpty();

/// <summary>
/// Выводит сообщение о существующем ключе
/// </summary>
void PrintKeyAlreadyExists();

/// <summary>
/// Выводит сообщение о достижении максимального размера
/// </summary>
/// <param name="maxSize">Максимальный размер</param>
void PrintMaxSizeReached(int maxSize);

/// <summary>
/// Выводит сообщение о сгенерированном дереве
/// </summary>
/// <param name="elementsAdded">Количество добавленных элементов</param>
/// <param name="treeType">Тип дерева</param>
void PrintTreeGenerated(int elementsAdded, const string& treeType);