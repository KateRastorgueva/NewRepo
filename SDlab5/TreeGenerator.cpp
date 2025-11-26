#include "TreeGenerator.h"
#include "Validator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void GenerateUniqueRandomKeys(int* keys, int count, int minKey, int maxKey)
{
    if (count <= 0 || keys == nullptr)
    {
        return;
    }
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; i++)
    {
        bool unique;
        int key;

        do
        {
            unique = true;
            key = minKey + rand() % (maxKey - minKey + 1);
            for (int j = 0; j < i; j++)
            {
                if (keys[j] == key)
                {
                    unique = false;
                    break;
                }
            }
        } while (!unique);

        keys[i] = key;
    }
}

void GenerateRandomPriorities(int* priorities, int count, int minPriority, int maxPriority)
{
    if (count <= 0 || priorities == nullptr)
    {
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr) + 1));

    for (int i = 0; i < count; i++)
    {
        priorities[i] = minPriority + rand() % (maxPriority - minPriority + 1);
    }
}

string GenerateRandomValue(int index)
{
    return "V" + to_string(index);
}

void GenerateRandomBinarySearchTree(BinarySearchTree* tree, int elementCount)
{
    if (tree == nullptr || elementCount <= 0)
    {
        return;
    }

    if (tree->Size + elementCount > maxBinaryTreeSize) {
        return;
    }

    int maxKey = maxKeyValue;
    int* keys = new int[elementCount];
    GenerateUniqueRandomKeys(keys, elementCount, minKeyValue, maxKey);

    for (int i = 0; i < elementCount; i++)
    {
        string value = GenerateRandomValue(i + 1);
        BinarySearchTreeAdd(tree, keys[i], value);
    }

    delete[] keys;
}

void GenerateRandomCartesianTree(CartesianTree* tree, int elementCount)
{
    if (tree == nullptr || elementCount <= 0)
    {
        return;
    }

    if (tree->Size + elementCount > maxCartesianTreeSize) {
        return;
    }

    int maxKey = maxKeyValue;
    int maxPriority = maxPriorityValue;

    int* keys = new int[elementCount];
    int* priorities = new int[elementCount];

    GenerateUniqueRandomKeys(keys, elementCount, minKeyValue, maxKey);
    GenerateRandomPriorities(priorities, elementCount, 1, maxPriority);

    for (int i = 0; i < elementCount; i++)
    {
        string value = GenerateRandomValue(i + 1);
        CartesianTreeAddOptimized(tree, keys[i], value, priorities[i]);
    }

    delete[] keys;
    delete[] priorities;
}