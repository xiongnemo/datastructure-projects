#include "sort.h"

void Sortdemo::show_menu()
{
    cout << "**                   Comparison between Eight Sort Algorithms                  **" << endl;
    cout << "**=============================================================================**" << endl;
    cout << "**                  [B]: [B]ubble Sort / Sinking Sort                          **" << endl;
    cout << "**                  [S]: [S]election Sort                                      **" << endl;
    cout << "**                  [I]: [I]nsertion Sort                                      **" << endl;
    cout << "**                  [L]: She[L]l Sort / Shellsort                              **" << endl;
    cout << "**                  [Q]: [Q]uicksort                                           **" << endl;
    cout << "**                  [H]: [H]eapsort                                            **" << endl;
    cout << "**                  [M]: [M]erge Sort                                          **" << endl;
    cout << "**                  [R]: [R]adix Sort / Bucket Sort                            **" << endl;
    //cout << "**                  [U]: (Extra) B[U]cket Sort / Bin Sort                      **" << endl;
    cout << "**                  [E]: Exit!                                                 **" << endl;
    cout << "**=============================================================================**" << endl;
}

void Sortdemo::select()
{
    cout << endl;
    cout << "Input [1] or [B] or [b] for [B]ubble Sort;" << endl;
    cout << "Input [2] or [S] or [s] for [S]election Sort;" << endl;
    cout << "Input [3] or [I] or [i] for [I]nsertion Sort;" << endl;
    cout << "Input [4] or [L] or [l] for She[L]l Sort;" << endl;
    cout << "Input [5] or [Q] or [q] for [Q]uicksort;" << endl;
    cout << "Input [6] or [H] or [h] for [H]eapsort;" << endl;
    cout << "Input [7] or [M] or [m] for [M]erge Sort;" << endl;
    cout << "Input [8] or [R] or [r] for [R]adix Sort;" << endl;
    //cout << "Input [9] or [U] or [u] for B[U]cket Sort;" << endl;
    cout << "Input [0] or [E] or [e] to exit." << endl;
    cout << "Your input: ";
    char option;
    uint64_t count = 0;
    cin >> option;
    if (option != '0' && option != 'E' && option != 'e')
    {
        switch (option)
        {
        case '1':
        case 'B':
        case 'b':
        case '2':
        case 'S':
        case 's':
        case '3':
        case 'I':
        case 'i':
        case '4':
        case 'L':
        case 'l':
        case '5':
        case 'Q':
        case 'q':
        case '6':
        case 'H':
        case 'h':
        case '7':
        case 'M':
        case 'm':
        case '8':
        case 'R':
        case 'r':
            // case '9':
            // case 'U':
            // case 'u':
            temp_random_num_data = (int *)malloc(sizeof(int) * random_num_count);
            for (int i = 0; i < random_num_count; i++)
            {
                temp_random_num_data[i] = random_num_data[i];
            }
            break;
        default:
            cerr << "Invaild option." << endl;
            cout << "Check your input and try again." << endl;
            return;
        }
        auto start = system_clock::now();
        switch (option)
        {
        case '1':
        case 'B':
        case 'b':
            count = bubble_sort(temp_random_num_data, random_num_count);
            break;
        case '2':
        case 'S':
        case 's':
            count = selection_sort(temp_random_num_data, random_num_count);
            break;
        case '3':
        case 'I':
        case 'i':
            count = insertion_sort(temp_random_num_data, random_num_count);
            break;
        case '4':
        case 'L':
        case 'l':
            count = shell_sort(temp_random_num_data, random_num_count);
            break;
        case '5':
        case 'Q':
        case 'q':
            quicksort(temp_random_num_data, 0, random_num_count, &count);
            break;
        case '6':
        case 'H':
        case 'h':
            heapsort(temp_random_num_data, random_num_count, &count);
            break;
        case '7':
        case 'M':
        case 'm':
            merge_sort(temp_random_num_data, random_num_count, &count);
            break;
        case '8':
        case 'R':
        case 'r':
            count = radix_sort(temp_random_num_data, random_num_count, biggest_digit_count_in_random_numbers);
            break;
        // case '9':
        // case 'U':
        // case 'u':
        //     cout << "To be implemented！" << endl;
        //     count = bucket_sort(temp_random_num_data, random_num_count);
        //     break;
        default:
            cerr << "Invaild option." << endl;
            cout << "Check your input and try again." << endl;
            break;
        }
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Spent "
             << double(duration.count()) * microseconds::period::num / microseconds::period::den
             << " seconds" << endl;
        cout << "Swap count: " << count << endl;
        free(temp_random_num_data);
        temp_random_num_data = nullptr;
    }
    else
    {
        quit_flag = true;
    }
}

void Sortdemo::initialize()
{
    srand(time(0));
    cout << "Input the quantity of the random numbers you want to generate: ";
    cin >> random_num_count;
    cout << "Generating pseudo random numbers using rand(), please wait..." << endl;
    random_num_data = (int *)malloc(sizeof(int) * random_num_count);
    for (int i = 0; i < random_num_count; i++)
    {
        int temp = rand();
        random_num_data[i] = temp;
        int temp_digits = log10(temp) + 1;
        if (temp_digits > biggest_digit_count_in_random_numbers)
        {
            biggest_digit_count_in_random_numbers = temp_digits;
        }
    }
}

uint64_t Sortdemo::bubble_sort(int *data, int size)
{
    uint64_t count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (data[j] > data[j + 1])
            {
                swap_in_array(data, j, j + 1);
                count++;
            }
        }
    }
    return count;
}
uint64_t Sortdemo::selection_sort(int *data, int size)
{
    uint64_t count = 0;
    int current_min = INT_MAX;
    int current_minimum_pos = 0;
    for (int i = 0; i < size - 1; i++)
    {
        current_min = data[i];
        current_minimum_pos = i;
        for (int j = i + 1; j < size; j++)
        {
            if (data[j] < current_min)
            {
                current_min = data[j];
                current_minimum_pos = j;
            }
        }
        if (current_minimum_pos != i)
        {
            swap_in_array(data, current_minimum_pos, i);
            count++;
        }
    }
    return count;
}

uint64_t Sortdemo::insertion_sort(int *data, int size)
{
    uint64_t count = 0;
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (data[j] > data[j - 1])
            {
                break;
            }
            else
            {
                swap_in_array(data, j, j - 1);
                count++;
            }
        }
    }
    return count;
}
uint64_t Sortdemo::shell_sort(int *data, int size)
{
    int count = 0;
    int gap = size / 3;
    while (gap > 1)
    {
        for (int i = 0; i < gap; i++)
        {
            for (int j = i; j < size; j += gap)
            {
                for (int k = j; k >= gap; k -= gap)
                {
                    if (data[k] > data[k - gap])
                    {
                        break;
                    }
                    else
                    {
                        swap_in_array(data, k, k - gap);
                        count++;
                    }
                }
            }
        }
        gap = gap / 3 + 1;
    }
    count += insertion_sort(data, size);
    return count;
}

void Sortdemo::quicksort(int *data, int begin_pos, int end_pos, uint64_t *op_count)
{
    if (end_pos > begin_pos)
    {
        int pivot = partition(data, begin_pos, end_pos, op_count);
        quicksort(data, begin_pos, pivot, op_count);
        quicksort(data, pivot + 1, end_pos, op_count);
    }
}

uint64_t Sortdemo::partition(int *data, int begin_pos, int end_pos, uint64_t *op_count)
{
    int first_element_in_partition = data[begin_pos];
    int pivot = begin_pos;
    for (int i = begin_pos + 1; i < end_pos; i++)
    {
        if (data[i] >= first_element_in_partition)
        {
            ;
        }
        else
        {
            pivot++;
            if (pivot != i)
            {
                swap_in_array(data, pivot, i);
                *op_count += 1;
            }
        }
    }
    swap_in_array(data, begin_pos, pivot);
    *op_count += 1;
    return pivot;
}

void Sortdemo::heapsort(int *data, int size, uint64_t *op_count)
{
    for (int i = size / 2; i >= 0; i--)
    {
        sift_down(data, i, size, op_count);
    }
    for (int i = size - 1; i > 0; i--)
    {
        swap_in_array(data, 0, i);
        *op_count += 1;
        sift_down(data, 0, i - 1, op_count);
    }
}

void Sortdemo::sift_down(int *data, int begin_pos, int end_pos, uint64_t *op_count)
{
    while (begin_pos < end_pos)
    {
        int child = begin_pos * 2 + 1;
        if (child > end_pos)
        {
            break;
        }
        if (begin_pos * 2 + 2 < end_pos && data[begin_pos * 2 + 2] > data[child])
        {
            child = begin_pos * 2 + 2;
        }
        if (data[child] > data[begin_pos])
        {
            swap_in_array(data, child, begin_pos);
            *op_count += 1;
        }
        begin_pos = child;
    }
}

void Sortdemo::merge_sort(int *data, int size, uint64_t *op_count)
{
    int *temp_data = (int *)malloc(sizeof(int) * random_num_count);
    for (int i = 0; i < random_num_count; i++)
    {
        temp_data[i] = random_num_data[i];
    }
    split_merge(temp_data, 0, size, data, op_count);
    free(temp_data);
}

void Sortdemo::split_merge(int *array_one, int begin_pos, int end_pos, int *array_two, uint64_t *op_count)
{
    if (end_pos - begin_pos < 2) // if size == 1, sorted!
    {
        return;
    }

    int mid_pos = (end_pos + begin_pos) / 2;

    split_merge(array_two, begin_pos, mid_pos, array_one, op_count);
    split_merge(array_two, mid_pos, end_pos, array_one, op_count);

    merge(array_one, begin_pos, mid_pos, end_pos, array_two, op_count);
}
void Sortdemo::merge(int *array_one, int begin_pos, int mid_pos, int end_pos, int *array_two, uint64_t *op_count)
{
    int i = begin_pos, j = mid_pos;

    for (int k = begin_pos; k < end_pos; k++)
    {
        if (i < mid_pos && (j >= end_pos || array_one[i] <= array_one[j]))
        {
            array_two[k] = array_one[i];
            *op_count += 1;
            i = i + 1;
        }
        else
        {
            array_two[k] = array_one[j];
            *op_count += 1;
            j = j + 1;
        }
    }
}

uint64_t Sortdemo::radix_sort(int *data, int size, int biggest_digit_count)
{
    int *basket[10];
    for (int i = 0; i <= 9; i++)
    {
        basket[i] = (int *)malloc(sizeof(int) * random_num_count);
    }
    for (int pos = 1; pos <= biggest_digit_count; pos++)
    {
        int current_index;
        int basket_element_count[10] = {0};
        for (current_index = 0; current_index < random_num_count; current_index++)
        {
            int current_judging = data[current_index];
            int temp_digit = get_dec_digit_in_num(current_judging, pos);
            // Now, put into basket[0] ~ basket[9]
            basket[temp_digit][basket_element_count[temp_digit]] = current_judging;
            basket_element_count[temp_digit]++;
        }
        // copy data back to original
        current_index = 0;
        for (int i = 0; i <= 9; i++)
        {
            for (int j = 0; j < basket_element_count[i]; j++)
            {
                data[current_index] = basket[i][j];
                current_index++;
            }
        }
    }
    for (int i = 0; i <= 9; i++)
    {
        free(basket[i]);
    }
    return 0;
}

uint8_t Sortdemo::get_dec_digit_in_num(int target, int pos)
{
    int result = 0;
    while (pos--)
    {
        result = target % 10;
        target /= 10;
    }
    return result;
}

// uint64_t Sortdemo::bucket_sort(int *data, int size)
// {
//     return -1;
// }

void Sortdemo::swap_in_array(int *target, int subscript_one, int subscript_two)
{
    int temp = target[subscript_one];
    target[subscript_one] = target[subscript_two];
    target[subscript_two] = temp;
}
