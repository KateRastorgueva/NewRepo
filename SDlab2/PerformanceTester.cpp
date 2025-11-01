#include "PerformanceTester.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

DoublyLinkedList PerformanceTester::CreateFilledList(int size) {
    DoublyLinkedList list;
    for (int i = 0; i < size; i++) {
        string value = "value_" + to_string(rand() % 1000);
        list.PushBack(value);
    }
    return list;
}

MeasurementResults* PerformanceTester::PerformMeasurements(int& resultsCount) {
    const int sizesCount = 5;
    int sizes[sizesCount] = { 10, 100, 1000, 5000, 10000 };
    resultsCount = sizesCount;

    static MeasurementResults results[sizesCount];

    for (int i = 0; i < sizesCount; i++) {
        int size = sizes[i];
        results[i].Size = size;
        const int measurements = 1;
        long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0;
        long totalSearch = 0, totalSort = 0;

        for (int j = 0; j < measurements; j++) {
            DoublyLinkedList list = CreateFilledList(size);

            // PushFront 
            steady_clock::time_point begin1 = steady_clock::now();
            list.PushFront("test_value");
            steady_clock::time_point end1 = steady_clock::now();
            totalPushFront += duration_cast<nanoseconds>(end1 - begin1).count();

            // PushBack 
            steady_clock::time_point begin2 = steady_clock::now();
            list.PushBack("test_value");
            steady_clock::time_point end2 = steady_clock::now();
            totalPushBack += duration_cast<nanoseconds>(end2 - begin2).count();

            // PopFront
            steady_clock::time_point begin3 = steady_clock::now();
            if (!list.IsEmpty()) list.PopFront();
            steady_clock::time_point end3 = steady_clock::now();
            totalPopFront += duration_cast<nanoseconds>(end3 - begin3).count();

            // PopBack 
            steady_clock::time_point begin4 = steady_clock::now();
            if (!list.IsEmpty()) list.PopBack();
            steady_clock::time_point end4 = steady_clock::now();
            totalPopBack += duration_cast<nanoseconds>(end4 - begin4).count();

            // Search 
            string target = "value_" + to_string(rand() % 1000);
            steady_clock::time_point begin5 = steady_clock::now();
            list.LinearSearch(target);
            steady_clock::time_point end5 = steady_clock::now();
            totalSearch += duration_cast<nanoseconds>(end5 - begin5).count();

            // Sort 
            steady_clock::time_point begin6 = steady_clock::now();
            list.Sort();
            steady_clock::time_point end6 = steady_clock::now();
            totalSort += duration_cast<microseconds>(end6 - begin6).count();
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

/*static string IntToString(int value) {
    if (value == 0) return "0";

    string result = "";
    bool negative = (value < 0);

    if (negative) {
        value = -value;
    }

    while (value > 0) {
        char digit = '0' + (value % 10);
        result = digit + result;
        value /= 10;
    }

    if (negative) {
        result = "-" + result;
    }

    return result;
}


 string value = "value_" + IntToString(rand() % 1000);

*/





/*#include "PerformanceTester.h"
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
template<typename Func>
static long MeasureOperationTime(Func operation, bool useMicroseconds = false) {
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
    int sizes[sizesCount] = { 1000, 5000, 10000, 25000 };
    resultsCount = sizesCount;

    static MeasurementResults results[sizesCount];

    for (int i = 0; i < sizesCount; i++) {
        int size = sizes[i];
        results[i].Size = size;
        const int measurements = 10;
        long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0, totalSearch = 0, totalSort = 0;

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
}*/