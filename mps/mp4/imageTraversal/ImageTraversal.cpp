#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator():traversal(NULL){
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, 
                                   Point & start) 
  : traversal(&traversal), start(start)                           
{
  //traversal = &traversal;
  //start = start;
  current = traversal.peek();
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal->empty()) {
    current = traversal->pop();
    traversal->add(current);
    current = traversal->peek();
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  
  bool this_empty = false; 
  bool other_empty = false;

  if (traversal == NULL) 
    this_empty = true; 
  if (other.traversal == NULL) 
    other_empty = true; 
      		
  if (!this_empty) 
    this_empty = traversal->empty(); 
  if (!other_empty) 
    other_empty = other.traversal->empty();
      	
  if (this_empty && other_empty) 
    return false; 
  else if ((!this_empty)&&(!other_empty)) 
    return (traversal != other.traversal); 
  else 
    return true; 
}

