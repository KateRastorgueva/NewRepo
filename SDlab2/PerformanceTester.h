#pragma once
#include "List.h"
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

struct MeasurementResults {
    int Size;
    long PushFrontTime;
    long PushBackTime;
    long PopFrontTime;
    long PopBackTime;
    long SearchTime;
    long SortTime;
};

class PerformanceTester {
private:
    static DoublyLinkedList<int> CreateFilledList(int size);

public:
    static MeasurementResults* PerformMeasurements(int& resultsCount);
};