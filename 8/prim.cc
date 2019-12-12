#include "prim.h"

void Prim::exec()
{
    print_head_tips();
    char option = 0;
    while (option != 'e' && option != 'E')
    {
        if (!first_run)
        {
            while ((getchar()) != '\n')
            {
                ;
            }
        }
        first_run = false;
        cout << endl;
        print_tips();
        option = getchar();
        switch (option)
        {
        case 'A':
        case 'a':
            if (!get_vertices_flag)
            {
                get_vertices();
                get_vertices_flag = true;
                continue;
            }
            cout << "You have input the data. Please choose other operations." << endl;
            continue;
        case 'B':
        case 'b':
            if (!get_vertices_flag)
            {
                cout << "Please get input first." << endl;
                continue;
            }
            if (!add_edges_flag)
            {
                add_edges();
                add_edges_flag = true;
                continue;
            }
            cout << "You have constructed the edges. Please choose other operations." << endl;
            continue;
        case 'C':
        case 'c':
            if (!get_vertices_flag)
            {
                cout << "Please get input first." << endl;
                continue;
            }
            if (!add_edges_flag)
            {
                cout << "Please add edges first." << endl;
                continue;
            }
            if (!construct_mst_flag)
            {
                construct_mst();
                construct_mst_flag = true;
                continue;
            }
            cout << "You have constructed the MST. " << endl;
            cout << "Do you want to reconstruct? (y/n)" << endl;
            cout << "Your choice:";
            cin >> option;
            switch (option)
            {
            case 'y':
            case 'Y':
                cout << "Now reconstructing MST..." << endl;
                construct_mst();
                break;
            case 'n':
            case 'N':
                cout << "Gladly you choose no!" << endl;
                break;
            default:
                cout << "Vague answers will be treated as 'n'." << endl;
            }
            continue;
        case 'D':
        case 'd':
            if (!get_vertices_flag)
            {
                cout << "Please get input first." << endl;
                continue;
            }
            if (!add_edges_flag)
            {
                cout << "Please add edges first." << endl;
                continue;
            }
            if (!construct_mst_flag)
            {
                cout << "Please construct MST first." << endl;
                continue;
            }
            show_mst();
            continue;
        case 'E':
        case 'e':
            quit_system();
            break;
        default:
            cerr << "Unrecognized option." << endl;
            continue;
        }
    }
}

void Prim::print_head_tips()
{
    cout << "*===========================================================*" << endl;
    cout << "|      Power Grid Construction Cost Simulation System       |" << endl;
    cout << "*===========================================================*" << endl;
    cout << "|                     Operation Lists:                      |" << endl;
    cout << "|              A --- create the vertices of the grid        |" << endl;
    cout << "|              B --- add edge(s) of the grid                |" << endl;
    cout << "|              C --- construct MST                          |" << endl;
    cout << "|              D --- show MST                               |" << endl;
    cout << "|              E --- quit system                            |" << endl;
    cout << "*===========================================================*" << endl;
}

void Prim::print_tips()
{
    cout << "Please choose the operation you want to do." << endl;
    cout << "Input: " << endl;
    cout << "A or a to create the vertices of the grid," << endl;
    cout << "B or b to add edge(s) of the grid," << endl;
    cout << "C or c to construct MST," << endl;
    cout << "D or d to show MST," << endl;
    cout << "E or e to quit." << endl;
    cout << "Your choice: ";
}

void Prim::get_vertices()
{
    cout << "Please input the number of the vertices." << endl;
    cout << "Your input: ";
    cin >> vertex_quantity;
    cout << "Please input each vertex's name, one by one. (You can seperate by spaces.)" << endl;
    cout << "Your input: ";
    for (int i = 0; i < vertex_quantity; i++)
    {
        cin >> vertex_name[i];
    }
}

void Prim::add_edges()
{
    cout << "Adding the edges. Input \"? ? 0\" to end." << endl;
    while (1)
    {
        cout << "Input the name of the two vertices and the length of the edge: ";
        char temp_vertex_name_1[NAME_BUFFER_SIZE];
        char temp_vertex_name_2[NAME_BUFFER_SIZE];
        int temp_edge_length;
        cin >> temp_vertex_name_1;
        cin >> temp_vertex_name_2;
        cin >> temp_edge_length;
        if (check_edge_input(temp_vertex_name_1, temp_vertex_name_2, temp_edge_length))
        {
            int temp_vertex_index_1 = find_vertex_by_name(temp_vertex_name_1);
            int temp_vertex_index_2 = find_vertex_by_name(temp_vertex_name_2);
            if (temp_vertex_index_1 == -1 || temp_vertex_index_2 == -1)
            {
                cout << "Finding process returned an error. Check your input and try again." << endl;
                continue;
            }
            graph[temp_vertex_index_1][temp_vertex_index_2] = temp_edge_length;
            graph[temp_vertex_index_2][temp_vertex_index_1] = temp_edge_length;
        }
        else
        {
            return;
        }
    }
}

int Prim::find_vertex_by_name(char *current_vertex_name)
{
    for (int i = 0; i < vertex_quantity; i++)
    {
        if (strcmp(vertex_name[i], current_vertex_name) == 0)
        {
            return i;
        }
    }
    cerr << "No match found with name " << current_vertex_name << "." << endl;
    return -1;
}

bool Prim::check_edge_input(char *vertex_1, char *vertex_2, int edge_length)
{
    if (strcmp(vertex_1, "?") == 0 && strcmp(vertex_2, "?") == 0 && edge_length == 0)
    {
        return false;
    }
    return true;
}

void Prim::construct_mst()
{
    int starting_vertex = get_starting_vertex();
    int current_edge_index = 0;
    for (int i = 0; i < vertex_quantity; i++)
    {
        if (i == starting_vertex)
        {
            continue;
        }
        lowest_weight[i] = graph[starting_vertex][i];
        mst_last_vertex[i] = starting_vertex;
    }
    mst_last_vertex[starting_vertex] = 0;
    while (current_edge_index < vertex_quantity - 1)
    {
        int min_weight = MAX_POSSIBLE_COST;
        int min_vertex = 0;
        for (int i = 0; i < vertex_quantity; i++)
        {
            if (i == starting_vertex)
            {
                continue;
            }
            if (lowest_weight[i] < min_weight && lowest_weight[i] != 0)
            {
                min_weight = lowest_weight[i];
                min_vertex = i;
            }
        }
        mst_edge_store_data[current_edge_index][0] = mst_last_vertex[min_vertex];
        mst_edge_store_data[current_edge_index][1] = min_vertex;
        mst_edge_store_data[current_edge_index][2] = min_weight;
        current_edge_index++;
        lowest_weight[min_vertex] = 0;
        for (int i = 0; i < vertex_quantity; i++)
        {
            if (i == starting_vertex)
            {
                continue;
            }
            if (graph[min_vertex][i] < lowest_weight[i])
            {
                lowest_weight[i] = graph[min_vertex][i];
                mst_last_vertex[i] = min_vertex;
            }
        }
    }
    cout << "Constructed Prim MST!" << endl;
}

int Prim::get_starting_vertex()
{
    int temp_starting_vertex;
    char temp_vertex[NAME_BUFFER_SIZE];
    cout << "Input starting vertex." << endl;
    cout << "Your input:";
    cin >> temp_vertex;
    while ((temp_starting_vertex = find_vertex_by_name(temp_vertex)) == -1)
    {
        cout << "Try input again." << endl;
        cout << "Your input:";
        cin >> temp_vertex;
    }
    return temp_starting_vertex;
}

void Prim::show_mst()
{
    int cost_accumulator = 0;
    for (int i = 0; i < vertex_quantity - 1; i++)
    {
        int current_vertex = mst_edge_store_data[i][0];
        int next_vertex = mst_edge_store_data[i][1];
        int current_cost = mst_edge_store_data[i][2];
        cout
            << vertex_name[current_vertex]
            << "-("
            << current_cost
            << ")->"
            << vertex_name[next_vertex]
            << endl;
        cost_accumulator += current_cost;
    }
    cout << "Total cost is: " << cost_accumulator << "." << endl;
}

void Prim::quit_system()
{
}