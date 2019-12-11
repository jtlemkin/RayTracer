//
// Created by James Lemkin on 12/5/19.
//

#include "Ray.h"

Ray::Ray(double x, double y, double z, double dx, double dy, double dz) : origin(Vector3(x, y, z)),
                                                                    direction(Vector3(dx, dy, dz)) {
  mediumIndex = 1;
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {
  mediumIndex = 1;
}

Vector3 Ray::getPointAt(double t) const {
  return Vector3(origin.x + t * direction.x, origin.y + t * direction.y, origin.z + t * direction.z);
}
