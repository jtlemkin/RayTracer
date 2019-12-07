//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_INTERSECTION_H
#define HW5_INTERSECTION_H

#include "Sphere.h"

class Intersection {
 public:
  const Sphere& sphere;
  float t;

  Intersection(const Sphere &sphere, float t);
};

#endif //HW5_INTERSECTION_H
