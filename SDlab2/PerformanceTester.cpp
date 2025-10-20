#include "PerformanceTester.h"
#include <cstdlib>
#include <ctime>

// Вспомогательная функция для создания заполненного списка
static DoublyLinkedList<int> create_filled_list(int size)
{
    DoublyLinkedList<int> list;
    for (int i = 0; i < size; i++)
    {
        list.push_back(rand() % 1000);
    }
    return list;
}

// Перечисление для типов операций
enum class OperationType
{
    PushFront,
    PushBack,
    PopFront,
    PopBack
};

// Функция для выполнения и измерения операции
static long long measure_list_operation(DoublyLinkedList<int>& list, OperationType opType)
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

// Единая шаблонная функция для измерения операций
template<typename Duration = nanoseconds, typename Operation>
static void measure_operation(int listSize, Operation op)
{
    auto list = create_filled_list(listSize);

    auto start = high_resolution_clock::now();
    op(list);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<Duration>(end - start);
    // duration можно использовать если нужно, но в оригинале он не используется
}

void PerformanceTester::performMeasurements()
{
    vector<int> sizes = { 10, 100, 1000, 5000, 10000 };

    for (int size : sizes)
    {
        int measurements = 5;
        long long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0;

        for (int i = 0; i < measurements; i++)
        {
            auto list = create_filled_list(size);

            // Измеряем все операции через switch case
            totalPushFront += measure_list_operation(list, OperationType::PushFront);
            totalPushBack += measure_list_operation(list, OperationType::PushBack);
            totalPopFront += measure_list_operation(list, OperationType::PopFront);
            totalPopBack += measure_list_operation(list, OperationType::PopBack);
        }

        // Измеряем поиск и сортировку
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
    }
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
    measure_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            list.push_front(999);
        });
}

void PerformanceTester::measurePushBack(int listSize)
{
    measure_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            list.push_back(999);
        });
}

void PerformanceTester::measurePopFront(int listSize)
{
    measure_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            if (!list.is_empty()) list.pop_front();
        });
}

void PerformanceTester::measurePopBack(int listSize)
{
    measure_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            if (!list.is_empty()) list.pop_back();
        });
}

void PerformanceTester::measureSearch(int listSize)
{
    measure_operation(listSize, [](DoublyLinkedList<int>& list)
        {
            int target = rand() % 1000;
            list.linear_search(target);
        });
}

void PerformanceTester::measureSort(int listSize)
{
    measure_operation<microseconds>(listSize, [](DoublyLinkedList<int>& list)
        {
            list.sort();
        });
}