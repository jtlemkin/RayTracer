//
// Created by James Lemkin on 12/5/19.
//

#include "Ray.h"

Ray::Ray(double x, double y, double z, double dx, double dy, double dz) : origin(Vector3(x, y, z)),
                                                                    direction(Vector3(dx, dy, dz)) {
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}

Vector3 Ray::getPointAt(double t) const {
  return Vector3(origin.x + t * direction.x, origin.y + t * direction.y, origin.z + t * direction.z);
}

double Ray::intersect(const Sphere& sphere) const {
  Vector3 dp = sphere.center - origin;

  Vector3 u = direction.normalize();

  double a = u.dot(dp);
  double b = (dp - u * (dp.dot(u))).magnitude();
  double c = (sphere.radius * sphere.radius) - (b * b);

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
double Ray::intersect(double z) const {
  return 0;
}
