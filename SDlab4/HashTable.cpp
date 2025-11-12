#pragma once
#include "HashTable.h"
#include <iostream>

HashTable* CreateHashTable(int capacity)
{
    if (capacity <= 0)
    {
        return nullptr;
    }

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
template<typename Type>
bool IsEmptyBool(Type* table, const string& key)
{
    if (table == nullptr || !key.size())
    {
        return false;
    }
}
template<typename Type>
string IsEmptyString(Type* table, const string& key)
{
    if (dictionary == nullptr || !key.size())
    {
        return "";
    }
}
template<typename Type>
void IsEmptyNothing(Type*& table)
{
    if (dictionary == nullptr)
    {
        return;
    }
}
bool DuplicateCheck(KeyValuePair* bucket, const string& searchKey)
{
    KeyValuePair* currentElement = bucket;
    while (currentElement != nullptr)
    {
        if (currentElement->Key == searchKey)
        {
            // Ключ найден
            return false;
        }
        currentElement = currentElement->Next;
    }
    return true;
}
bool Add(HashTable* table, const string& key, const string& value)
{
    IsEmptyBool(table, key);

    int index = PearsonHash(key, table->Capacity);

    // Проверка на дубликат
    if (!DuplicateCheck(table->Buckets[index], key))
    {
        // Ключ уже существует
        return false;
    }
    
    // Добавление в начало цепочки
    KeyValuePair* newPair = new KeyValuePair;
    newPair->Key = key;
    newPair->Value = value;
    newPair->Next = table->Buckets[index];
    table->Buckets[index] = newPair;
    table->Count++;

    return true;
}

bool Remove(HashTable* table, const string& key)
{
    IsEmptyBool(table, key);

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

string Find(const HashTable* table, const string& key)
{
    IsEmptyString(table, key);
    int index = PearsonHash(key, table->Capacity);
    if (!DuplicateCheck(table->Buckets[index], key))
    {
        // Ключ уже существует
        return false;
    }

    return "";
}
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
void Rehash(HashTable*& table)
{
    IsEmptyNothing(table);
    int newCapacity = table->Capacity * 2;
    HashTable* newTable = CreateHashTable(newCapacity);
    TransferElements(table, &newTable, true);
    table->Buckets = newTable->Buckets;
    table->Capacity = newTable->Capacity;
    table->Count = newTable->Count;
    delete newTable;
}

void DeleteHashTable(HashTable* table)
{
    IsEmptyNothing(table);
    TransferElements(table, nullptr, false);
    delete table;
}

bool NeedsRehash(const HashTable* table)
{
    if (table == nullptr)
    {
        return false;
    }
    return table->Count > (3 * table->Capacity) / 4;
}

Dictionary* CreateDictionary(int initialCapacity)
{
    if (initialCapacity <= 0)
    {
        return nullptr;
    }

    Dictionary* dictionary = new Dictionary;
    dictionary->HashTable = CreateHashTable(initialCapacity);
    if (dictionary->HashTable == nullptr)
    {
        delete dictionary;
        return nullptr;
    }
    return dictionary;
}
bool DictionaryAdd(Dictionary* dictionary, const string& key, const string& value)
{
    IsEmptyBool(dictionary, key);

    if (NeedsRehash(dictionary->HashTable))
    {
        Rehash(dictionary->HashTable);
    }

    return Add(dictionary->HashTable, key, value);
}

bool DictionaryRemove(Dictionary* dictionary, const string& key)
{
    IsEmptyBool(dictionary, key);
    return Remove(dictionary->HashTable, key);
}

string DictionaryFind(const Dictionary* dictionary, const string& key)
{
    IsEmptyString(dictionary, key);
    return Find(dictionary->HashTable, key);
}

void DeleteDictionary(Dictionary* dictionary)
{
    IsEmptyNothing(dictionary);
    DeleteHashTable(dictionary->HashTable);
    delete dictionary;
}