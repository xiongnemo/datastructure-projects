#include "heap.h"

int main()
{
    Heap heap;
    int quantity;
    int sum = 0;
    cin >> quantity;
    Heapnode *node = heap.create_heap(quantity);
    for (int i = 1; i <= quantity; i++)
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
    free(node->data);
    free(node);
}
