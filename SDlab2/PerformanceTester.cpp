#include "PerformanceTester.h"
#include <cstdlib>
#include <ctime>

DoublyLinkedList<int> PerformanceTester::create_filled_list(int size)
{
    DoublyLinkedList<int> list;
    for (int i = 0; i < size; i++)
    {
        list.push_back(rand() % 1000);
    }
    return list;
}

long long PerformanceTester::measure_list_operation(DoublyLinkedList<int>& list, OperationType opType)
{
    auto start = high_resolution_clock::now();

    switch (opType)
    {
    case OperationType::PushFront:
        list.push_front(999);
        break;
    case OperationType::PushBack:
        list.push_back(999);
        break;
    case OperationType::PopFront:
        if (!list.is_empty()) list.pop_front();
        break;
    case OperationType::PopBack:
        if (!list.is_empty()) list.pop_back();
        break;
    }

    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

// Простая функция для операций с nanoseconds
void PerformanceTester::measure_simple_operation(int listSize, void(*op)(DoublyLinkedList<int>&))
{
    auto list = create_filled_list(listSize);

    auto start = high_resolution_clock::now();
    op(list);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start);
}

// Специальная функция для сортировки (microseconds)
void PerformanceTester::measure_sort_operation(int listSize)
{
    auto list = create_filled_list(listSize);

    auto start = high_resolution_clock::now();
    list.sort();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
}

vector<MeasurementResults> PerformanceTester::performMeasurements()
{
    vector<int> sizes = { 10, 100, 1000, 5000, 10000 };
    vector<MeasurementResults> results;

    for (int size : sizes)
    {
        MeasurementResults result;
        result.size = size;

        int measurements = 5;
        long long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0;

        for (int i = 0; i < measurements; i++)
        {
            auto list = create_filled_list(size);

            totalPushFront += measure_list_operation(list, OperationType::PushFront);
            totalPushBack += measure_list_operation(list, OperationType::PushBack);
            totalPopFront += measure_list_operation(list, OperationType::PopFront);
            totalPopBack += measure_list_operation(list, OperationType::PopBack);
        }

        result.pushFrontTime = totalPushFront / measurements;
        result.pushBackTime = totalPushBack / measurements;
        result.popFrontTime = totalPopFront / measurements;
        result.popBackTime = totalPopBack / measurements;

        long long totalSearch = 0, totalSort = 0;
        for (int i = 0; i < measurements; i++)
        {
            auto list = create_filled_list(size);
            int target = rand() % 1000;

            auto start = high_resolution_clock::now();
            list.linear_search(target);
            auto end = high_resolution_clock::now();
            totalSearch += duration_cast<nanoseconds>(end - start).count();

            start = high_resolution_clock::now();
            list.sort();
            end = high_resolution_clock::now();
            totalSort += duration_cast<microseconds>(end - start).count();
        }

        result.searchTime = totalSearch / measurements;
        result.sortTime = totalSort / measurements;

        results.push_back(result);
    }

    return results;
}

void PerformanceTester::measureIndividualOperations()
{
    vector<int> sizes = { 100, 1000, 10000 };
    for (int size : sizes)
    {
        measurePushFront(size);
        measurePushBack(size);
        measurePopFront(size);
        measurePopBack(size);
        measureSearch(size);
        measureSort(size);
    }
}

void PerformanceTester::measurePushFront(int listSize)
{
    measure_simple_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            list.push_front(999);
        });
}

void PerformanceTester::measurePushBack(int listSize)
{
    measure_simple_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            list.push_back(999);
        });
}

void PerformanceTester::measurePopFront(int listSize)
{
    measure_simple_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            if (!list.is_empty()) list.pop_front();
        });
}

void PerformanceTester::measurePopBack(int listSize)
{
    measure_simple_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            if (!list.is_empty()) list.pop_back();
        });
}

void PerformanceTester::measureSearch(int listSize)
{
    measure_simple_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            int target = rand() % 1000;
            list.linear_search(target);
        });
}

void PerformanceTester::measureSort(int listSize)
{
    measure_sort_operation(listSize);
}