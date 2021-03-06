#ifndef MANAG_SYS_H
#define MANAG_SYS_H

#include "linked_list.h"

class Managementsystem
{
public:
    Managementsystem()
    {
        total_num = 0;
    }
    Linkedlist list;
    Node *initalize_system();
    void show_current_table(Node *head);
    void find_examinee(Node *head);
    Node *insert_examinee(Node *head);
    void edit_examinee(Node *head);
    Node *delete_examinee(Node *head);
    void quit(Node *head);
private:
    void show_current_item(Node *current);
    void edit_current_item(Node *current);
    void delete_current_item(Node *current, Node *head);
    Node* find_examinee_by_id(Node *head);
    void print_table_head();
    int total_num;
};

#endif