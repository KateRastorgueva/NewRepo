#pragma once
#include <string>

using namespace std;

struct KeyValuePair
{
    string Key;
    string Value;
    KeyValuePair* Next;
};

struct HashTable
{
    KeyValuePair** Buckets;
    int Capacity;
    int Count;
};

struct Dictionary
{
    HashTable* HashTable;
};

HashTable* CreateHashTable(int capacity);
int PearsonHash(const string& key, int capacity);
bool Add(HashTable* table, const string& key, const string& value);
bool Remove(HashTable* table, const string& key);
string Find(const HashTable* table, const string& key);
void Rehash(HashTable*& table);
void DeleteHashTable(HashTable* table);
bool NeedsRehash(const HashTable* table);

Dictionary* CreateDictionary(int initialCapacity);
bool DictionaryAdd(Dictionary* dictionary, const string& key, const string& value);
bool DictionaryRemove(Dictionary* dictionary, const string& key);
string DictionaryFind(const Dictionary* dictionary, const string& key);
void DeleteDictionary(Dictionary* dictionary);