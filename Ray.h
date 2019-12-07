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
  Ray(const Vector3 &origin, const Vector3 &direction);

  Vector3 getPointAt(float t) const;
  float intersect(const Sphere& sphere) const;
};

#endif //HW5_RAY_H
