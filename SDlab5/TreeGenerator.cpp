#include "TreeGenerator.h"
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

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; i++)
    {
        bool unique;
        int key;

        do
        {
            unique = true;
            key = minKey + rand() % (maxKey - minKey + 1);

            // Проверка на уникальность
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

    srand(static_cast<unsigned int>(time(nullptr) + 1)); // Разное seed для приоритетов

    for (int i = 0; i < count; i++)
    {
        priorities[i] = minPriority + rand() % (maxPriority - minPriority + 1);
    }
}

string GenerateRandomValue(int index)
{
    return "Value_" + to_string(index);
}

void GenerateRandomBinarySearchTree(BinarySearchTree* tree, int elementCount)
{
    if (tree == nullptr || elementCount <= 0)
    {
        return;
    }

    int* keys = new int[elementCount];
    GenerateUniqueRandomKeys(keys, elementCount, 1, elementCount * 10);

    for (int i = 0; i < elementCount; i++)
    {
        BinarySearchTreeAdd(tree, keys[i], GenerateRandomValue(i + 1));
    }

    delete[] keys;
}

void GenerateRandomCartesianTree(CartesianTree* tree, int elementCount)
{
    if (tree == nullptr || elementCount <= 0)
    {
        return;
    }

    int* keys = new int[elementCount];
    int* priorities = new int[elementCount];

    GenerateUniqueRandomKeys(keys, elementCount, 1, elementCount * 10);
    GenerateRandomPriorities(priorities, elementCount, 1, elementCount * 5);

    for (int i = 0; i < elementCount; i++)
    {
        CartesianTreeAddOptimized(tree, keys[i], GenerateRandomValue(i + 1), priorities[i]);
    }

    delete[] keys;
    delete[] priorities;
}