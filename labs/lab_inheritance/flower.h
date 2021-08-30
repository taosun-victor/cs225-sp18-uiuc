/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#ifndef FLOWER_H_
#define FLOWER_H_

#include "drawable.h"
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"


class Flower : public Drawable
{
  private:
    Rectangle * stem;
    Circle * pistil; // center piece of flower
    Triangle * leaf;

    void drawPetals(PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    void draw(PNG* canvas) const;
};

#endif // FLOWER_H_
