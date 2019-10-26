#include "management_system.h"

Node *Managementsystem::initalize_system()
{
    int examinee_quantity;
    cout << "Please set up the system first." << endl;
    cout << "Please input the No. of the examinees: ";
    cin >> examinee_quantity;
    total_num += examinee_quantity;
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
        << setiosflags(ios::left)
        << setw(15) << "Examinee ID"
        << setw(20) << "Name"
        << setw(8) << "Gender"
        << setw(6) << "Age"
        << setw(30) << "Test type"
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
        << setiosflags(ios::left)
        << setw(15) << "Examinee ID"
        << setw(20) << "Name"
        << setw(8) << "Gender"
        << setw(6) << "Age"
        << setw(30) << "Test type"
        << endl;
    list.show_item(current);
}

Node *Managementsystem::insert_examinee(Node *head)
{
    int pos_target = 0;
    Node *current = head;
    cout << "\nPlease input the INDEX of the NEW student you want to add to." << endl;
    cin >> pos_target;
    if (pos_target < 1 || pos_target > total_num + 1)
    {
        cerr << "Invaild pos to insert!" << endl;
        return head;
    }
    else if (pos_target == 1)
    {
        Node *fake_head = (Node *)malloc(sizeof(Node));
        cout << "Please enter the id, name, gender, age and test type of each examinee, one by one." << endl;
        Node *fake_current = list.add_member(fake_head);
        fake_current->next = head->next;
        free(head);
        total_num++;
        return fake_head;
    }
    else if (pos_target == total_num + 1)
    {
        Node *current = head;
        Node *last = current;
        while (current)
        {
            last = current;
            current = current->next;
        }
        cout << "Please enter the id, name, gender, age and test type of each examinee, one by one." << endl;
        list.add_member(last);
        total_num++;
        return head;
    }
    Node *last = current;
    int current_index = 0;
    while (current)
    {
        if (current_index == pos_target)
        {
            break;
        }
        current_index++;
        last = current;
        current = current->next;
    }
    Node *fake_head = (Node *)malloc(sizeof(Node));
    cout << "Please enter the id, name, gender, age and test type of each examinee, one by one." << endl;
    Node *fake_current = list.add_member(fake_head);
    last->next = fake_current;
    fake_current->next = current;
    free(fake_head);
    total_num++;
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
    int id_target;
    Node *current = head;
    Node *last = head;
    cout << "Input the Examinee ID of the student you want to delete." << endl;
    cin >> id_target;
    while (current)
    {
        if (current->id == id_target)
        {
            if (current == head)
            {
                current = current->next;
                cout << "You will delete: ";
                show_current_item(current);
                free(head);
                total_num--;
                show_current_table(current);
                return current;
            }
            else if (current->next == NULL)
            {
                last->next = NULL;
                cout << "You will delete: ";
                show_current_item(current);
                free(current);
                total_num--;
                show_current_table(head);
                return head;
            }
            last->next = current->next;
            cout << "You will delete: ";
            show_current_item(current);
            free(current);
            total_num--;
            show_current_table(head);
            return head;
        }
        last = current;
        current = current->next;
    }
    cout << "Not found!" << endl;
    return head;
}

void Managementsystem::quit(Node *head)
{
    cout << "Quitting system..." << endl;
    list.free_list(head);
}