/*
 * File: Circle.h
 * Author: Dhruv
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "easygl.h"

class Circle : public Shape {
private:
   // radius of the circle
   float radius; 

public:
   Circle (string _name, string _colour, float _xcen, float _ycen,
         float _radius);

   // virtual functions from Shape
   virtual ~Circle();
    
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
} ;

#endif /* CIRCLE_H */