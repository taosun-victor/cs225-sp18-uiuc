#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
  : png(png), start(start), tolerance(tolerance)
 {  
  /** @todo [Part 1] */
  //png = png;
  //start = start;
  //tolerance = tolerance;
  myStack.push(start);
  visited.resize(png.height() * png.width(), false);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS * dfs = new DFS(png, start, tolerance);
  return ImageTraversal::Iterator(*dfs, start);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  HSLAPixel start_pixel = png.getPixel(start.x, start.y);

  //right, x+1
  if ( (point.x+1) < png.width() ){
    HSLAPixel curr_pixel = png.getPixel(point.x + 1, point.y);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if ( (dist<tolerance) && (visited[point.y*png.width() + point.x+1]==false)){ 
      myStack.push(Point(point.x+1, point.y));
      //visited[point.y * png.width() + point.x+1] = true;
      //cout << "adding right" << " " << empty() << endl;
    }
  }

  //below, y+1
  if ( (point.y+1) < png.height() ){
    HSLAPixel curr_pixel = png.getPixel(point.x, point.y + 1);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if ( (dist<tolerance) && (visited[(point.y+1)*png.width() + point.x]==false) ){ 
      myStack.push(Point(point.x, point.y+1));
      //visited[(point.y+1) * png.width() + point.x] = true;
      //cout << "adding below" << " " << empty() << endl;
    }
  }

  //left, x-1
  if ( (int(point.x)-1) >= 0 ){
    HSLAPixel curr_pixel = png.getPixel(point.x - 1, point.y);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if ( (dist<tolerance) && (visited[point.y*png.width() + point.x-1]==false) ){
      myStack.push(Point(point.x-1, point.y));
      //visited[point.y * png.width() + point.x-1] = true;
      //cout << "adding left" << " " << empty() << endl;
    }
  }

  //above, y-1
  if ( (int(point.y)-1) >= 0 ){
    HSLAPixel curr_pixel = png.getPixel(point.x, point.y - 1);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if ( (dist<tolerance) && (visited[(point.y-1)*png.width() + point.x]==false) ){
      myStack.push(Point(point.x, point.y-1));
      //visited[(point.y-1) * png.width() + point.x] = true;
      //cout << "adding above" << " " << empty() << endl;
    }
  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point p = myStack.top();
  visited[p.y * png.width() + p.x] = true;
  myStack.pop();
  //cout << "popping out" << " " << empty() << endl;

  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() {
  /** @todo [Part 1] */
  /*  
  if (!empty()){
    int x_top = (myStack.top()).x;
    int y_top = (myStack.top()).y;
    check = visited[y_top * png.width() + x_top]
    if (visited[y_top * png.width() + x_top] == true ){
      myStack.pop();
    }
  } */

  while((!empty()) && (visited[(myStack.top()).y * png.width() + (myStack.top()).x] == true))
    myStack.pop();

  return empty()? Point(2000, 2000) : myStack.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return myStack.empty();
}
