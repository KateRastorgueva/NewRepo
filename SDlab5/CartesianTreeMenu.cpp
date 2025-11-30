#include <iostream>
#include "CartesianTree.h"
#include "TreeConsoleService.h"
#include "Validator.h"
#include "TreeGenerator.h"

using namespace std;

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
                TreeConsoleService::PrintTreeDeleted("Декартово дерево");
            }
            break;
        }

        case 1:
        {
            if (cartesianTree != nullptr)
            {
                TreeConsoleService::PrintError("Дерево уже создано");
                break;
            }
            cartesianTree = CreateCartesianTree();
            TreeConsoleService::PrintTreeCreated("Декартово дерево");
            TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            break;
        }

        case 2:
        {
            if (!cartesianTree)
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

            int priority = TreeConsoleService::GetPriorityInput();
            if (!ValidatePriority(priority))
            {
                TreeConsoleService::PrintError("Приоритет должен быть от 1 до " + to_string(maxPriorityValue));
                break;
            }

            if (CartesianTreeAddUnoptimized(cartesianTree, key, value, priority))
            {
                TreeConsoleService::PrintElementAdded("неоптимизированный метод");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                TreeConsoleService::PrintKeyAlreadyExists();
            }
            break;
        }

        case 3:
        {
            if (!cartesianTree)
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

            int priority = TreeConsoleService::GetPriorityInput();
            if (!ValidatePriority(priority))
            {
                TreeConsoleService::PrintError("Приоритет должен быть от 1 до " + to_string(maxPriorityValue));
                break;
            }

            if (CartesianTreeAddOptimized(cartesianTree, key, value, priority))
            {
                TreeConsoleService::PrintElementAdded("оптимизированный метод");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                TreeConsoleService::PrintError("при добавлении");
            }
            break;
        }

        case 4:
        {
            if (!cartesianTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ для удаления: ");
            if (CartesianTreeRemoveUnoptimized(cartesianTree, key))
            {
                TreeConsoleService::PrintElementRemoved("неоптимизированный метод");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                TreeConsoleService::PrintElementNotFound();
            }
            break;
        }

        case 5:
        {
            if (!cartesianTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ для удаления: ");
            if (CartesianTreeRemoveOptimized(cartesianTree, key))
            {
                TreeConsoleService::PrintElementRemoved("оптимизированный метод");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                TreeConsoleService::PrintElementNotFound();
            }
            break;
        }

        case 6:
        {
            if (!cartesianTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ для поиска: ");
            string result = CartesianTreeFind(cartesianTree, key);
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

        case 7:
        {
            if (!cartesianTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-6): ");
            if (elementCount < 1 || elementCount > maxCartesianTreeSize)
            {
                TreeConsoleService::PrintError("Количество элементов должно быть от 1 до " + to_string(maxCartesianTreeSize));
                break;
            }

            int oldSize = cartesianTree->Size;
            GenerateRandomCartesianTree(cartesianTree, elementCount);

            if (cartesianTree->Size == oldSize)
            {
                TreeConsoleService::PrintError("Не удалось сгенерировать дерево. Возможно, достигнут максимальный размер (" +
                    to_string(maxCartesianTreeSize) + " элементов) или недостаточно уникальных ключей");
            }
            else
            {
                TreeConsoleService::PrintTreeGenerated(cartesianTree->Size - oldSize, "декартово дерево");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            break;
        }

        case 8:
        {
            if (!cartesianTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ для перезаписи значения: ");
            if (!ValidateKey(key))
            {
                TreeConsoleService::PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            // Проверяем существование ключа и получаем оригинальный приоритет
            int originalPriority = CartesianTreeGetPriority(cartesianTree, key);
            if (originalPriority == -1)
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

            // Удаляем и добавляем с оригинальным приоритетом
            if (CartesianTreeRemoveOptimized(cartesianTree, key) &&
                CartesianTreeAddOptimized(cartesianTree, key, newValue, originalPriority))
            {
                TreeConsoleService::PrintSuccess("Значение ключа перезаписано");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                TreeConsoleService::PrintError("Ошибка при перезаписи значения");
            }
            break;
        }

        case 9:
        {
            if (!cartesianTree)
            {
                TreeConsoleService::PrintError("Сначала создайте дерево");
                break;
            }

            int key = TreeConsoleService::GetKeyInput("Введите ключ для перезаписи приоритета: ");
            if (!ValidateKey(key))
            {
                TreeConsoleService::PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                break;
            }

            // Проверяем существование ключа и получаем оригинальное значение
            string originalValue = CartesianTreeFind(cartesianTree, key);
            if (originalValue.empty())
            {
                TreeConsoleService::PrintError("Ключ не существует");
                break;
            }

            int newPriority = TreeConsoleService::GetPriorityInput();
            if (!ValidatePriority(newPriority))
            {
                TreeConsoleService::PrintError("Приоритет должен быть от 1 до " + to_string(maxPriorityValue));
                break;
            }

            // Удаляем и добавляем с оригинальным значением
            if (CartesianTreeRemoveOptimized(cartesianTree, key) &&
                CartesianTreeAddOptimized(cartesianTree, key, originalValue, newPriority))
            {
                TreeConsoleService::PrintSuccess("Приоритет ключа перезаписан");
                TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            }
            else
            {
                TreeConsoleService::PrintError("Ошибка при перезаписи приоритета");
            }
            break;
        }
        }
    } while (choice != 0);
}