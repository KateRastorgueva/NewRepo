#pragma once
#include <stdbool.h>
#include "CircularBuffer.h"

CircularBuffer* CreateCircularBuffer(int capacity);
int GetFreeSpaceCircular(CircularBuffer* circularBuffer);
int GetUsedSpace(CircularBuffer* circularBuffer);
bool EnqueueCircularBuffer(CircularBuffer* circularBuffer, int value);
int DequeueCircularBuffer(CircularBuffer* circularBuffer);
void DeleteCircularBuffer(CircularBuffer* circularBuffer);