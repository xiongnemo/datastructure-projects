#include "sort.h"

int main()
{
    Sortdemo demo;
    demo.show_menu();
    demo.initialize();
    while (!demo.quit_flag)
    {
        demo.select();
    }
    return 0;
}