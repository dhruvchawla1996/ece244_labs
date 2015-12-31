/* 
 * File:   Polygon.h
 * Author: Dhruv
 */

#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 100 points in relVertex; 
   // each is the (x,y) coordinate of one polygon vertex relative to the shape 
   // center.
   t_point relVertex[100];   

   // number of vertices the polygon has
   int vertices;
   
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Polygon (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[100], float _ycoords[100], int _vertices);
   
   // virtual functions from Shape
   virtual ~Polygon();
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif	/* POLYGON_H */
