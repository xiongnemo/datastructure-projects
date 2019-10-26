#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>

#define NAME_BUFFER_SIZE 20
#define GENDER_BUFFER_SIZE 10
#define TEST_TYPE_BUFFER_SIZE 30

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::setw;
using std::setiosflags;
using std::ios;

class Node
{
public:
    Node* prev;
    int id = 0;
    char name[NAME_BUFFER_SIZE];
    int gender = 0;
    int age = 0;
    char test_type[TEST_TYPE_BUFFER_SIZE];
    Node *next;
};

class Linkedlist
{
public:
    Node* create_linked_list();
    Node* add_member(Node* current_list_end);
    void insert_member(int index);
    void show_list(Node *head);
    void show_item(Node *current);
    void free_list(Node *head);
};

#endif