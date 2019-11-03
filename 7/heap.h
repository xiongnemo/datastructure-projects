#ifndef HEAP_H
#define HEAP_H

#include <cstdio>
#include <cstdlib>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Heapnode // Heap Structure
{
public:
    int *data; // Data
    int size;  // Data Size
};

class Heap
{
public:
    Heapnode *create_heap(int quality);            // Create Minimum Heap
    void insert(Heapnode *heap_node, int element); // Insert Minimum Heap
    int delete_from_heap(Heapnode *heap_node);     // Delete Minimum Heap
};

#endif