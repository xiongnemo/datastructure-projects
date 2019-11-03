#include "family_tree_management_system.h"

int main()
{
    Familymanagementsystem family_tree_system;
    family_tree_system.print_head_tips();
    Familynode *head = family_tree_system.initalize_system();
    char option = 0;
    while (option != 'e' && option != 'E')
    {
        while ((getchar()) != '\n')
            ;
        cout << endl;
        family_tree_system.print_tips();
        option = getchar();
        switch (option)
        {
        case 'A':
        case 'a':
            family_tree_system.create_family(head);
            continue;
        case 'B':
        case 'b':
            family_tree_system.add_family_member(head);
            continue;
        case 'C':
        case 'c':
            family_tree_system.dismiss_family(head);
            continue;
        case 'D':
        case 'd':
            family_tree_system.change_member_name(head);
            continue;
        case 'E':
        case 'e':
            family_tree_system.quit_system(head);
            break;
        case 'P':
        case 'p':
            family_tree_system.show_next_generation(head);
            break;
        default:
            cerr << "Unrecognized option." << endl;
            continue;
        }
    }
    return 0;
}