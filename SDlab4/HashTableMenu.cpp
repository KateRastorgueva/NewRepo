#include "HashTableMenu.h"
#include <iostream>

using namespace std;

void HashTableMenu::ShowHashTableMenu(HashTable*& hashTable)
{
    int choice;
    do
    {
        cout << "\nМЕНЮ ХЕШ-ТАБЛИЦЫ" << endl;
        cout << "0 - Вернуться в главное меню" << endl;
        cout << "1 - Добавить элемент (key-value)" << endl;
        cout << "2 - Удалить элемент по ключу" << endl;
        cout << "3 - Найти элемент по ключу" << endl;
        cout << "4 - Выполнить перехеширование" << endl;
        cout << "5 - Показать состояние хеш-таблицы" << endl;

        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 0:
            cout << "Возврат в главное меню..." << endl;
            break;

        case 1:
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

            if (!ValidateStringLength(key, "Ключ", 100))
            {
                break;
            }
            if (!ValidateStringLength(value, "Значение", 1000))
            {
                break;
            }

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

            ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
            cout << "Вместимость: " << hashTable->Capacity << endl;
            cout << "Количество элементов: " << hashTable->Count << endl;
            cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;
            for (int i = 0; i < hashTable->Capacity; i++)
            {
                cout << "Ячейка " << i << ": ";
                KeyValuePair* current = hashTable->Buckets[i];
                ConsoleService::PrintBucketChain(current);
                cout << endl;
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

            ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
            cout << "Вместимость: " << hashTable->Capacity << endl;
            cout << "Количество элементов: " << hashTable->Count << endl;
            cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;
            for (int i = 0; i < hashTable->Capacity; i++)
            {
                cout << "Ячейка " << i << ": ";
                KeyValuePair* current = hashTable->Buckets[i];
                ConsoleService::PrintBucketChain(current);
                cout << endl;
            }
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
            ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
            cout << "Вместимость: " << hashTable->Capacity << endl;
            cout << "Количество элементов: " << hashTable->Count << endl;
            cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;
            for (int i = 0; i < hashTable->Capacity; i++)
            {
                cout << "Ячейка " << i << ": ";
                KeyValuePair* current = hashTable->Buckets[i];
                ConsoleService::PrintBucketChain(current);
                cout << endl;
            }
            break;
        }

        case 4:
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

            ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
            cout << "Вместимость: " << hashTable->Capacity << endl;
            cout << "Количество элементов: " << hashTable->Count << endl;
            cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;
            for (int i = 0; i < hashTable->Capacity; i++)
            {
                cout << "Ячейка " << i << ": ";
                KeyValuePair* current = hashTable->Buckets[i];
                ConsoleService::PrintBucketChain(current);
                cout << endl;
            }
            break;
        }

        case 5:
            if (hashTable != nullptr)
            {
                // ВЫВОД СОСТОЯНИЯ ХЕШ-ТАБЛИЦЫ
                ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
                cout << "Вместимость: " << hashTable->Capacity << endl;
                cout << "Количество элементов: " << hashTable->Count << endl;
                cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;
                for (int i = 0; i < hashTable->Capacity; i++)
                {
                    cout << "Ячейка " << i << ": ";
                    KeyValuePair* current = hashTable->Buckets[i];
                    ConsoleService::PrintBucketChain(current);
                    cout << endl;
                }
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Хеш-таблица не создана");
            }
            break;
        }

        if (hashTable != nullptr && choice >= 1 && choice <= 2 && NeedsRehash(hashTable))
        {
            ConsoleService::PrintTitle("АВТОМАТИЧЕСКОЕ ПЕРЕХЕШИРОВАНИЕ");
            Rehash(hashTable);
            ConsoleService::PrintMessage("Информация", "Новая вместимость: " + to_string(hashTable->Capacity));

            ConsoleService::PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
            cout << "Вместимость: " << hashTable->Capacity << endl;
            cout << "Количество элементов: " << hashTable->Count << endl;
            cout << "Коэффициент заполнения: " << (double)hashTable->Count / hashTable->Capacity << endl;
            for (int i = 0; i < hashTable->Capacity; i++)
            {
                cout << "Ячейка " << i << ": ";
                KeyValuePair* current = hashTable->Buckets[i];
                ConsoleService::PrintBucketChain(current);
                cout << endl;
            }
        }

    } while (choice != 0);
}
