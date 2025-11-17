#include "HashTable.h"
#include <iostream>

/// <summary>
/// Создает новую хеш-таблицу указанной вместимости
/// </summary>
/// <param name="capacity">Вместимость создаваемой хеш-таблицы</param>
/// <returns>Указатель на созданную хеш-таблицу или nullptr при ошибке</returns>
HashTable* CreateHashTable(int capacity)
{
    if (capacity <= 0) return nullptr;

    HashTable* table = new HashTable;
    table->Buckets = new KeyValuePair * [capacity];
    for (int i = 0; i < capacity; i++)
    {
        table->Buckets[i] = nullptr;
    }
    table->Capacity = capacity;
    table->Count = 0;
    return table;
}

/// <summary>
/// Вычисляет хеш-код для ключа using метод Пирсона
/// </summary>
/// <param name="key">Ключ для вычисления хеша</param>
/// <param name="capacity">Вместимость хеш-таблицы</param>
/// <returns>Индекс ячейки в хеш-таблице</returns>
int PearsonHash(const string& key, int capacity)
{
    const unsigned char permutation[256] = {
        98, 6, 85, 150, 36, 23, 112, 164, 135, 207, 169, 5, 26, 64, 165, 219,
        61, 20, 68, 89, 130, 63, 52, 102, 24, 229, 132, 245, 80, 216, 195, 115,
        90, 168, 156, 203, 177, 120, 2, 190, 188, 7, 100, 185, 174, 243, 162, 10,
        237, 18, 253, 225, 8, 208, 172, 244, 255, 126, 101, 79, 145, 235, 228, 121,
        123, 251, 67, 250, 161, 0, 107, 97, 241, 111, 181, 82, 249, 33, 69, 55,
        59, 153, 29, 9, 213, 167, 84, 93, 30, 46, 94, 75, 151, 114, 73, 222,
        197, 96, 210, 45, 16, 227, 248, 202, 51, 152, 252, 125, 81, 206, 215, 186,
        39, 158, 178, 187, 131, 136, 1, 49, 50, 17, 141, 91, 47, 129, 60, 99,
        154, 35, 86, 171, 105, 34, 38, 200, 147, 58, 77, 118, 173, 246, 76, 254,
        133, 232, 196, 144, 198, 124, 53, 4, 108, 74, 223, 234, 134, 230, 157, 139,
        189, 205, 199, 128, 176, 19, 211, 236, 127, 192, 231, 70, 233, 88, 146, 44,
        183, 201, 22, 83, 13, 214, 116, 109, 159, 32, 95, 226, 140, 220, 57, 12,
        221, 31, 209, 182, 143, 92, 149, 184, 148, 62, 113, 65, 37, 27, 106, 166,
        3, 14, 204, 72, 21, 41, 56, 66, 28, 193, 40, 217, 25, 54, 179, 117,
        238, 87, 240, 155, 180, 170, 242, 212, 191, 163, 78, 218, 137, 194, 175, 110,
        43, 119, 224, 71, 122, 142, 42, 160, 104, 48, 247, 103, 15, 11, 138, 239
    };

    unsigned char hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
        unsigned char character = key[i];
        hash = permutation[hash ^ character];
    }
    return hash % capacity;
}

/// <summary>
/// Проверяет наличие дубликатов ключа в цепочке
/// </summary>
/// <param name="bucket">Начало цепочки</param>
/// <param name="searchKey">Ключ для поиска</param>
/// <returns>true если дубликат не найден, false если ключ уже существует</returns>
bool DuplicateCheck(KeyValuePair* bucket, const string& searchKey)
{
    KeyValuePair* currentElement = bucket;
    while (currentElement != nullptr)
    {
        if (currentElement->Key == searchKey)
        {
            return false;
        }
        currentElement = currentElement->Next;
    }
    return true;
}

/// <summary>
/// Добавляет пару ключ-значение в хеш-таблицу
/// </summary>
/// <param name="table">Хеш-таблица для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool Add(HashTable* table, const string& key, const string& value)
{
    if (table == nullptr || key.empty()) return false;

    int index = PearsonHash(key, table->Capacity);

    if (!DuplicateCheck(table->Buckets[index], key))
    {
        return false;
    }

    KeyValuePair* newPair = new KeyValuePair;
    newPair->Key = key;
    newPair->Value = value;
    newPair->Next = table->Buckets[index];
    table->Buckets[index] = newPair;
    table->Count++;

    return true;
}

/// <summary>
/// Удаляет элемент с указанным ключом из хеш-таблицы
/// </summary>
/// <param name="table">Хеш-таблица для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool Remove(HashTable* table, const string& key)
{
    if (table == nullptr || key.empty()) return false;

    int index = PearsonHash(key, table->Capacity);
    KeyValuePair* current = table->Buckets[index];
    KeyValuePair* previous = nullptr;

    while (current != nullptr)
    {
        if (current->Key == key)
        {
            if (previous == nullptr)
            {
                table->Buckets[index] = current->Next;
            }
            else
            {
                previous->Next = current->Next;
            }
            delete current;
            table->Count--;
            return true;
        }
        previous = current;
        current = current->Next;
    }
    return false;
}

/// <summary>
/// Переносит элементы из старой таблицы в новую
/// </summary>
/// <param name="table">Исходная таблица</param>
/// <param name="newTable">Новая таблица</param>
/// <param name="needAdd">Флаг необходимости добавления элементов</param>
void TransferElements(HashTable*& table, HashTable** newTable, bool needAdd)
{
    for (int i = 0; i < table->Capacity; i++)
    {
        KeyValuePair* current = table->Buckets[i];
        while (current != nullptr)
        {
            if (needAdd && newTable != nullptr)
            {
                Add(*newTable, current->Key, current->Value);
            }
            KeyValuePair* temp = current;
            current = current->Next;
            delete temp;
        }
    }
    delete[] table->Buckets;
}

/// <summary>
/// Выполняет перехеширование таблицы с увеличением вместимости
/// </summary>
/// <param name="table">Ссылка на указатель хеш-таблицы для перехеширования</param>
void Rehash(HashTable*& table)
{
    if (table == nullptr) return;

    int newCapacity = table->Capacity * 2;
    HashTable* newTable = CreateHashTable(newCapacity);
    TransferElements(table, &newTable, true);
    table->Buckets = newTable->Buckets;
    table->Capacity = newTable->Capacity;
    table->Count = newTable->Count;
    delete newTable;
}

/// <summary>
/// Удаляет хеш-таблицу и освобождает всю занятую память
/// </summary>
/// <param name="table">Хеш-таблица для удаления</param>
void DeleteHashTable(HashTable* table)
{
    if (table == nullptr) return;

    TransferElements(table, nullptr, false);
    delete table;
}

/// <summary>
/// Проверяет необходимость перехеширования таблицы
/// </summary>
/// <param name="table">Хеш-таблица для проверки</param>
/// <returns>true если требуется перехеширование, false в противном случае</returns>
bool NeedsRehash(const HashTable* table)
{
    if (table == nullptr) return false;
    return table->Count >= (3 * table->Capacity) / 4;
}
/// <summary>
/// Находит значение по ключу в хеш-таблице
/// </summary>
/// <param name="table">Хеш-таблица для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string Find(const HashTable* table, const string& key)
{
    if (table == nullptr || key.empty()) return "";

    int index = PearsonHash(key, table->Capacity);
    KeyValuePair* current = table->Buckets[index];

    while (current != nullptr)
    {
        if (current->Key == key) return current->Value;
        current = current->Next;
    }
    return "";
}