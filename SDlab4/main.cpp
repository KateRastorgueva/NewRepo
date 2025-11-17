#include <iostream>
#include <windows.h>
#include "HashTable.h"
#include "Dictionary.h"
#include "Validator.h"
#include "ConsoleService.h"
#include "DictionaryMenu.h"
#include "HashTableMenu.h"

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
/// Отображает главное меню программы
/// </summary>
void ShowMainMenu()
{
    cout << "\nГЛАВНОЕ МЕНЮ СТРУКТУР ДАННЫХ" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Работа со словарем" << endl;
    cout << "2 - Работа с хеш-таблицей" << endl;
    cout << "3 - Показать состояния обеих структур" << endl;
}

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main()
{
    SetRussianEncoding();

    int choice;

    cout << "ДЕМОНСТРАЦИЯ ХЕШ-ТАБЛИЦЫ И СЛОВАРЯ" << endl;

    do
    {
        ShowMainMenu();
        choice = GetValidatedInputInRange(0, 3);

        switch (choice)
        {
        case 0:
            cout << "Выход из программы..." << endl;
            break;
        case 1:
            DictionaryMenu::ShowDictionaryMenu(globalDictionary);
            break;
        case 2:
            if (globalDictionary != nullptr)
            {
                HashTableMenu::ShowHashTableMenu(globalDictionary->HashTable);
            }
            else
            {
                ConsoleService::PrintMessage("Ошибка", "Сначала создайте словарь");
            }
            break;
        case 3:
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

    if (globalDictionary != nullptr)
    {
        DeleteDictionary(globalDictionary);
    }

    return 0;
}