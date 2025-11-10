#pragma once
#include "CircularBuffer.h"
#include <string>
using namespace std;

/// <summary>
/// Отображает меню операций с кольцевым буфером
/// </summary>
void ShowCircularBufferStructureMenu();

/// <summary>
/// Выводит подробную информацию о состоянии кольцевого буфера
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
/// <param name="name">Название для отображения в заголовке</param>
void PrintCircularBufferInfo(CircularBuffer* circularBuffer, const string& name);

/// <summary>
/// Создает новый кольцевой буфер с запросом параметров у пользователя
/// </summary>
/// <returns>Указатель на созданный буфер или nullptr при отмене</returns>
CircularBuffer* CreateCircularBufferMenu();

/// <summary>
/// Добавляет элемент в кольцевой буфер с запросом значения у пользователя
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
void AddElementToCircularBuffer(CircularBuffer* circularBuffer);

/// <summary>
/// Извлекает элемент из кольцевого буфера с отображением результата
/// </summary>
/// <param name="circularBuffer">Указатель на кольцевой буфер</param>
void ExtractElementFromCircularBuffer(CircularBuffer* circularBuffer);

/// <summary>
/// Изменяет размер кольцевого буфера с запросом нового размера у пользователя
/// </summary>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
void ResizeCircularBufferMenu(CircularBuffer*& circularBuffer);

/// <summary>
/// Удаляет кольцевой буфер с освобождением памяти
/// </summary>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
void DeleteCircularBufferMenu(CircularBuffer*& circularBuffer);

/// <summary>
/// Обрабатывает главное меню работы с кольцевым буфером
/// </summary>
/// <param name="circularBuffer">Ссылка на указатель кольцевого буфера</param>
void HandleCircularBufferMenu(CircularBuffer*& circularBuffer);