#pragma once
#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

class ConsoleService
{
public:
    static void PrintTitle(const string& title);
    static void PrintMessage(const string& prefix, const string& message);
    static void PrintDictionaryState(const Dictionary* dictionary);
    static void PrintHashTableState(const Dictionary* dictionary);
    static void PrintBucketChain(KeyValuePair* current);
};