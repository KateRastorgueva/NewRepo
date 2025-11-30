#include <iostream>
#include "BinarySearchTree.h"
#include "TreeConsoleService.h"
#include "Validator.h"
#include "TreeGenerator.h"

using namespace std;

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
                TreeConsoleService::PrintTreeDeleted("Бинарное дерево поиска");
            }
            break;
        }

        case 1:
        {
            if (binarySearchTree != nullptr)
            {
                TreeConsoleService::PrintError("Дерево уже создано");
                break;
            }
            binarySearchTree = CreateBinarySearchTree();
            TreeConsoleService::PrintTreeCreated("Бинарное дерево поиска");
            TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
            break;
        }

        case 2:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ: ");
            if (!ValidateKey(key))
            {
                TreeConsoleService::PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            string value = TreeConsoleService::GetValueInput();
            if (!ValidateValue(value))
            {
                TreeConsoleService::PrintError("Значение слишком длинное. Максимальная длина: " + to_string(maxStringLength) + " символов");
                break;
            }

            if (BinarySearchTreeAdd(binarySearchTree, key, value))
            {
                TreeConsoleService::PrintElementAdded();
                TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
            }
            else
            {
                if (binarySearchTree->Size >= maxBinaryTreeSize)
                {
                    TreeConsoleService::PrintMaxSizeReached(maxBinaryTreeSize);
                }
                else
                {
                    TreeConsoleService::PrintKeyAlreadyExists();
                }
            }
            break;
        }


        case 3:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetValidatedInput("Введите ключ для удаления: ");
            if (BinarySearchTreeRemove(binarySearchTree, key))
            {
                TreeConsoleService::PrintElementRemoved();
                TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
            }
            else
            {
                TreeConsoleService::PrintElementNotFound();
            }
            break;
        }

        case 4:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetValidatedInput("Введите ключ для поиска: ");
            string result = BinarySearchTreeFind(binarySearchTree, key);
            if (!result.empty())
            {
                TreeConsoleService::PrintElementFound(result);
            }
            else
            {
                TreeConsoleService::PrintElementNotFound();
            }
            break;
        }

        case 5:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            string result = BinarySearchTreeFindMin(binarySearchTree);
            if (!result.empty())
            {
                cout << "Минимальный элемент: " << result << endl;
            }
            else
            {
                TreeConsoleService::PrintTreeIsEmpty();
            }
            break;
        }

        case 6:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            string result = BinarySearchTreeFindMax(binarySearchTree);
            if (!result.empty())
            {
                cout << "Максимальный элемент: " << result << endl;
            }
            else
            {
                TreeConsoleService::PrintTreeIsEmpty();
            }
            break;
        }

        case 7:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-7): ");
            if (elementCount < 1 || elementCount > maxBinaryTreeSize)
            {
                TreeConsoleService::PrintError("Количество элементов должно быть от 1 до " + to_string(maxBinaryTreeSize));
                break;
            }

            int oldSize = binarySearchTree->Size;
            GenerateRandomBinarySearchTree(binarySearchTree, elementCount);

            if (binarySearchTree->Size == oldSize)
            {
                TreeConsoleService::PrintError("Не удалось сгенерировать дерево. Возможно, достигнут максимальный размер (" +
                    to_string(maxBinaryTreeSize) + " элементов) или недостаточно уникальных ключей");
            }
            else
            {
                TreeConsoleService::PrintTreeGenerated(binarySearchTree->Size - oldSize, "бинарное дерево поиска");
                TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
            }
            break;
        }

        case 8:
        {
            if (!binarySearchTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ для перезаписи: ");
            if (!ValidateKey(key))
            {
                TreeConsoleService::PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            // Проверяем существование ключа
            string existingValue = BinarySearchTreeFind(binarySearchTree, key);
            if (existingValue.empty())
            {
                TreeConsoleService::PrintError("Ключ не существует");
                break;
            }

            string newValue = TreeConsoleService::GetValueInput();
            if (!ValidateValue(newValue))
            {
                TreeConsoleService::PrintError("Значение слишком длинное. Максимальная длина: " + to_string(maxStringLength) + " символов");
                break;
            }

            // Удаляем старый элемент и добавляем с новым значением
            if (BinarySearchTreeRemove(binarySearchTree, key) && BinarySearchTreeAdd(binarySearchTree, key, newValue))
            {
                TreeConsoleService::PrintSuccess("Значение ключа перезаписано");
                TreeConsoleService::PrintBinarySearchTreeState(binarySearchTree);
            }
            else
            {
                TreeConsoleService::PrintError("Ошибка при перезаписи значения");
            }
            break;
        }
        }
    } while (choice != 0);
}