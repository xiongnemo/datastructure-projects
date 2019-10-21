#include "linked_list.h"

// create a linked list according to the "array" and the "size" as received in the para
node *create_linked_list(int *array, int size)
{
    if (size == 0)
    {
        return NULL;
    }
    node *head = (node *)malloc(sizeof(node));
    node *current = head;
    node *next_node = NULL;
    for (int i = 0; i < size; i++)
    {
        current->data = array[i];
        if (i == size - 1)
        {
            break;
        }
        next_node = (node *)malloc(sizeof(node));
        current->next = next_node;
        current = next_node;
    }
    current->next = NULL;
    return head;
}

// return the intersection of the two linked list received in the para
node *intersect(node *first_list, node *second_list)
{
    node *fake_head = (node *)malloc(sizeof(node));
    node *result_head = fake_head;
    node *temp_head_one = first_list;
    node *temp_head_two = second_list;
    bool intersect_flag = false;

    // do the routine till both linked list end
    while ((temp_head_one != NULL) && (temp_head_two != NULL))
    {
        // compare
        if ((temp_head_one->data) < (temp_head_two->data))
        {
            temp_head_one = temp_head_one->next;
        }
        else if ((temp_head_one->data) > (temp_head_two->data))
        {
            temp_head_two = temp_head_two->next;
        }
        else if ((temp_head_one->data) == (temp_head_two->data))
        {
            // new node
            node *temp_node = (node *)malloc(sizeof(node));
            temp_node->data = temp_head_one->data;
            temp_node->next = NULL;
            result_head->next = temp_node;
            result_head = result_head->next;
            temp_head_one = temp_head_one->next;
            temp_head_two = temp_head_two->next;
            intersect_flag = true;
        }
    }

    // whether it's a null set
    if (intersect_flag)
    {
        result_head = fake_head->next;
    }
    else
    {
        result_head = NULL;
    }
    
    return result_head;
}

// show the linked list according to the "head" as received in the para
void show_list(node *head)
{
    node *current = head;
    node *next = NULL;
    while (current)
    {
        printf("%d ", current->data);
        next = current->next;
        current = next;
    }
    printf("\n");
}

// free the linked list according to the "head" as received in the para
void free_list(node *head)
{
    node *current = head;
    node *next = NULL;
    
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }

    current = NULL;
    next = NULL;
    head = NULL;
}