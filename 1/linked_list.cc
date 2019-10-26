#include "linked_list.h"

Node *Linkedlist::create_linked_list()
{
    Node *head = (Node *)malloc(sizeof(Node));
    return head;
}

Node *Linkedlist::add_member(Node *current_list_end)
{
    Node *current = (Node *)malloc(sizeof(Node));
    current_list_end->next = current;
    string temp_gender;
    cin >> (current->id);
    cin >> (current->name);
    cin >> temp_gender;
    if (temp_gender == "male")
    {
        current->gender = 1;
    }
    else if (temp_gender == "female")
    {
        current->gender = 2;
    }
    else
    {
        cerr << "Unsupported gender!" << endl;
    }
    cin >> (current->age);
    cin >> (current->test_type);
    current->next = NULL;
    current->prev = current_list_end;
    return current;
}

// show the linked list according to the "head" as received in the para
void Linkedlist::show_list(Node *head)
{
    Node *current = head;
    Node *next = NULL;
    while (current)
    {
        show_item(current);
        next = current->next;
        current = next;
    }
    printf("\n");
}

void Linkedlist::show_item(Node *current)
{
    string temp_gender;
    switch (current->gender)
    {
    case 1:
        temp_gender = "male  ";
        break;
    case 2:
        temp_gender = "female";
        break;
    default:
        cerr << "Error or unsupported gender in the list!" << endl;
        break;
    }
    cout
        << setiosflags(ios::left)
        << setw(ID_BUFFER_WIDTH) << (current->id)
        << setw(NAME_BUFFER_SIZE) << (current->name)
        << setw(GENDER_BUFFER_SIZE)<< temp_gender
        << setw(AGE_BUFFER_WIDTH) << (current->age)
        << setw(TEST_TYPE_BUFFER_SIZE) << (current->test_type)
        << endl;
}

// free the linked list according to the "head" as received in the para
void Linkedlist::free_list(Node *head)
{
    Node *current = head;
    Node *next = NULL;

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