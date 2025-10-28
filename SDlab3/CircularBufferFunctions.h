#pragma once
#include <stdbool.h>

CircularBuffer* CreateCircularBuffer(int capacity);
int GetFreeSpace(CircularBuffer* circularBuffer);
int GetUsedSpace(CircularBuffer* circularBuffer);
bool EnqueueCircularBuffer(CircularBuffer* circularBuffer, int value);
int DequeueCircularBuffer(CircularBuffer* circularBuffer);
void DeleteCircularBuffer(CircularBuffer* circularBuffer);