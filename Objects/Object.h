//
// Created by James Lemkin on 12/7/19.
//

#ifndef HW5_OBJECT_H
#define HW5_OBJECT_H

#include "../Vector3.h"
#include "../Color.h"
#include "../Light.h"
class Object {
 private:
  virtual Vector3 computeNormalAt(const Vector3 &point) const = 0;

 public:
  Color color;
  float specularity;

  Object(float r, float g, float b, float specularity);

  Color computeColorAt(const Vector3 &point, const Vector3& cameraPos, const Light& light, float k) const;
};

#endif //HW5_OBJECT_H
