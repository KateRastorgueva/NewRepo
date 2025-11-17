#include "DictionaryMenu.h"
#include <iostream>

using namespace std;

void DictionaryMenu::ShowDictionaryMenu(Dictionary*& dictionary)
{
    int choice;
    do
    {
        cout << "\nМЕНЮ СЛОВАРЯ" << endl;
        cout << "0 - Вернуться в главное меню" << endl;
        cout << "1 - Создать словарь" << endl;
        cout << "2 - Добавить элемент (key-value)" << endl;
        cout << "3 - Удалить элемент по ключу" << endl;
        cout << "4 - Найти элемент по ключу" << endl;
        cout << "5 - Показать состояние словаря" << endl;

        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 0:
            cout << "Возврат в главное меню..." << endl;
            break;

        case 1:
        {
            if (dictionary != nullptr)
            {
                DeleteDictionary(dictionary);
                dictionary = nullptr;
            }
            int capacity = GetValidatedCapacity("словаря");
            dictionary = CreateDictionary(capacity);
            if (dictionary != nullptr)
            {
                ConsoleService::PrintMessage("Успешно", "Словарь создан");
                ConsoleService::PrintDictionaryState(dictionary);
                ConsoleService::PrintHashTableState(dictionary);
            }
            break;
        }

        case 2:
        {
            if (dictionary == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Словарь не создан");
                break;
            }
            string key, value;
            cout << "Введите ключ: ";
            getline(cin, key);
            cout << "Введите значение: ";
            getline(cin, value);

            if (!ValidateStringLength(key, "Ключ", 100)) break;
            if (!ValidateStringLength(value, "Значение", 1000)) break;

            double currentLoadFactor = (double)(dictionary->HashTable->Count) / dictionary->HashTable->Capacity;
            cout << "Текущий коэффициент заполнения: " << currentLoadFactor << endl;

            if (currentLoadFactor > 0.75)
            {
                ConsoleService::PrintMessage("Внимание", "Коэффициент заполнения превышает 0.75 - возможно перехеширование");
            }

            if (DictionaryAdd(dictionary, key, value))
            {
                ConsoleService::PrintMessage("Успешно", "Элемент добавлен в словарь");
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Ключ уже существует в словаре");
            }
            ConsoleService::PrintDictionaryState(dictionary);
            ConsoleService::PrintHashTableState(dictionary);
            break;
        }

        case 3:
        {
            if (dictionary == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Словарь не создан");
                break;
            }
            string key;
            cout << "Введите ключ для удаления: ";
            getline(cin, key);

            if (DictionaryRemove(dictionary, key))
            {
                ConsoleService::PrintMessage("Успешно", "Элемент удален из словаря");
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Элемент не найден в словаре");
            }
            ConsoleService::PrintDictionaryState(dictionary);
            ConsoleService::PrintHashTableState(dictionary);
            break;
        }

        case 4:
        {
            if (dictionary == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Словарь не создан");
                break;
            }
            string key;
            cout << "Введите ключ для поиска: ";
            getline(cin, key);

            string value = DictionaryFind(dictionary, key);
            if (!value.empty())
            {
                ConsoleService::PrintMessage("Найдено в словаре", "ключ '" + key + "' -> значение '" + value + "'");
            }
            else
            {
                ConsoleService::PrintMessage("Информация", "Элемент не найден в словаре");
            }
            ConsoleService::PrintDictionaryState(dictionary);
            ConsoleService::PrintHashTableState(dictionary);
            break;
        }

        case 5:
            if (dictionary != nullptr)
            {
                ConsoleService::PrintDictionaryState(dictionary);
                ConsoleService::PrintHashTableState(dictionary);
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Словарь не создан");
            }
            break;
        }

        // Автоматическое перехеширование для словаря
        if (dictionary != nullptr && dictionary->HashTable != nullptr &&
            choice >= 2 && choice <= 3 && NeedsRehash(dictionary->HashTable))
        {
            ConsoleService::PrintTitle("АВТОМАТИЧЕСКОЕ ПЕРЕХЕШИРОВАНИЕ");
            Rehash(dictionary->HashTable);
            ConsoleService::PrintMessage("Информация", "Новая вместимость: " + to_string(dictionary->HashTable->Capacity));
            ConsoleService::PrintDictionaryState(dictionary);
            ConsoleService::PrintHashTableState(dictionary);
        }

    } while (choice != 0);
}