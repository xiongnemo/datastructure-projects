#ifndef COURSE_ARRANGEMENT_H
#define COURSE_ARRANGEMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "stack.h"

#define COURSE_IDENTIFIER_BUFFER_SIZE 20
#define COURSE_NAME_BUFFER_SIZE 40
#define PER_COURSE_PREREQUISITIES_MAX 5
#define PREREQUISITIY_MAX 10
#define CREDIT_HOUR_WIDTH 15
#define SELECTED_SEMESTER_WIDTH 20
#define COURSE_PREREQUISITIES_WIDTH 30

#define MAX_COURSE_NUMBER 100

#define SEMESTER_MAX_CREDIT_HOURS 50
#define SEMESTER_COUNT 8

#define NO_OUTPUT 0
#define FULL_OUTPUT 1

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::getline;
using std::ifstream;
using std::ios;
using std::noskipws;
using std::ofstream;
using std::setiosflags;
using std::setw;
using std::string;
using std::stringstream;
using std::ws;

class Course
{
public:
    string course_identifier;
    string course_name;
    int course_credit_hours;
    int course_selected_semester;
    string course_prerequisites[PER_COURSE_PREREQUISITIES_MAX];
    int course_prerequisites_subscript[PER_COURSE_PREREQUISITIES_MAX];
    int course_prerequisites_quantity;
};

class Coursearrangementsystem
{
public:
    Coursearrangementsystem()
    {
        course_quantity = 0;
        last_course_id_for_course_has_no_prerequisity = 0;
        for (int current_semester = 0; current_semester < 8; current_semester++)
        {
            required_classes_quantity_for_each_semester[current_semester] = 0;
            actual_classes_quantity_in_each_semester[current_semester] = 0;
            for (int class_index = 0; class_index < 4; class_index++)
            {
                for (int weekday = 0; weekday < 5; weekday++)
                {
                    table[current_semester][weekday][class_index] = -1;
                }
            }
        }
    }
    bool initialize();
    void show_course_list(int output_mode);
    void show_semester_timetable();
    void write_timatable_to_file();
    bool construct_priority();
    bool construct_semester_timetable();
    

private:
    void print_table_head();
    bool open_course_list_input_file();
    bool load_course_info_from_file();
    bool prerequisities_parser();
    void convert_to_output();

    /*
    Insert course course_id
    */
    void insert_course(int course_id, int semester);

    bool check_table(int course_id, int semester);

    Course course_list[MAX_COURSE_NUMBER];

    /* 
    For each course, [0] is Credit Hours and [1] is Selected Semester
    during the process of inserting courses, [0] can be substracted.
    */
    int lite_list[MAX_COURSE_NUMBER][2];
    int table[8][5][4];
    int output_table[8][5][10];
    int course_quantity;
    int last_course_id_for_course_has_no_prerequisity;
    string file_name;
    ifstream course_list_input_file;
    ofstream course_list_out_file;
    StackForInt priority;
    StackForInt to_be_inserted;
    const int template_timetable[5][4] =
        {
            {2, 3, 2, 3},
            {2, 3, 2, 3},
            {2, 3, 2, 3},
            {2, 3, 2, 3},
            {2, 3, 2, 3},
    };

    // 0 1 2 3 4
    const int jump_days[5][5]=
    {
        {2, 3, 4, 1, 0},
        {3, 4, 0, 2, 1},
        {0, 4, 1, 3, 2},
        {1, 0, 2, 4, 3},
        {2, 1, 0, 3, 4}
    };
    int required_classes_quantity_for_each_semester[8];
    int actual_classes_quantity_in_each_semester[8];
};

#endif