#include "PerformanceTester.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;

DoublyLinkedList<int> PerformanceTester::create_filled_list(int size) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < size; i++) {
        list.push_back(rand() % 1000);
    }
    return list;
}

MeasurementResults* PerformanceTester::performMeasurements(int& resultsCount) {
    const int sizesCount = 5;
    int sizes[sizesCount] = { 10, 100, 1000, 5000, 10000 };
    resultsCount = sizesCount;

    static MeasurementResults results[sizesCount];

    for (int i = 0; i < sizesCount; i++) {
        int size = sizes[i];
        results[i].size = size;
        const int measurements = 3;
        long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0;
        long totalSearch = 0, totalSort = 0;

        for (int j = 0; j < measurements; j++) {
            auto list = create_filled_list(size);

            // Push Front
            auto begin = steady_clock::now();
            list.push_front(999);
            auto end = steady_clock::now();
            totalPushFront += duration_cast<nanoseconds>(end - begin).count();

            // Push Back
            begin = steady_clock::now();
            list.push_back(999);
            end = steady_clock::now();
            totalPushBack += duration_cast<nanoseconds>(end - begin).count();

            // Pop Front
            begin = steady_clock::now();
            if (!list.is_empty()) list.pop_front();
            end = steady_clock::now();
            totalPopFront += duration_cast<nanoseconds>(end - begin).count();

            // Pop Back
            begin = steady_clock::now();
            if (!list.is_empty()) list.pop_back();
            end = steady_clock::now();
            totalPopBack += duration_cast<nanoseconds>(end - begin).count();

            // Search
            int target = rand() % 1000;
            begin = steady_clock::now();
            list.linear_search(target);
            end = steady_clock::now();
            totalSearch += duration_cast<nanoseconds>(end - begin).count();

            // Sort
            begin = steady_clock::now();
            list.sort();
            end = steady_clock::now();
            totalSort += duration_cast<microseconds>(end - begin).count();
        }

        results[i].pushFrontTime = totalPushFront / measurements;
        results[i].pushBackTime = totalPushBack / measurements;
        results[i].popFrontTime = totalPopFront / measurements;
        results[i].popBackTime = totalPopBack / measurements;
        results[i].searchTime = totalSearch / measurements;
        results[i].sortTime = totalSort / measurements;
    }

    return results;
}