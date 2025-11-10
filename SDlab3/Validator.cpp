#include <iostream>
#include <string>
#include "Validator.h"
using namespace std;

bool IsValidIntegerString(const string& value)
{
    if (value.empty()) return false;

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
            cout << "Число слишком большое! Введите меньшее число: ";
            continue;
        }

        int result = 0;
        for (int i = 0; i < input.length(); i++)
        {
            int digit = input[i] - '0';
            if (result > (2147483647 - digit) / 10)
            {
                cout << "Число слишком большое! Введите меньшее число: ";
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

int GetValidatedCapacity(const string& structureName)
{
    return GetValidatedInput("Введите вместимость " + structureName + ": ");
}

int GetValueForAddition()
{
    return GetValidatedInput("Введите значение для добавления: ");
}

bool ValidateCapacity(int capacity)
{
    if (capacity <= 0)
    {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return false;
    }
    return true;
}