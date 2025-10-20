#pragma once
#include "List.h"
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;


struct MeasurementResults {
    int size;
    long pushFrontTime;
    long pushBackTime;
    long popFrontTime;
    long popBackTime;
    long searchTime;
    long sortTime;
};

class PerformanceTester {
private:
    static DoublyLinkedList<int> create_filled_list(int size);

public:
    static MeasurementResults* performMeasurements(int& resultsCount);
};