#include "family_tree_management_system.h"

void Familymanagementsystem::print_head_tips()
{
    cout << "*===========================================================*" << endl;
    cout << "|               Family Tree Management System               |" << endl;
    cout << "*===========================================================*" << endl;
    cout << "|                    Operation Lists:                       |" << endl;
    cout << "|              A --- add a family to an existing member     |" << endl;
    cout << "|              B --- add a member to an existing member     |" << endl;
    cout << "|              C --- dismiss a family                       |" << endl;
    cout << "|              D --- change a member's name                 |" << endl;
    cout << "|              P --- show a member's next generation        |" << endl;
    cout << "|              E --- quit system                            |" << endl;
    cout << "*===========================================================*" << endl;
}

void Familymanagementsystem::print_tips()
{
    cout << "Please choose the operation you want to do." << endl;
    cout << "Input: " << endl;
    cout << "A or a to add a family to an existing member," << endl;
    cout << "B or b to add a member to an existing member," << endl;
    cout << "C or c to dismiss a family," << endl;
    cout << "D or d to change a member's name," << endl;
    cout << "P or p to show a member's next generation," << endl;
    cout << "E or e to quit." << endl;
    cout << "Your choice: ";
}

Familynode *Familymanagementsystem::initalize_system()
{
    Familynode *current = create_new_node();
    cout << "Set up a family tree first." << endl;
    cout << "Input the name of the ancestor of the family: ";
    cin >> (current->name);
    current->prev = NULL;
    cout << "The ancestor's name is: " << current->name << endl;
    return current;
}

void Familymanagementsystem::create_family(Familynode *head)
{
    int temp_member_quality;
    cout << "Please input the name of the target you want to create his/hers family." << endl;
    Familynode *current = find_person_by_name(head);
    if (current)
    {
        if (current->descendant_quality > 0)
        {
            cerr << "Current target's descendant quality is not zero." << endl;
            return;
        }
        else
        {
            cout << "Please inpt the quality of " << current->name << "'s descendant." << endl;
            cout << "Input number: ";
            cin >> temp_member_quality;
            while (temp_member_quality > MOST_DESCEN_QUALITY)
            {
                cerr << "MOST_DESCEN_QUALITY " << MOST_DESCEN_QUALITY << " reached." << endl;
                cout << "Current target's descendant quality excceeded. Try again." << endl;
                cout << "Please inpt the quality of " << current->name << "'s descendant." << endl;
                cout << "Input number: ";
                cin >> temp_member_quality;
            }
            cout << "Please input each descendant's name, one by one: ";
            for (int i = 0; i < temp_member_quality; i++)
            {
                Familynode *temp = create_new_node();
                temp->prev = current;
                current->next[current->descendant_quality] = temp;
                cin >> temp->name;
                (current->descendant_quality) += 1;
            }
            print_next_generation_member(current);
        }
    }
}

void Familymanagementsystem::add_family_member(Familynode *head)
{
    cout << "Please input the name of the target you want to add his/her family member." << endl;
    Familynode *current = find_person_by_name(head);
    if (current)
    {
        if (current->descendant_quality == MOST_DESCEN_QUALITY)
        {
            cerr << "MOST_DESCEN_QUALITY " << MOST_DESCEN_QUALITY << " reached." << endl;
            cout << "Current target's descendant quality excceeded. Try again." << endl;
            return;
        }
        cout << "Please input his/her new descendant's name: ";
        Familynode *temp = create_new_node();
        temp->prev = current;
        current->next[current->descendant_quality] = temp;
        cin >> temp->name;
        (current->descendant_quality) += 1;
        print_next_generation_member(current);
    }
}

void Familymanagementsystem::dismiss_family(Familynode *head)
{
    cout << "Please input the name of the target you want to dismiss his/her family." << endl;
    Familynode *current = find_person_by_name(head);
    if (current)
    {
        if (current == head)
        {
            cout << "Currently, we don't allow you to dismiss your ancestor's family." << endl;
            cout << endl;
            return;
        }
        Familynode *prev = current->prev;
        cout << "The person, which is or was or will be the head of the family you want to dismiss, is " << current->name << "." << endl;
        dismiss_node(current, FULL_OUTPUT);
        if (prev->descendant_quality == 1)
        {
            prev->descendant_quality = 0;
            prev->next[prev->descendant_quality] = NULL;
            return;
        }
        int temp_index = 0;
        for (temp_index = 0; temp_index < prev->descendant_quality; temp_index++)
        {
            if (prev->next[temp_index] == current)
            {
                break;
            }
        }
        for (int i = temp_index; i < prev->descendant_quality; i++)
        {
            prev->next[i] = prev->next[i + 1];
        }
        prev->descendant_quality -= 1;
    }
}

void Familymanagementsystem::change_member_name(Familynode *head)
{
    cout << "Please input the name of the target you want to change name." << endl;
    Familynode *current = find_person_by_name(head);
    if (current)
    {
        cout << "Input his/her new name." << endl;
        cout << "Your input: ";
        cin >> current->name;
        cout << "Current target's name changed to " << current->name << "." << endl;
    }
}

void Familymanagementsystem::quit_system(Familynode *head)
{
    dismiss_node(head, NO_OUTPUT);
    return;
}

void Familymanagementsystem::show_next_generation(Familynode *head)
{
    cout << "Please input the name of the target you want to show his/her next generation." << endl;
    Familynode *current = find_person_by_name(head);
    if (current)
    {
        print_next_generation_member(current);
    }
}

Familynode *Familymanagementsystem::create_new_node()
{
    Familynode *current = (Familynode *)malloc(sizeof(Familynode));
    current->descendant_quality = 0;
    for (int i = 0; i < MOST_DESCEN_QUALITY; i++)
    {
        current->next[i] = NULL;
    }
    return current;
}

Familynode *Familymanagementsystem::find_person_by_name(Familynode *head)
{
    char temp_name_buffer[NAME_BUFFER_SIZE];
    cout << "Name: ";
    cin >> temp_name_buffer;
    Familynode *target = find_node_by_name(head, temp_name_buffer);
    if (!target)
    {
        cerr << "Name " << temp_name_buffer << " not found." << endl;
        cout << "Given operation failed because of no entry." << endl;
        cout << endl;
        return NULL;
    }
    else
    {
        return target;
    }
    return NULL;
}

Familynode *Familymanagementsystem::find_node_by_name(Familynode *current, char *compare)
{
    if (compare_node_by_name(current, compare))
    {
        return current;
    }
    else if ((current->descendant_quality) > 0)
    {
        for (int i = 0; i < current->descendant_quality;)
        {
            Familynode *temp_result = (find_node_by_name(current->next[i], compare));
            if (temp_result != NULL)
            {
                return temp_result;
            }
            else
            {
                i++;
            }
        }
        return NULL;
    }
    else
    {
        return NULL;
    }
}

bool Familymanagementsystem::compare_node_by_name(Familynode *current, char *compare)
{
    if (strcmp(current->name, compare) == 0)
    {
        return true;
    }
    return false;
}

void Familymanagementsystem::print_next_generation_member(Familynode *current)
{
    if (current->descendant_quality == 0)
    {
        cout << "This member has no descendant(s)." << endl;
        return;
    }
    cout << current->name << "'s next generation is";
    for (int i = 0; i < current->descendant_quality; i++)
    {
        cout << " " << current->next[i]->name;
    }
    cout << "." << endl;
}

void Familymanagementsystem::dismiss_node(Familynode *current, int mode)
{
    if (current->descendant_quality == 0)
    {
        free(current);
        return;
    }
    else
    {
        if (mode == FULL_OUTPUT)
        {
            print_next_generation_member(current);
            cout << "We will dismiss them." << endl;
        }
        for (int i = 0; i < current->descendant_quality; i++)
        {
            dismiss_node(current->next[i], mode);
        }
        free(current);
    }
}