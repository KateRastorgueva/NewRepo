#pragma once
#include "HashTable.h"

/// <summary>
/// Структура, представляющая словарь на основе хеш-таблицы
/// </summary>
struct Dictionary
{
    HashTable* HashTable;
};

/// <summary>
/// Создает новый словарь с указанной начальной вместимостью
/// </summary>
/// <param name="initialCapacity">Начальная вместимость словаря</param>
/// <returns>Указатель на созданный словарь или nullptr при ошибке</returns>
Dictionary* CreateDictionary(int initialCapacity);

/// <summary>
/// Добавляет пару ключ-значение в словарь
/// </summary>
/// <param name="dictionary">Словарь для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool DictionaryAdd(Dictionary* dictionary, const string& key, const string& value);

/// <summary>
/// Удаляет элемент с указанным ключом из словаря
/// </summary>
/// <param name="dictionary">Словарь для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool DictionaryRemove(Dictionary* dictionary, const string& key);

/// <summary>
/// Находит значение по ключу в словаре
/// </summary>
/// <param name="dictionary">Словарь для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string DictionaryFind(const Dictionary* dictionary, const string& key);

/// <summary>
/// Удаляет словарь и освобождает всю занятую память
/// </summary>
/// <param name="dictionary">Словарь для удаления</param>
void DeleteDictionary(Dictionary* dictionary);