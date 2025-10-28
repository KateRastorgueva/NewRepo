#pragma once
#include "QueueTwoStacks.h"

QueueTwoStacks* CreateQueueTwoStacks(int capacity);
void EnqueueTwoStacks(QueueTwoStacks* queue, int value);
int DequeueTwoStacks(QueueTwoStacks* queue);
void DeleteQueueTwoStacks(QueueTwoStacks* queue);
bool IsQueueTwoStacksEmpty(QueueTwoStacks* queue);
bool ResizeQueueTwoStacks(QueueTwoStacks* queue, int newCapacity);