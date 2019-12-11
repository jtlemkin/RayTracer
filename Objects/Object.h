//
// Created by James Lemkin on 12/7/19.
//

#ifndef HW5_OBJECT_H
#define HW5_OBJECT_H

#include <optional>
#include "../Vector3.h"
#include "../Color.h"
#include "../Light.h"
#include "../Ray.h"
#include "../Intersection.h"

class Intersection;

class Object {
 public:
  Color color;
  float specularity;
  float indexOfRefraction;

  Object(float r, float g, float b, float specularity, float indexOfRefraction);

  Color computeColorAt(const Vector3 &point, const Vector3& cameraPos, const Light& light, float k) const;

  virtual std::optional<Intersection> intersect(Ray ray) const = 0;

  virtual Vector3 computeNormalAt(const Vector3 &point) const = 0;
};

#endif //HW5_OBJECT_H
