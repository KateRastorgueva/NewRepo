#include "TreeGenerator.h"
#include "Validator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool IsGenerationParametersValid(const void* tree, int elementCount)
{
    if (!tree || elementCount <= 0)
    {
        return false;
    }
    return true;
}

void GenerateUniqueRandomKeys(int* keys, int count, int minKey, int maxKey)
{
    if (!keys || count <= 0)
    {
        return;
    }

    srand((int)(time(nullptr)));

    for (int i = 0; i < count; i++)
    {
        bool isUnique;
        int key;

        do
        {
            isUnique = true;
            key = minKey + rand() % (maxKey - minKey + 1);

            for (int j = 0; j < i; j++)
            {
                if (keys[j] == key)
                {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);

        keys[i] = key;
    }
}

void GenerateRandomPriorities(int* priorities, int count, int minPriority, int maxPriority)
{
    if (!priorities || count <= 0)
    {
        return;
    }

    srand((int)(time(nullptr) + 1));

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
    if (!IsGenerationParametersValid(tree, elementCount))
    {
        return;
    }

    if (tree->Size + elementCount > maxBinaryTreeSize)
    {
        return;
    }

    int* keys = new int[elementCount];
    GenerateUniqueRandomKeys(keys, elementCount, minKeyValue, maxKeyValue);

    for (int i = 0; i < elementCount; i++)
    {
        string value = GenerateRandomValue(i + 1);
        BinarySearchTreeAdd(tree, keys[i], value);
    }

    delete[] keys;
}

void GenerateRandomCartesianTree(CartesianTree* tree, int elementCount)
{
    if (!IsGenerationParametersValid(tree, elementCount))
    {
        return;
    }

    if (tree->Size + elementCount > maxCartesianTreeSize)
    {
        return;
    }

    int* keys = new int[elementCount];
    int* priorities = new int[elementCount];

    GenerateUniqueRandomKeys(keys, elementCount, minKeyValue, maxKeyValue);
    GenerateRandomPriorities(priorities, elementCount, 1, maxPriorityValue);

    for (int i = 0; i < elementCount; i++)
    {
        string value = GenerateRandomValue(i + 1);
        CartesianTreeAddOptimized(tree, keys[i], value, priorities[i]);
    }

    delete[] keys;
    delete[] priorities;
}