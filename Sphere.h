//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SPHERE_H
#define HW5_SPHERE_H

#include "Vector3.h"
#include "Color.h"

class Sphere {
 public:
  Vector3 center;
  float radius;
  Color color;

  Sphere(float x, float y, float z, float radius, float r, float g, float b);

  Vector3 getNormalAt(const Vector3& point) const;
};

#endif //HW5_SPHERE_H
