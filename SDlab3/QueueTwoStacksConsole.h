#pragma once
#include "QueueTwoStacks.h"
#include <string>
using namespace std;

/// <summary>
/// Отображает меню операций с очередью на двух стеках
/// </summary>
void ShowQueueTwoStacksStructureMenu();

/// <summary>
/// Выводит подробную информацию о состоянии очереди на двух стеках
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="name">Название для отображения в заголовке</param>
void PrintQueueTwoStacksInfo(QueueTwoStacks* queue, const string& name);

/// <summary>
/// Создает новую очередь на двух стеках с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданную очередь или nullptr при отмене</returns>
QueueTwoStacks* CreateQueueTwoStacksMenu();

/// <summary>
/// Добавляет элемент в очередь на двух стеках с запросом значения у пользователя
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void AddElementToQueueTwoStacks(QueueTwoStacks* queue);

/// <summary>
/// Извлекает элемент из очереди на двух стеках с отображением результата
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void ExtractElementFromQueueTwoStacks(QueueTwoStacks* queue);

/// <summary>
/// Изменяет размер очереди на двух стеках с запросом нового размера у пользователя
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void ResizeQueueTwoStacksMenu(QueueTwoStacks*& queue);

/// <summary>
/// Удаляет очередь на двух стеках с освобождением памяти
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void DeleteQueueTwoStacksMenu(QueueTwoStacks*& queue);

/// <summary>
/// Обрабатывает главное меню работы с очередью на двух стеках
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void HandleQueueTwoStacksMenu(QueueTwoStacks*& queue);