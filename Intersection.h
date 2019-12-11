//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_INTERSECTION_H
#define HW5_INTERSECTION_H

#include "Objects/Object.h"

class Object;

class Intersection {
 public:
  const Object& object;
  double t;
  int numIntersections;

  Intersection(const Object &object, double t, int numIntersections);
};

#endif //HW5_INTERSECTION_H
