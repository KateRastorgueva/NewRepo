#pragma once
#include <string>
using namespace std;

/// <summary>
/// Структура, представляющая пару ключ-значение в хеш-таблице
/// </summary>
struct KeyValuePair
{
    string Key;
    string Value;
    KeyValuePair* Next;
};

/// <summary>
/// Структура, представляющая хеш-таблицу с методом цепочек
/// </summary>
struct HashTable
{
    KeyValuePair** Buckets;
    int Capacity;
    int Count;
};

/// <summary>
/// Создает новую хеш-таблицу указанной вместимости
/// </summary>
/// <param name="capacity">Вместимость создаваемой хеш-таблицы</param>
/// <returns>Указатель на созданную хеш-таблицу или nullptr при ошибке</returns>
HashTable* CreateHashTable(int capacity);

/// <summary>
/// Вычисляет хеш-код для ключа using метод Пирсона
/// </summary>
/// <param name="key">Ключ для вычисления хеша</param>
/// <param name="capacity">Вместимость хеш-таблицы</param>
/// <returns>Индекс ячейки в хеш-таблице</returns>
int PearsonHash(const string& key, int capacity);

/// <summary>
/// Добавляет пару ключ-значение в хеш-таблицу
/// </summary>
/// <param name="table">Хеш-таблица для добавления</param>
/// <param name="key">Ключ добавляемого элемента</param>
/// <param name="value">Значение добавляемого элемента</param>
/// <returns>true если элемент добавлен, false если ключ уже существует</returns>
bool Add(HashTable* table, const string& key, const string& value);

/// <summary>
/// Удаляет элемент с указанным ключом из хеш-таблицы
/// </summary>
/// <param name="table">Хеш-таблица для удаления</param>
/// <param name="key">Ключ удаляемого элемента</param>
/// <returns>true если элемент удален, false если элемент не найден</returns>
bool Remove(HashTable* table, const string& key);

/// <summary>
/// Выполняет перехеширование таблицы с увеличением вместимости
/// </summary>
/// <param name="table">Ссылка на указатель хеш-таблицы для перехеширования</param>
void Rehash(HashTable*& table);

/// <summary>
/// Удаляет хеш-таблицу и освобождает всю занятую память
/// </summary>
/// <param name="table">Хеш-таблица для удаления</param>
void DeleteHashTable(HashTable* table);

/// <summary>
/// Проверяет необходимость перехеширования таблицы
/// </summary>
/// <param name="table">Хеш-таблица для проверки</param>
/// <returns>true если требуется перехеширование, false в противном случае</returns>
bool NeedsRehash(const HashTable* table);
/// <summary>
/// Находит значение по ключу в хеш-таблице
/// </summary>
/// <param name="table">Хеш-таблица для поиска</param>
/// <param name="key">Ключ для поиска</param>
/// <returns>Значение элемента или пустая строка если элемент не найден</returns>
string Find(const HashTable* table, const string& key);