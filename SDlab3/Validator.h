#pragma once
#include <string>
using namespace std;

/// <summary>
/// Проверяет, является ли строка корректным целым числом
/// </summary>
/// <param name="value">Строка для проверки</param>
/// <returns>true если строка содержит только цифры, иначе false</returns>
bool IsValidIntegerString(const string& value);

/// <summary>
/// Получает валидированный числовой ввод от пользователя
/// </summary>
/// <param name="message">Сообщение-приглашение для ввода</param>
/// <returns>Корректное целое число, введенное пользователем</returns>
int GetValidatedInput(const string& message);

/// <summary>
/// Получает валидированный числовой ввод в указанном диапазоне
/// </summary>
/// <param name="min">Минимальное допустимое значение</param>
/// <param name="max">Максимальное допустимое значение</param>
/// <returns>Число в диапазоне от min до max</returns>
int GetValidatedInputInRange(int min, int max);

/// <summary>
/// Получает валидированную вместимость для структуры данных
/// </summary>
/// <param name="structureName">Название структуры для сообщения</param>
/// <returns>Корректная вместимость (положительное число)</returns>
int GetValidatedCapacity(const string& structureName);

/// <summary>
/// Получает значение для добавления в структуру данных
/// </summary>
/// <returns>Целое число для добавления</returns>
int GetValueForAddition();

/// <summary>
/// Проверяет корректность значения вместимости
/// </summary>
/// <param name="capacity">Проверяемое значение вместимости</param>
/// <returns>true если вместимость положительна, иначе false</returns>
bool ValidateCapacity(int capacity);