//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_RAY_H
#define HW5_RAY_H

#include <cmath>
#include "Vector3.h"
#include "Sphere.h"

class Ray {
 private:
  Vector3 origin;

  Vector3 direction;

 public:
  Ray(float x, float y, float z, float dx, float dy, float dz);

  Vector3 getPointAt(float t);
  float intersect(Sphere sphere);
};

#endif //HW5_RAY_H
