#include <cmath>
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double width, double height){
  width_ = width;
  height_ = height;
}


HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  const double Pi = 3.1415926;
  double h = 0.5 * (sin(Pi*(double)x/width_) + cos(Pi*(double)y/height_)) * 360;
  double s = 1.0;
  double l = double(y)/height_;

  return HSLAPixel(h, s, l);
}
