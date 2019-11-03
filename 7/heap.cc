#include "heap.h"

Heapnode *Heap::create_heap(int quality) // Create Minimum Heap
{
    Heapnode *new_node = (Heapnode *)malloc(sizeof(Heapnode));
    new_node->data = (int *)malloc((quality + 1) * sizeof(int));
    new_node->size = 0;
    new_node->data[0] = -1; // Impossible value, serves as guard
    return new_node;
}
void Heap::insert(Heapnode *heap_node, int element) // Insert Minimum Heap
{
    int i;
    for (i = ++heap_node->size; heap_node->data[i / 2] > element; i /= 2)
    {
        heap_node->data[i] = heap_node->data[i / 2];
    }
    heap_node->data[i] = element;
}

int Heap::delete_from_heap(Heapnode *heap_node) // Delete Minimum Heap
{
    int parent, child;
    int min, x;
    min = heap_node->data[1];
    x = heap_node->data[heap_node->size--];
    for (parent = 1; parent * 2 <= heap_node->size; parent = child)
    {
        child = parent * 2;
        if ((child != heap_node->size) && (heap_node->data[child] > heap_node->data[child + 1]))
        {
            child++;
        }
        if (heap_node->data[child] >= x)
        {
            break;
        }
        else
        {
            heap_node->data[parent] = heap_node->data[child];
        }
    }
    heap_node->data[parent] = x;
    return min;
}