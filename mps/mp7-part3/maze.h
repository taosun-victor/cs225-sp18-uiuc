/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <utility>
#include "dsets.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();

        PNG * drawCreativeMaze() const;
        PNG * drawCreativeMazeWithSolution();

    private:
        int width_;
        int height_;
        int size_;
        DisjointSets dsets_;
        vector<bool> rightWall_;
        vector<bool> downWall_;
        
        //pair<int, int> source_;
        //pair<int, int> dest_;

        
};

#endif
