//
// Created by James Lemkin on 12/7/19.
//

#include "Plane.h"
Plane::Plane(double A, double B, double C, double D, float r, float g, float b, float specularity)
    : Object(r, g, b, specularity), A(A), B(B), C(C), D(D) {}

Vector3 Plane::computeNormalAt(const Vector3 &point) const {
  return Vector3(A, B, C);
}
double Plane::intersect(Ray ray) const {
  return -(A * ray.origin.x + B * ray.origin.y + C * ray.origin.z + D) /
      (A * ray.direction.x + B * ray.direction.y + C * ray.direction.z);
}
