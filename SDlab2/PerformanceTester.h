#pragma once
#include "List.h"

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