#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <cstdio>
#include <cstring>

#define MAZE_HEIGHT 7
#define MAZE_WIDTH 7
#define ENDPOINT_X 5
#define ENDPOINT_Y 5

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

class Maze
{
public:
    bool input();
    void draw_orig_maze();
    void draw_final_maze();
    void use_examples();
    bool solve(int x, int y);

private:
    char maze[MAZE_HEIGHT + 1][MAZE_WIDTH + 1];
    const char wall = '#';
    const char space = '0';
    const char walked = '*';
    const char template_maze[3][MAZE_HEIGHT + 1][MAZE_WIDTH + 1] =
        {
            {{"#######"},
             {"#0#000#"},
             {"#0#0###"},
             {"#000#0#"},
             {"#0#000#"},
             {"#0#0#0#"},
             {"#######"}},
            {{"#######"},
             {"#0#000#"},
             {"#000#0#"},
             {"#000#0#"},
             {"#0#000#"},
             {"#0#000#"},
             {"#######"}},
            {{"#######"},
             {"#0#000#"},
             {"#0#0###"},
             {"#000#0#"},
             {"#0#00##"},
             {"#0#0#0#"},
             {"#######"}}};
};

#endif