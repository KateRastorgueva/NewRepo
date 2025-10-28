#pragma once
#include "Queue.h"

Queue* CreateQueue(int capacity);
bool Enqueue(Queue* queue, int value);
int Dequeue(Queue* queue);
void DeleteQueue(Queue* queue);
bool IsQueueEmpty(Queue* queue);
bool IsQueueFull(Queue* queue);
bool ResizeQueue(Queue* queue, int newCapacity);