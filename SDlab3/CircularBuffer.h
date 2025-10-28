#pragma once

struct CircularBuffer
{
    int* _buffer;
    int _capacity;
    int _head;
    int _tail;
    int _count;
};