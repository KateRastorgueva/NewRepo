#pragma once
#include "Queue.h"
#include <string>
using namespace std;

/// <summary>
/// Отображает меню операций с очередью на кольцевом буфере
/// </summary>
void ShowQueueStructureMenu();

/// <summary>
/// Выводит подробную информацию о состоянии очереди
/// </summary>
/// <param name="queue">Указатель на очередь</param>
/// <param name="name">Название для отображения в заголовке</param>
void PrintQueueInfo(Queue* queue, const string& name);

/// <summary>
/// Создает новую очередь с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданную очередь или nullptr при отмене</returns>
Queue* CreateQueueMenu();

/// <summary>
/// Добавляет элемент в очередь с запросом значения у пользователя
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void AddElementToQueue(Queue* queue);

/// <summary>
/// Извлекает элемент из очереди с отображением результата
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void ExtractElementFromQueue(Queue* queue);

/// <summary>
/// Изменяет размер очереди с запросом нового размера у пользователя
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void ResizeQueueMenu(Queue*& queue);

/// <summary>
/// Удаляет очередь с освобождением памяти
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void DeleteQueueMenu(Queue*& queue);

/// <summary>
/// Обрабатывает главное меню работы с очередью
/// </summary>
/// <param name="queue">Ссылка на указатель очереди</param>
void HandleQueueMenu(Queue*& queue);