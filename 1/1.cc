#include "management_system.h"

int main(void)
{
    Managementsystem register_system;
    Node *current = register_system.initalize_system();
    register_system.show_current_table(current);
    char option = 0;
    while (option != '0')
    {
        cout << "Please choose the operation you want to do." << endl;
        cout << "Input: " << endl;
        cout << "1 or I for [I]nsert item, 2 or D for [D]elete item, 3 or F for [F]ind in table, " << endl;
        cout << "4 or E for [E]dit item, 5 or S to [S]how current table, 0 to quit system." << endl;
        cout << endl;
        option = getchar();
        switch (option)
        {
        case '1':
        case 'i':
            current = register_system.insert_examinee(current);
            continue;
        case '2':
        case 'd':
            current = register_system.delete_examinee(current);
            continue;
        case '3':
        case 'f':
            register_system.find_examinee(current);
            continue;
        case '4':
        case 'e':
            register_system.edit_examinee(current);
            continue;
        case '5':
        case 's':
            register_system.show_current_table(current);
            continue;
        case '0':
            register_system.quit(current);
            break;
        default:
            cerr << "Unrecognized option." << endl;
            continue;
        }
    }
    return 0;
}
/*
1 aaa male 20 qqq
2 bbb female 30 www
3 ccc male 40 eee

999 eee male 99 uuu
998 fff female 88 ttt
*/
