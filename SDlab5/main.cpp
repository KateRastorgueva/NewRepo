#include <iostream>
#include <windows.h>
#include "TreeConsoleService.h"
#include "Validator.h"
#include "BinarySearchTreeMenu.h"
#include "CartesianTreeMenu.h"

using namespace std;

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
    cout << "\nГЛАВНОЕ МЕНЮ ДЕРЕВЬЕВ ПОИСКА" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Работа с бинарным деревом поиска" << endl;
    cout << "2 - Работа с декартовым деревом" << endl;
}

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main()
{
    SetRussianEncoding();

    int choice;

    cout << "ДЕРЕВЬЯ ПОИСКА" << endl;

    do
    {
        ShowMainMenu();
        choice = GetValidatedInputInRange(0, 2);

        switch (choice)
        {
        case 0:
        {
            cout << "Выход из программы..." << endl;
            break;
        }
        case 1:
        {
            BinarySearchTreeMenu();
            break;
        }
        case 2:
        {
            CartesianTreeMenu();
            break;
        }
        }

    } while (choice != 0);

    return 0;
}