#include <iostream>
#include "BinarySearchTree.h"
#include "TreeConsoleService.h"
#include "TreeVisualizer.h"
#include "Validator.h"
#include "TreeGenerator.h"

using namespace std;

/// <summary>
/// Отображает меню операций с бинарным деревом поиска
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
    cout << "7 - Сгенерировать случайное дерево" << endl;
    cout << "8 - Перезаписать значение ключа" << endl;
}

/// <summary>
/// Основная функция меню бинарного дерева поиска
/// </summary>
void BinarySearchTreeMenu()
{
    BinarySearchTree* binarySearchTree = nullptr;
    int choice;

    do
    {
        ShowBinarySearchTreeMenu();
        choice = GetValidatedInputInRange(0, 8);

        switch (choice)
        {
        case 0:
        {
            if (binarySearchTree != nullptr)
            {
                DeleteBinarySearchTree(binarySearchTree);
                binarySearchTree = nullptr;
                PrintTreeDeleted("Бинарное дерево поиска");
            }
            break;
        }

        case 1:
        {
            if (binarySearchTree != nullptr)
            {
                PrintError("Дерево уже создано");
                break;
            }
            binarySearchTree = CreateBinarySearchTree();
            PrintTreeCreated("Бинарное дерево поиска");
            PrintBinarySearchTreeState(binarySearchTree);
            break;
        }

        case 2:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ: ");
            if (!ValidateKey(key))
            {
                PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            string value = GetValueInput();
            if (!ValidateValue(value))
            {
                PrintError("Значение слишком длинное. Максимальная длина: " + to_string(maxStringLength) + " символов");
                break;
            }

            if (BinarySearchTreeAdd(binarySearchTree, key, value))
            {
                PrintElementAdded();
                PrintBinarySearchTreeState(binarySearchTree);
            }
            else
            {
                if (binarySearchTree->Size >= maxBinaryTreeSize)
                {
                    PrintMaxSizeReached(maxBinaryTreeSize);
                }
                else
                {
                    PrintKeyAlreadyExists();
                }
            }
            break;
        }

        case 3:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetValidatedInput("Введите ключ для удаления: ");
            if (BinarySearchTreeRemove(binarySearchTree, key))
            {
                PrintElementRemoved();
                PrintBinarySearchTreeState(binarySearchTree);
            }
            else
            {
                PrintElementNotFound();
            }
            break;
        }

        case 4:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetValidatedInput("Введите ключ для поиска: ");
            string result = BinarySearchTreeFind(binarySearchTree, key);
            if (result.size() > 0)
            {
                PrintElementFound(result);
            }
            else
            {
                PrintElementNotFound();
            }
            break;
        }

        case 5:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            string result = BinarySearchTreeFindMin(binarySearchTree);
            if (result.size() > 0)
            {
                cout << "Минимальный элемент: " << result << endl;
            }
            else
            {
                PrintTreeIsEmpty();
            }
            break;
        }

        case 6:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            string result = BinarySearchTreeFindMax(binarySearchTree);
            if( result.size() > 0)
            {
                cout << "Максимальный элемент: " << result << endl;
            }
            else
            {
                PrintTreeIsEmpty();
            }
            break;
        }

        case 7:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-" + to_string(maxBinaryTreeSize) + "): ");
            if (elementCount < 1 || elementCount > maxBinaryTreeSize)
            {
                PrintError("Количество элементов должно быть от 1 до " + to_string(maxBinaryTreeSize));
                break;
            }

            int oldSize = binarySearchTree->Size;
            GenerateRandomBinarySearchTree(binarySearchTree, elementCount);

            if (binarySearchTree->Size == oldSize)
            {
                PrintError("Не удалось сгенерировать дерево.");
            }
            else
            {
                PrintTreeGenerated(binarySearchTree->Size - oldSize, "бинарное дерево поиска");
                PrintBinarySearchTreeState(binarySearchTree);
            }
            break;
        }

        case 8:
        {
            if (!binarySearchTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ для перезаписи: ");
            if (!ValidateKey(key))
            {
                PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            string existingValue = BinarySearchTreeFind(binarySearchTree, key);
            if (existingValue.size() == 0)
            {
                PrintError("Ключ не существует");
                break;
            }

            string newValue = GetValueInput();
            if (!ValidateValue(newValue))
            {
                PrintError("Значение слишком длинное. Максимальная длина: " + to_string(maxStringLength) + " символов");
                break;
            }

            if (BinarySearchTreeRemove(binarySearchTree, key) && BinarySearchTreeAdd(binarySearchTree, key, newValue))
            {
                PrintSuccess("Значение ключа перезаписано");
                PrintBinarySearchTreeState(binarySearchTree);
            }
            else
            {
                PrintError("Ошибка при перезаписи значения");
            }
            break;
        }
        }
    } while (choice != 0);
}