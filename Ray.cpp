//
// Created by James Lemkin on 12/5/19.
//

#include "Ray.h"

Ray::Ray(float x, float y, float z, float dx, float dy, float dz) : origin(Vector3(x, y, z)),
                                                                    direction(Vector3(dx, dy, dz)) {
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}

Vector3 Ray::getPointAt(float t) {
  return Vector3(origin.x + t * direction.x, origin.y + t * direction.y, origin.z + t * direction.z);
}

float Ray::intersect(Sphere sphere) {
  //a = dx^2 + dy^2 + dz^2
  float a = (direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z);
  //b = 2[(x0 - xc)dx + (y0 - yc)dy + (z0 - zc)dz]
  float b = 2 * ((origin.x - sphere.center.x) * direction.x + (origin.y - sphere.center.y) * direction.y +
      (origin.z - sphere.center.z) * direction.z);
  //c = x0^2 + y0^2 + z0^2 - r^2
  float c = (origin.x * origin.x) + (origin.y * origin.y) + (origin.z * origin.z) + (sphere.center.x * sphere.center.x)
      + (sphere.center.y * sphere.center.y) + (sphere.center.z * sphere.center.z) - (sphere.radius * sphere.radius);

  //d = b^2 - 4ac
  float d = (b * b) - 4 * a * c;

  //If there is no solution, return the max float value implying that there is no intersection
  if (d < 0) {
    return std::numeric_limits<float>::max();
  }

  float intersection = (-b - sqrt(d)) / (2*a);

  //The first calculation will return the smallest value of t because we know sqrt(d) is positive
  //We can't have an intersection value of zero though, so if it is less than zero we need to check the next
  //intersection
  if (intersection >= 0.0f) {
    return intersection;
  }

  intersection = (-b + sqrt(d)) / (2*a);

  if (intersection >= 0.0f) {
    return intersection;
  } else {
    //There's no intersection within the domain of t
    return std::numeric_limits<float>::max();
  }
}

/*float Ray::intersect(Sphere sphere) {
  Vector3 dp = sphere.center - origin;

  Vector3 u = direction.normalize();

  float a = u * dp;
  float b = (dp - u * (dp * u)).magnitude();
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
}*/