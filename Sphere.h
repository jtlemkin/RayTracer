//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SPHERE_H
#define HW5_SPHERE_H

#include "Vector3.h"

class Sphere {
 public:
  Vector3 center;
  float radius;

  Sphere(float x, float y, float z, float radius);
};

#endif //HW5_SPHERE_H
