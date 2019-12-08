//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SPHERE_H
#define HW5_SPHERE_H

#include <vector>
#include "Vector3.h"
#include "Color.h"
#include "Light.h"

class Sphere {
 public:
  Vector3 center;
  double radius;
  Color color;
  float specularity;

  Sphere(double x, double y, double z, double radius, float r, float g, float b, float specularity);

  Color computeColorAt(const Vector3 &point, const Vector3& cameraPos, const Light& light, float k) const;
 private:
  Vector3 computeNormalAt(const Vector3 &point) const;
};

#endif //HW5_SPHERE_H
