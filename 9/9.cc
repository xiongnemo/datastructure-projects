#include "course_arrangement_system.h"

int main()
{
    Coursearrangementsystem course_arran_system;
    if (course_arran_system.initialize())
        course_arran_system.show_course_list(FULL_OUTPUT);
    else
    {
        cout << "Can't initialize system." << endl;
        return -1;
    }
    if (course_arran_system.construct_priority(FULL_OUTPUT))
    {
        if (course_arran_system.construct_semester_timetable())
        {
            course_arran_system.show_semester_timetable();
            course_arran_system.write_timatable_to_file();
        }
        else
        {
            cout << "Construct semester timetable failed." << endl;
            return -1;
        }
    }
    else
    {
        cout << "Construct priorities failed." << endl;
        return -1;
    }
    return 0;
}