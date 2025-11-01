#pragma once
#include "List.h"
#include <string>

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
    static DoublyLinkedList CreateFilledList(int size);

public:
    static MeasurementResults* PerformMeasurements(int& resultsCount);
};