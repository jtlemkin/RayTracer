//
// Created by James Lemkin on 12/5/19.
//

#include "Ray.h"

Ray::Ray(float x, float y, float z, float dx, float dy, float dz) : origin(Vector3(x, y, z)),
                                                                    direction(Vector3(dx, dy, dz)) {
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}

Vector3 Ray::getPointAt(float t) const {
  return Vector3(origin.x + t * direction.x, origin.y + t * direction.y, origin.z + t * direction.z);
}

float Ray::intersect(const Sphere& sphere) const {
  Vector3 dp = sphere.center - origin;

  Vector3 u = direction.normalize();

  float a = u.dot(dp);
  float b = (dp - u * (dp.dot(u))).magnitude();
  float c = (sphere.radius * sphere.radius) - (b * b);

  //If there is no solution, return the max float value implying that there is no intersection
  if (c < 0) {
    return std::numeric_limits<float>::max();
  }

  float d = sqrt(c);
  float intersection = a - d;

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
    return std::numeric_limits<float>::max();
  }
}