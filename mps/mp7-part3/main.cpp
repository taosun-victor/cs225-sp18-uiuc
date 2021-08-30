#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze(5, 5);
    PNG *p = maze.drawCreativeMaze();
    p->writeToFile("check_make.png");


    return 0;
}
