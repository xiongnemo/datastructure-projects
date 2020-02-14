#ifndef PRIM_H
#define PRIM_H

#include <iostream>
#include <cstring>
#include <limits.h>

#define MAX_VERTEX_COUNT 100
#define NAME_BUFFER_SIZE 100
#define MAX_POSSIBLE_COST INT_MAX

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

class Prim
{
public:
    Prim()
    {
        vertex_quantity = 0;
        get_vertices_flag = false;
        add_edges_flag = false;
        construct_mst_flag = false;
        for (int i = 0; i < MAX_VERTEX_COUNT; i++)
        {
            for (int j = 0; j < MAX_VERTEX_COUNT; j++)
            {
                graph[i][j] = MAX_POSSIBLE_COST - 1;
            }
        }
    }
    void exec();

private:
    void print_head_tips();
    void print_tips();
    void get_vertices();
    void add_edges();
    int find_vertex_by_name(char *current_vertex_name);
    bool check_edge_input(char *vertex_1, char *vertex_2, int edge_length);
    void construct_mst();
    int get_starting_vertex();
    void show_mst();
    void quit_system();
    int vertex_quantity;
    bool get_vertices_flag;
    bool add_edges_flag;
    bool construct_mst_flag;
    bool first_run = true;
    bool judged_vertex[MAX_VERTEX_COUNT] = {false};
    char vertex_name[MAX_VERTEX_COUNT][NAME_BUFFER_SIZE];
    int graph[MAX_VERTEX_COUNT][MAX_VERTEX_COUNT];
    int mst_edge_store_data[MAX_VERTEX_COUNT][3];
    int mst_last_vertex[MAX_VERTEX_COUNT] = {-2};// from where to vertex No.(subscript)
    int lowest_weight[MAX_VERTEX_COUNT] = {MAX_POSSIBLE_COST - 1};// min weight from current to the vertex No.(subscript)
};

#endif