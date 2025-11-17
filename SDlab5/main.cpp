#include <iostream>
#include <windows.h>
#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include "TreeConsoleService.h"
#include "Validator.h"

using namespace std;

void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ ДЕРЕВЬЕВ ПОИСКА" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Работа с бинарным деревом поиска" << endl;
    cout << "2 - Работа с декартовым деревом" << endl;
}

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
}

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
}

void BinarySearchTreeMenu()
{
    BinarySearchTree* bst = nullptr;
    int choice;

    do
    {
        ShowBinarySearchTreeMenu();
        choice = GetValidatedInputInRange(0, 6);

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
            TreeConsoleService::PrintBinarySearchTreeState(bst);
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
                    TreeConsoleService::PrintBinarySearchTreeState(bst);
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
                    TreeConsoleService::PrintBinarySearchTreeState(bst);
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
        }

    } while (choice != 0);
}

void CartesianTreeMenu()
{
    CartesianTree* cartesianTree = nullptr;
    int choice;

    do
    {
        ShowCartesianTreeMenu();
        choice = GetValidatedInputInRange(0, 6);

        switch (choice)
        {
        case 0:
            if (cartesianTree != nullptr)
            {
                DeleteCartesianTree(cartesianTree);
                cartesianTree = nullptr;
                cout << "Декартово дерево удалено" << endl;
            }
            break;

        case 1:
            if (cartesianTree != nullptr)
            {
                cout << "Ошибка: Дерево уже создано" << endl;
                break;
            }
            cartesianTree = CreateCartesianTree();
            cout << "Декартово дерево создано" << endl;
            TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            break;

        case 2:
            if (cartesianTree == nullptr)
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

                if (CartesianTreeAddUnoptimized(cartesianTree, key, value, priority))
                {
                    cout << "Элемент добавлен (неоптимизированный метод)" << endl;
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
                else
                {
                    cout << "Ошибка: Ключ уже существует" << endl;
                }
            }
            break;

        case 3:
            if (cartesianTree == nullptr)
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

                if (CartesianTreeAddOptimized(cartesianTree, key, value, priority))
                {
                    cout << "Элемент добавлен (оптимизированный метод)" << endl;
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
                else
                {
                    cout << "Ошибка при добавлении" << endl;
                }
            }
            break;

        case 4:
            if (cartesianTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (CartesianTreeRemoveUnoptimized(cartesianTree, key))
                {
                    cout << "Элемент удален (неоптимизированный метод)" << endl;
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
                else
                {
                    cout << "Ошибка: Элемент не найден" << endl;
                }
            }
            break;

        case 5:
            if (cartesianTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (CartesianTreeRemoveOptimized(cartesianTree, key))
                {
                    cout << "Элемент удален (оптимизированный метод)" << endl;
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
                else
                {
                    cout << "Ошибка: Элемент не найден" << endl;
                }
            }
            break;

        case 6:
            if (cartesianTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для поиска: ");
                string result = CartesianTreeFind(cartesianTree, key);
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
        }

    } while (choice != 0);
}

int main()
{
    SetRussianEncoding();

    int choice;

    cout << "ДЕРЕВЬЯ ПОИСКА" << endl;

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