#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
  : png(png), start(start), tolerance(tolerance)
 {  
  /** @todo [Part 1] */
  myQueue.push(start);
  visited.resize(png.height() * png.width(), false);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS * bfs = new BFS(png, start, tolerance);
  return ImageTraversal::Iterator(*bfs, start);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  HSLAPixel start_pixel = png.getPixel(start.x, start.y);

  //right, x+1
  if ( (point.x+1) < png.width() ){
    HSLAPixel curr_pixel = png.getPixel(point.x + 1, point.y);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if (dist<tolerance && visited[point.y*png.width() + point.x+1]==false){
      myQueue.push(Point(point.x+1, point.y));
      visited[point.y * png.width() + point.x+1] = true; 
    }
  }

  //below, y+1
  if ( (point.y+1) < png.height() ){
    HSLAPixel curr_pixel = png.getPixel(point.x, point.y + 1);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if (dist<tolerance && visited[(point.y+1)*png.width() + point.x]==false){
      myQueue.push(Point(point.x, point.y+1));
      visited[(point.y+1) * png.width() + point.x] = true;
    }
  }

  //left, x-1
  if ( (int(point.x)-1) >= 0 ){
    HSLAPixel curr_pixel = png.getPixel(point.x - 1, point.y);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if (dist<tolerance && visited[point.y*png.width() + point.x-1]==false){
      myQueue.push(Point(point.x-1, point.y));
      visited[point.y * png.width() + point.x-1] = true;   
    }
  }

  //above, y-1
  if ( (int(point.y)-1) >= 0 ){
    HSLAPixel curr_pixel = png.getPixel(point.x, point.y - 1);
    double dist = calculateDelta(curr_pixel, start_pixel);
    if (dist<tolerance && visited[(point.y-1)*png.width() + point.x]==false){
      myQueue.push(Point(point.x, point.y-1));
      visited[(point.y-1) * png.width() + point.x] = true;
    }
  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point p = myQueue.front();
  myQueue.pop();
  visited[p.y * png.width() + p.x] = true;
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek()  {
  /** @todo [Part 1] */
  return empty()? Point(2000, 2000) : myQueue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return myQueue.empty();
}
