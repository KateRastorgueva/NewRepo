#include <iostream>
#include <windows.h>
#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include "TreeConsoleService.h"
#include "Validator.h"

using namespace std;

/// <summary>
/// Устанавливает русскую кодировку для консоли
/// </summary>
void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

/// <summary>
/// Отображает главное меню программы
/// </summary>
void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ ДЕРЕВЬЕВ ПОИСКА" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Работа с бинарным деревом поиска" << endl;
    cout << "2 - Работа с декартовым деревом" << endl;
}

/// <summary>
/// Отображает меню для бинарного дерева поиска
/// </summary>
void ShowBinarySearchTreeMenu()
{
    cout << "\nМЕНЮ БИНАРНОГО ДЕРЕВА ПОИСКА" << endl;
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать дерево" << endl;
    cout << "2 - Добавить элемент" << endl;
    cout << "3 - Удалить элемент" << endl;
    cout << "4 - Найти элемент" << endl;
    cout << "5 - Найти минимальный элемент" << endl;
    cout << "6 - Найти максимальный элемент" << endl;
    cout << "7 - Показать состояние дерева" << endl;
}

/// <summary>
/// Отображает меню для декартова дерева
/// </summary>
void ShowCartesianTreeMenu()
{
    cout << "\nМЕНЮ ДЕКАРТОВА ДЕРЕВА" << endl;
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать дерево" << endl;
    cout << "2 - Добавить элемент (неоптимизированный)" << endl;
    cout << "3 - Добавить элемент (оптимизированный)" << endl;
    cout << "4 - Удалить элемент (неоптимизированный)" << endl;
    cout << "5 - Удалить элемент (оптимизированный)" << endl;
    cout << "6 - Найти элемент" << endl;
    cout << "7 - Показать состояние дерева" << endl;
}

/// <summary>
/// Меню для работы с бинарным деревом поиска
/// </summary>
void BinarySearchTreeMenu()
{
    BinarySearchTree* bst = nullptr;
    int choice;

    do
    {
        ShowBinarySearchTreeMenu();
        choice = GetValidatedInputInRange(0, 7);

        switch (choice)
        {
        case 0:
            if (bst != nullptr)
            {
                DeleteBinarySearchTree(bst);
                bst = nullptr;
                cout << "Бинарное дерево поиска удалено" << endl;
            }
            break;

        case 1:
            if (bst != nullptr)
            {
                cout << "Ошибка: Дерево уже создано" << endl;
                break;
            }
            bst = CreateBinarySearchTree();
            cout << "Бинарное дерево поиска создано" << endl;
            break;

        case 2:
            if (bst == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ: ");
                string value;
                cout << "Введите значение: ";
                getline(cin, value);

                if (BinarySearchTreeAdd(bst, key, value))
                {
                    cout << "Элемент добавлен" << endl;
                }
                else
                {
                    cout << "Ошибка: Ключ уже существует" << endl;
                }
            }
            break;

        case 3:
            if (bst == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (BinarySearchTreeRemove(bst, key))
                {
                    cout << "Элемент удален" << endl;
                }
                else
                {
                    cout << "Ошибка: Элемент не найден" << endl;
                }
            }
            break;

        case 4:
            if (bst == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для поиска: ");
                string result = BinarySearchTreeFind(bst, key);
                if (!result.empty())
                {
                    cout << "Найдено: " << result << endl;
                }
                else
                {
                    cout << "Элемент не найден" << endl;
                }
            }
            break;

        case 5:
            if (bst == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                string result = BinarySearchTreeFindMin(bst);
                if (!result.empty())
                {
                    cout << "Минимальный элемент: " << result << endl;
                }
                else
                {
                    cout << "Дерево пустое" << endl;
                }
            }
            break;

        case 6:
            if (bst == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                string result = BinarySearchTreeFindMax(bst);
                if (!result.empty())
                {
                    cout << "Максимальный элемент: " << result << endl;
                }
                else
                {
                    cout << "Дерево пустое" << endl;
                }
            }
            break;

        case 7:
            TreeConsoleService::PrintBinarySearchTreeState(bst);
            break;
        }

    } while (choice != 0);
}

/// <summary>
/// Меню для работы с декартовым деревом
/// </summary>
void CartesianTreeMenu()
{
    CartesianTree* ct = nullptr;
    int choice;

    do
    {
        ShowCartesianTreeMenu();
        choice = GetValidatedInputInRange(0, 7);

        switch (choice)
        {
        case 0:
            if (ct != nullptr)
            {
                DeleteCartesianTree(ct);
                ct = nullptr;
                cout << "Декартово дерево удалено" << endl;
            }
            break;

        case 1:
            if (ct != nullptr)
            {
                cout << "Ошибка: Дерево уже создано" << endl;
                break;
            }
            ct = CreateCartesianTree();
            cout << "Декартово дерево создано" << endl;
            break;

        case 2:
            if (ct == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ: ");
                string value;
                cout << "Введите значение: ";
                getline(cin, value);
                int priority = GetValidatedInput("Введите приоритет: ");

                if (CartesianTreeAddUnoptimized(ct, key, value, priority))
                {
                    cout << "Элемент добавлен (неоптимизированный метод)" << endl;
                }
                else
                {
                    cout << "Ошибка при добавлении" << endl;
                }
            }
            break;

        case 3:
            if (ct == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ: ");
                string value;
                cout << "Введите значение: ";
                getline(cin, value);
                int priority = GetValidatedInput("Введите приоритет: ");

                if (CartesianTreeAddOptimized(ct, key, value, priority))
                {
                    cout << "Элемент добавлен (оптимизированный метод)" << endl;
                }
                else
                {
                    cout << "Ошибка при добавлении" << endl;
                }
            }
            break;

        case 4:
            if (ct == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (CartesianTreeRemoveUnoptimized(ct, key))
                {
                    cout << "Элемент удален (неоптимизированный метод)" << endl;
                }
                else
                {
                    cout << "Ошибка: Элемент не найден" << endl;
                }
            }
            break;

        case 5:
            if (ct == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (CartesianTreeRemoveOptimized(ct, key))
                {
                    cout << "Элемент удален (оптимизированный метод)" << endl;
                }
                else
                {
                    cout << "Ошибка: Элемент не найден" << endl;
                }
            }
            break;

        case 6:
            if (ct == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для поиска: ");
                string result = CartesianTreeFind(ct, key);
                if (!result.empty())
                {
                    cout << "Найдено: " << result << endl;
                }
                else
                {
                    cout << "Элемент не найден" << endl;
                }
            }
            break;

        case 7:
            TreeConsoleService::PrintCartesianTreeState(ct);
            break;
        }

    } while (choice != 0);
}

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main()
{
    SetRussianEncoding();

    int choice;

    cout << "ЛАБОРАТОРНАЯ РАБОТА 5. ДЕРЕВЬЯ ПОИСКА" << endl;

    do
    {
        ShowMainMenu();
        choice = GetValidatedInputInRange(0, 2);

        switch (choice)
        {
        case 0:
            cout << "Выход из программы..." << endl;
            break;

        case 1:
            BinarySearchTreeMenu();
            break;

        case 2:
            CartesianTreeMenu();
            break;
        }

    } while (choice != 0);

    return 0;
}