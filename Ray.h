//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_RAY_H
#define HW5_RAY_H

#include <cmath>
#include "Vector3.h"

class Ray {
 public:
  Vector3 origin;
  Vector3 direction;

  Ray(double x, double y, double z, double dx, double dy, double dz);
  Ray(const Vector3 &origin, const Vector3 &direction);

  Vector3 getPointAt(double t) const;
};

#endif //HW5_RAY_H
