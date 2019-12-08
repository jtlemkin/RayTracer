//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SPHERE_H
#define HW5_SPHERE_H

#include <vector>
#include "../Vector3.h"
#include "Object.h"

class Sphere : public Object {
 public:
  Vector3 center;
  double radius;

  Sphere(double x, double y, double z, double radius, float r, float g, float b, float specularity);

  Vector3 computeNormalAt(const Vector3 &point) const override;
};

#endif //HW5_SPHERE_H
