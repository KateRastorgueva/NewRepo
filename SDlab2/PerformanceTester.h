// PerformanceTester.h
#pragma once

#include "List.h"
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;
using namespace std::chrono;

class PerformanceTester {
public:
    static void performMeasurements();
    static void measureIndividualOperations();

private:
    static void measurePushFront(int listSize);
    static void measurePushBack(int listSize);
    static void measurePopFront(int listSize);
    static void measurePopBack(int listSize);
    static void measureSearch(int listSize);
    static void measureSort(int listSize);
};