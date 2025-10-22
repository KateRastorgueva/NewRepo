#include "PerformanceTester.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <functional>

using namespace std::chrono;

DoublyLinkedList<int> PerformanceTester::CreateFilledList(int size) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < size; i++) {
        list.PushBack(rand() % 1000);
    }
    return list;
}

static long MeasureOperationTime(const std::function<void()>& operation, bool useMicroseconds = false) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    operation();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (useMicroseconds) {
        return duration_cast<microseconds>(end - begin).count();
    }
    else {
        return duration_cast<nanoseconds>(end - begin).count();
    }
}

MeasurementResults* PerformanceTester::PerformMeasurements(int& resultsCount) {
    const int sizesCount = 5;
    int sizes[sizesCount] = { 10, 100, 1000, 5000, 10000 };
    resultsCount = sizesCount;

    static MeasurementResults results[sizesCount];

    for (int i = 0; i < sizesCount; i++) {
        int size = sizes[i];
        results[i].Size = size;
        const int measurements = 3;
        long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0;
        long totalSearch = 0, totalSort = 0;

        for (int j = 0; j < measurements; j++) {
            DoublyLinkedList<int> list = CreateFilledList(size);

            totalPushFront += MeasureOperationTime([&list]() { list.PushFront(999); });
            totalPushBack += MeasureOperationTime([&list]() { list.PushBack(999); });
            totalPopFront += MeasureOperationTime([&list]() { if (!list.IsEmpty()) list.PopFront(); });
            totalPopBack += MeasureOperationTime([&list]() { if (!list.IsEmpty()) list.PopBack(); });
            int target = rand() % 1000;
            totalSearch += MeasureOperationTime([&list, target]() { list.LinearSearch(target); });
            totalSort += MeasureOperationTime([&list]() { list.Sort(); }, true);
        }

        results[i].PushFrontTime = totalPushFront / measurements;
        results[i].PushBackTime = totalPushBack / measurements;
        results[i].PopFrontTime = totalPopFront / measurements;
        results[i].PopBackTime = totalPopBack / measurements;
        results[i].SearchTime = totalSearch / measurements;
        results[i].SortTime = totalSort / measurements;
    }

    return results;
}