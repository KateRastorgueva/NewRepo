// PerformanceTester.cpp
#include "PerformanceTester.h"
#include <cstdlib>
#include <ctime>

void PerformanceTester::performMeasurements() {
    vector<int> sizes = { 10, 100, 1000, 5000, 10000 };

    cout << "=== Performance Measurements ===\n" << endl;

    for (int size : sizes) {
        cout << "--- Testing with list size: " << size << " ---" << endl;

        int measurements = 5;
        long long totalPushFront = 0, totalPushBack = 0, totalPopFront = 0, totalPopBack = 0;

        for (int i = 0; i < measurements; i++) {
            DoublyLinkedList<int> list;

            // Заполняем список
            for (int j = 0; j < size; j++) {
                list.push_back(rand() % 1000);
            }

            // Измеряем PushFront
            auto start = high_resolution_clock::now();
            list.push_front(999);
            auto end = high_resolution_clock::now();
            totalPushFront += duration_cast<nanoseconds>(end - start).count();

            // Измеряем PushBack
            start = high_resolution_clock::now();
            list.push_back(999);
            end = high_resolution_clock::now();
            totalPushBack += duration_cast<nanoseconds>(end - start).count();

            // Измеряем PopFront
            start = high_resolution_clock::now();
            if (!list.is_empty()) list.pop_front();
            end = high_resolution_clock::now();
            totalPopFront += duration_cast<nanoseconds>(end - start).count();

            // Измеряем PopBack
            start = high_resolution_clock::now();
            if (!list.is_empty()) list.pop_back();
            end = high_resolution_clock::now();
            totalPopBack += duration_cast<nanoseconds>(end - start).count();
        }

        cout << "PushFront (avg): " << totalPushFront / measurements << " ns" << endl;
        cout << "PushBack (avg): " << totalPushBack / measurements << " ns" << endl;
        cout << "PopFront (avg): " << totalPopFront / measurements << " ns" << endl;
        cout << "PopBack (avg): " << totalPopBack / measurements << " ns" << endl;

        // Измеряем поиск и сортировку
        long long totalSearch = 0, totalSort = 0;
        for (int i = 0; i < measurements; i++) {
            DoublyLinkedList<int> list;
            for (int j = 0; j < size; j++) {
                list.push_back(rand() % 1000);
            }

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

        cout << "Search (avg): " << totalSearch / measurements << " ns" << endl;
        cout << "Sort (avg): " << totalSort / measurements << " μs" << endl;
        cout << endl;
    }
}

void PerformanceTester::measureIndividualOperations() {
    cout << "=== Individual Operation Measurements ===\n" << endl;

    vector<int> sizes = { 100, 1000, 10000 };
    for (int size : sizes) {
        cout << "List size: " << size << endl;

        measurePushFront(size);
        measurePushBack(size);
        measurePopFront(size);
        measurePopBack(size);
        measureSearch(size);
        measureSort(size);

        cout << endl;
    }
}

// Реализации отдельных функций измерений
void PerformanceTester::measurePushFront(int listSize) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < listSize; i++) {
        list.push_back(rand() % 1000);
    }

    auto start = high_resolution_clock::now();
    list.push_front(999);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "  PushFront: " << duration.count() << " ns" << endl;
}

void PerformanceTester::measurePushBack(int listSize) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < listSize; i++) {
        list.push_back(rand() % 1000);
    }

    auto start = high_resolution_clock::now();
    list.push_back(999);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "  PushBack: " << duration.count() << " ns" << endl;
}

void PerformanceTester::measurePopFront(int listSize) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < listSize; i++) {
        list.push_back(rand() % 1000);
    }

    auto start = high_resolution_clock::now();
    if (!list.is_empty()) list.pop_front();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "  PopFront: " << duration.count() << " ns" << endl;
}

void PerformanceTester::measurePopBack(int listSize) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < listSize; i++) {
        list.push_back(rand() % 1000);
    }

    auto start = high_resolution_clock::now();
    if (!list.is_empty()) list.pop_back();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "  PopBack: " << duration.count() << " ns" << endl;
}

void PerformanceTester::measureSearch(int listSize) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < listSize; i++) {
        list.push_back(rand() % 1000);
    }

    int target = rand() % 1000;
    auto start = high_resolution_clock::now();
    list.linear_search(target);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "  Search: " << duration.count() << " ns" << endl;
}

void PerformanceTester::measureSort(int listSize) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < listSize; i++) {
        list.push_back(rand() % 1000);
    }

    auto start = high_resolution_clock::now();
    list.sort();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "  Sort: " << duration.count() << " μs" << endl;
}