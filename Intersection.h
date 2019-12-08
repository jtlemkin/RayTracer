//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_INTERSECTION_H
#define HW5_INTERSECTION_H

#include "Objects/Sphere.h"

class Intersection {
 public:
  const Object& object;
  double t;

  Intersection(const Object &sphere, double t);
};

#endif //HW5_INTERSECTION_H
