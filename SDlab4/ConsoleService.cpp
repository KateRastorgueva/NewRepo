#include "ConsoleService.h"
#include "Dictionary.h"
#include <iomanip>
/// <summary>
/// Выводит заголовок в консоль
/// </summary>
/// <param name="title">Текст заголовка</param>
void ConsoleService::PrintTitle(const string& title)
{
    cout << endl;
    cout << title << endl;
}
/// <summary>
/// Выводит сообщение с префиксом в консоль
/// </summary>
/// <param name="prefix">Префикс сообщения</param>
/// <param name="message">Текст сообщения</param>
void ConsoleService::PrintMessage(const string& prefix, const string& message)
{
    cout << prefix << ": " << message << endl;
}
/// <summary>
/// Выводит ключ - > значение
/// </summary>
/// <param name="key">ключ</param>
/// <param name="value">значение</param>
void PrintKeyValue(const string& key, const string& value)
{
    cout << "   " << key << " -> " << value << endl;
}
/// <summary>
/// Выводит количество элементов
/// </summary>
/// <param name="dictionary">структура словарь</param>
void CountElements(const Dictionary* dictionary)
{
    cout << "Количество элементов: " << dictionary->HashTable->Count << endl;
}
/// <summary>
/// Выводит состояние словаря в консоль
/// </summary>
/// <param name="dictionary">Словарь для отображения</param>
void ConsoleService::PrintDictionaryState(const Dictionary* dictionary)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr)
    {
        PrintMessage("Ошибка", "Словарь не создан или удален");
        return;
    }

    PrintTitle("СОСТОЯНИЕ СЛОВАРЯ");
    CountElements(dictionary);

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
        PrintMessage("Информация", "Словарь пуст");
    }
}
/// <summary>
/// Выводит состояние хеш-таблицы в консоль
/// </summary>
/// <param name="dictionary">Словарь с хеш-таблицей для отображения</param>
void ConsoleService::PrintHashTableState(const Dictionary* dictionary)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr)
    {
        PrintMessage("Ошибка", "Хеш-таблица не создана или удалена");
        return;
    }

    PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
    cout << "Вместимость: " << dictionary->HashTable->Capacity << endl;
    CountElements(dictionary);
    cout << "Коэффициент заполнения: "
        << (double)(dictionary->HashTable->Count) / dictionary->HashTable->Capacity << endl;

    for (int i = 0; i < dictionary->HashTable->Capacity; i++)
    {
        cout << "Ячейка " << i << ": ";
        KeyValuePair* current = dictionary->HashTable->Buckets[i];
        PrintBucketChain(current);
        cout << endl;
    }
}

/// <summary>
/// Выводит цепочку элементов в ячейке хеш-таблицы
/// </summary>
/// <param name="current">Указатель на первый элемент цепочки</param>
void ConsoleService::PrintBucketChain(KeyValuePair* current)
{
    if (current == nullptr)
    {
        cout << "пусто";
        return;
    }

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