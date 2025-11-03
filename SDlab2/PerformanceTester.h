#pragma once
#include "List.h"
#include <string>

/// <summary>
/// —труктура дл€ хранени€ результатов измерени€ производительности операций списка
/// </summary>
struct MeasurementResults
{
    /// <summary>
    /// –азмер списка, дл€ которого проводились измерени€
    /// </summary>
    int Size;
    /// <summary>
    /// —реднее врем€ операции PushFront в наносекундах
    /// </summary>
    long PushFrontTime;
    /// <summary>
    /// —реднее врем€ операции PushBack в наносекундах
    /// </summary>
    long PushBackTime;
    /// <summary>
    /// —реднее врем€ операции PopFront в наносекундах
    /// </summary>
    long PopFrontTime;
    /// <summary>
    /// —реднее врем€ операции PopBack в наносекундах
    /// </summary>
    long PopBackTime;
    /// <summary>
    /// —реднее врем€ операции поиска в наносекундах
    /// </summary>
    long SearchTime;
    /// <summary>
    /// —реднее врем€ операции сортировки в микросекундах
    /// </summary>
    long SortTime;
};

/// <summary>
///  ласс дл€ тестировани€ производительности операций двусв€зного списка
/// </summary>
class PerformanceTester
{
private:
    /// <summary>
    /// —оздает заполненный список указанного размера
    /// </summary>
    /// <param name="size">–азмер списка дл€ создани€</param>
    /// <returns>«аполненный двусв€зный список</returns>
    static DoublyLinkedList CreateFilledList(int size);

public:
    /// <summary>
    /// ¬ыполн€ет измерени€ производительности дл€ различных размеров списка
    /// </summary>
    /// <param name="resultsCount">¬ыходной параметр - количество результатов измерений</param>
    /// <returns>”казатель на массив результатов измерений</returns>
    static MeasurementResults* PerformMeasurements(int& resultsCount);
};