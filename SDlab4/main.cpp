#include <iostream>
#include <windows.h>
#include "HashTable.h"
#include "Dictionary.h"
#include "Validator.h"
#include "ConsoleService.h"

using namespace std;

Dictionary* globalDictionary = nullptr;

/// <summary>
/// Устанавливает русскую кодировку для консоли
/// </summary>
void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

/// <summary>
/// Получает ключ от пользователя
/// </summary>
/// <returns>Введенный ключ</returns>
string GetKeyFromUser()
{
    string key;
    cout << "Введите ключ: ";
    getline(cin, key);
    return key;
}

/// <summary>
/// Получает значение от пользователя
/// </summary>
/// <returns>Введенное значение</returns>
string GetValueFromUser()
{
    string value;
    cout << "Введите значение: ";
    getline(cin, value);
    return value;
}

/// <summary>
/// Создает словарь (и внутреннюю хеш-таблицу)
/// </summary>
void CreateDictionaryMenu()
{
    if (globalDictionary != nullptr)
    {
        ConsoleService::PrintMessage("Ошибка", "Словарь уже создан. Выйдите из программы для создания нового.");
        return;
    }

    int capacity = GetValidatedCapacity("словаря");
    if (!ValidateCapacity(capacity))
    {
        return;
    }

    globalDictionary = CreateDictionary(capacity);

    if (globalDictionary != nullptr)
    {
        ConsoleService::PrintMessage("Успешно", "Словарь создан");
        // Показываем оба состояния после создания
        ConsoleService::PrintDictionaryState(globalDictionary);
        ConsoleService::PrintHashTableState(globalDictionary);
    }
    else
    {
        ConsoleService::PrintMessage("Ошибка", "Не удалось создать словарь");
    }
}

/// <summary>
/// Добавляет элемент в словарь
/// </summary>
void AddToDictionaryMenu()
{
    if (globalDictionary == nullptr)
    {
        ConsoleService::PrintMessage("Ошибка", "Сначала создайте словарь");
        return;
    }

    string key = GetKeyFromUser();
    string value = GetValueFromUser();

    if (!ValidateStringLength(key, "Ключ", 50) || !ValidateStringLength(value, "Значение", 100))
    {
        return;
    }

    if (DictionaryAdd(globalDictionary, key, value))
    {
        ConsoleService::PrintMessage("Успешно", "Элемент добавлен в словарь");
        // Показываем оба состояния после операции
        ConsoleService::PrintDictionaryState(globalDictionary);
        ConsoleService::PrintHashTableState(globalDictionary);
    }
    else
    {
        ConsoleService::PrintMessage("Ошибка", "Ключ уже существует или ошибка добавления");
    }
}

/// <summary>
/// Удаляет элемент из словаря
/// </summary>
void RemoveFromDictionaryMenu()
{
    if (globalDictionary == nullptr)
    {
        ConsoleService::PrintMessage("Ошибка", "Сначала создайте словарь");
        return;
    }

    string key = GetKeyFromUser();

    if (!ValidateStringLength(key, "Ключ", 50))
    {
        return;
    }

    if (DictionaryRemove(globalDictionary, key))
    {
        ConsoleService::PrintMessage("Успешно", "Элемент удален из словаря");
        // Показываем оба состояния после операции
        ConsoleService::PrintDictionaryState(globalDictionary);
        ConsoleService::PrintHashTableState(globalDictionary);
    }
    else
    {
        ConsoleService::PrintMessage("Ошибка", "Элемент не найден");
    }
}

/// <summary>
/// Ищет элемент в словаре
/// </summary>
void FindInDictionaryMenu()
{
    if (globalDictionary == nullptr)
    {
        ConsoleService::PrintMessage("Ошибка", "Сначала создайте словарь");
        return;
    }

    string key = GetKeyFromUser();

    if (!ValidateStringLength(key, "Ключ", 50))
    {
        return;
    }

    string value = DictionaryFind(globalDictionary, key);
    if (!value.empty())
    {
        ConsoleService::PrintMessage("Найдено", "Ключ: '" + key + "' -> Значение: '" + value + "'");
    }
    else
    {
        ConsoleService::PrintMessage("Не найдено", "Элемент с ключом '" + key + "' не существует");
    }
}

/// <summary>
/// Отображает главное меню программы (только словарь)
/// </summary>
void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ СЛОВАРЯ" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Создать словарь" << endl;
    cout << "2 - Добавить элемент (key-value)" << endl;
    cout << "3 - Удалить элемент по ключу" << endl;
    cout << "4 - Найти элемент по ключу" << endl;
    cout << "5 - Показать состояние словаря и хеш-таблицы" << endl;
}

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main()
{
    SetRussianEncoding();

    int choice;

    cout << "СЛОВАРЬ НА ОСНОВЕ ХЕШ-ТАБЛИЦЫ" << endl;
    do
    {
        ShowMainMenu();
        choice = GetValidatedInputInRange(0, 5);

        switch (choice)
        {
        case 0:
            cout << "Выход из программы..." << endl;
            break;
        case 1:
            CreateDictionaryMenu();
            break;
        case 2:
            AddToDictionaryMenu();
            break;
        case 3:
            RemoveFromDictionaryMenu();
            break;
        case 4:
            FindInDictionaryMenu();
            break;
        case 5:
            if (globalDictionary != nullptr)
            {
                ConsoleService::PrintDictionaryState(globalDictionary);
                ConsoleService::PrintHashTableState(globalDictionary);
            }
            else
            {
                ConsoleService::PrintMessage("Информация", "Словарь не создан");
            }
            break;
        }

    } while (choice != 0);

    // Очистка памяти
    if (globalDictionary != nullptr)
    {
        DeleteDictionary(globalDictionary);
    }

    return 0;
}