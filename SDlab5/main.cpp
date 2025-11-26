#include <iostream>
#include <windows.h>
#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include "TreeConsoleService.h"
#include "Validator.h"
#include "TreeGenerator.h"

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
    cout << "7 - Сгенерировать случайное дерево" << endl;
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
    cout << "7 - Сгенерировать случайное дерево" << endl;
}

void BinarySearchTreeMenu()
{
    BinarySearchTree* binarySearchTree = nullptr;
    int choice;

    do
    {
        ShowBinarySearchTreeMenu();
        choice = GetValidatedInputInRange(0, 7);

        switch (choice)
        {
        case 0:
            if (binarySearchTree != nullptr)
            {
                DeleteBinarySearchTree(binarySearchTree);
                binarySearchTree = nullptr;
                cout << "Бинарное дерево поиска удалено" << endl;
            }
            break;

        case 1:
            if (binarySearchTree != nullptr)
            {
                cout << "Ошибка: Дерево уже создано" << endl;
                break;
            }
            binarySearchTree = CreateBinarySearchTree();
            cout << "Бинарное дерево поиска создано" << endl;
            TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
            break;

        case 2:
            if (binarySearchTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ: ");
                string value;
                cout << "Введите значение: ";
                getline(cin, value);

                if (BinarySearchTreeAdd(binarySearchTree, key, value))
                {
                    cout << "Элемент добавлен" << endl;
                    TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
                }
                else
                {
                    if (binarySearchTree->Size >= maxBinaryTreeSize) {
                        cout << "Ошибка: Достигнут максимальный размер дерева (" << maxBinaryTreeSize << " элементов)" << endl;
                    }
                    else {
                        cout << "Ошибка: Ключ уже существует" << endl;
                    }
                }
            }
            break;

        case 3:
            if (binarySearchTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (BinarySearchTreeRemove(binarySearchTree, key))
                {
                    cout << "Элемент удален" << endl;
                    TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
                }
                else
                {
                    cout << "Ошибка: Элемент не найден" << endl;
                }
            }
            break;

        case 4:
            if (binarySearchTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для поиска: ");
                string result = BinarySearchTreeFind(binarySearchTree, key);
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
            if (binarySearchTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                string result = BinarySearchTreeFindMin(binarySearchTree);
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
            if (binarySearchTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                string result = BinarySearchTreeFindMax(binarySearchTree);
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
            if (binarySearchTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-10): ");

                if (elementCount < 1 || elementCount > maxBinaryTreeSize) {
                    cout << "Ошибка: Количество элементов должно быть от 1 до " << maxBinaryTreeSize << endl;
                    break;
                }

                int oldSize = binarySearchTree->Size;
                GenerateRandomBinarySearchTree(binarySearchTree, elementCount);

                if (binarySearchTree->Size == oldSize) {
                    cout << "Ошибка: Не удалось сгенерировать дерево. Возможно, достигнут максимальный размер ("
                        << maxBinaryTreeSize << " элементов) или недостаточно уникальных ключей" << endl;
                }
                else {
                    cout << "Сгенерировано случайное бинарное дерево поиска с "
                        << (binarySearchTree->Size - oldSize) << " элементами" << endl;
                    TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
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
        choice = GetValidatedInputInRange(0, 7);

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

        case 7:
            if (cartesianTree == nullptr)
            {
                cout << "Ошибка: Сначала создайте дерево" << endl;
                break;
            }
            {
                int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-6): ");

                if (elementCount < 1 || elementCount > maxCartesianTreeSize) {
                    cout << "Ошибка: Количество элементов должно быть от 1 до " << maxCartesianTreeSize << endl;
                    break;
                }

                int oldSize = cartesianTree->Size;
                GenerateRandomCartesianTree(cartesianTree, elementCount);

                if (cartesianTree->Size == oldSize) {
                    cout << "Ошибка: Не удалось сгенерировать дерево. Возможно, достигнут максимальный размер ("
                        << maxCartesianTreeSize << " элементов) или недостаточно уникальных ключей" << endl;
                }
                else {
                    cout << "Сгенерировано случайное декартово дерево с "
                        << (cartesianTree->Size - oldSize) << " элементами" << endl;
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
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