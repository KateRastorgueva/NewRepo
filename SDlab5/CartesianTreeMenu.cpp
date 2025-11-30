#include <iostream>
#include "CartesianTree.h"
#include "TreeConsoleService.h"
#include "Validator.h"
#include "TreeGenerator.h"
#include "Constants.h"

using namespace std;

/// <summary>
/// Отображает меню операций с декартовым деревом
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
    cout << "7 - Сгенерировать случайное дерево" << endl;
    cout << "8 - Перезаписать значение ключа" << endl;
    cout << "9 - Перезаписать приоритет ключа" << endl;
}

/// <summary>
/// Основная функция меню декартова дерева
/// </summary>
void CartesianTreeMenu()
{
    CartesianTree* cartesianTree = nullptr;
    int choice;

    do
    {
        ShowCartesianTreeMenu();
        choice = GetValidatedInputInRange(0, 9);

        switch (choice)
        {
        case 0:
        {
            if (cartesianTree != nullptr)
            {
                DeleteCartesianTree(cartesianTree);
                cartesianTree = nullptr;
                PrintTreeDeleted("Декартово дерево");
            }
            break;
        }

        case 1:
        {
            if (cartesianTree != nullptr)
            {
                PrintError("Дерево уже создано");
                break;
            }
            cartesianTree = CreateCartesianTree();
            PrintTreeCreated("Декартово дерево");
            PrintCartesianTreeState(cartesianTree);
            break;
        }

        case 2:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            if (cartesianTree->Size >= maxCartesianTreeSize)
            {
                PrintMaxSizeReached(maxCartesianTreeSize);
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

            int priority = GetPriorityInput();
            if (!ValidatePriority(priority))
            {
                PrintError("Приоритет должен быть от 1 до " + to_string(maxPriorityValue));
                break;
            }

            if (CartesianTreeAddUnoptimized(cartesianTree, key, value, priority))
            {
                PrintElementAdded("неоптимизированный метод");
                PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                if (cartesianTree->Size >= maxCartesianTreeSize)
                {
                    PrintMaxSizeReached(maxCartesianTreeSize);
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
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            if (cartesianTree->Size >= maxCartesianTreeSize)
            {
                PrintMaxSizeReached(maxCartesianTreeSize);
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

            int priority = GetPriorityInput();
            if (!ValidatePriority(priority))
            {
                PrintError("Приоритет должен быть от 1 до " + to_string(maxPriorityValue));
                break;
            }

            if (CartesianTreeAddOptimized(cartesianTree, key, value, priority))
            {
                PrintElementAdded("оптимизированный метод");
                PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                if (cartesianTree->Size >= maxCartesianTreeSize)
                {
                    PrintMaxSizeReached(maxCartesianTreeSize);
                }
                else
                {
                    PrintError("Ключ уже существует");
                }
            }
            break;
        }

        case 4:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ для удаления: ");
            if (CartesianTreeRemoveUnoptimized(cartesianTree, key))
            {
                PrintElementRemoved("неоптимизированный метод");
                PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                PrintElementNotFound();
            }
            break;
        }

        case 5:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ для удаления: ");
            if (CartesianTreeRemoveOptimized(cartesianTree, key))
            {
                PrintElementRemoved("оптимизированный метод");
                PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                PrintElementNotFound();
            }
            break;
        }

        case 6:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ для поиска: ");
            string result = CartesianTreeFind(cartesianTree, key);
            if (!result.empty())
            {
                PrintElementFound(result);
            }
            else
            {
                PrintElementNotFound();
            }
            break;
        }

        case 7:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-" + to_string(maxCartesianTreeSize) + "): ");
            if (elementCount < 1 || elementCount > maxCartesianTreeSize)
            {
                PrintError("Количество элементов должно быть от 1 до " + to_string(maxCartesianTreeSize));
                break;
            }

            int oldSize = cartesianTree->Size;
            GenerateRandomCartesianTree(cartesianTree, elementCount);

            if (cartesianTree->Size == oldSize)
            {
                PrintError("Не удалось сгенерировать дерево.");
            }
            else
            {
                PrintTreeGenerated(cartesianTree->Size - oldSize, "декартово дерево");
                PrintCartesianTreeState(cartesianTree);
            }
            break;
        }

        case 8:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ для перезаписи значения: ");
            if (!ValidateKey(key))
            {
                PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            int originalPriority = CartesianTreeGetPriority(cartesianTree, key);
            if (originalPriority == -1)
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

            if (CartesianTreeRemoveOptimized(cartesianTree, key) &&
                CartesianTreeAddOptimized(cartesianTree, key, newValue, originalPriority))
            {
                PrintSuccess("Значение ключа перезаписано");
                PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                PrintError("Ошибка при перезаписи значения");
            }
            break;
        }

        case 9:
        {
            if (!cartesianTree)
            {
                PrintError("Сначала создайте дерево");
                break;
            }

            int key = GetKeyInput("Введите ключ для перезаписи приоритета: ");
            if (!ValidateKey(key))
            {
                PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            string originalValue = CartesianTreeFind(cartesianTree, key);
            if (originalValue.empty())
            {
                PrintError("Ключ не существует");
                break;
            }

            int newPriority = GetPriorityInput();
            if (!ValidatePriority(newPriority))
            {
                PrintError("Приоритет должен быть от 1 до " + to_string(maxPriorityValue));
                break;
            }

            if (CartesianTreeRemoveOptimized(cartesianTree, key) &&
                CartesianTreeAddOptimized(cartesianTree, key, originalValue, newPriority))
            {
                PrintSuccess("Приоритет ключа перезаписан");
                PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                PrintError("Ошибка при перезаписи приоритета");
            }
            break;
        }
        }
    } while (choice != 0);
}