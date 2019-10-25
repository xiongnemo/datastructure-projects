#include "management_system.h"

Node *Managementsystem::initalize_system()
{
    int examinee_quantity;
    cout << "Please set up the system first." << endl;
    cout << "Please input the No. of the examinees: ";
    cin >> examinee_quantity;
    cout << "Please enter the id, name, gender, age and test type of each examinee, one by one." << endl;
    Node *head = list.create_linked_list();
    Node *current = head;
    for (int i = 0; i < examinee_quantity; i++)
    {
        current = list.add_member(current);
    }
    return head;
}

void Managementsystem::show_current_table(Node *head)
{
    cout
        << "Examinee ID "
        << "  "
        << "Name"
        << "      "
        << "Gender"
        << "    "
        << "Age"
        << "    "
        << "Test type"
        << endl;
    list.show_list(head->next);
}
void Managementsystem::find_examinee(Node *head)
{
    int index;
    Node *current = head;
    cout << "\nPlease enter the Examinee ID you want to find." << endl;
    cin >> index;
    while (current)
    {
        if (current->id == index)
        {
            cout << endl;
            show_current_item(current);
            cout << endl;
            return;
        }
        current = current->next;
    }
    cout << "Not found!" << endl;
    cout << endl;
}

void Managementsystem::show_current_item(Node *current)
{
    cout
        << "Examinee ID "
        << "  "
        << "Name"
        << "      "
        << "Gender"
        << "    "
        << "Age"
        << "    "
        << "Test type"
        << endl;
    list.show_item(current);
}

Node *Managementsystem::insert_examinee(Node *head)
{
    return head;
}

void Managementsystem::edit_examinee(Node *head)
{
    int id_target = 0;
    Node *current = head;
    cout << "Input the Examinee ID of the student you want to edit." << endl;
    cin >> id_target;
    while (current)
    {
        if (current->id == id_target)
        {
            edit_current_item(current);
            return;
        }
        current = current->next;
    }
    cout << "Not found!" << endl;
}

void Managementsystem::edit_current_item(Node *current)
{
    char option = 0;
    bool vaild_flag = true;
    string temp_gender;
    show_current_item(current);
    cout << "Press 1 or N to edit [N]ame, 2 or G to edit [G]ender, 3 or A to edit [A]ge, 4 or T to edit [T]ype." << endl;
    option = getch();
    switch (option)
    {
    case '1':
    case 'n':
        cout << "Editing name. Please enter new name for the entry." << endl;
        cout << "Your input: ";
        cin >> current->name;
        break;
    case '2':
    case 'g':
        cout << "Editing gender. Please enter new gender for the entry." << endl;
        cout << "Your input: ";
        cin >> temp_gender;
        if (temp_gender == "male")
        {
            current->gender = 1;
        }
        else if (temp_gender == "female")
        {
            current->gender = 2;
        }
        else
        {
            cerr << "Unsupported gender!" << endl;
        }
        break;
    case '3':
    case 'a':
        cout << "Editing age. Please input new age for the entry." << endl;
        cout << "Your input: ";
        cin >> current->age;
        break;
    case '4':
    case 't':
        cout << "Editing testing type. Please provide new type for the entry." << endl;
        cout << "Your input: ";
        cin >> current->test_type;
        break;
    default:
        cerr << "Unrecognized option. Nothing done." << endl;
        vaild_flag = false;
        break;
    }
    if (vaild_flag)
    {
        cout << "\n\nAfter editing: " << endl;
        show_current_item(current);
        cout << endl;
        cout << endl;
    }
}

Node *Managementsystem::delete_examinee(Node *head)
{
    int index;
    
    return head;
}

void Managementsystem::quit(Node *head)
{
    cout << "Quitting system..." << endl;
    list.free_list(head);
}