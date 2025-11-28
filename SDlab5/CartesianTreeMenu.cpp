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
}
void PrintTreeNotCreatedError()
{
    TreeConsoleService::PrintError("Сначала создайте дерево");
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
                TreeConsoleService::PrintTreeDeleted("Декартово дерево");
            }
            break;

        case 1:
            if (cartesianTree != nullptr)
            {
                TreeConsoleService::PrintError("Дерево уже создано");
                break;
            }
            cartesianTree = CreateCartesianTree();
            TreeConsoleService::PrintTreeCreated("Декартово дерево");
            TreeConsoleService::PrintCartesianTreeState(cartesianTree);
            break;

        case 2:
            if (!cartesianTree)
            {
                PrintTreeNotCreatedError();
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ: ");

                if (!ValidateKey(key)) {
                    TreeConsoleService::PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                    break;
                }

                string value;
                cout << "Введите значение: ";
                getline(cin, value);

                if (!ValidateValue(value)) {
                    TreeConsoleService::PrintWarning("Значение обрезано до " + to_string(maxStringLength) + " символов");
                    value = TrimValue(value);
                }

                int priority = GetValidatedInput("Введите приоритет: ");

                if (!ValidatePriority(priority)) {
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
            }
            break;

        case 3:
            if (!cartesianTree)
            {
                PrintTreeNotCreatedError();
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ: ");

                if (!ValidateKey(key)) {
                    TreeConsoleService::PrintError("Ключ должен быть от " + to_string(minKeyValue) + " до " + to_string(maxKeyValue));
                    break;
                }

                string value;
                cout << "Введите значение: ";
                getline(cin, value);

                if (!ValidateValue(value)) {
                    TreeConsoleService::PrintWarning("Значение обрезано до " + to_string(maxStringLength) + " символов");
                    value = TrimValue(value);
                }

                int priority = GetValidatedInput("Введите приоритет: ");

                if (!ValidatePriority(priority)) {
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
            }
            break;

        case 4:
            if (!cartesianTree)
            {
                PrintTreeNotCreatedError();
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (CartesianTreeRemoveUnoptimized(cartesianTree, key))
                {
                    TreeConsoleService::PrintElementRemoved("неоптимизированный метод");
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
                else
                {
                    TreeConsoleService::PrintElementNotFound();
                }
            }
            break;

        case 5:
            if (!cartesianTree)
            {
                PrintTreeNotCreatedError();
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для удаления: ");
                if (CartesianTreeRemoveOptimized(cartesianTree, key))
                {
                    TreeConsoleService::PrintElementRemoved("оптимизированный метод");
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
                else
                {
                    TreeConsoleService::PrintElementNotFound();
                }
            }
            break;

        case 6:
            if (!cartesianTree)
            {
                PrintTreeNotCreatedError();
                break;
            }
            {
                int key = GetValidatedInput("Введите ключ для поиска: ");
                string result = CartesianTreeFind(cartesianTree, key);
                if (!result.empty())
                {
                    TreeConsoleService::PrintElementFound(result);
                }
                else
                {
                    TreeConsoleService::PrintElementNotFound();
                }
            }
            break;

        case 7:
            if (!cartesianTree)
            {
                PrintTreeNotCreatedError();
                break;
            }
            {
                int elementCount = GetValidatedInput("Введите количество элементов для генерации (1-6): ");

                if (elementCount < 1 || elementCount > maxCartesianTreeSize) {
                    TreeConsoleService::PrintError("Количество элементов должно быть от 1 до " + to_string(maxCartesianTreeSize));
                    break;
                }

                int oldSize = cartesianTree->Size;
                GenerateRandomCartesianTree(cartesianTree, elementCount);

                if (cartesianTree->Size == oldSize) {
                    TreeConsoleService::PrintError("Не удалось сгенерировать дерево. Возможно, достигнут максимальный размер (" +
                        to_string(maxCartesianTreeSize) + " элементов) или недостаточно уникальных ключей");
                }
                else {
                    TreeConsoleService::PrintTreeGenerated(cartesianTree->Size - oldSize, "декартово дерево");
                    TreeConsoleService::PrintCartesianTreeState(cartesianTree);
                }
            }
            break;
        }
    } while (choice != 0);
}