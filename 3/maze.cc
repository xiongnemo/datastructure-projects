#include "maze.h"

bool Maze::input()
{
    cout << "Do you want to use an example? (Y/N)" << endl;
    char option;
    cin >> option;
    if (option == 'n' || option == 'N')
    {
        cout << "Maze size: " << MAZE_HEIGHT << "x" << MAZE_WIDTH << endl;
        cout << "# stands for wall, 0 stands for space" << endl;
        cout << "Entrance is (1, 1), exit is (5, 5)" << endl;
        // cout << "The input should ensure that there's a solution" << endl;
        cout << "Now please input maze:" << endl;
        for (int i = 0; i < MAZE_HEIGHT; i++)
        {
            cin >> maze[i];
            maze[i][MAZE_WIDTH] = '\0';
        }

        if (maze[1][1] != '0' || maze[5][5] != '0')
        {
            return false;
        }

        return true;
    }
    else if (option == 'y' || option == 'Y')
    {
        use_examples();
        return true;
    }
    else
    {
        cerr << "Invalid option received." << endl;
        return false;
    }
    return true;
}

void Maze::use_examples()
{
    cout << "Select from 1, 2, 3: ";
    int option;
    cin >> option;
    while (option > 3 || option < 1)
    {
        cerr << "Input not in range [1, 3]." << endl;
        cout << "Try again." << endl;
        cout << "Select from 1, 2, 3: " << endl;
        int option;
        cin >> option;
    }
    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for (int j = 0; j < MAZE_WIDTH; j++)
        {
            maze[i][j] = template_maze[option - 1][i][j];
        }
        maze[i][MAZE_WIDTH] = '\0';
    }
}

void Maze::draw_orig_maze()
{
    cout << "Original maze:" << endl;
    cout << "        ";
    for (int i = 0; i < 7; i++)
    {
        cout << "Column #" << i << "      ";
    }
    cout << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "Line #" << i << "         ";
        for (int j = 0; j < 7; j++)
        {
            cout << maze[i][j] << "              ";
        }
        cout << endl;
    }
}

bool Maze::solve(int x, int y)
{
    // marked current block as walked
    maze[y][x] = walked;
    // found the end
    if (x == ENDPOINT_X && y == ENDPOINT_Y)
    {
        cout << "(end) <- "
             << "(" << x << ", " << y << ")"
             << " <- ";
        return true;
    }
    // whether the block left to it is available
    if (x > 0 && maze[y][x - 1] == space && solve(x - 1, y))
    {
        cout << "(" << x << ", " << y << ")"
             << " <- ";
        return true;
    }
    // whether the block right to it is available
    if (x < MAZE_WIDTH && maze[y][x + 1] == space && solve(x + 1, y))
    {
        cout << "(" << x << ", " << y << ")"
             << " <- ";
        return true;
    }
    // whether the block above it is available
    if (y > 0 && maze[y - 1][x] == space && solve(x, y - 1))
    {
        cout << "(" << x << ", " << y << ")"
             << " <- ";
        return true;
    }
    // whether the block below it is available
    if (y < MAZE_HEIGHT && maze[y + 1][x] == space && solve(x, y + 1))
    {
        cout << "(" << x << ", " << y << ")"
             << " <- ";
        return true;
    }
    // if you got into an dead-end
    // go back and remark current block
    maze[y][x] = space;
    return false;
}

void Maze::draw_final_maze()
{
    cout << "(start)" << endl;
    cout << "Maze after:" << endl;
    cout << "        ";
    for (int i = 0; i < 7; i++)
    {
        cout << "Column #" << i << "      ";
    }
    cout << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "Line #" << i << "         ";
        for (int j = 0; j < 7; j++)
        {
            cout << maze[i][j] << "              ";
        }
        cout << endl;
    }
}