#include "linked_list.h"

bool check_ordering(int *target, int size);

int main(void)
{
    int a[100];
    int b[100];
    int temp;
    int a_size = 0;
    int b_size = 0;
    bool a_finish_flag = false;
    bool empty_flag = false;
    node *list_one = NULL;
    node *list_two = NULL;
    node *list_intersection = NULL;

    // put data into buffer array
    printf("Input two list as required.\nInput -1 when you've finished one list.\n");
    while (1)
    {
        scanf("%d", &temp);
        if (temp != -1 && !a_finish_flag)
        {
            a[a_size] = temp;
            a_size++;
            continue;
        }
        if (temp == -1 && !a_finish_flag)
        {
            a_finish_flag = true;
            continue;
        }
        if (temp != -1 && a_finish_flag)
        {
            b[b_size] = temp;
            b_size++;
            continue;
        }
        if (temp == -1 && a_finish_flag)
        {
            break;
        }
    }

    if ((!check_ordering(a, a_size)) || (!check_ordering(b, b_size)))
    {
        cerr << "Input don't meet requirement: one or two of the list is not non-descending." << endl;
        cout << "The program will now quit.\nCheck your input and try again." << endl;
        return 0;
    }

    list_one = create_linked_list(a, a_size);
    list_two = create_linked_list(b, b_size);

    if (list_one)
    {
        printf("List one is: ");
        show_list(list_one);
    }
    else
    {
        printf("List one is empty or error(s) occured when creating list one.\n");
        empty_flag = true;
    }
    if (list_two)
    {
        printf("List two is: ");
        show_list(list_two);
    }
    else
    {
        printf("List two is empty or error(s) occured when creating list two.\n");
        empty_flag = true;
    }

    if (!empty_flag)
    {
        list_intersection = intersect(list_one, list_two);
    }
    printf("The intersection of the two list is:\n");
    if (!list_intersection)
    {
        printf("NULL\n");
    }
    else
    {
        show_list(list_intersection);
    }

    free_list(list_one);
    free_list(list_two);
    free_list(list_intersection);
}

bool check_ordering(int *target, int size)
{
    for (int i = 1; i < size; i++)
    {
        if (target[i] < target[i - 1])
        {
            return false;
        }
    }
    return true;
}
