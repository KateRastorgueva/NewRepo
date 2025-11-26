#include "BinarySearchTree.h"
#include "CartesianTree.h"
#include <string>

void GenerateUniqueRandomKeys(int* keys, int count, int minKey, int maxKey);
void GenerateRandomPriorities(int* priorities, int count, int minPriority, int maxPriority);
string GenerateRandomValue(int index);
void GenerateRandomBinarySearchTree(BinarySearchTree* tree, int elementCount);
void GenerateRandomCartesianTree(CartesianTree* tree, int elementCount);