#ifndef FAMILY_MANAGEMENT_H
#define FAMILY_MANAGEMENT_H

#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <conio.h>

#define NAME_BUFFER_SIZE 20
#define MOST_DESCEN_QUALITY 10
#define NO_OUTPUT 0
#define FULL_OUTPUT 1

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::setiosflags;
using std::setw;

class Familynode
{
public:
    Familynode *prev;
    char name[NAME_BUFFER_SIZE];
    int descendant_quality;
    Familynode *next[MOST_DESCEN_QUALITY];
};

class Familymanagementsystem
{
public:
    void print_head_tips();
    void print_tips();
    Familynode *initalize_system();
    void create_family(Familynode *head);
    void add_family_member(Familynode *head);
    void dismiss_family(Familynode *head);
    void change_member_name(Familynode *head);
    void quit_system(Familynode *head);
    void show_next_generation(Familynode *head);

private:
    Familynode *create_new_node();
    Familynode *find_person_by_name(Familynode *head);
    Familynode *find_node_by_name(Familynode *current, char *compare);
    bool compare_node_by_name(Familynode *current, char *compare);
    void print_next_generation_member(Familynode *current);
    void dismiss_node(Familynode *current, int mode);
};

#endif