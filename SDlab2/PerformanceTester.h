#pragma once
#include "List.h"
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

struct MeasurementResults {
    int size;
    long long pushFrontTime;
    long long pushBackTime;
    long long popFrontTime;
    long long popBackTime;
    long long searchTime;
    long long sortTime;
};

class PerformanceTester {
public:
    static vector<MeasurementResults> performMeasurements();
    static void measureIndividualOperations();

private:
    static DoublyLinkedList<int> create_filled_list(int size);
    enum class OperationType { PushFront, PushBack, PopFront, PopBack };
    static long long measure_list_operation(DoublyLinkedList<int>& list, OperationType opType);
    static void measure_simple_operation(int listSize, void(*op)(DoublyLinkedList<int>&));
    static void measure_sort_operation(int listSize);

    static void measurePushFront(int listSize);
    static void measurePushBack(int listSize);
    static void measurePopFront(int listSize);
    static void measurePopBack(int listSize);
    static void measureSearch(int listSize);
    static void measureSort(int listSize);
};