#pragma once
#include <iostream>
#include <string>
using namespace std;

/// <summary>
/// Проверяет существование структуры данных
/// </summary>
/// <param name="structure">Указатель на структуру данных</param>
/// <param name="structureName">Название структуры для сообщений</param>
/// <returns>true если структура существует, иначе false</returns>
bool CheckStructureExists(void* structure, const string& structureName);

/// <summary>
/// Проверяет отсутствие структуры данных
/// </summary>
/// <param name="structure">Указатель на структуру данных</param>
/// <param name="structureName">Название структуры для сообщений</param>
/// <returns>true если структура не существует, иначе false</returns>
bool CheckStructureNotExists(void* structure, const string& structureName);

/// <summary>
/// Проверяет, является ли структура данных пустой
/// </summary>
/// <param name="isEmpty">Результат проверки на пустоту</param>
/// <param name="structureName">Название структуры для сообщений</param>
/// <returns>true если структура пуста, иначе false</returns>
bool CheckStructureEmpty(bool isEmpty, const string& structureName);

/// <summary>
/// Отображает извлеченный элемент
/// </summary>
/// <param name="value">Значение извлеченного элемента</param>
void ShowExtractedElement(int value);

/// <summary>
/// Отображает сообщение об успешном создании структуры
/// </summary>
/// <param name="structureName">Название созданной структуры</param>
void ShowCreationSuccess(const string& structureName);

/// <summary>
/// Отображает сообщение об ошибке создания структуры
/// </summary>
/// <param name="structureName">Название структуры</param>
void ShowCreationError(const string& structureName);

/// <summary>
/// Отображает сообщение об успешном добавлении элемента
/// </summary>
/// <param name="value">Добавленное значение</param>
/// <param name="structureName">Название структуры</param>
void ShowAddSuccess(int value, const string& structureName);

/// <summary>
/// Отображает сообщение об ошибке добавления элемента
/// </summary>
/// <param name="structureName">Название структуры</param>
void ShowAddError(const string& structureName);

/// <summary>
/// Отображает сообщение об успешном изменении размера
/// </summary>
/// <param name="newCapacity">Новый размер структуры</param>
/// <param name="structureName">Название структуры</param>
void ShowResizeSuccess(int newCapacity, const string& structureName);

/// <summary>
/// Отображает сообщение об ошибке изменения размера
/// </summary>
/// <param name="structureName">Название структуры</param>
void ShowResizeError(const string& structureName);

/// <summary>
/// Отображает сообщение о результате удаления структуры
/// </summary>
/// <param name="wasDeleted">Факт выполнения удаления</param>
/// <param name="structureName">Название структуры</param>
void ShowDeleteMessage(bool wasDeleted, const string& structureName);

/// <summary>
/// Выводит базовую информацию о структуре
/// </summary>
/// <param name="capacity">Вместимость структуры</param>
/// <param name="top">Индекс вершины/головы</param>
void WriteInfo(int capacity, int top);

/// <summary>
/// Выводит информацию о состоянии заполнения структуры
/// </summary>
/// <param name="isEmpty">Признак пустоты</param>
/// <param name="isFull">Признак полноты</param>
void WriteFullEmptyInfo(bool isEmpty, bool isFull);

/// <summary>
/// Выводит подробную информацию о кольцевом буфере
/// </summary>
/// <param name="capacity">Вместимость буфера</param>
/// <param name="head">Индекс головы</param>
/// <param name="tail">Индекс хвоста</param>
/// <param name="count">Количество элементов</param>
void WriteCircularBufferInfo(int capacity, int head, int tail, int count);

/// <summary>
/// Выводит информацию о занятом и свободном месте
/// </summary>
/// <param name="used">Количество занятых мест</param>
/// <param name="free">Количество свободных мест</param>
void WriteSpaceInfo(int used, int free);

/// <summary>
/// Выводит сообщение об отсутствии структуры
/// </summary>
/// <param name="value">Название структуры</param>
void WriteIsDeleteNotCreated(string value);

/// <summary>
/// Проверяет и выводит заголовок структуры
/// </summary>
/// <param name="structure">Указатель на структуру</param>
/// <param name="name">Название структуры</param>
/// <returns>true если структура существует, иначе false</returns>
bool CheckAndPrintHeader(void* structure, const string& name);

/// <summary>
/// Выводит заголовок для содержимого структуры
/// </summary>
/// <param name="isEmpty">Признак пустоты структуры</param>
/// <param name="contentDescription">Описание содержимого</param>
void PrintContentHeader(bool isEmpty, const string& contentDescription);