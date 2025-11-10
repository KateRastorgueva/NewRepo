#pragma once
#include "Stack.h"
#include <string>
using namespace std;

/// <summary>
/// Отображает меню операций со стеком
/// </summary>
void ShowStackStructureMenu();

/// <summary>
/// Выводит подробную информацию о состоянии стека
/// </summary>
/// <param name="stack">Указатель на стек</param>
/// <param name="name">Название для отображения в заголовке</param>
void PrintStackInfo(Stack* stack, const string& name);

/// <summary>
/// Создает новый стек с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданный стек или nullptr при отмене</returns>
Stack* CreateStackMenu();

/// <summary>
/// Добавляет элемент в стек с запросом значения у пользователя
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void AddElementToStack(Stack* stack);

/// <summary>
/// Извлекает элемент из стека с отображением результата
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void ExtractElementFromStack(Stack* stack);

/// <summary>
/// Изменяет размер стека с запросом нового размера у пользователя
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void ResizeStackMenu(Stack*& stack);

/// <summary>
/// Удаляет стек с освобождением памяти
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void DeleteStackMenu(Stack*& stack);

/// <summary>
/// Обрабатывает главное меню работы со стеком
/// </summary>
/// <param name="stack">Ссылка на указатель стека</param>
void HandleStackMenu(Stack*& stack);