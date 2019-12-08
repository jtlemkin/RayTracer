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
  Ray(double x, double y, double z, double dx, double dy, double dz);
  Ray(const Vector3 &origin, const Vector3 &direction);

  Vector3 getPointAt(double t) const;
  double intersect(const Sphere& sphere) const;
  double intersect(double z) const;
};

#endif //HW5_RAY_H
