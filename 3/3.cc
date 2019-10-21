#include "maze.h"

int main()
{ 
    Maze maze;
    if (!maze.input())
    {
        cout << "Invaild input!" << endl;
        return -1;
    }
    maze.draw_orig_maze();
    if (!maze.solve(1, 1))
    {
        cout << "Cannot solve!" << endl;
        return -2;
    }
    maze.draw_final_maze();
    return 0;
}

/*
#######
#0#000#
#0#0###
#000#0#
#0#000#
#0#0#0#
#######

*/
/*
#######
#0#000#
#000#0#
#000#0#
#0#000#
#0#000#
#######

*/
/*
#######
#0#000#
#0#0###
#000#0#
#0#00##
#0#0#0#
#######

*/