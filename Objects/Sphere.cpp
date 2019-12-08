//
// Created by James Lemkin on 12/5/19.
//

#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(double x, double y, double z, double radius, float r, float g, float b, float specularity = 10) :
    Object(r, g, b, specularity), center(Vector3(x, y, z)), radius(radius) {}

Vector3 Sphere::computeNormalAt(const Vector3 &point) const {
  return Vector3(2 * (point.x - center.x), 2 * (point.y - center.y), 2 * (point.z - center.z)).normalize();
}