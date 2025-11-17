#include <iostream>
#include <string>
#include "Validator.h"
using namespace std;

/// <summary>
/// Проверяет, является ли строка корректным целым числом
/// </summary>
/// <param name="value">Строка для проверки</param>
/// <returns>true если строка содержит только цифры, иначе false</returns>
bool IsValidIntegerString(const string& value)
{
    if (value.empty())
    {
        return false;
    }
    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] < '0' || value[i] > '9')
        {
            return false;
        }
    }

    if (value.length() > 1 && value[0] == '0')
    {
        return false;
    }
    return true;
}

/// <summary>
/// Вывод, что число очень большое
/// </summary>
void NumberIsBig()
{
    cout << "Число слишком большое! Введите меньшее число: ";
}

/// <summary>
/// Получает валидированный числовой ввод от пользователя
/// </summary>
/// <param name="message">Сообщение-приглашение для ввода</param>
/// <returns>Корректное целое число, введенное пользователем</returns>
int GetValidatedInput(const string& message)
{
    string input;
    while (true)
    {
        cout << message;
        getline(cin, input);

        if (!IsValidIntegerString(input))
        {
            cout << "Ошибка! Введите корректное число: ";
            continue;
        }

        if (input.length() > 10)
        {
            NumberIsBig();
            continue;
        }

        int result = 0;
        for (int i = 0; i < input.length(); i++)
        {
            int digit = input[i] - '0';
            if (result > (INT_MAX - digit) / 10)
            {
                NumberIsBig();
                break;
            }
            result = result * 10 + digit;

            if (i == input.length() - 1)
            {
                return result;
            }
        }
    }
}

/// <summary>
/// Получает валидированный числовой ввод в указанном диапазоне
/// </summary>
/// <param name="min">Минимальное допустимое значение</param>
/// <param name="max">Максимальное допустимое значение</param>
/// <returns>Число в диапазоне от min до max</returns>
int GetValidatedInputInRange(int min, int max)
{
    int value;
    while (true)
    {
        value = GetValidatedInput("Выберите действие: ");
        if (value >= min && value <= max)
        {
            return value;
        }
        cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
    }
}

/// <summary>
/// Получает валидированную вместимость для структуры данных
/// </summary>
/// <param name="structureName">Название структуры для сообщения</param>
/// <returns>Корректная вместимость (положительное число)</returns>
int GetValidatedCapacity(const string& structureName)
{
    return GetValidatedInput("Введите вместимость " + structureName + ": ");
}

/// <summary>
/// Получает значение для добавления в структуру данных
/// </summary>
/// <returns>Целое число для добавления</returns>
int GetValueForAddition()
{
    return GetValidatedInput("Введите значение для добавления: ");
}
/// <summary>
/// Проверяет корректность значения вместимости
/// </summary>
/// <param name="capacity">Проверяемое значение вместимости</param>
/// <returns>true если вместимость положительна, иначе false</returns>
bool ValidateCapacity(int capacity)
{
    if (capacity <= 0)
    {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return false;
    }
    return true;
}
/// <summary>
/// Универсальная проверка длины строки
/// </summary>
/// <param name="str">Строка для проверки</param>
/// <param name="fieldName">Название поля для сообщения об ошибке</param>
/// <param name="maxLength">Максимальная допустимая длина</param>
/// <returns>true если длина допустима</returns>
bool ValidateStringLength(const string& str, const string& fieldName, int maxLength)
{
    if (str.empty())
    {
        cout << "Ошибка! " << fieldName << " не может быть пустым." << endl;
        return false;
    }

    if (str.length() > maxLength)
    {
        cout << "Ошибка! " << fieldName << " слишком длинный. Максимум "
            << maxLength << " символов." << endl;
        return false;
    }

    return true;
}