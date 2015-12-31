#include <iostream>
#include <cmath>
#include "Circle.h"
using namespace std;

Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
         float _radius) : Shape (_name, _colour, _xcen, _ycen) {
   radius = _radius;
}

Circle::~Circle() {
   // nothing to delete
}

void Circle::print () const {
   Shape::print();
   cout << "circle radius: " << radius << endl;
}

void Circle::scale (float scaleFac) {
   radius *= scaleFac;
}

float Circle::computeArea () const {
   return PI * radius * radius;
}

float Circle::computePerimeter () const {
   return 2 * PI * radius;
}

void Circle::draw (easygl* window) const {
   // set colour
   window->gl_setcolor(getColour());
   // draw
   window->gl_fillarc(getXcen(), getYcen(), radius, 0, 360);
}

bool Circle::pointInside (float x, float y) const {
   // true if (x-Xcen)^2 + (y-Ycen)^2 < r^2
   return ( pow(x - getXcen(),2) + pow(y - getYcen(),2) < pow(radius,2) );
}