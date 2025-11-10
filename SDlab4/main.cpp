#include <iostream>
#include <windows.h>
#include "HashTable.h"
#include "Validator.h"

using namespace std;

void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void PrintDictionaryInfo(const Dictionary* dictionary)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr)
    {
        cout << "Словарь не создан или удален" << endl;
        return;
    }

    cout << "=== СОСТОЯНИЕ СЛОВАРЯ ===" << endl;
    cout << "Количество элементов: " << dictionary->HashTable->Count << endl;

    bool isEmpty = true;
    for (int i = 0; i < dictionary->HashTable->Capacity; i++)
    {
        KeyValuePair* current = dictionary->HashTable->Buckets[i];
        while (current != nullptr)
        {
            cout << "Ключ: '" << current->Key << "' -> Значение: '" << current->Value << "'" << endl;
            current = current->Next;
            isEmpty = false;
        }
    }

    if (isEmpty)
    {
        cout << "Словарь пуст" << endl;
    }
    cout << "=========================" << endl << endl;
}

void PrintHashTableInfo(const Dictionary* dictionary)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr)
    {
        cout << "Хеш-таблица не создана или удалена" << endl;
        return;
    }

    cout << "=== СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ ===" << endl;
    cout << "Вместимость: " << dictionary->HashTable->Capacity << endl;
    cout << "Количество элементов: " << dictionary->HashTable->Count << endl;
    cout << "Коэффициент заполнения: " << static_cast<double>(dictionary->HashTable->Count) / dictionary->HashTable->Capacity << endl;

    for (int i = 0; i < dictionary->HashTable->Capacity; i++)
    {
        cout << "Ячейка " << i << ": ";
        KeyValuePair* current = dictionary->HashTable->Buckets[i];
        if (current == nullptr)
        {
            cout << "пусто";
        }
        else
        {
            while (current != nullptr)
            {
                cout << "['" << current->Key << "'->'" << current->Value << "']";
                if (current->Next != nullptr)
                {
                    cout << " -> ";
                }
                current = current->Next;
            }
        }
        cout << endl;
    }
    cout << "==============================" << endl << endl;
}

void DemoRehashing(Dictionary*& dictionary)
{
    cout << "\n=== ДЕМОНСТРАЦИЯ ПЕРЕХЕШИРОВАНИЯ ===" << endl;

    if (dictionary == nullptr)
    {
        dictionary = CreateDictionary(3); // Маленькая таблица для быстрой демонстрации
        cout << "Создан словарь с вместимостью 3" << endl;
    }

    cout << "Начальное состояние:" << endl;
    PrintHashTableInfo(dictionary);

    // Добавляем элементы до срабатывания перехеширования
    string testData[][2] = {
        {"name", "John"}, {"age", "25"}, {"city", "Moscow"},
        {"country", "Russia"}, {"job", "Developer"}, {"language", "C++"}
    };

    for (int i = 0; i < 6; i++)
    {
        cout << "\n--- Шаг " << (i + 1) << " ---" << endl;
        cout << "Добавляем: '" << testData[i][0] << "' -> '" << testData[i][1] << "'" << endl;

        DictionaryAdd(dictionary, testData[i][0], testData[i][1]);

        cout << "Коэффициент заполнения: "
            << static_cast<double>(dictionary->HashTable->Count) / dictionary->HashTable->Capacity << endl;

        if (NeedsRehash(dictionary->HashTable))
        {
            cout << "!!! СРАБАТЫВАНИЕ ПЕРЕХЕШИРОВАНИЯ !!!" << endl;
            Rehash(dictionary->HashTable);
            cout << "Новая вместимость: " << dictionary->HashTable->Capacity << endl;
        }

        PrintHashTableInfo(dictionary);
    }

    cout << "=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===" << endl;
}

void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ ХЕШ-ТАБЛИЦЫ" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Создать словарь" << endl;
    cout << "2 - Добавить элемент (key-value)" << endl;
    cout << "3 - Удалить элемент по ключу" << endl;
    cout << "4 - Найти элемент по ключу" << endl;
    cout << "5 - Показать состояние словаря" << endl;
    cout << "6 - Показать состояние хеш-таблицы" << endl;
    cout << "7 - Демонстрация всех возможностей" << endl;
    cout << "8 - Демонстрация перехеширования" << endl;
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
        cout << "Словарь создан успешно!" << endl;
    }
    else
    {
        cout << "Ошибка создания словаря!" << endl;
    }
    return dictionary;
}

void AddElementMenu(Dictionary* dictionary)
{
    if (dictionary == nullptr)
    {
        cout << "Словарь не создан!" << endl;
        return;
    }

    string key, value;
    cout << "Введите ключ: ";
    getline(cin, key);
    cout << "Введите значение: ";
    getline(cin, value);

    if (DictionaryAdd(dictionary, key, value))
    {
        cout << "Элемент успешно добавлен!" << endl;
    }
    else
    {
        cout << "Ошибка добавления! Возможно, ключ уже существует." << endl;
    }
}

void RemoveElementMenu(Dictionary* dictionary)
{
    if (dictionary == nullptr)
    {
        cout << "Словарь не создан!" << endl;
        return;
    }

    string key;
    cout << "Введите ключ для удаления: ";
    getline(cin, key);

    if (DictionaryRemove(dictionary, key))
    {
        cout << "Элемент успешно удален!" << endl;
    }
    else
    {
        cout << "Элемент с таким ключом не найден!" << endl;
    }
}

void FindElementMenu(const Dictionary* dictionary)
{
    if (dictionary == nullptr)
    {
        cout << "Словарь не создан!" << endl;
        return;
    }

    string key;
    cout << "Введите ключ для поиска: ";
    getline(cin, key);

    string value = DictionaryFind(dictionary, key);
    if (!value.empty())
    {
        cout << "Найдено: ключ '" << key << "' -> значение '" << value << "'" << endl;
    }
    else
    {
        cout << "Элемент с ключом '" << key << "' не найден!" << endl;
    }
}

void DemoAllFeatures(Dictionary*& dictionary)
{
    cout << "\n=== ДЕМОНСТРАЦИЯ ВСЕХ ВОЗМОЖНОСТЕЙ ===" << endl;

    // Создание словаря если не создан
    if (dictionary == nullptr)
    {
        cout << "1. Создаем словарь с вместимостью 5..." << endl;
        dictionary = CreateDictionary(5);
        if (dictionary == nullptr)
        {
            return;
        }
    }

    // Добавление нескольких элементов
    cout << "\n2. Добавляем несколько элементов..." << endl;
    DictionaryAdd(dictionary, "name", "John");
    DictionaryAdd(dictionary, "age", "25");
    DictionaryAdd(dictionary, "city", "Moscow");
    DictionaryAdd(dictionary, "country", "Russia");
    PrintDictionaryInfo(dictionary);
    PrintHashTableInfo(dictionary);

    // Демонстрация дубликатов
    cout << "3. Пытаемся добавить дублирующий ключ 'name'..." << endl;
    if (!DictionaryAdd(dictionary, "name", "Duplicate"))
    {
        cout << "Дубликат отклонен - корректно!" << endl;
    }

    // Поиск элементов
    cout << "\n4. Поиск элементов..." << endl;
    cout << "Поиск 'name': " << DictionaryFind(dictionary, "name") << endl;
    cout << "Поиск 'age': " << DictionaryFind(dictionary, "age") << endl;

    // Удаление элемента
    cout << "\n5. Удаляем элемент 'city'..." << endl;
    DictionaryRemove(dictionary, "city");
    PrintDictionaryInfo(dictionary);

    // Добавление до перехеширования
    cout << "6. Добавляем элементы до перехеширования..." << endl;
    DictionaryAdd(dictionary, "job", "Developer");
    DictionaryAdd(dictionary, "language", "C++");
    DictionaryAdd(dictionary, "hobby", "Programming");
    PrintHashTableInfo(dictionary);

    cout << "=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===" << endl;
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
        choice = GetValidatedInputInRange(0, 8);

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
                cout << "Словарь уже существует! Удалите сначала." << endl;
            }
            else
            {
                myDictionary = CreateDictionaryMenu();
            }
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
            break;
        }
        case 5:
        {
            PrintDictionaryInfo(myDictionary);
            break;
        }
        case 6:
        {
            PrintHashTableInfo(myDictionary);
            break;
        }
        case 7:
        {
            DemoAllFeatures(myDictionary);
            break;
        }
        case 8:
        {
            DemoRehashing(myDictionary);
            break;
        }
        }
    } while (choice != 0);

    if (myDictionary != nullptr)
    {
        DeleteDictionary(myDictionary);
        myDictionary = nullptr;
    }

    return 0;
}