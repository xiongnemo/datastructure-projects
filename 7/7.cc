#include "heap.h"

int main()
{
    Heap heap;
    int quality;
    int sum = 0;
    cin >> quality;
    Heapnode *node = heap.create_heap(quality);
    for (int i = 1; i <= quality; i++)
    {
        int temp_int;
        cin >> temp_int;
        heap.insert(node, temp_int); // Insert all elements into heap
    }
    while (node->size != 1)
    {
        int a = heap.delete_from_heap(node);
        int b = heap.delete_from_heap(node);
        b = a + b;
        sum += b;
        heap.insert(node, b);
    }
    cout << sum << endl;
}
