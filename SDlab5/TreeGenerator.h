#pragma once
#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include <string>

/// <summary>
/// Генерирует массив уникальных случайных ключей
/// </summary>
/// <param name="keys">Массив для сохранения ключей</param>
/// <param name="count">Количество ключей</param>
/// <param name="minKey">Минимальное значение ключа</param>
/// <param name="maxKey">Максимальное значение ключа</param>
void GenerateUniqueRandomKeys(int* keys, int count, int minKey, int maxKey);

/// <summary>
/// Генерирует массив случайных приоритетов
/// </summary>
/// <param name="priorities">Массив для сохранения приоритетов</param>
/// <param name="count">Количество приоритетов</param>
/// <param name="minPriority">Минимальное значение приоритета</param>
/// <param name="maxPriority">Максимальное значение приоритета</param>
void GenerateRandomPriorities(int* priorities, int count, int minPriority, int maxPriority);

/// <summary>
/// Генерирует случайное значение для узла
/// </summary>
/// <param name="index">Индекс узла</param>
/// <returns>Сгенерированное значение</returns>
string GenerateRandomValue(int index);

/// <summary>
/// Генерирует случайное бинарное дерево поиска
/// </summary>
/// <param name="tree">Дерево для заполнения</param>
/// <param name="elementCount">Количество элементов для генерации</param>
void GenerateRandomBinarySearchTree(BinarySearchTree* tree, int elementCount);

/// <summary>
/// Генерирует случайное декартово дерево
/// </summary>
/// <param name="tree">Дерево для заполнения</param>
/// <param name="elementCount">Количество элементов для генерации</param>
void GenerateRandomCartesianTree(CartesianTree* tree, int elementCount);