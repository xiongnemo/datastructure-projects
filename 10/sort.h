#ifndef SORT_VIII_H
#define SORT_VIII_H
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <cmath>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

using namespace std::chrono;

class Sortdemo
{
public:
    Sortdemo()
    {
        random_num_count = 0;
        random_num_data = nullptr;
        temp_random_num_data = nullptr;
        biggest_digit_count_in_random_numbers = 0;
        quit_flag = false;
    }
    ~Sortdemo()
    {
        free(random_num_data);
    }
    void show_menu();
    void select();
    void initialize();
    bool quit_flag;

private:
    uint64_t bubble_sort(int *data, int size);

    uint64_t selection_sort(int *data, int size);

    uint64_t insertion_sort(int *data, int size);

    uint64_t shell_sort(int *data, int size);

    /*
    Pick an element, called a pivot, from the array.
    Partitioning: see below.
    Recursively apply the above steps to the sub-array of elements with smaller values and separately to the sub-array of elements with greater values.
    */
    void quicksort(int *data, int begin_pos, int end_pos, uint64_t *op_count);
    /*
    Partitioning: 
    reorder the array so that all elements with values less than the pivot come before the pivot, 
    while all elements with values greater than the pivot come after it (equal values can go either way). 
    After this partitioning, 
    the pivot is in its final position. 
    This is called the partition operation
    */
    uint64_t partition(int *data, int begin_pos, int end_pos, uint64_t *op_count);

    /*
    Heapsort:
    The steps are:
    1. Call the buildMaxHeap() function on the list. Also referred to as heapify(), this builds a heap from a list in O(n) operations.
    2. Swap the first element of the list with the final element. Decrease the considered range of the list by one.
    3. Call the siftDown() function on the list to sift the new first element to its appropriate index in the heap.
    4. Go to step (2) unless the considered range of the list is one element.
    */
    void heapsort(int *data, int size, uint64_t *op_count);
    //void heapify(int *data, int begin_pos, int end_pos, uint64_t*op_count);
    /*
    sift_down is a common subroutine for implementing heapify
    */
    void sift_down(int *data, int begin_pos, int end_pos, uint64_t *op_count);

    /*
    Recursively splits the list (called runs in this example) into sublists until sublist size is 1, 
    then merges those sublists to produce a sorted list. 
    */
    void merge_sort(int *data, int size, uint64_t *op_count);
    void split_merge(int *array_one, int begin_pos, int end_pos, int *array_two, uint64_t *op_count);
    void merge(int *array_one, int begin_pos, int mid_pos, int end_pos, int *array_two, uint64_t *op_count);

    
    
    uint64_t radix_sort(int *data, int size, int biggest_digit_count);
    /*
    Get digit pos n (from right to left) in target N
    Example: target = 20, pos = 2
    return 2
    */
    uint8_t get_dec_digit_in_num(int target, int pos);

    //uint64_t bucket_sort(int *data, int size);
    

    void swap_in_array(int *target, int subscript_one, int subscript_two);

    int random_num_count;
    int *random_num_data;
    int *temp_random_num_data;
    int biggest_digit_count_in_random_numbers;
};

#endif
