//
// Created by James Lemkin on 12/5/19.
//

#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(double x, double y, double z, double radius, float r, float g, float b, float specularity,
               float indexOfRefraction) :
    Object(r, g, b, specularity, indexOfRefraction), center(Vector3(x, y, z)), radius(radius) {}

Vector3 Sphere::computeNormalAt(const Vector3 &point) const {
  return Vector3(2 * (point.x - center.x), 2 * (point.y - center.y), 2 * (point.z - center.z)).normalize();
}

std::optional<Intersection> Sphere::intersect(Ray ray) const {
  Vector3 dp = center - ray.origin;

  Vector3 u = ray.direction.normalize();

  double a = u.dot(dp);
  double b = (dp - u * (dp.dot(u))).magnitude();
  double c = std::pow(radius, 2) - std::pow(b, 2);

  //If there is no solution, return the max double value implying that there is no intersection
  if (c < 0) {
    return {};
  }

  double d = sqrt(c);
  double intersection1 = a - d;
  double intersection2 = a + d;

  int numIntersections;

  if (intersection1 > 0.0f) {
    numIntersections = d == 0 ? 1 : 2;

    return Intersection(*this, intersection1, numIntersections);
  }

  if (intersection2 > 0.0f) {
    numIntersections = 1;

    return Intersection(*this, intersection2, numIntersections);
  } else {
    return {};
  }
}
