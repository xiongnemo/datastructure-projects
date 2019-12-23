#include "management_system.h"

Node *Managementsystem::initalize_system()
{
    int examinee_quantity;
    cout << "Please set up the system first." << endl;
    cout << "Please input the No. of the examinees: ";
    cin >> examinee_quantity;
    while (examinee_quantity <= 0)
    {
        cerr << "The input for examinee_quantity is equal or small than 0." << endl;
        cout << "Invaild input. Check your input and try again." << endl;
        cout << "Please input the No. of the examinees: ";
        cin >> examinee_quantity;
    }
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
    print_table_head();
    list.show_list(head->next);
}

void Managementsystem::find_examinee(Node *head)
{
    Node *current = find_examinee_by_id(head);
    if (current)
    {
        cout << endl;
        show_current_item(current);
        cout << endl;
    }
    return;
}

void Managementsystem::show_current_item(Node *current)
{
    print_table_head();
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
        cout << endl;
        cerr << "Invaild pos to insert!" << endl;
        cout << endl;
        return head;
    }
    else if (pos_target == 1)
    {
        Node *fake_head = (Node *)malloc(sizeof(Node));
        cout << "\nPlease enter the id, name, gender, age and test type of the examinee, one by one." << endl;
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
        cout << "\nPlease enter the id, name, gender, age and test type of the examinee, one by one." << endl;
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
    cout << "\nPlease enter the id, name, gender, age and test type of the examinee, one by one." << endl;
    Node *fake_current = list.add_member(fake_head);
    last->next = fake_current;
    fake_current->next = current;
    free(fake_head);
    total_num++;
    return head;
}

void Managementsystem::edit_examinee(Node *head)
{
    Node *current = find_examinee_by_id(head);
    if (current)
    {
        edit_current_item(current);
        return;
    }
}

void Managementsystem::edit_current_item(Node *current)
{
    char option = 0;
    bool vaild_flag = true;
    string temp_gender;
    cout << "\nCurrent item: " << endl;
    show_current_item(current);
    cout << "\nPress 1 or N to edit [N]ame, 2 or G to edit [G]ender, 3 or A to edit [A]ge, 4 or T to edit [T]ype." << endl;
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
    Node *current = find_examinee_by_id(head);
    if (current)
    {
        if (current == head)
        {
            Node *new_head = current->next;
            current = head;
            delete_current_item(current, new_head);
            return new_head;
        }
        else if (current->next == NULL)
        {
            current->prev->next = NULL;
            delete_current_item(current, head);
            return head;
        }
        current->prev->next = current->next;
        delete_current_item(current, head);
        return head;
    }
    return head;
}

void Managementsystem::quit(Node *head)
{
    cout << "Quitting system..." << endl;
    list.free_list(head);
}

Node *Managementsystem::find_examinee_by_id(Node *head)
{
    int id_target;
    Node *current = head;
    cout << "\nPlease enter the Examinee ID you want to find." << endl;
    cin >> id_target;
    while (current)
    {
        if (current->id == id_target)
        {
            return current;
        }
        current = current->next;
    }
    cerr << "Examinee ID " << id_target << " not found. Nothing done." << endl;
    cout << endl;
    return NULL;
}

void Managementsystem::delete_current_item(Node *current, Node *head)
{
    cout << "You will delete: " << endl;
    show_current_item(current);
    free(current);
    total_num--;
    cout << "\nCurrent table: " << endl;
    show_current_table(head);
}

void Managementsystem::print_table_head()
{
    cout
        << setiosflags(ios::left)
        << setw(ID_BUFFER_WIDTH) << "Examinee ID"
        << setw(NAME_BUFFER_SIZE) << "Name"
        << setw(GENDER_BUFFER_SIZE) << "Gender"
        << setw(AGE_BUFFER_WIDTH) << "Age"
        << setw(TEST_TYPE_BUFFER_SIZE) << "Test type"
        << endl;
}