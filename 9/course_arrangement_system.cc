#include "course_arrangement_system.h"

bool Coursearrangementsystem::initialize()
{
    if (!open_course_list_input_file())
    {
        cout << "Can't open given file." << endl;
        return false;
    }
    if (!load_course_info_from_file())
        return false;
    if (!prerequisities_parser())
    {
        cout << "Can't parse prerequisities." << endl;
        cout << "Maybe you should check your input." << endl;
        return false;
    }
    return true;
}
void Coursearrangementsystem::show_course_list(int output_mode)
{
    print_table_head();
    for (int i = 0; i < course_quantity; i++)
    {
        Course *current_course = &course_list[i];
        cout
            << setiosflags(ios::left)
            << setw(COURSE_IDENTIFIER_BUFFER_SIZE) << current_course->course_identifier
            << setw(COURSE_NAME_BUFFER_SIZE) << current_course->course_name
            << setw(CREDIT_HOUR_WIDTH) << current_course->course_credit_hours
            << setw(SELECTED_SEMESTER_WIDTH) << current_course->course_selected_semester;
        if (current_course->course_prerequisites_quantity != 0)
        {
            for (int j = 0; j < current_course->course_prerequisites_quantity; j++)
            {
                cout << current_course->course_prerequisites[j] << ' ';
            }
        }
        if (output_mode)
        {
            if (current_course->course_prerequisites_quantity != 0)
            {
                for (int j = 0; j < current_course->course_prerequisites_quantity; j++)
                {
                    cout << current_course->course_prerequisites_subscript[j] << ' ';
                }
            }
        }
        cout << endl;
    }
}

void Coursearrangementsystem::print_table_head()
{
    cout
        << setiosflags(ios::left)
        << setw(COURSE_IDENTIFIER_BUFFER_SIZE) << "Course Identifier"
        << setw(COURSE_NAME_BUFFER_SIZE) << "Course Name"
        << setw(CREDIT_HOUR_WIDTH) << "Credit Hours"
        << setw(SELECTED_SEMESTER_WIDTH) << "Selected Semester"
        << setw(COURSE_PREREQUISITIES_WIDTH) << "Course Prerequisites"
        << endl;
}
bool Coursearrangementsystem::open_course_list_input_file()
{

    cout << "Input the relative path of the course_list file: ";
    cin >> file_name;
    course_list_input_file.open(file_name, ios::in);
    while (!course_list_input_file)
    {
        cerr << "Error in opening file " << file_name << "." << endl;
        cout << "Error(s) ocurred in opening file. You may try again or exit. (y/n)" << endl;
        char option;
        cin >> option;
        switch (option)
        {
        case 'y':
        case 'Y':
            cout << "Input the relative path of the course_list file: ";
            cin >> file_name;
            course_list_input_file.open(file_name, ios::in);
            continue;
        case 'n':
        case 'N':
            return false;
        default:
            cout << "Vague answers will be treated as 'n'." << endl;
            return false;
        }
    }
    return true;
}
bool Coursearrangementsystem::load_course_info_from_file()
{
    string line_buffer;
    bool first_line_flag = true;
    while (getline(course_list_input_file, line_buffer))
    {
        if (first_line_flag)
        {
            first_line_flag = false;
            continue;
        }
        stringstream current_line(line_buffer);
        Course *current_course = &course_list[course_quantity];
        current_line >> current_course->course_identifier >> current_course->course_name >> current_course->course_credit_hours >> current_course->course_selected_semester;
        current_course->course_prerequisites_quantity = 0;
        current_line >> ws;
        while (current_line.peek() != EOF)
        {
            current_line >> current_course->course_prerequisites[current_course->course_prerequisites_quantity];
            current_course->course_prerequisites_quantity++;
            current_line >> ws;
        }
        if (current_course->course_selected_semester != 0 && current_course->course_prerequisites_quantity != 0)
        {
            cerr << "Unsupported: input don't meet requirement of selected semester and course prerequisities." << endl;
            return false;
        }
        /*
        if (current_course->course_credit_hours != 2 || current_course->course_credit_hours != 3 || current_course->course_credit_hours != 4 || current_course->course_credit_hours != 5 || current_course->course_credit_hours != 6)
        {
            cerr << "Unsupported: input don't meet requirement of supported credit hours: 2, 3, 4, 5, 6." << endl;
            cerr << line_buffer << endl;
            return false;
        }
        */
        course_quantity++;
    }
    course_list_input_file.close();
    for (int i = 0; i < course_quantity; i++)
    {
        lite_list[i][0] = course_list[i].course_credit_hours;
        lite_list[i][1] = course_list[i].course_selected_semester;
    }
    return true;
}
bool Coursearrangementsystem::prerequisities_parser()
{
    int cache_size = 0;
    string cache_string[PREREQUISITIY_MAX];
    int cache_subscript[PREREQUISITIY_MAX];
    for (int i = 0; i < course_quantity; i++)
    {
        Course *current_course = &course_list[i];
        if (current_course->course_prerequisites_quantity == 0)
            continue;
        for (int j = 0; j < current_course->course_prerequisites_quantity; j++)
        {
            bool cache_hit_flag = false;
            bool found_flag = false;
            for (int k = 0; k < cache_size; k++)
            {
                if (current_course->course_prerequisites[j] == cache_string[k])
                {
                    current_course->course_prerequisites_subscript[j] = cache_subscript[k];
                    cache_hit_flag = true;
                    break;
                }
            }
            if (cache_hit_flag)
            {
                continue;
            }
            for (int k = 0; k < course_quantity; k++)
            {
                if (current_course->course_prerequisites[j] == course_list[k].course_identifier)
                {
                    current_course->course_prerequisites_subscript[j] = k;
                    cache_string[cache_size] = course_list[k].course_identifier;
                    cache_subscript[cache_size] = k;
                    cache_size++;
                    found_flag = true;
                    break;
                }
            }
            if (found_flag)
            {
                continue;
            }
            cerr << "Error in prasing prerequisities: prerequisity " << current_course->course_prerequisites[j] << " in course " << current_course->course_identifier << " can not be found." << endl;
            return false;
        }
    }
    return true;
}

bool Coursearrangementsystem::construct_priority(int output_mode)
{
    int attended_course[MAX_COURSE_NUMBER] = {0};
    int course_quantity_needed_to_be_sort = 0;
    for (int i = 0; i < course_quantity; i++)
    {
        Course *current_course = &course_list[i];
        if (current_course->course_selected_semester == 0)
        {
            course_quantity_needed_to_be_sort++;
            if (current_course->course_prerequisites_quantity == 0)
            {
                course_quantity_needed_to_be_sort--;
                attended_course[i] = 1;
                priority.push(i);
            }
        }
    }
    last_course_id_for_course_has_no_prerequisity = priority.top();
    int remaining_course_quantity = course_quantity_needed_to_be_sort;
    for (int count = 0; count < course_quantity_needed_to_be_sort; count++)
    {
        if (remaining_course_quantity == 0)
        {
            break;
        }
        for (int i = 0; i < course_quantity; i++)
        {
            Course *current_course = &course_list[i];
            if ((current_course->course_selected_semester == 0) && (!attended_course[i]))
            {
                int satisfied = 1;
                for (int j = 0; j < current_course->course_prerequisites_quantity; j++)
                {
                    satisfied *= attended_course[current_course->course_prerequisites_subscript[j]];
                }
                if (satisfied)
                {
                    remaining_course_quantity--;
                    attended_course[i] = 1;
                    priority.push(i);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
    }
    if (remaining_course_quantity)
    {
        cerr << "Not satisfied. remaining_course_quantity: " << remaining_course_quantity << "." << endl;
        cout << "There is probably no solution, maybe your dependencies is circular. Check your input and try again." << endl;
        return false;
    }
    if (output_mode)
    {
        priority.print();
    }
    return true;
}

bool Coursearrangementsystem::construct_semester_timetable()
{
    // from "priority" pop all to another stack
    int temp = priority.size();
    for (int i = 0; i < temp; i++)
    {
        to_be_inserted.push(priority.pop());
    }
    // for each semester
    for (int current_semester = 0; current_semester < 8; current_semester++)
    {
        // Insert courses with selected semester first.
        for (int i = 0; i < course_quantity; i++)
        {
            if (lite_list[i][1] == current_semester + 1)
            {
                insert_course(i, current_semester);

                // as "priority" doesn't contain those classes
                // no need to add
                // current_progress_in_queue++;
            }
        }

        // Insert or continue to insert
        if (to_be_inserted.size() == 0)
        {
            continue;
        }
        while (check_table(to_be_inserted.top(), current_semester))
        {
            if (to_be_inserted.top() == last_course_id_for_course_has_no_prerequisity)
            {
                // insert this
                // and go on to next semester
                insert_course(to_be_inserted.pop(), current_semester);
                break;
            }
            insert_course(to_be_inserted.pop(), current_semester);
            if (to_be_inserted.size() == 0)
            {
                break;
            }
        }
    }
    convert_to_output();
    return true;
}

bool Coursearrangementsystem::check_table(int course_id, int semester)
{
    // [2], [3] is for empty count of two or three sequent classes
    int counts[4] = {0};
    for (int weekday = 0; weekday < 5; weekday++)
    {
        for (int class_index = 0; class_index < 4; class_index++)
        {
            if (table[semester][weekday][class_index] == -1)
            {
                counts[template_timetable[weekday][class_index]]++;
            }
        }
    }
    switch (lite_list[course_id][0])
    {
    case 6:
        if (counts[3] >= 2)
            return true;
        break;
    case 5:
        if (counts[2] >= 1 && counts[3] >= 1)
            return true;
        break;
    case 4:
        if (counts[2] >= 2)
            return true;
        break;
    case 3:
        if (counts[3] >= 1)
            return true;
        break;
    case 2:
        if (counts[2] >= 1)
            return true;
        break;
    }
    return false;
}

void Coursearrangementsystem::insert_course(int course_id, int semester)
{
    bool found_flag = false;
    int class_count = 0;
    int last_arranged = 0;
    switch (lite_list[course_id][0])
    {
    //find time for 3 hours
    case 6:
    case 5:
    case 4:
        class_count = 2;
        break;
    // find place for 2 hours
    case 3:
    case 2:
        class_count = 1;
        break;
    default:
        cerr << "This should not happen." << endl;
        return;
    }
    // try to find place
    while (lite_list[course_id][0] != 0)
    {
        switch (lite_list[course_id][0])
        {
        //find time for 3 hours
        case 6:
        case 5:
        case 3:
            found_flag = false;
            for (int weekday = 0; weekday < 5; weekday++)
            {
                int temp_day = 0;
                if (class_count)
                {
                    temp_day = jump_days[last_arranged][weekday];
                }
                for (int class_index = 0; class_index < 4; class_index++)
                {
                    if (class_count)
                    {
                        if (template_timetable[temp_day][class_index] == 3 && table[semester][temp_day][class_index] == -1)
                        {
                            found_flag = true;
                            last_arranged = temp_day;
                            table[semester][temp_day][class_index] = course_id;
                            class_count--;
                            break;
                        }
                    }
                    else
                    {
                        if (template_timetable[weekday][class_index] == 3 && table[semester][weekday][class_index] == -1)
                        {
                            found_flag = true;
                            last_arranged = weekday;
                            table[semester][weekday][class_index] = course_id;
                            class_count--;
                            break;
                        }
                    }
                }
                if (found_flag)
                {
                    break;
                }
            }
            lite_list[course_id][0] -= 3;
            break;
        // find place for 2 hours
        case 4:
        case 2:
            found_flag = false;
            for (int weekday = 0; weekday < 5; weekday++)
            {
                int temp_day = 0;
                if (class_count)
                {
                    temp_day = jump_days[last_arranged][weekday];
                }
                for (int class_index = 0; class_index < 4; class_index++)
                {
                    if (class_count)
                    {
                        if (template_timetable[temp_day][class_index] == 2 && table[semester][temp_day][class_index] == -1)
                        {
                            found_flag = true;
                            last_arranged = temp_day;
                            table[semester][temp_day][class_index] = course_id;
                            class_count--;
                            break;
                        }
                    }
                    else
                    {
                        if (template_timetable[weekday][class_index] == 2 && table[semester][weekday][class_index] == -1)
                        {
                            found_flag = true;
                            last_arranged = weekday;
                            table[semester][weekday][class_index] = course_id;
                            class_count--;
                            break;
                        }
                    }
                }
                if (found_flag)
                {
                    break;
                }
            }
            lite_list[course_id][0] -= 2;
            break;
        default:
            cerr << "This should not happen." << endl;
            return;
        }
    }
}

void Coursearrangementsystem::convert_to_output()
{
    for (int current_semester = 0; current_semester < 8; current_semester++)
    {
        for (int weekday = 0; weekday < 5; weekday++)
        {
            for (int class_index = 0; class_index < 4; class_index++)
            {
                int temp_id = table[current_semester][weekday][class_index];
                switch (class_index)
                {
                case 0:
                    output_table[current_semester][weekday][0] = temp_id;
                    output_table[current_semester][weekday][1] = temp_id;
                    break;
                case 1:
                    output_table[current_semester][weekday][2] = temp_id;
                    output_table[current_semester][weekday][3] = temp_id;
                    output_table[current_semester][weekday][4] = temp_id;
                    break;
                case 2:
                    output_table[current_semester][weekday][5] = temp_id;
                    output_table[current_semester][weekday][6] = temp_id;
                    break;
                case 3:
                    output_table[current_semester][weekday][7] = temp_id;
                    output_table[current_semester][weekday][8] = temp_id;
                    output_table[current_semester][weekday][9] = temp_id;
                    break;
                }
            }
        }
    }
}

void Coursearrangementsystem::show_semester_timetable()
{
    for (int current_semester = 0; current_semester < 8; current_semester++)
    {
        // head of each semester
        cout << endl;
        cout << "Semester " << current_semester + 1 << ":" << endl;
        cout << "*";
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < COURSE_NAME_BUFFER_SIZE; j++)
            {
                cout << "=";
            }
            cout << "*";
        }
        cout << endl;
        for (int class_index = 0; class_index < 10; class_index++)
        {
            char temp[12] = {"| Class"};
            temp[7] = ' ';
            if (class_index < 9)
            {
                temp[8] = class_index + 1 + 48;
                temp[9] = ':';
                temp[10] = '\0';
            }
            else
            {
                temp[8] = '1';
                temp[9] = '0';
                temp[10] = ':';
                temp[11] = '\0';
            }

            cout
                << setiosflags(ios::left)
                << setw(COURSE_NAME_BUFFER_SIZE + 1)
                << temp;
            for (int weekday = 0; weekday < 5; weekday++)
            {
                int temp_course_id = output_table[current_semester][weekday][class_index];
                if (temp_course_id != -1)
                {
                    cout << "|";
                    int course_name_length = course_list[temp_course_id].course_name.length();
                    int space_count = (COURSE_NAME_BUFFER_SIZE - course_name_length) / 2;
                    int remaining_space_count = COURSE_NAME_BUFFER_SIZE - course_name_length - space_count;
                    for (int i = 0; i < space_count; i++)
                    {
                        cout << " ";
                    }
                    //<< setw(COURSE_NAME_BUFFER_SIZE)
                    cout
                        << course_list[temp_course_id].course_name;
                    for (int i = 0; i < remaining_space_count; i++)
                    {
                        cout << " ";
                    }
                }
                else
                {
                    cout << "|";
                    for (int i = 0; i < COURSE_NAME_BUFFER_SIZE; i++)
                    {
                        cout << " ";
                    }
                }
            }
            cout << "|" << endl;
            // end of each
            if (class_index < 9)
            {
                cout << "*";
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < COURSE_NAME_BUFFER_SIZE; j++)
                    {
                        cout << "-";
                    }
                    if (i < 5)
                    {
                        cout << "+";
                    }
                    else
                    {
                        cout << "*";
                    }
                }
                cout << endl;
            }
        }
        // end of each semester
        cout << "*";
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < COURSE_NAME_BUFFER_SIZE; j++)
            {
                cout << "=";
            }
            cout << "*";
        }
        cout << endl;
    }
}

void Coursearrangementsystem::write_timatable_to_file()
{
    cout << "Input the relative path of your result course_list file: ";
    cin >> file_name;
    course_list_out_file.open(file_name, ios::out);
    for (int current_semester = 0; current_semester < 8; current_semester++)
    {
        // head of each semester
        course_list_out_file << endl;
        course_list_out_file << "Semester " << current_semester + 1 << ":" << endl;
        course_list_out_file << "*";
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < COURSE_NAME_BUFFER_SIZE; j++)
            {
                course_list_out_file << "=";
            }
            course_list_out_file << "*";
        }
        course_list_out_file << endl;
        for (int class_index = 0; class_index < 10; class_index++)
        {
            char temp[12] = {"| Class"};
            temp[7] = ' ';
            if (class_index < 9)
            {
                temp[8] = class_index + 1 + 48;
                temp[9] = ':';
                temp[10] = '\0';
            }
            else
            {
                temp[8] = '1';
                temp[9] = '0';
                temp[10] = ':';
                temp[11] = '\0';
            }

            course_list_out_file
                << setiosflags(ios::left)
                << setw(COURSE_NAME_BUFFER_SIZE + 1)
                << temp;
            for (int weekday = 0; weekday < 5; weekday++)
            {
                int temp_course_id = output_table[current_semester][weekday][class_index];
                if (temp_course_id != -1)
                {
                    course_list_out_file << "|";
                    int course_name_length = course_list[temp_course_id].course_name.length();
                    int space_count = (COURSE_NAME_BUFFER_SIZE - course_name_length) / 2;
                    int remaining_space_count = COURSE_NAME_BUFFER_SIZE - course_name_length - space_count;
                    for (int i = 0; i < space_count; i++)
                    {
                        course_list_out_file << " ";
                    }
                    course_list_out_file
                        << course_list[temp_course_id].course_name;
                    for (int i = 0; i < remaining_space_count; i++)
                    {
                        course_list_out_file << " ";
                    }
                }
                else
                {
                    course_list_out_file << "|";
                    for (int i = 0; i < COURSE_NAME_BUFFER_SIZE; i++)
                    {
                        course_list_out_file << " ";
                    }
                }
            }
            course_list_out_file << "|" << endl;
            // end of each
            if (class_index < 9)
            {
                course_list_out_file << "*";
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < COURSE_NAME_BUFFER_SIZE; j++)
                    {
                        course_list_out_file << "-";
                    }
                    if (i < 5)
                    {
                        course_list_out_file << "+";
                    }
                    else
                    {
                        course_list_out_file << "*";
                    }
                }
                course_list_out_file << endl;
            }
        }
        // end of each semester
        course_list_out_file << "*";
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < COURSE_NAME_BUFFER_SIZE; j++)
            {
                course_list_out_file << "=";
            }
            course_list_out_file << "*";
        }
        course_list_out_file << endl;
    }
    course_list_out_file.close();
}