#include "Dictionary.h"
#include <iostream>

/// <summary>
/// Создает новый словарь с указанной начальной вместимостью
/// </summary>
/// <param name="initialCapacity">Начальная вместимость словаря</param>
/// <returns>Указатель на созданный словарь или nullptr при ошибке</returns>
Dictionary* CreateDictionary(int initialCapacity)
{
    if (initialCapacity <= 0) return nullptr;

    Dictionary* dictionary = new Dictionary;
    dictionary->HashTable = CreateHashTable(initialCapacity);
    if (dictionary->HashTable == nullptr)
    {
        delete dictionary;
        return nullptr;
    }
    return dictionary;
}

/// <summary>
/// Добавляет пару ключ-значение в словарь
/// </summary>
/// <param name="dictionary">Словарь для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool DictionaryAdd(Dictionary* dictionary, const string& key, const string& value)
{
    if (dictionary == nullptr || key.empty()) return false;

    if (NeedsRehash(dictionary->HashTable))
    {
        Rehash(dictionary->HashTable);
    }

    return Add(dictionary->HashTable, key, value);
}

/// <summary>
/// Удаляет элемент с указанным ключом из словаря
/// </summary>
/// <param name="dictionary">Словарь для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool DictionaryRemove(Dictionary* dictionary, const string& key)
{
    if (dictionary == nullptr || key.empty()) return false;
    return Remove(dictionary->HashTable, key);
}

/// <summary>
/// Находит значение по ключу в словаре
/// </summary>
/// <param name="dictionary">Словарь для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string DictionaryFind(const Dictionary* dictionary, const string& key)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr || key.empty())
    {
        return "";
    }

    HashTable* table = dictionary->HashTable;
    int index = PearsonHash(key, table->Capacity);
    KeyValuePair* current = table->Buckets[index];

    while (current != nullptr)
    {
        if (current->Key == key)
        {
            return current->Value;
        }
        current = current->Next;
    }

    return "";
}

/// <summary>
/// Удаляет словарь и освобождает всю занятую память
/// </summary>
/// <param name="dictionary">Словарь для удаления</param>
void DeleteDictionary(Dictionary* dictionary)
{
    if (dictionary == nullptr) return;

    DeleteHashTable(dictionary->HashTable);
    delete dictionary;
}