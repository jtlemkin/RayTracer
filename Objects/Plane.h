//
// Created by James Lemkin on 12/7/19.
//

#ifndef HW5_PLANE_H
#define HW5_PLANE_H

#include "Object.h"

class Plane : public Object {
 public:
  double A, B, C, D;

  Plane(double A, double B, double C, double D, float r, float g, float b, float specularity, float indexOfRefraction);

  Vector3 computeNormalAt(const Vector3 &point) const override;

  std::optional<Intersection> intersect(Ray ray) const override;
};

#endif //HW5_PLANE_H
