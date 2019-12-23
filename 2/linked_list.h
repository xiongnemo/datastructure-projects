#include <cstdio>
#include <cmath>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

struct node
{
    int data;
    node* next;
};

node* create_linked_list(int* list, int size);
node* intersect(node* first_list, node* second_list);
void show_list(node* head);
void free_list(node* head);
