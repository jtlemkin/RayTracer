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
double Sphere::intersect(Ray ray) const {
  Vector3 dp = center - ray.origin;

  Vector3 u = ray.direction.normalize();

  double a = u.dot(dp);
  double b = (dp - u * (dp.dot(u))).magnitude();
  double c = std::pow(radius, 2) - std::pow(b, 2);

  //If there is no solution, return the max double value implying that there is no intersection
  if (c < 0) {
    return std::numeric_limits<double>::max();
  }

  double d = sqrt(c);
  double intersection = a - d;

  //The first calculation will return the smallest value of t because we know sqrt(d) is positive
  //We can't have an intersection value of zero though, so if it is less than zero we need to check the next
  //intersection
  if (intersection >= 0.0f) {
    return intersection;
  }

  intersection = a + d;

  if (intersection >= 0.0f) {
    return intersection;
  } else {
    //There's no intersection within the domain of t
    return std::numeric_limits<double>::max();
  }
}
