/**
 * @file BFS.h
 */

#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek();
  bool empty() const;

private:
  /** @todo [Part 1] */
  /** add private members here*/
  std::queue <Point> myQueue;
  const PNG png;
  Point start;
  double tolerance;
  std::vector <bool> visited;
};

#endif
