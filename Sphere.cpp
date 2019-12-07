//
// Created by James Lemkin on 12/5/19.
//

#include "Sphere.h"

Sphere::Sphere(float x, float y, float z, float radius) : center(Vector3(x, y, z)), radius(radius) {}

Vector3 Sphere::getNormalAt(const Vector3 &point) const {
  return Vector3(2 * (point.x - center.x), 2 * (point.y - center.y), 2 * (point.z - center.z));
}
