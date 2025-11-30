#include "TreeConsoleService.h"
#include "Validator.h"
#include <iostream>

using namespace std;

/// <summary>
/// Выводит заголовок в консоль
/// </summary>
/// <param name="title">Текст заголовка</param>
void PrintTitle(const string& title)
{
    cout << endl;
    cout << "    " << title << endl;
}

/// <summary>
/// Получает ключ от пользователя
/// </summary>
/// <param name="value">Сообщение для ввода</param>
/// <returns>Введенный ключ</returns>
int GetKeyInput(const string& value)
{
    cout << value;
    return GetValidatedInput("");
}

/// <summary>
/// Получает значение от пользователя
/// </summary>
/// <returns>Введенное значение</returns>
string GetValueInput()
{
    string value;
    cout << "Введите значение: ";
    getline(cin, value);
    return value;
}

/// <summary>
/// Получает приоритет от пользователя
/// </summary>
/// <returns>Введенный приоритет</returns>
int GetPriorityInput()
{
    cout << "Введите приоритет: ";
    return GetValidatedInput("");
}

/// <summary>
/// Выводит состояние бинарного дерева поиска
/// </summary>
/// <param name="tree">Указатель на дерево</param>
void PrintBinarySearchTreeState(const BinarySearchTree* tree)
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

    DisplayBinarySearchTree(tree->Root);
}

/// <summary>
/// Выводит состояние декартова дерева
/// </summary>
/// <param name="tree">Указатель на дерево</param>
void PrintCartesianTreeState(const CartesianTree* tree)
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

    DisplayCartesianTree(tree->Root);
}

/// <summary>
/// Выводит сообщение об ошибке
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintError(const string& message)
{
    cout << "Ошибка: " << message << endl;
}

/// <summary>
/// Выводит сообщение об успехе
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintSuccess(const string& message)
{
    cout << message << endl;
}

/// <summary>
/// Выводит информационное сообщение
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintInfo(const string& message)
{
    cout << "Информация: " << message << endl;
}

/// <summary>
/// Выводит предупреждение
/// </summary>
/// <param name="message">Текст сообщения</param>
void PrintWarning(const string& message)
{
    cout << "Внимание: " << message << endl;
}

/// <summary>
/// Выводит сообщение о создании дерева
/// </summary>
/// <param name="treeType">Тип дерева</param>
void PrintTreeCreated(const string& treeType)
{
    cout << treeType << " создано" << endl;
}

/// <summary>
/// Выводит сообщение об удалении дерева
/// </summary>
/// <param name="treeType">Тип дерева</param>
void PrintTreeDeleted(const string& treeType)
{
    cout << treeType << " удалено" << endl;
}

/// <summary>
/// Выводит сообщение о добавлении элемента
/// </summary>
/// <param name="method">Метод добавления</param>
void PrintElementAdded(const string& method)
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

/// <summary>
/// Выводит сообщение об удалении элемента
/// </summary>
/// <param name="method">Метод удаления</param>
void PrintElementRemoved(const string& method)
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

/// <summary>
/// Выводит сообщение о найденном элементе
/// </summary>
/// <param name="value">Значение элемента</param>
void PrintElementFound(const string& value)
{
    cout << "Найдено: " << value << endl;
}

/// <summary>
/// Выводит сообщение о ненайденном элементе
/// </summary>
void PrintElementNotFound()
{
    cout << "Элемент не найден" << endl;
}

/// <summary>
/// Выводит сообщение о пустом дереве
/// </summary>
void PrintTreeIsEmpty()
{
    cout << "Дерево пустое" << endl;
}

/// <summary>
/// Выводит сообщение о существующем ключе
/// </summary>
void PrintKeyAlreadyExists()
{
    cout << "Ошибка: Ключ уже существует" << endl;
}

/// <summary>
/// Выводит сообщение о достижении максимального размера
/// </summary>
/// <param name="maxSize">Максимальный размер</param>
void PrintMaxSizeReached(int maxSize)
{
    cout << "Ошибка: Достигнут максимальный размер дерева (" << maxSize << " элементов)" << endl;
}

/// <summary>
/// Выводит сообщение о сгенерированном дереве
/// </summary>
/// <param name="elementsAdded">Количество добавленных элементов</param>
/// <param name="treeType">Тип дерева</param>
void PrintTreeGenerated(int elementsAdded, const string& treeType)
{
    cout << "Сгенерировано случайное " << treeType << " с " << elementsAdded << " элементами" << endl;
}