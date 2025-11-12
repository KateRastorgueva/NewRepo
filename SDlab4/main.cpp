#include <iostream>
#include <windows.h>
#include "HashTable.h"
#include "Validator.h"
#include "ConsoleService.h"

using namespace std;

void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

// Общие функции для устранения дублирования
bool ValidateDictionary(const Dictionary* dictionary)
{
    if (dictionary == nullptr)
    {
        ConsoleService::PrintMessage("Ошибка", "Словарь не создан");
        return false;
    }
    return true;
}

void PrintFullDictionaryState(const Dictionary* dictionary)
{
    ConsoleService::PrintDictionaryState(dictionary);
    ConsoleService::PrintHashTableState(dictionary);
}

void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ ХЕШ-ТАБЛИЦЫ" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Создать словарь" << endl;
    cout << "2 - Добавить элемент (key-value)" << endl;
    cout << "3 - Удалить элемент по ключу" << endl;
    cout << "4 - Найти элемент по ключу" << endl;
}

Dictionary* CreateDictionaryMenu()
{
    int capacity = GetValidatedCapacity("словаря");
    if (!ValidateCapacity(capacity))
    {
        return nullptr;
    }

    Dictionary* dictionary = CreateDictionary(capacity);
    if (dictionary != nullptr)
    {
        ConsoleService::PrintMessage("Успешно", "Словарь создан");
        ConsoleService::PrintHashTableState(dictionary);
    }
    else
    {
        ConsoleService::PrintMessage("Ошибка", "Создания словаря");
    }
    return dictionary;
}

void AddElementMenu(Dictionary* dictionary)
{
    if (!ValidateDictionary(dictionary))
    {
        return;
    }

    string key, value;
    cout << "Введите ключ: ";
    getline(cin, key);
    cout << "Введите значение: ";
    getline(cin, value);

    if (DictionaryAdd(dictionary, key, value))
    {
        ConsoleService::PrintMessage("Успешно", "Элемент добавлен");

        ConsoleService::PrintTitle("Попытка добавления дубликата:");
        if (!DictionaryAdd(dictionary, key, value))
        {
            ConsoleService::PrintMessage("Информация", "Дубликат отклонен - метод устранения коллизий работает");
        }
    }
    else
    {
        ConsoleService::PrintMessage("Ошибка", "Ключ уже существует");
    }

    PrintFullDictionaryState(dictionary);
}

void RemoveElementMenu(Dictionary* dictionary)
{
    if (!ValidateDictionary(dictionary))
    {
        return;
    }

    string key;
    cout << "Введите ключ для удаления: ";
    getline(cin, key);

    if (DictionaryRemove(dictionary, key))
    {
        ConsoleService::PrintMessage("Успешно", "Элемент удален");
    }
    else
    {
        ConsoleService::PrintMessage("Ошибка", "Элемент не найден");
    }

    PrintFullDictionaryState(dictionary);
}

void FindElementMenu(const Dictionary* dictionary)
{
    if (!ValidateDictionary(dictionary))
    {
        return;
    }

    string key;
    cout << "Введите ключ для поиска: ";
    getline(cin, key);

    string value = DictionaryFind(dictionary, key);
    if (!value.empty())
    {
        ConsoleService::PrintMessage("Найдено", "ключ '" + key + "' -> значение '" + value + "'");
    }
    else
    {
        ConsoleService::PrintMessage("Информация", "Элемент не найден");
    }
}

void DemoRehashingScenario()
{
    ConsoleService::PrintTitle("ДЕМОНСТРАЦИЯ ПЕРЕХЕШИРОВАНИЯ");

    Dictionary* demoDictionary = CreateDictionary(3);
    if (demoDictionary == nullptr)
    {
        return;
    }

    string testData[][2] = {
        {"name", "John"},
        {"age", "25"},
        {"city", "Moscow"},
        {"country", "Russia"},
        {"job", "Developer"},
        {"language", "C++"},
        {"email", "test@mail.com"},
        {"phone", "123456789"}
    };

    for (int i = 0; i < 8; i++)
    {
        ConsoleService::PrintTitle("Шаг " + to_string(i + 1) + ": Добавление '" + testData[i][0] + "'");

        DictionaryAdd(demoDictionary, testData[i][0], testData[i][1]);

        double loadFactor = static_cast<double>(demoDictionary->HashTable->Count) / demoDictionary->HashTable->Capacity;
        cout << "Коэффициент заполнения: " << loadFactor << endl;

        if (loadFactor > 0.75)
        {
            ConsoleService::PrintMessage("Внимание", "Превышен порог 0.75 - требуется перехеширование");
        }

        ConsoleService::PrintHashTableState(demoDictionary);
    }

    DeleteDictionary(demoDictionary);
}

int main()
{
    SetRussianEncoding();

    Dictionary* myDictionary = nullptr;
    int choice;

    cout << "ДЕМОНСТРАЦИЯ ХЕШ-ТАБЛИЦЫ СО СЛОВАРЕМ" << endl;

    do
    {
        ShowMainMenu();
        choice = GetValidatedInputInRange(0, 4);

        switch (choice)
        {
        case 0:
        {
            cout << "Выход из программы..." << endl;
            break;
        }
        case 1:
        {
            if (myDictionary != nullptr)
            {
                ConsoleService::PrintMessage("Информация", "Удаляем существующий словарь");
                DeleteDictionary(myDictionary);
            }
            myDictionary = CreateDictionaryMenu();
            break;
        }
        case 2:
        {
            AddElementMenu(myDictionary);
            break;
        }
        case 3:
        {
            RemoveElementMenu(myDictionary);
            break;
        }
        case 4:
        {
            FindElementMenu(myDictionary);

            if (myDictionary != nullptr)
            {
                ConsoleService::PrintTitle("Демонстрация поиска нескольких элементов:");
                string testKeys[] = { "name", "age", "nonexistent" };
                for (const string& key : testKeys)
                {
                    string value = DictionaryFind(myDictionary, key);
                    if (!value.empty())
                    {
                        ConsoleService::PrintMessage("Найдено", key + " -> " + value);
                    }
                    else
                    {
                        ConsoleService::PrintMessage("Не найдено", key);
                    }
                }
            }
            break;
        }
        }

        if (choice != 0 && myDictionary != nullptr && NeedsRehash(myDictionary->HashTable))
        {
            ConsoleService::PrintTitle("АВТОМАТИЧЕСКОЕ ПЕРЕХЕШИРОВАНИЕ");
            Rehash(myDictionary->HashTable);
            ConsoleService::PrintMessage("Информация", "Новая вместимость: " + to_string(myDictionary->HashTable->Capacity));
            ConsoleService::PrintHashTableState(myDictionary);
        }

    } while (choice != 0);

    if (myDictionary == nullptr)
    {
        DemoRehashingScenario();
    }

    if (myDictionary != nullptr)
    {
        DeleteDictionary(myDictionary);
        myDictionary = nullptr;
    }

    return 0;
}