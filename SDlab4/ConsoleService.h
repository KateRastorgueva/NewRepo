#pragma once
#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

/// <summary>
/// Сервисный класс для вывода информации в консоль
/// </summary>
class ConsoleService
{
public:
    /// <summary>
    /// Выводит заголовок в консоль
    /// </summary>
    /// <param name="title">Текст заголовка</param>
    static void PrintTitle(const string& title);

    /// <summary>
    /// Выводит сообщение с префиксом в консоль
    /// </summary>
    /// <param name="prefix">Префикс сообщения</param>
    /// <param name="message">Текст сообщения</param>
    static void PrintMessage(const string& prefix, const string& message);

    /// <summary>
    /// Выводит состояние словаря в консоль
    /// </summary>
    /// <param name="dictionary">Словарь для отображения</param>
    static void PrintDictionaryState(const Dictionary* dictionary);

    /// <summary>
    /// Выводит состояние хеш-таблицы в консоль
    /// </summary>
    /// <param name="dictionary">Словарь с хеш-таблицей для отображения</param>
    static void PrintHashTableState(const Dictionary* dictionary);

    /// <summary>
    /// Выводит цепочку элементов в ячейке хеш-таблицы
    /// </summary>
    /// <param name="current">Указатель на первый элемент цепочки</param>
    static void PrintBucketChain(KeyValuePair* current);
};