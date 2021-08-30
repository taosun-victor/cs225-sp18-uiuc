/* Your code here! */
#include "maze.h"
#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <cmath>

#define PI 3.141582653

using namespace std;

SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
    size_ = 0;
}


void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;
    size_ = width_ * height_;

    dsets_.addelements(size_);
    rightWall_.resize(size_, true);
    downWall_.resize(size_, true);

    //srand(time(NULL));
    while(dsets_.getNumSets() > 1){
        // randomly pick up a cell
        int cell_idx = rand() % size_;
        // check this cell, if its right neighbor is out of border
        int cell_right_idx = cell_idx + 1;
        if (cell_right_idx % width_ != 0){
            if (rightWall_[cell_idx] == true  &&  
                dsets_.find(cell_idx) != dsets_.find(cell_right_idx)){
                dsets_.setunion(cell_idx, cell_right_idx);
                rightWall_[cell_idx] = false;
            }
        }
        // check this cell, if its down neighbor is out or border
        int cell_down_idx = cell_idx + width_;
        if (cell_down_idx <= (size_ -1)){
            if (downWall_[cell_idx] == true &&
                dsets_.find(cell_idx) != dsets_.find(cell_down_idx)){
                dsets_.setunion(cell_idx, cell_down_idx);
                downWall_[cell_idx] = false;
            }
        }
    }

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    // Folk Aluru
    //int new_x, new_y;
    if (x<0 || x>= width_ || y<0 || y>= height_ || dir <0 || dir>3){
        cout << "invalide input." << endl;
        return false;
    }

    if (dir == 0){
        return (x+1 <  width_ && rightWall_[y*width_ + x] == false );
    }
    else if (dir == 1){
        return (y+1 < height_ && downWall_[y*width_ + x] == false);
    }
    else if (dir == 2){
        return (x-1 >=0 && rightWall_[y*width_ + x -1] == false);
    }
    else{
        return (y-1 >=0 && downWall_[(y-1)*width_ + x] == false);
    }
}


void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (x<0 || x>= width_ || y<0 || y>= height_ || dir <0 || dir >1)
        cout << "invalid input." << endl;

    if (dir == 0)
        rightWall_[y*width_ + x] = exists;   
    else 
        downWall_[y*width_ + x] = exists;

}

vector<int> SquareMaze::solveMaze(){
    
    vector<int> last_row;

    map<int, int> solution;
    vector<bool> visited(size_ , false);

    queue<int> q;
    q.push(0);
    visited[0] = true;

    // BFS
    while(!q.empty()){
        int cell = q.front();
        q.pop();
        
        int maze_x = cell % width_;
        int maze_y = cell / width_;

        if (maze_y == height_ -1)
            last_row.push_back(cell);

        if (canTravel(maze_x, maze_y, 0) == true && visited[cell+1] == false){
            solution.insert(pair<int, int>(cell+1, cell));
            visited[cell+1] = true;
            q.push(cell+1);
        }
        if (canTravel(maze_x, maze_y, 1) == true && visited[cell+width_] == false){
            solution.insert(pair<int, int>(cell+width_, cell));
            visited[cell+width_] = true;
            q.push(cell+width_);
        }
        if (canTravel(maze_x, maze_y, 2) == true && visited[cell-1] == false){
            solution.insert(pair<int, int>(cell-1, cell));
            visited[cell-1] = true;
            q.push(cell-1);
        }
        if (canTravel(maze_x, maze_y, 3) == true && visited[cell-width_] == false){
            solution.insert(pair<int, int>(cell-width_, cell));
            visited[cell-width_] = true;
            q.push(cell-width_);
        }
    }

    
    vector<vector<int>> back_track;
    for (size_t i=0; i<last_row.size(); i++){
        int start = last_row[i];
        vector<int> ith;
        while(start != 0){
            auto kval = solution.find(start);
            int prev = kval->second;
            if (start == prev + 1)
                ith.push_back(0);
            else if (start == prev + width_)
                ith.push_back(1);
            else if (start == prev -1)
                ith.push_back(2);
            else if (start == prev - width_)
                ith.push_back(3);
            else{ cout << "error!" << endl; break; }

            start = prev;
        }

        reverse(ith.begin(), ith.end());
        back_track.push_back(ith);
    }

    size_t max_length = 0;
    int back_index = -1;
    int last_index = -1;
    for (size_t i=0; i<last_row.size(); i++){
        if (back_track[i].size() > max_length){
            max_length = back_track[i].size();
            back_index = i;
            last_index = last_row[i];
        }
        else if (back_track[i].size() == max_length){
            if (last_row[i] < last_index){
                max_length = back_track[i].size();
                back_index = i;
                last_index = last_row[i];
            }
        }
        else {}
    }

    return back_track[back_index];
    
}




PNG * SquareMaze::drawMaze() const{
    int pixel_block = 10;
    PNG * maze_png = new PNG(width_ * pixel_block + 1, height_ * pixel_block + 1);
    // cap the top line
    for (int i=pixel_block; i<width_*pixel_block+1; i++){
        HSLAPixel & curr_pixel = maze_png->getPixel(i, 0);
        curr_pixel.h = 0;
        curr_pixel.s = 0;
        curr_pixel.l = 0;
        curr_pixel.a = 1;
    }
    // cap the left line
    for (int i=0; i<height_*pixel_block+1; i++){
        HSLAPixel & curr_pixel = maze_png->getPixel(0, i);
        curr_pixel.h = 0;
        curr_pixel.s = 0;
        curr_pixel.l = 0;
        curr_pixel.a = 1;
    }
    // go through each maze
    // draw according to down and right wall
    for (int i=0; i<size_; i++){

        int maze_x = i % width_;
        int maze_y = i / width_;

        if (rightWall_[i] == true){
            for (int j=0; j<=pixel_block; j++){
                int curr_x = (maze_x + 1) * pixel_block;
                int curr_y = maze_y * pixel_block + j;

                HSLAPixel & curr_pixel = maze_png->getPixel(curr_x, curr_y);
                curr_pixel.h = 0;
                curr_pixel.s = 0;
                curr_pixel.l = 0;
                curr_pixel.a = 1;
            }
        }

        if (downWall_[i] == true){
            for (int j=0; j<=pixel_block; j++){
                int curr_x = maze_x * pixel_block + j;
                int curr_y = (maze_y + 1) * pixel_block;

                HSLAPixel & curr_pixel = maze_png->getPixel(curr_x, curr_y);
                curr_pixel.h = 0;
                curr_pixel.s = 0;
                curr_pixel.l = 0;
                curr_pixel.a = 1;
            }
        }

    }

    return maze_png;

}


PNG * SquareMaze::drawMazeWithSolution(){
    int pixel_block = 10;
    PNG * maze_png = drawMaze();
    vector<int> sol = solveMaze();

    int x = pixel_block/2;
    int y = pixel_block/2;

    for (size_t i=0; i<sol.size(); i++){
        if (sol[i] == 0){
            for (int j=0; j<pixel_block; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                x += 1;
            }
        }
        else if (sol[i] == 1){
            for (int j=0; j<pixel_block; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                y += 1;
            }
        }
        else if (sol[i] == 2){
            for (int j=0; j<pixel_block; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                x -= 1;
            }
        }
        else if (sol[i] == 3){
            for (int j=0; j<pixel_block; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                y -= 1;
            }
        }
        else {}
    }

    // the very last pixel on the path
    HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
    curr_pixel.h = 0;
    curr_pixel.s = 1;
    curr_pixel.l = 0.5;
    curr_pixel.a = 1;

    // the exit
    y += 5;
    //x -= 5 + 1;
    x -= 4;
    for (int i=0; i<9; i++){
        HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
        curr_pixel.h = 0;
        curr_pixel.s = 0;
        curr_pixel.l = 1;
        curr_pixel.a = 1;
        x += 1;
    }

    return maze_png;
}

double distance(int i, int j, int cx, int cy){
    return sqrt((i-cx)*(i-cx) + (j-cy)*(j-cy));
}


PNG * SquareMaze::drawCreativeMaze() const {

    int pixel_block1 = 10;
    int pixel_block2 = 20;
    PNG * maze_png = new PNG(width_ * pixel_block2 + 1, height_ * pixel_block1 + 1);
    // cap the top line
    for (int i=pixel_block2; i<width_*pixel_block2+1; i++){
        HSLAPixel & curr_pixel = maze_png->getPixel(i, 0);
        curr_pixel.h = 0;
        curr_pixel.s = 0;
        curr_pixel.l = 0;
        curr_pixel.a = 1;
    }
    // cap the left line
    for (int i=0; i<height_*pixel_block1+1; i++){
        HSLAPixel & curr_pixel = maze_png->getPixel(0, i);
        curr_pixel.h = 0;
        curr_pixel.s = 0;
        curr_pixel.l = 0;
        curr_pixel.a = 1;
    }

    for (int i=0; i<width_*pixel_block2+1; i++){
        for(int j=0; j<height_*pixel_block1+1; j++){
            HSLAPixel & curr_pixel = maze_png->getPixel(i, j);
            curr_pixel.h = 0.5 * (sin(PI*(double)i/(double)width_) + cos(PI*(double)j/(double)height_)) * 360;
            curr_pixel.s = 0;
            curr_pixel.l = (double)j/(double)height_;
            curr_pixel.a = 1;
        }
    }


    // go through each maze
    // draw according to down and right wall
    for (int i=0; i<size_; i++){

        int maze_x = i % width_;
        int maze_y = i / width_;

        if (rightWall_[i] == true){
            for (int j=0; j<=pixel_block1; j++){
                int curr_x = (maze_x + 1) * pixel_block2;
                int curr_y = maze_y * pixel_block1 + j;

                HSLAPixel & curr_pixel = maze_png->getPixel(curr_x, curr_y);
                curr_pixel.h = 0;
                curr_pixel.s = 0;
                curr_pixel.l = 0;
                curr_pixel.a = 1;
            }
        }

        if (downWall_[i] == true){
            for (int j=0; j<=pixel_block2; j++){
                int curr_x = maze_x * pixel_block2 + j;
                int curr_y = (maze_y + 1) * pixel_block1;

                HSLAPixel & curr_pixel = maze_png->getPixel(curr_x, curr_y);
                curr_pixel.h = 0;
                curr_pixel.s = 0;
                curr_pixel.l = 0;
                curr_pixel.a = 1;

            }
        }

    }

    return maze_png;
}

PNG * SquareMaze::drawCreativeMazeWithSolution(){

    int pixel_block1 = 10;
    int pixel_block2 = 20;

    PNG * maze_png = drawCreativeMaze();
    vector<int> sol = solveMaze();

    int x = pixel_block2/2;
    int y = pixel_block1/2;

    for (size_t i=0; i<sol.size(); i++){
        if (sol[i] == 0){
            for (int j=0; j<pixel_block2; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                x += 1;
            }
        }
        else if (sol[i] == 1){
            for (int j=0; j<pixel_block1; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                y += 1;
            }
        }
        else if (sol[i] == 2){
            for (int j=0; j<pixel_block2; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                x -= 1;
            }
        }
        else if (sol[i] == 3){
            for (int j=0; j<pixel_block1; j++){
                HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
                curr_pixel.h = 0;
                curr_pixel.s = 1;
                curr_pixel.l = 0.5;
                curr_pixel.a = 1;
                y -= 1;
            }
        }
        else {}
    }

    // the very last pixel on the path
    HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
    curr_pixel.h = 0;
    curr_pixel.s = 1;
    curr_pixel.l = 0.5;
    curr_pixel.a = 1;

    // the exit
    y += pixel_block1/2;
    //x -= 5 + 1;
    x -= pixel_block2/2-1;
    for (int i=0; i<pixel_block2-1; i++){
        HSLAPixel & curr_pixel = maze_png->getPixel(x, y);
        curr_pixel.h = 0;
        curr_pixel.s = 0;
        curr_pixel.l = 1;
        curr_pixel.a = 1;
        x += 1;
    }

    return maze_png;


}
