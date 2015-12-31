#include <iostream>
#include <cmath>
#include "Polygon.h"
using namespace std;

Polygon::Polygon (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[100], float _ycoords[100], int _vertices) : 
              Shape (_name, _colour, _xcen, _ycen) {
   for (int i = 0; i < _vertices; i++) {
      relVertex[i].x = _xcoords[i];
      relVertex[i].y = _ycoords[i];
   }
   vertices = _vertices;
}

Polygon::~Polygon () {
   // nothing to delete
}

void Polygon::print () const {
   Shape::print();
   cout << "polygon";
   for (int i = 0; i < vertices; i++) {
      cout << " (" << getXcen() + relVertex[i].x << "," 
              << getYcen() + relVertex[i].y << ")";
   }
   cout << endl;
}

void Polygon::scale (float scaleFac) {
   for (int i = 0; i < vertices; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}

float Polygon::computeArea () const {
   float area = 0;
   int j = vertices - 1;
   for (int i = 0; i < vertices; i++) {
      area += (relVertex[j].x + relVertex[i].x + 2*getXcen()) \
            * (relVertex[j].y - relVertex[i].y);
      j = i;
   }
   return area/2;
}

float Polygon::computePerimeter () const {
   float perimeter = 0;
   float sideLength;
   int j = vertices - 1;
   t_point dist;
   
   for (int i = 0; i < vertices; i++) {
      dist = getVecBetweenPoints (relVertex[i], relVertex[j]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
      j = i;
   }
   return perimeter;
}

void Polygon::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the polygon
   // using the easygl::draw_polygon call.
   t_point coords[vertices]; 
   for (int i = 0; i < vertices; i++) {
      // get absolute value of coordinates of vertices
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, vertices);
}

bool Polygon::pointInside (float x, float y) const {
   // This function is a generilazation of the pointInside function of 
   // Triangle.cpp 

   // combine the x and y coordinates of the click point and make it 
   // relative to the centroid of the polygon
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();

   // implement crossing number method: 
   // http://geomalgorithms.com/a03_inclusion.html

   // The test is that a horizontal line (ray) from x = -infinity to the click 
   // point will cross (intersect) only one side of polygon to the left of the 
   // click point.  If the point is above or below the polygon, the ray will not
   // intersect any polygon sides. If the point is to the left of the polygon
   // the ray will also not intersect any sides to the left of the point.
   // If the point is to the right of the polygon, the ray will intersect
   // two sides of the polygon to its left. Only if the point is inside the 
   // polygon will the ray intersect exactly one side to the left of the point.

   t_point vecOfSide; // vector along an edge of polygon
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;

   for (int istart = 0; istart < vertices; istart++) {
      endIndex = (istart + 1) % vertices; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (relVertex[istart], relVertex[endIndex]);
      yDistance = (click.y - relVertex[istart].y);
      if (vecOfSide.y != 0) { // edge is not horizontal
         distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) { // click point is right on edge
         distanceAlongVector = 0;
      }
      else { // click point is not on edge
         distanceAlongVector = 1e10; // Ideally should be infinity, 
                                     // but this is an appropriate 
                                     // approximation
      }
   
      // We intersect this side if the distance (scaling) along the side vector to 
      // get to our "click" y point is between 0 and 1.  Count the first 
      // endpoint of the side as being part of the line (distanceAlongVector = 0)
      // but don't count the second endPoint; we'll intersect that point later 
      // when we check the next side.
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = relVertex[istart].x + vecOfSide.x \
                           * distanceAlongVector;
         if (xIntersection <= click.x ) 
            sidesToLeft++;
      }
   }

   return (sidesToLeft == 1);
}

// Private helper functions below for working out perimeter and pointInside  

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}