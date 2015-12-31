#include <iostream>
#include <cmath>
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
               float _width, float _height) 
                  : Shape (_name, _colour, _xcen, _ycen) {
   width = _width;
   height = _height;
}

Rectangle::~Rectangle () {
   // nothing to delete
}

void Rectangle::print () const {
   Shape::print();
   cout << "rectangle width: " << width << " height: " << height << endl;
}

void Rectangle::scale (float scaleFac) {
   width *= scaleFac;
   height *= scaleFac;
}

float Rectangle::computeArea () const {
   return width * height;
}

float Rectangle::computePerimeter () const {
   return 2 * (width + height);
}

void Rectangle::draw (easygl* window) const {
   // get coordinates for edges of rectangle
   float xleft = getXcen() - width/2, ybottom = getYcen() + height/2, 
        xright = getXcen() + width/2, ytop = getYcen() - height/2;

   // set colour for drawing
   window->gl_setcolor(getColour());
   // draw
   window->gl_fillrect(xleft, ybottom, xright, ytop);
}

bool Rectangle::pointInside (float x, float y) const {
   // get coordinates for edges of rectangle
   float xleft = getXcen() - width/2, ybottom = getYcen() + height/2, 
        xright = getXcen() + width/2, ytop = getYcen() - height/2;

   // x, y must lie between the edges
   return (x > xleft && x < xright) && (y > ytop && y < ybottom);
}