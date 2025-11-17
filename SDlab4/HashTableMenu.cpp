#include "HashTableMenu.h"
#include <iostream>

using namespace std;

/// <summary>
/// Показывает состояние хеш-таблицы
/// </summary>
void ShowHashTableState(const HashTable* table)
{
    if (table == nullptr)
    {
        ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
        return;
    }

    ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
    cout << "Вместимость: " << table->Capacity << endl;
    cout << "Количество элементов: " << table->Count << endl;
    cout << "Коэффициент заполнения: " << (double)table->Count / table->Capacity << endl;

    for (int i = 0; i < table->Capacity; i++)
    {
        cout << "Ячейка " << i << ": ";
        KeyValuePair* current = table->Buckets[i];
        ConsoleService::PrintBucketChain(current);
        cout << endl;
    }
}

void HashTableMenu::ShowHashTableMenu(HashTable*& hashTable)
{
    int choice;
    do
    {
        cout << "\nМЕНЮ ХЕШ-ТАБЛИЦЫ" << endl;
        cout << "0 - Вернуться в главное меню" << endl;
        cout << "1 - Создать хеш-таблицу" << endl;
        cout << "2 - Добавить элемент (key-value)" << endl;
        cout << "3 - Удалить элемент по ключу" << endl;
        cout << "4 - Найти элемент по ключу" << endl;
        cout << "5 - Выполнить перехеширование" << endl;
        cout << "6 - Показать состояние хеш-таблицы" << endl;

        choice = GetValidatedInputInRange(0, 6);

        switch (choice)
        {
        case 0:
            cout << "Возврат в главное меню..." << endl;
            break;

        case 1:
        {
            if (hashTable != nullptr)
            {
                DeleteHashTable(hashTable);
                hashTable = nullptr;
            }
            int capacity = GetValidatedCapacity("хеш-таблицы");
            hashTable = CreateHashTable(capacity);
            if (hashTable != nullptr)
            {
                ConsoleService::PrintMessage("Успешно", "Хеш-таблица создана");
                ShowHashTableState(hashTable);
            }
            break;
        }

        case 2:
        {
            if (hashTable == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
                break;
            }
            string key, value;
            cout << "Введите ключ: ";
            getline(cin, key);
            cout << "Введите значение: ";
            getline(cin, value);

            if (!ValidateStringLength(key, "Ключ", 100)) break;
            if (!ValidateStringLength(value, "Значение", 1000)) break;

            double currentLoadFactor = (double)hashTable->Count / hashTable->Capacity;
            cout << "Текущий коэффициент заполнения: " << currentLoadFactor << endl;

            if (currentLoadFactor > 0.75)
            {
                ConsoleService::PrintMessage("Внимание", "Коэффициент заполнения превышает 0.75 - рекомендуется перехеширование");
            }

            if (Add(hashTable, key, value))
            {
                ConsoleService::PrintMessage("Успешно", "Элемент добавлен в хеш-таблицу");
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Ключ уже существует в хеш-таблице");
            }
            ShowHashTableState(hashTable);
            break;
        }

        case 3:
        {
            if (hashTable == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
                break;
            }
            string key;
            cout << "Введите ключ для удаления: ";
            getline(cin, key);

            if (Remove(hashTable, key))
            {
                ConsoleService::PrintMessage("Успешно", "Элемент удален из хеш-таблицы");
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Элемент не найден в хеш-таблице");
            }
            ShowHashTableState(hashTable);
            break;
        }

        case 4:
        {
            if (hashTable == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
                break;
            }
            string key;
            cout << "Введите ключ для поиска: ";
            getline(cin, key);

            string value = Find(hashTable, key);
            if (!value.empty())
            {
                ConsoleService::PrintMessage("Найдено в хеш-таблице", "ключ '" + key + "' -> значение '" + value + "'");
            }
            else
            {
                ConsoleService::PrintMessage("Информация", "Элемент не найден в хеш-таблице");
            }
            ShowHashTableState(hashTable);
            break;
        }

        case 5:
        {
            if (hashTable == nullptr)
            {
                ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
                break;
            }
            ConsoleService::PrintTitle("ПЕРЕХЕШИРОВАНИЕ ХЕШ-ТАБЛИЦЫ");
            cout << "Текущая вместимость: " << hashTable->Capacity << endl;
            cout << "Количество элементов: " << hashTable->Count << endl;
            cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;

            Rehash(hashTable);
            ConsoleService::PrintMessage("Успешно", "Перехеширование выполнено");
            ConsoleService::PrintMessage("Информация", "Новая вместимость: " + to_string(hashTable->Capacity));
            ShowHashTableState(hashTable);
            break;
        }

        case 6:
            if (hashTable != nullptr)
            {
                ShowHashTableState(hashTable);
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
            }
            break;
        }

        // Автоматическое перехеширование для хеш-таблицы
        if (hashTable != nullptr && choice >= 2 && choice <= 3 && NeedsRehash(hashTable))
        {
            ConsoleService::PrintTitle("АВТОМАТИЧЕСКОЕ ПЕРЕХЕШИРОВАНИЕ");
            Rehash(hashTable);
            ConsoleService::PrintMessage("Информация", "Новая вместимость: " + to_string(hashTable->Capacity));
            ShowHashTableState(hashTable);
        }

    } while (choice != 0);
}