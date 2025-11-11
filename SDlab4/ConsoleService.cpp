#include "ConsoleService.h"
#include <iomanip>

void ConsoleService::PrintTitle(const string& title)
{
    cout << endl;
    cout << title << endl;
}

void ConsoleService::PrintMessage(const string& prefix, const string& message)
{
    cout << prefix << ": " << message << endl;
}

void ConsoleService::PrintKeyValue(const string& key, const string& value)
{
    cout << "   " << key << " -> " << value << endl;
}

void ConsoleService::PrintEmptyLine()
{
    cout << endl;
}

void ConsoleService::PrintDictionaryState(const Dictionary* dictionary)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr)
    {
        PrintMessage("Ошибка", "Словарь не создан или удален");
        return;
    }

    PrintTitle("СОСТОЯНИЕ СЛОВАРЯ");
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
        PrintMessage("Информация", "Словарь пуст");
    }
}

void ConsoleService::PrintHashTableState(const Dictionary* dictionary)
{
    if (dictionary == nullptr || dictionary->HashTable == nullptr)
    {
        PrintMessage("Ошибка", "Хеш-таблица не создана или удалена");
        return;
    }

    PrintTitle("СОСТОЯНИЕ ХЕШ-ТАБЛИЦЫ");
    cout << "Вместимость: " << dictionary->HashTable->Capacity << endl;
    cout << "Количество элементов: " << dictionary->HashTable->Count << endl;
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